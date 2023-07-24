export module compiler.pretty_print:syntax_node;

import std;

import compiler.syntax_token;
import compiler.syntax_node;

namespace compiler
{
	void pretty_print(std::ostream& stream, const std::shared_ptr<syntax_node>& node,
	                  std::string indent = std::string(),
	                  const bool is_last = true) noexcept
	{
		const auto token_marker{ is_last ? "©¸©¤©¤" : "©À©¤©¤" };

		stream << indent << token_marker << to_string(node->kind());
		if (const auto token = std::dynamic_pointer_cast<syntax_token>(node); token)
		{
			stream << ' ' << token->text;
		}

		stream << std::endl;

		indent += is_last ? "   " : "©¦  ";

		auto children{ node->children() };
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

	export std::string to_string(const std::shared_ptr<syntax_node>& node) noexcept
	{
		auto stream{ std::stringstream() };
		pretty_print(stream, node);
		return std::string(stream.str());
	}
}
