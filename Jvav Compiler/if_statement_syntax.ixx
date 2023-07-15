export module compiler.if_statement_syntax;

import std;

import compiler.else_clause_syntax;
import compiler.expression_syntax;
import compiler.statement_syntax;
import compiler.syntax_token;

namespace compiler
{
	export class if_statement_syntax final : public statement_syntax
	{
	public:
		using super = statement_syntax;

		const std::shared_ptr<syntax_token> if_keyword;
		const std::shared_ptr<expression_syntax> condition;
		const std::shared_ptr<statement_syntax> then_statement;
		const std::shared_ptr<else_clause_syntax> else_clause;

		[[nodiscard]] if_statement_syntax(const std::shared_ptr<syntax_token>& if_keyword,
		                                  const std::shared_ptr<expression_syntax>& condition,
		                                  const std::shared_ptr<statement_syntax>& then_statement,
		                                  const std::shared_ptr<else_clause_syntax>& else_clause) noexcept :
			if_keyword(if_keyword), condition(condition), then_statement(then_statement), else_clause(else_clause)
		{
		}

		syntax_kind kind() const noexcept override
		{
			return syntax_kind::if_statement;
		}

		std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			auto children = std::vector<std::shared_ptr<syntax_node>>{if_keyword, condition, then_statement};
			if (else_clause)
			{
				children.emplace_back(else_clause);
			}
			return children;
		}
	};
}
