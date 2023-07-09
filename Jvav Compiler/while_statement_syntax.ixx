export module compiler.while_statement_syntax;

import std;

import compiler.expression_syntax;
import compiler.statement_syntax;
import compiler.syntax_token;

namespace compiler {
    export class while_statement_syntax final : public statement_syntax {
    public:
        using super = statement_syntax;

        std::shared_ptr<syntax_token> const keyword;
        std::shared_ptr<expression_syntax> const condition;
        std::shared_ptr<statement_syntax> const body;

        [[nodiscard]] while_statement_syntax(std::shared_ptr<syntax_token> const& keyword, 
            std::shared_ptr<expression_syntax> const& condition, std::shared_ptr<statement_syntax> const& body) 
            noexcept : keyword(keyword), condition(condition), body(body) {}

        virtual syntax_kind kind() const noexcept override
        {
            return syntax_kind::while_statement;
        }

        virtual std::vector<std::shared_ptr<syntax_node>> const children() const noexcept override
        {
            return { keyword,condition,body };
        }

    };
}