export module compiler.source_text;

import std;
import compiler.text_line;

namespace compiler {
    export class source_text final {
    public:
        using text_line = compiler::text_line<source_text>;

        std::string_view const text;
        std::vector<text_line> const lines;

        [[nodiscard]] source_text(std::string_view const& text) 
            noexcept : text(text), lines(parse_lines(*this, text)) {}

        [[nodiscard]] char const& operator[](std::size_t const index) const noexcept {
            return text.at(index);
        }

        [[nodiscard]] std::size_t length() const noexcept {
            return text.length();
        }

        [[nodiscard]] std::size_t get_line_index(std::size_t const position) noexcept {
            auto lower_bound = std::size_t();
            auto upper_bound = lines.size() - 1;
            
            while (lower_bound <= upper_bound) {
                auto const index = lower_bound + (upper_bound - lower_bound) / 2;
                auto const start = lines[index].start;

                if (position == start) {
                    return index;
                }

                if (start > position) {
                    upper_bound = index - 1;
                }
                else {
                    lower_bound = index + 1;
                }
            }

            return lower_bound - 1;
        }

    private:
        static std::vector<text_line> parse_lines(source_text& source_text, std::string_view const& text) noexcept {
            auto result = std::vector<text_line>();

            auto position = std::size_t();
            auto line_start = std::size_t();

            while (position < text.length()) {
                auto const line_break_width = get_line_break_width(text, position);
                if (line_break_width == 0) {
                    ++position;
                }
                else {
                    add_line(result, source_text, position, line_start, line_break_width);

                    position += line_break_width;
                    line_start = position;
                }
            }

            if (position >= line_start) {
                add_line(result, source_text, position, line_start, 0);
            }
        }

        static void add_line(std::vector<text_line>& result, source_text& source_text, std::size_t const position,
            std::size_t const line_start, std::size_t const line_break_width) noexcept {
            auto const line_length = position - line_start;
            auto line = text_line(source_text, line_start, line_length, line_break_width);
            result.emplace_back(line);
        }

        static std::size_t get_line_break_width(std::string_view const& text, std::size_t const position) noexcept {
            auto const character = text[position];
            auto const next_character = position + 1 >= text.length() ? '\0' : text[position + 1];

            if (character == '\r' && next_character == '\n') {
                return 2;
            }

            if (character == '\r' || character == '\n') {
                return 1;
            }

            return 0;
        }
    };
}