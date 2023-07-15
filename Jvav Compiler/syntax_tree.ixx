export module compiler.syntax_tree;

import std;

import compiler.compilation_unit_syntax;
import compiler.expression_syntax;
import compiler.syntax_token;
import compiler.diagnostic_list;
import compiler.source_text;
import compiler.parser;


namespace compiler
{
	export class syntax_tree final
	{
	public:
		const std::shared_ptr<source_text> text;
		diagnostic_list diagnostics;
		const std::shared_ptr<compilation_unit_syntax> root;

	private:
		[[nodiscard]] syntax_tree(const std::shared_ptr<source_text>& text)
			noexcept : text(text), root(compiler::parser(text, diagnostics).parse_compilation_unit())
		{
		}

	public:
		[[nodiscard]] static syntax_tree parse(const std::string_view& text) noexcept
		{
			const auto source_text = std::make_shared<compiler::source_text>(text);
			return parse(source_text);
		}

		[[nodiscard]] static syntax_tree parse(const std::shared_ptr<source_text>& source_text) noexcept
		{
			return syntax_tree(source_text);
		}
	};
}
