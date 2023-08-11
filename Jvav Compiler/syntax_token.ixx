export module compiler.syntax_token;

import std;

import compiler.literal_variant;
import compiler.syntax_kind;
import compiler.syntax_node;
import compiler.text_span;

namespace compiler
{
	export class syntax_token : public syntax_node
	{
	public:
		using super = syntax_node;

		const syntax_kind syntax_kind;
		const std::size_t position;
		const std::string_view text;
		builtin_literal_type value;

		[[nodiscard]] syntax_token(const compiler::syntax_kind kind, const std::size_t position,
								   const std::string_view& text)
			noexcept : syntax_kind{ kind }, position{ position }, text{ text }
		{
		}

		[[nodiscard]] syntax_token(const compiler::syntax_kind kind, const std::size_t position,
								   const std::string_view& text, const builtin_literal_type& value
		)
			noexcept : syntax_kind{ kind }, position{ position }, text{ text }, value{ value }
		{
		}

		syntax_token(const syntax_token&) = default;

		text_span span() const noexcept override
		{
			return { position, text.length() };
		}

		compiler::syntax_kind kind() const noexcept override
		{
			return syntax_kind;
		}

		std::vector<std::shared_ptr<syntax_node>> children() const noexcept override
		{
			return {};
		}
	};
}