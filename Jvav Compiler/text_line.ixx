export module compiler.text_line;

import std;

namespace compiler
{
	export template <typename source_text>
	class text_line final
	{
	public:
		const source_text& text;
		const std::size_t start;
		const std::size_t length;
		const std::size_t line_break_length;

		[[nodiscard]] constexpr text_line(const source_text& text, const std::size_t start,
		                                  const std::size_t length, const std::size_t line_break_length) noexcept :
			text(text), start(start),
			length(length), line_break_length(line_break_length)
		{
		}
	};
}
