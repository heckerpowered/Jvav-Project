export module compiler.bound_expression_statement;

import std;

import compiler.bound_expression;
import compiler.bound_statement;
import compiler.bound_node;

namespace compiler
{
	export class bound_expression_statement final : public bound_statement
	{
	public:
		using super = bound_statement;

		const std::shared_ptr<bound_expression> expression;

		[[nodiscard]] bound_expression_statement(const std::shared_ptr<bound_expression>& expression)
			noexcept : expression(expression)
		{
		}

		bound_node_kind kind() const noexcept override
		{
			return bound_node_kind::expression_statement;
		}

		std::vector<std::shared_ptr<bound_node>> children() const noexcept override
		{
			return { expression };
		}

	};
}