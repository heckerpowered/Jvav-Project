export module compiler.block_statement_syntax;

import std;

import compiler.statement_syntax;
import compiler.syntax_token;

namespace compiler {
    export class block_statement_syntax final : public statement_syntax {
    public:

        using super = statement_syntax;

        std::shared_ptr<syntax_token> const open_brace_token;
        std::vector<std::shared_ptr<statement_syntax>> const statements;
        std::shared_ptr<syntax_token> const close_brace_token;

        [[nodiscard]] block_statement_syntax(std::shared_ptr<syntax_token> const& open_brace_token,
            std::vector<std::shared_ptr<statement_syntax>> const& statements,
            std::shared_ptr<syntax_token> const& close_brace_token)  noexcept :
            open_brace_token(open_brace_token), statements(statements), close_brace_token(close_brace_token) {}

        [[nodiscard]] block_statement_syntax(std::shared_ptr<syntax_token> const& open_brace_token,
            std::vector<std::shared_ptr<statement_syntax>>&& statements,
            std::shared_ptr<syntax_token> const& close_brace_token)  noexcept :
            open_brace_token(open_brace_token), statements(statements), close_brace_token(close_brace_token) {}

        virtual syntax_kind kind() const noexcept override
        {
            return syntax_kind::block_statement;
        }

        virtual std::vector<std::shared_ptr<syntax_node>> const children() const noexcept override
        {
            auto children = std::vector<std::shared_ptr<syntax_node>>(statements.size() + 2);
            children.emplace_back(open_brace_token);
            children.insert(children.end(), statements.begin(), statements.end());
            children.emplace_back(close_brace_token);

            return children;
        }
    };
}