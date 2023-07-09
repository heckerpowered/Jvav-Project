export module compiler.variable_declaration_syntax;

import std;

import compiler.expression_syntax;
import compiler.statement_syntax;
import compiler.syntax_token;

namespace compiler {
    export class variable_declaration_syntax final : public statement_syntax {
    public:

        std::shared_ptr<syntax_token> const type_identifier_token;
        std::shared_ptr<syntax_token> const identifier_token;
        std::shared_ptr<syntax_token> const equals_token;
        std::shared_ptr<expression_syntax> const initializer;

        [[nodiscard]] variable_declaration_syntax(std::shared_ptr<syntax_token> const& type_identifier_token,
            std::shared_ptr<syntax_token> const& identifier_token,
            std::shared_ptr<syntax_token> const& equals_token,
            std::shared_ptr<expression_syntax> const& initializer)
            noexcept : type_identifier_token(type_identifier_token),
            identifier_token(identifier_token),
            equals_token(equals_token),
            initializer(initializer) {}

        virtual syntax_kind kind() const noexcept override
        {
            return syntax_kind::variable_declaration;
        }

        virtual std::vector<std::shared_ptr<syntax_node>> const children() const noexcept override
        {
            return { type_identifier_token, identifier_token, equals_token, initializer };
        }
    };
}