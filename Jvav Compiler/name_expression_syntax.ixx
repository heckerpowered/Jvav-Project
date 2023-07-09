export module compiler.name_expression_syntax;

import std;

import compiler.expression_syntax;
import compiler.syntax_token;

namespace compiler {
    export class name_expression_syntax final : public expression_syntax {
    public:

        using super = expression_syntax;

        std::shared_ptr<syntax_token> const identifier_token;

        [[nodiscard]] name_expression_syntax(std::shared_ptr<syntax_token> const& identifier_token)
            noexcept : identifier_token(identifier_token) {}

        virtual syntax_kind kind() const noexcept override
        {
            return syntax_kind::name_expression;
        }

        virtual std::vector<std::shared_ptr<syntax_node>> const children() const noexcept override
        {
            return { identifier_token };
        }
    };
}