export module compiler.pretty_print;

import std;

import compiler.syntax_token;
import compiler.syntax_node;
import compiler.syntax_kind;

namespace compiler {
    void pretty_print(std::ostream& stream, std::shared_ptr<syntax_node> const& node, std::string&& indent = std::string(),
        bool const is_last = false) noexcept {
        auto const marker = is_last ? "©¸©¤©¤©¤" : "©À©¤©¤©¤";

        stream << indent;
        stream << marker;

        stream << ' ';
        stream << compiler::to_string(node->kind());

        auto const token = std::dynamic_pointer_cast<syntax_token>(node);
        if (token) {
            stream << ' ';
            stream << token->text;
        }

        stream << std::endl;

        indent += is_last ? "     " : "|   ";

        auto const children = node->children();
        if (children.empty()) {
            return;
        }

        auto const& back = children.back();

        for (auto&& child : children) {
            pretty_print(stream, child, std::move(indent), child == back);
        }
    }

    export std::string to_string(std::shared_ptr<syntax_node> const& node) noexcept {
        auto stream = std::stringstream();
        pretty_print(stream, node);
        return std::string(stream.str());
    }
}