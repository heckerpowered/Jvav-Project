export module compiler.diagnostic;

import std;
import compiler.text_span;

namespace compiler {
    export class diagnostic final {
    public:
        text_span const span;
        std::string const message;

        [[nodiscard]] diagnostic(text_span const& span, std::string const& message)
            noexcept : span(span), message(message){}
    };
}