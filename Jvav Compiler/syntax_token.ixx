export module compiler.syntax_token;

import std;
import compiler.syntax_kind;

namespace compiler {
    export class syntax_token {
    public:
        syntax_kind const kind;
        std::size_t const position;
        std::string const text;
        std::optional<std::any> const value;

        [[nodiscard]] syntax_token(syntax_kind const kind, std::size_t const position, std::string text, 
            std::optional<std::any> value = std::nullopt)
            noexcept : kind(kind), position(position), text(std::move(text)), value(value) {}
    };
}