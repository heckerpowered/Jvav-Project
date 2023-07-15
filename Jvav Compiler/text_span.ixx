export module compiler.text_span;

import std;

namespace compiler
{
	export class text_span
	{
	public:
		const std::size_t start;
		const std::size_t length;

		[[nodiscard]] constexpr text_span(const std::size_t start, const std::size_t length)
			noexcept : start(start), length(length)
		{
		}

		constexpr std::size_t end() const noexcept
		{
			return start + length;
		}

		static text_span from_bounds(const std::size_t start, const std::size_t end) noexcept
		{
			const auto length = end - start;
			return text_span(start, length);
		}
	};
}
