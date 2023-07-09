export module compiler.expression_statement_syntax;

import std;

import compiler.expression_syntax;
import compiler.statement_syntax;

namespace compiler {
    export class expression_statement_syntax : public statement_syntax {
    public:

        std::shared_ptr<expression_syntax> expression;

        [[nodiscard]] expression_statement_syntax(std::shared_ptr<expression_syntax> const& expression)
            noexcept : expression(expression) {}

        virtual syntax_kind kind() const noexcept override
        {
            return syntax_kind::expression_statement;
        }

        virtual std::vector<std::shared_ptr<syntax_node>> const children() const noexcept override
        {
            return { expression };
        }
    };
}