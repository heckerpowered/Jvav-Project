export module compiler.assignment_expression_syntax;

import std;

import compiler.expression_syntax;
import compiler.syntax_token;

namespace compiler {
    export class assignment_expression_syntax final : public expression_syntax {
    public:

        using super = expression_syntax;

        std::shared_ptr<syntax_token> const identifier_token;
        std::shared_ptr<syntax_token> const equals_token;
        std::shared_ptr<expression_syntax> const expression;

        [[nodiscard]] assignment_expression_syntax(std::shared_ptr<syntax_token> const& identifier_token,
            std::shared_ptr<syntax_token> const& equals_token,
            std::shared_ptr<expression_syntax> const& expression) noexcept :
            identifier_token(identifier_token), equals_token(equals_token), expression(expression) {};

        virtual syntax_kind kind() const noexcept override
        {
            return syntax_kind::assignment_expression;
        }

        virtual std::vector<std::shared_ptr<syntax_node>> const children() const noexcept override
        {
            return { identifier_token, equals_token, expression };
        }
    };
}