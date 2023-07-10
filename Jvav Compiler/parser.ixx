export module compiler.parser;

import std;

import compiler.boolean_literal_expression_syntax;
import compiler.number_literal_expression_syntax;
import compiler.parenthesized_expression_syntax;
import compiler.assignment_expression_syntax;
import compiler.expression_statement_syntax;
import compiler.variable_declaration_syntax;
import compiler.binary_expression_syntax;
import compiler.unary_expression_syntax;
import compiler.compilation_unit_syntax;
import compiler.name_expression_syntax;
import compiler.block_statement_syntax;
import compiler.while_statement_syntax;
import compiler.if_statement_syntax;
import compiler.else_clause_syntax;
import compiler.expression_syntax;
import compiler.statement_syntax;
import compiler.lexical_analyzer;
import compiler.syntax_token;
import compiler.syntax_facts;
import compiler.source_text;
import compiler.diagnostics;
import compiler.syntax_kind;
import compiler.diagnostic;
import compiler.zero_copy;

namespace compiler {
    export class parser {
    private:
        std::vector<std::shared_ptr<syntax_token>> tokens;
        std::size_t position;
        diagnostics& diagnostics;

    public:
        [[nodiscard]] parser(std::shared_ptr<source_text> const& text, compiler::diagnostics& diagnostics) 
            noexcept : position(), diagnostics(diagnostics) {
            auto tokens = std::vector<std::shared_ptr<syntax_token>>();
            auto analyzer = lexical_analyzer(text->text, diagnostics);
            while (true) {
                auto token = analyzer.analyze();
                if (token->kind() != syntax_kind::whitespace_token &&
                    token->kind() != syntax_kind::bad_token) {
                    tokens.emplace_back(token);
                }

                if (token->kind() == syntax_kind::end_token) {
                    break;
                }
            }

            this->tokens = std::move(tokens);
        }

    private:
        [[nodiscard]] std::shared_ptr<syntax_token> peek(std::size_t const offset) noexcept {
            auto const index = position + offset;
            if (index >= tokens.size()) {
                return tokens.back();
            }

            return tokens[index];
        }

        [[nodiscard]] std::shared_ptr<syntax_token> current() noexcept {
            return peek(0);
        }

        [[nodiscard]] std::shared_ptr<syntax_token> next_token() noexcept {
            auto const& current = this->current();
            ++position;
            return current;
        }

        [[nodiscard]] std::shared_ptr<syntax_token> match_token(syntax_kind const kind) noexcept {
            if (current()->kind() == kind) {
                return next_token();
            }

            diagnostics.report_unexpected_token(current()->span(), current()->kind(), kind);
            return std::make_shared<syntax_token>(kind, current()->position, "");
        }

        [[nodiscard]] std::shared_ptr<expression_syntax> parse_expression() noexcept {
            return parse_assignment_expression();
        }

        [[nodiscard]] std::shared_ptr<variable_declaration_syntax> parse_variable_declaration() noexcept {
            auto const type_identifier_token = match_token(syntax_kind::identifier_token);
            auto const identifier_token = match_token(syntax_kind::identifier_token);
            auto const equals_token = match_token(syntax_kind::equals_token);
            auto const expression = parse_expression();

            return std::make_shared<variable_declaration_syntax>(type_identifier_token, identifier_token,
                equals_token, expression);
        }

        [[nodiscard]] std::shared_ptr<name_expression_syntax> parse_name_expression() noexcept {
            auto const identifier_token = match_token(syntax_kind::identifier_token);
            return std::make_shared<name_expression_syntax>(identifier_token);
        }

        [[nodiscard]] std::shared_ptr<number_literal_expression_syntax> parse_number_literal() noexcept {
            auto const number_token = match_token(syntax_kind::literal_token);
            return std::make_shared<number_literal_expression_syntax>(number_token);
        }

        [[nodiscard]] std::shared_ptr<boolean_literal_expression_syntax> parse_boolean_literal() noexcept {
            auto const is_true = current()->kind() == syntax_kind::true_keyword;
            auto const keyword_token = match_token(is_true ? syntax_kind::true_keyword : syntax_kind::false_keyword);
            return std::make_shared<boolean_literal_expression_syntax>(keyword_token);
        }

        [[nodiscard]] std::shared_ptr<parenthesized_expression_syntax> parse_parenthesized_expression() noexcept {
            auto const left = match_token(syntax_kind::open_parenthesis_token);
            auto const expression = parse_expression();
            auto const right = match_token(syntax_kind::close_parenthesis_token);
            return std::make_shared<parenthesized_expression_syntax>(left, expression, right);
        }

        [[nodiscard]] std::shared_ptr<expression_syntax> parse_primary_expression() noexcept {
            switch (current()->kind())
            {
            case syntax_kind::open_parenthesis_token:
                return parse_parenthesized_expression();
            case syntax_kind::false_keyword:
            case syntax_kind::true_keyword:
                return parse_boolean_literal();
            case syntax_kind::literal_token:
                return parse_number_literal();
            default:
                return parse_name_expression();
            }
        }

        [[nodiscard]]
        std::shared_ptr<expression_syntax> parse_binary_expression(std::uint_fast8_t const parent_precedence = 0) noexcept {
            auto left = std::shared_ptr<expression_syntax>();

            auto const unary_operator_precedence = syntax_facts::get_unary_operator_precedence(current()->kind());
            if (unary_operator_precedence != 0 && unary_operator_precedence > parent_precedence) {
                auto const operator_token = next_token();
                auto const operand = parse_binary_expression(unary_operator_precedence);
                left = std::make_shared<unary_expression_syntax>(operator_token, operand);
            }
            else {
                left = parse_primary_expression();
            }

            while (true) {
                auto const precedence = syntax_facts::get_binary_operator_precedence(current()->kind());
                if (precedence == 0 || precedence <= parent_precedence) {
                    break;
                }

                auto const operator_token = next_token();
                auto const right = parse_binary_expression(precedence);
                left = std::make_shared<binary_expression_syntax>(left, operator_token, right);
            }

            return left;
        }

        [[nodiscard]] std::shared_ptr<expression_syntax> parse_factor() noexcept {
            auto left = parse_primary_expression();
            while (current()->kind() == syntax_kind::multiplication_token ||
                current()->kind() == syntax_kind::slash_token) {
                auto const operator_token = next_token();
                auto const right = parse_primary_expression();
                left = std::make_shared<binary_expression_syntax>(left, operator_token, right);
            }
            return left;
        }

        [[nodiscard]] std::shared_ptr<expression_syntax> parse_term() noexcept {
            auto left = parse_factor();
            while (current()->kind() == syntax_kind::plus_token ||
                current()->kind() == syntax_kind::minus_token) {
                auto const operator_token = next_token();
                auto const right = parse_primary_expression();
                left = std::make_shared<binary_expression_syntax>(left, operator_token, right);
            }
            return left;
        }

        [[nodiscard]] std::shared_ptr<expression_syntax> parse_assignment_expression() noexcept {
            if (peek(0)->kind() == syntax_kind::identifier_token &&
                peek(1)->kind() == syntax_kind::equals_token) {
                auto const identifier_token = match_token(syntax_kind::identifier_token);
                auto const operator_token = match_token(syntax_kind::equals_token);
                auto const right = parse_assignment_expression();
                return std::make_shared<assignment_expression_syntax>(identifier_token, operator_token, right);
            }

            return parse_binary_expression();
        }

        [[nodiscard]] std::shared_ptr<else_clause_syntax> parse_else_clause() noexcept {
            if (current()->kind() != syntax_kind::else_clause) {
                return nullptr;
            }

            auto const keyword = match_token(syntax_kind::else_clause);
            auto const statement = parse_statement();
            return std::make_shared<else_clause_syntax>(keyword, statement);
        }

        [[nodiscard]] std::shared_ptr<expression_statement_syntax> parse_expression_statement() noexcept {
            auto const expression = parse_expression();
            return std::make_shared<expression_statement_syntax>(expression);
        }

        [[nodiscard]] std::shared_ptr<if_statement_syntax> parse_if_statement() noexcept {
            auto const keyword = match_token(syntax_kind::if_keyword);
            auto const condition = parse_expression();
            auto const statement = parse_statement();
            auto const else_clause = parse_else_clause();
            return std::make_shared<if_statement_syntax>(keyword, condition, statement, else_clause);
        }

        [[nodiscard]] std::shared_ptr<while_statement_syntax> parse_while_statement() noexcept {
            auto const keyword = match_token(syntax_kind::while_keyword);
            auto const condition = parse_expression();
            auto const body = parse_statement();
            return std::make_shared<while_statement_syntax>(keyword, condition, body);
        }

        [[nodiscard]] std::shared_ptr<statement_syntax> parse_block_statement() noexcept {
            auto statements = std::vector<std::shared_ptr<statement_syntax>>();
            auto const open_brace_token = match_token(syntax_kind::open_brace_token);

            while (current()->kind() != syntax_kind::end_token &&
                current()->kind() != syntax_kind::close_brace_token) {
                auto const start_token = current();

                statements.emplace_back(zero_copy{ [this] { return parse_statement(); } });

                // If parse_statements() did not consume any tokens,
                // skip the current token and continue in order to
                // avoid infinite loop.
                // 
                // We don't need to report an error, because we'll
                // already tried to parse an expression statement
                // and reported one.
                if (current() == start_token) {
                    static_cast<void>(next_token());
                }
            }

            auto const close_brace_token = match_token(syntax_kind::close_brace_token);
            return std::make_shared<block_statement_syntax>(open_brace_token, std::move(statements), close_brace_token);
        }

        [[nodiscard]] std::shared_ptr<statement_syntax> parse_statement() noexcept {
            if (peek(0)->kind() == syntax_kind::identifier_token &&
                peek(1)->kind() == syntax_kind::identifier_token) {
                return parse_variable_declaration();
            }

            switch (current()->kind())
            {
            case syntax_kind::open_brace_token:
                return parse_block_statement();
            case syntax_kind::if_keyword:
                return parse_if_statement();
            case syntax_kind::while_keyword:
                return parse_while_statement();
            default:
                return parse_expression_statement();
            }
        }

    public:
        [[nodiscard]] std::shared_ptr<compilation_unit_syntax> parse_compilation_unit() noexcept {
            auto const statement = parse_statement();
            auto const end_token = match_token(syntax_kind::end_token);
            return std::make_shared<compilation_unit_syntax>(statement, end_token);
        }
    };
}