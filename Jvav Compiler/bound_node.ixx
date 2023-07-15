export module compiler.bound_node;

import std;

import compiler.bound_node_kind;

namespace compiler
{
	export class bound_node
	{
	public:
		[[nodiscard]] virtual bound_node_kind kind() const noexcept = 0;
		[[nodiscard]] virtual std::vector<std::shared_ptr<bound_node>> children() const noexcept = 0;

		virtual ~bound_node() noexcept
		{
		};
	};
}
