export module compiler.bound_block_statement;

import std;

import compiler.bound_statement;

namespace compiler
{
	export class bound_block_statement final : public bound_statement
	{
	public:
		using super = bound_statement;

		const std::vector<std::shared_ptr<bound_statement>> statements;

		[[nodiscard]] bound_block_statement(const std::vector<std::shared_ptr<bound_statement>>& statements)
			noexcept : statements(statements)
		{
		}

		[[nodiscard]] bound_block_statement(std::vector<std::shared_ptr<bound_statement>>&& statements)
			noexcept : statements(statements)
		{
		}

		bound_node_kind kind() const noexcept override
		{
			return bound_node_kind::block_statement;
		}

		std::vector<std::shared_ptr<bound_node>> children() const noexcept override
		{
			auto children = std::vector<std::shared_ptr<bound_node>>();
			children.insert(children.begin(), statements.begin(), statements.end());
			return children;
		}
	};
}
