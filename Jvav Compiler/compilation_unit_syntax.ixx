export module compiler.compilation_unit_syntax;

import std;
import compiler.syntax_node;
import compiler.syntax_token;
import compiler.statement_syntax;

namespace compiler {
    export class compilation_unit_syntax : public syntax_node {
    public:
        using super = syntax_node;

        std::shared_ptr<statement_syntax> const statement;
        std::shared_ptr<syntax_token> const end_of_file_token;

        [[nodiscard]] compilation_unit_syntax(std::shared_ptr<statement_syntax> const& statement,
            std::shared_ptr<syntax_token> const& end_of_file_token)
            noexcept : statement(statement), end_of_file_token(end_of_file_token) {}

        virtual syntax_kind kind() const noexcept override
        {
            return syntax_kind::compilation_unit;
        }

        virtual std::vector<std::shared_ptr<syntax_node>> const children() const noexcept override
        {
            return { statement };
        }
    };
}