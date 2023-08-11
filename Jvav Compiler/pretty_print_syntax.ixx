export module compiler.pretty_print:syntax_node;

import std;

import compiler.assignment_expression_syntax;
import compiler.variable_declaration_syntax;
import compiler.literal_expression_syntax;
import compiler.name_expression_syntax;
import compiler.console_color;
import compiler.syntax_token;
import compiler.syntax_node;

namespace compiler
{
	auto random_engine{ std::default_random_engine{} };
	auto uniform_distribution{ std::uniform_int_distribution{0, 15} };

	void pretty_print(std::ostream& stream, const std::shared_ptr<syntax_node>& node,
	                  std::string indent = std::string(),
	                  const bool is_last = true) noexcept
	{
		const auto token_marker{ is_last ? "©¸©¤©¤" : "©À©¤©¤" };

		stream << indent << token_marker;

		switch_foreground_color(static_cast<console_color>(uniform_distribution(random_engine)), [&]
		{
			stream << to_string(node->kind());
		});

		if (const auto token{ std::dynamic_pointer_cast<literal_expression_syntax>(node) })
		{
			std::visit([&](auto&& value) noexcept
			{
				stream << ' ';
				switch_foreground_color(static_cast<console_color>(uniform_distribution(random_engine)), [&]
				{
					stream << value;
				});
			}, token->value);
		}
		else if (const auto token{ std::dynamic_pointer_cast<syntax_token>(node) }; 
				 token && token->kind() == syntax_kind::identifier_token)
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

	export void pretty_print(const std::shared_ptr<syntax_node>& node) noexcept
	{
		pretty_print(std::cout, node);
	}
}
