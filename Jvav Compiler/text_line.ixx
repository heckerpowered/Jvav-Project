export module compiler.text_line;

import std;

namespace compiler {

    export template<typename source_text> class text_line final {
    public:
        source_text const& text;
        std::size_t const start;
        std::size_t const length;
        std::size_t const line_break_length;

        [[nodiscard]] constexpr text_line(source_text const& text, std::size_t const start,
            std::size_t const length,  std::size_t const line_break_length) noexcept : text(text), start(start), 
            length(length), line_break_length(line_break_length) {}
    };
}