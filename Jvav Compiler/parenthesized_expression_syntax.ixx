export module compiler.parenthesized_expression_syntax;

import std;

import compiler.expression_syntax;
import compiler.syntax_token;

namespace compiler {
    export class parenthesized_expression_syntax final : public expression_syntax {
    public:
        using super = expression_syntax;

        std::shared_ptr<syntax_token> const open_parenthesis_token;
        std::shared_ptr<expression_syntax> const expression;
        std::shared_ptr<syntax_token> const close_parenthesis_token;

        [[nodiscard]] parenthesized_expression_syntax(std::shared_ptr<syntax_token> const& open_parenthesis_token,
            std::shared_ptr<expression_syntax> const& expression,
            std::shared_ptr<syntax_token> const& close_parenthesis_token) noexcept :
            open_parenthesis_token(open_parenthesis_token), expression(expression),
            close_parenthesis_token(close_parenthesis_token) {}

        virtual syntax_kind kind() const noexcept override
        {
            return syntax_kind::parenthesized_expression;
        }

        virtual std::vector<std::shared_ptr<syntax_node>> const children() const noexcept override
        {
            return { open_parenthesis_token, expression, close_parenthesis_token };
        }
    };
}