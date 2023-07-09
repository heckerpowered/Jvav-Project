export module compiler.diagnostics;

import std;
import compiler.diagnostic;
import compiler.text_span;
import compiler.syntax_kind;

export namespace compiler {
    export class diagnostics final {
    private:
        std::vector<diagnostic> diagnostics;

        constexpr void add_range(std::vector<diagnostic> const& range) noexcept {
            diagnostics.append_range(range);
        }

        constexpr void report(text_span const& span, std::string const& message) noexcept {
            auto diagnostic = compiler::diagnostic{ span, message };
            diagnostics.push_back(diagnostic);
        }

    public:
        [[nodiscard]] constexpr auto begin() noexcept {
            return diagnostics.begin();
        }

        [[nodiscard]] constexpr auto end() noexcept {
            return diagnostics.end();
        }

        void report_unexpected_token(text_span const& span, syntax_kind const actual_kind,
            syntax_kind const expected_kind) noexcept {
            // Formatting makes IntelliSense crash, Visual Studio 2022 17.7.0 Preview 2
#ifndef __INTELLISENSE__
            auto const message = std::format("Unexpected token {}, expected {}", "");
#endif // __INTELLISENSE__

        }
    };
}