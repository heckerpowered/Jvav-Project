export module compiler.else_clause_syntax;

import std;

import compiler.statement_syntax;
import compiler.syntax_token;
import compiler.syntax_node;

namespace compiler
{
	export class else_clause_syntax final : public syntax_node
	{
	public:
		using super = syntax_node;

		const std::shared_ptr<syntax_token> else_keyword;
		const std::shared_ptr<statement_syntax> else_statement;

		[[nodiscard]] else_clause_syntax(const std::shared_ptr<syntax_token>& else_keyword,
		                                 const std::shared_ptr<statement_syntax>& else_statement) noexcept :
			else_keyword(else_keyword), else_statement(else_statement)
		{
		};

		syntax_kind kind() const noexcept override
		{
			return syntax_kind::else_clause;
		}

		const std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			return {else_keyword, else_statement};
		}
	};
}
