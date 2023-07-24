export module compiler.source_text;

import std;
import compiler.text_line;

namespace compiler
{
	export class source_text final
	{
	public:
		using text_line = text_line<source_text>;

		const std::string_view text;
		const std::vector<text_line> lines;

		[[nodiscard]] source_text(const std::string_view& text)
			noexcept : text(text), lines(parse_lines(*this, text))
		{
		}

		[[nodiscard]] const char& operator[](const std::size_t index) const noexcept
		{
			return text.at(index);
		}

		[[nodiscard]] std::size_t length() const noexcept
		{
			return text.length();
		}

		[[nodiscard]] std::size_t get_line_index(const std::size_t position) noexcept
		{
			auto lower_bound{ std::size_t() };
			auto upper_bound{ lines.size() - 1 };

			while (lower_bound <= upper_bound)
			{
				const auto index{ lower_bound + (upper_bound - lower_bound) / 2 };
				const auto start{ lines[index].start };

				if (position == start)
				{
					return index;
				}

				if (start > position)
				{
					upper_bound = index - 1;
				}
				else
				{
					lower_bound = index + 1;
				}
			}

			return lower_bound - 1;
		}

	private:
		static std::vector<text_line> parse_lines(const source_text& source_text,
		                                          const std::string_view& text) noexcept
		{
			auto result{ std::vector<text_line>() };

			auto position{ std::size_t{} };
			auto line_start{ std::size_t{} };

			while (position < text.length())
			{
				const auto line_break_width{ get_line_break_width(text, position) };
				if (line_break_width == 0)
				{
					++position;
				}
				else
				{
					add_line(result, source_text, position, line_start, line_break_width);

					position += line_break_width;
					line_start = position;
				}
			}

			if (position >= line_start)
			{
				add_line(result, source_text, position, line_start, 0);
			}

			return result;
		}

		static void add_line(std::vector<text_line>& result, const source_text& source_text, const std::size_t position,
		                     const std::size_t line_start, const std::size_t line_break_width) noexcept
		{
			const auto line_length{ position - line_start };
			auto line{ text_line(source_text, line_start, line_length, line_break_width) };
			result.emplace_back(line);
		}

		static std::size_t get_line_break_width(const std::string_view& text, const std::size_t position) noexcept
		{
			const auto character{ text[position] };
			const auto next_character{ position + 1 >= text.length() ? '\0' : text[position + 1] };

			if (character == '\r' && next_character == '\n')
			{
				return 2;
			}

			if (character == '\r' || character == '\n')
			{
				return 1;
			}

			return 0;
		}
	};
}
