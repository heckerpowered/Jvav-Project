export module compiler.syntax_token;

import std;
import compiler.syntax_kind;
import compiler.text_span;
import compiler.syntax_node;

namespace compiler
{
	export class syntax_token : public syntax_node
	{
	public:
		const syntax_kind syntax_kind;
		const std::size_t position;
		const std::string text;

		[[nodiscard]] syntax_token(const compiler::syntax_kind kind, const std::size_t position,
		                           const std::string_view& text)
			noexcept : syntax_kind(kind), position(position), text(text)
		{
		}

		syntax_token(const syntax_token&) = default;

		text_span span() const noexcept override
		{
			return {position, text.length()};
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
