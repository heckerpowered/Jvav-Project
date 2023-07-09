export module compiler.number_literal_expression_syntax;

import std;

import compiler.expression_syntax;
import compiler.syntax_token;

namespace compiler {
    export class number_literal_expression_syntax : public expression_syntax {
    public:
        using super = expression_syntax;

        std::shared_ptr<syntax_token> const literal_token;

        number_literal_expression_syntax(std::shared_ptr<syntax_token> const& literal_token)
            noexcept : literal_token(literal_token) {}

        virtual syntax_kind kind() const noexcept override {
            return syntax_kind::number_literal_expression;
        }

        virtual std::vector<std::shared_ptr<syntax_node>> const children() const noexcept override
        {
            return { literal_token };
        }
    };
}