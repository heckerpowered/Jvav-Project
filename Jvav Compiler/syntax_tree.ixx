export module compiler.syntax_tree;

import std;

import compiler.compilation_unit_syntax;
import compiler.expression_syntax;
import compiler.syntax_token;
import compiler.diagnostic_list;
import compiler.source_text;
import compiler.parser;


namespace compiler {
    export class syntax_tree final {
    public:

        std::shared_ptr<source_text> const text;
        diagnostic_list diagnostic_list;
        std::shared_ptr<compilation_unit_syntax> const root;

    private:
        [[nodiscard]] syntax_tree(std::shared_ptr<source_text> const& text) 
            noexcept : text(text), root(compiler::parser(text, diagnostic_list).parse_compilation_unit()) {}

    public:
        [[nodiscard]] static syntax_tree parse(std::string_view const& text) noexcept {
            auto const source_text = std::make_shared<compiler::source_text>(text);
            return parse(source_text);
        }

        [[nodiscard]] static syntax_tree parse(std::shared_ptr<source_text> const& source_text) noexcept {
            return syntax_tree(source_text);
        }
    };
}