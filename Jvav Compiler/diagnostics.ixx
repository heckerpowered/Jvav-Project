export module compiler.diagnostics;

import std;
import compiler.diagnostic;
import compiler.text_span;
import compiler.syntax_kind;

export namespace compiler {
    export class diagnostics final {
    private:
        std::vector<diagnostic> diagnostic;

        constexpr void add_range(std::vector<compiler::diagnostic> const& range) noexcept {
            diagnostic.append_range(range);
        }

        void report(text_span const& span, std::string const& message) noexcept {
            auto diagnostic = compiler::diagnostic{ span, message };
            this->diagnostic.push_back(diagnostic);
            std::cout << message << std::endl;
        }

    public:
        [[nodiscard]] constexpr auto begin() noexcept {
            return diagnostic.begin();
        }

        [[nodiscard]] constexpr auto end() noexcept {
            return diagnostic.end();
        }

        void report_unexpected_token(text_span const& span, syntax_kind const actual_kind,
            syntax_kind const expected_kind) noexcept {
            // Formatting makes IntelliSense crash, Visual Studio 2022 17.7.0 Preview 2
#ifndef __INTELLISENSE__
            auto const message = std::format("Unexpected token {}, expected {}", compiler::to_string(actual_kind), 
                compiler::to_string(expected_kind));
            report(span, message);
#endif // __INTELLISENSE__
        }

        void report_bad_character(text_span const& span, char const character) noexcept {
            // Formatting makes IntelliSense crash, Visual Studio 2022 17.7.0 Preview 2
#ifndef __INTELLISENSE__
            auto const message = std::format("Bad character input {}", character);
            report(span, message);
#endif // __INTELLISENSE__
        }
    };
}