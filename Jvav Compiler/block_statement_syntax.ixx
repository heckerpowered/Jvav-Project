export module compiler.block_statement_syntax;

import std;

import compiler.statement_syntax;
import compiler.syntax_token;

namespace compiler
{
	export class block_statement_syntax final : public statement_syntax
	{
	public:
		using super = statement_syntax;

		const std::shared_ptr<syntax_token> open_brace_token;
		const std::vector<std::shared_ptr<statement_syntax>> statements;
		const std::shared_ptr<syntax_token> close_brace_token;

		[[nodiscard]] block_statement_syntax(const std::shared_ptr<syntax_token>& open_brace_token,
		                                     const std::vector<std::shared_ptr<statement_syntax>>& statements,
		                                     const std::shared_ptr<syntax_token>& close_brace_token) noexcept :
			open_brace_token(open_brace_token), statements(statements), close_brace_token(close_brace_token)
		{
		}

		[[nodiscard]] block_statement_syntax(const std::shared_ptr<syntax_token>& open_brace_token,
		                                     std::vector<std::shared_ptr<statement_syntax>>&& statements,
		                                     const std::shared_ptr<syntax_token>& close_brace_token) noexcept :
			open_brace_token(open_brace_token), statements(statements), close_brace_token(close_brace_token)
		{
		}

		syntax_kind kind() const noexcept override
		{
			return syntax_kind::block_statement;
		}

		std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			auto children = std::vector<std::shared_ptr<syntax_node>>();
			children.emplace_back(open_brace_token);
			children.insert(children.end(), statements.begin(), statements.end());
			children.emplace_back(close_brace_token);

			return children;
		}
	};
}
