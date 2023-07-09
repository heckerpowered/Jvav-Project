export module compiler.experimental.intelli_parser;

import std;

import compiler.source_text;
import compiler.syntax_token;
import compiler.lexical_analyzer;
import compiler.diagnostics;
import compiler.diagnostic;
import compiler.expression_syntax;
import compiler.variable_declaration_syntax;
import compiler.assignment_expression_syntax;

namespace compiler::experimental {
    export class intelli_parser {
    private:
        std::vector<std::shared_ptr<syntax_token>> tokens;
        std::string_view const text;
        std::size_t position;
        diagnostics diagnostics;

    public:
        [[nodiscard]] intelli_parser(source_text& text) noexcept : position() {
            auto tokens = std::vector<std::shared_ptr<syntax_token>>();
            auto analyzer = lexical_analyzer(text.text);
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
    };

    export using smart_parser = intelli_parser;
}