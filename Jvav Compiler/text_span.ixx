export module compiler.text_span;

import std;

namespace compiler {
    export class text_span {
    public:
        std::size_t const start;
        std::size_t const length;

        [[nodiscard]] constexpr text_span(std::size_t const start, std::size_t const length)
            noexcept : start(start), length(length) {}

        constexpr std::size_t end() const noexcept {
            return start + length;
        }

        static text_span from_bounds(std::size_t const start, std::size_t const end) noexcept {
            auto const length = end - start;
            return text_span(start, length);
        }
    };
}