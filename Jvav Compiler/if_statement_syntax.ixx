export module compiler.if_statement_syntax;

import std;

import compiler.else_clause_syntax;
import compiler.expression_syntax;
import compiler.statement_syntax;
import compiler.syntax_token;

namespace compiler {
    export class if_statement_syntax final : public statement_syntax {
    public:
        using super = statement_syntax;

        std::shared_ptr<syntax_token> const if_keyword;
        std::shared_ptr<expression_syntax> const condition;
        std::shared_ptr<statement_syntax> const then_statement;
        std::shared_ptr<else_clause_syntax> const else_clause;

        [[nodiscard]] if_statement_syntax(std::shared_ptr<syntax_token> const& if_keyword,
            std::shared_ptr<expression_syntax> const& condition,
            std::shared_ptr<statement_syntax> const& then_statement,
            std::shared_ptr<else_clause_syntax> const& else_clause) noexcept :
            if_keyword(if_keyword), condition(condition), then_statement(then_statement), else_clause(else_clause) {}

        virtual syntax_kind kind() const noexcept override
        {
            return syntax_kind::if_statement;
        }

        virtual std::vector<std::shared_ptr<syntax_node>> const children() const noexcept override
        {
            return { if_keyword,condition,then_statement,else_clause };
        }
    };
}