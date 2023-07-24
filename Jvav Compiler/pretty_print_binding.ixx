export module compiler.pretty_print:bound_node;

import std;

import compiler.bound_node;

namespace compiler
{
	void write_node(std::ostream& stream, const std::shared_ptr<bound_node>& node) noexcept
	{
		stream << ' ';
		stream << to_string(node->kind());
	}

	void pretty_print(std::ostream& stream, const std::shared_ptr<bound_node>& node, std::string indent = std::string(),
	                  const bool is_last = true) noexcept
	{
		const auto token_marker{ is_last ? "©¸©¤©¤" : "©À©¤©¤" };

		stream << indent << token_marker;

		write_node(stream, node);

		stream << std::endl;

		indent += is_last ? "   " : "©¦  ";

		auto children = node->children();
		if (children.empty())
		{
			return;
		}

		const auto& last_child{ children.back() };
		for (auto&& child : children)
		{
			pretty_print(stream, child, indent, child == last_child);
		}
	}
}
