export module compiler.bound_boolean_literal_expression;

import std;

import compiler.bound_expression;

namespace compiler
{
	export class bound_literal_expression final : bound_expression
	{
	public:
		using super = bound_expression;

		const bool value;

		[[nodiscard]] bound_literal_expression(const bool value) noexcept : value(value)
		{
		}

		bound_node_kind kind() const noexcept override
		{
			return bound_node_kind::literal_expression;
		}

		std::vector<std::shared_ptr<bound_node>> children() const noexcept override
		{
			return {};
		}

		const compiler::type_symbol& type() const noexcept override
		{
			return bool_type;
		}
	};
}