export module compiler.bound_assignment_expression;

import std;

import compiler.bound_expression;
import compiler.variable_symbol;

namespace compiler
{
	export class bound_assignment_expression : public bound_expression
	{
	public:
		using super = bound_expression;

		const std::shared_ptr<variable_symbol> variable;
		const std::shared_ptr<bound_expression> expression;

		[[nodiscard]] bound_assignment_expression(const std::shared_ptr<variable_symbol>& variable,
		                                          const std::shared_ptr<bound_expression>& expression) noexcept :
			variable{ variable }, expression{ expression }
		{
		}

		bound_node_kind kind() const noexcept override
		{
			return bound_node_kind::assignment_expression;
		}

		std::vector<std::shared_ptr<bound_node>> children() const noexcept override
		{
			return { expression };
		}

		type_symbol type() const noexcept override
		{
			return expression->type();
		}
	};
}
