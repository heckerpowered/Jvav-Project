export module compiler.bound_if_statement;

import std;

import compiler.bound_expression;
import compiler.bound_statement;

namespace compiler
{
	export class bound_if_statement final : public bound_statement
	{
	public:
		using super = bound_statement;

		const std::shared_ptr<bound_expression> condition;
		const std::shared_ptr<bound_statement> then_statement;
		const std::shared_ptr<bound_statement> else_statement;

		[[nodiscard]] bound_if_statement(const std::shared_ptr<bound_expression>& condition,
										 const std::shared_ptr<bound_statement>& then_statement,
										 const std::shared_ptr<bound_statement>& else_statement) noexcept :
			condition{ condition },
			then_statement{ then_statement },
			else_statement{ else_statement }
		{
		}

		bound_node_kind kind() const noexcept override
		{
			return bound_node_kind::if_statement;
		}

		std::vector<std::shared_ptr<bound_node>> children() const noexcept override
		{
			return { condition,then_statement,else_statement };
		}
	};
}