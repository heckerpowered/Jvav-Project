export module compiler.expression_statement_syntax;

import std;

import compiler.expression_syntax;
import compiler.statement_syntax;

namespace compiler
{
	export class expression_statement_syntax : public statement_syntax
	{
	public:
		std::shared_ptr<expression_syntax> expression;

		[[nodiscard]] expression_statement_syntax(const std::shared_ptr<expression_syntax>& expression)
			noexcept : expression(expression)
		{
		}

		syntax_kind kind() const noexcept override
		{
			return syntax_kind::expression_statement;
		}

		std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			return {expression};
		}
	};
}
