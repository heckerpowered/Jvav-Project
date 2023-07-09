export module compiler.binary_expression_syntax;

import std;

import compiler.expression_syntax;
import compiler.syntax_token;

namespace compiler {
    export class binary_expression_syntax final : public expression_syntax {
    public:
        using super = expression_syntax;

        std::shared_ptr<expression_syntax> const left;
        std::shared_ptr<syntax_token> const operator_token;
        std::shared_ptr<expression_syntax> const right;

        [[nodiscard]] binary_expression_syntax(std::shared_ptr<expression_syntax> const& left,
            std::shared_ptr<syntax_token> const& operator_token, std::shared_ptr<expression_syntax> const& right)
            noexcept : left(left), operator_token(operator_token), right(right) {}

        virtual syntax_kind kind() const noexcept override
        {
            return syntax_kind::binary_expression;
        }

        virtual std::vector<std::shared_ptr<syntax_node>> const children() const noexcept override
        {
            return { left,operator_token, right };
        }
    };
}