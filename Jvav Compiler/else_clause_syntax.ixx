export module compiler.else_clause_syntax;

import std;

import compiler.statement_syntax;
import compiler.syntax_token;
import compiler.syntax_node;

namespace compiler {
    export class else_clause_syntax final : public syntax_node {
    public:

        using super = syntax_node;

        std::shared_ptr<syntax_token> const else_keyword;
        std::shared_ptr<statement_syntax> const else_statement;

        [[nodiscard]] else_clause_syntax(std::shared_ptr<syntax_token> const& else_keyword,
            std::shared_ptr<statement_syntax> const& else_statement) noexcept :
            else_keyword(else_keyword), else_statement(else_statement) {};

        virtual syntax_kind kind() const noexcept override
        {
            return syntax_kind::else_clause;
        }

        virtual std::vector<std::shared_ptr<syntax_node>> const children() const noexcept override
        {
            return { else_keyword,else_statement };
        }
    };
}