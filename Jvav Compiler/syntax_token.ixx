export module compiler.syntax_token;

import std;
import compiler.syntax_kind;
import compiler.text_span;
import compiler.syntax_node;

namespace compiler {
    export class syntax_token : public syntax_node {
    public:
        syntax_kind const syntax_kind;
        std::size_t const position;
        std::string_view const text; 

        [[nodiscard]] syntax_token(compiler::syntax_kind const kind, std::size_t const position, std::string_view const& text)
            noexcept : syntax_kind(kind), position(position), text(text) {}

        syntax_token(syntax_token const&) = default;

        virtual text_span span() const noexcept override {
            return { position, text.length() };
        }

        virtual compiler::syntax_kind kind() const noexcept override
        {
            return syntax_kind;
        }

        virtual std::vector<std::shared_ptr<syntax_node>> const children() const noexcept override
        {
            return {};
        }
    };
}