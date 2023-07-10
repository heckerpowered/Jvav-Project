export module compiler.pretty_print;

import std;

import compiler.syntax_token;
import compiler.syntax_node;
import compiler.syntax_kind;

namespace compiler {
    void pretty_print(std::ostream& stream, std::shared_ptr<syntax_node> const& node, std::string indent = std::string(),
        bool const is_last = true) noexcept {
        auto const token_marker = is_last ? "©¸©¤©¤" : "©À©¤©¤";

        stream << indent << token_marker << to_string(node->kind());
        if (auto const token = std::dynamic_pointer_cast<syntax_token>(node); token) {
            stream << ' ' << token->text;
        }

        stream << std::endl;

        indent += is_last ? "   " : "©¦  ";

        if (node->children().empty()) {
            return;
        }
        auto const last_child = node->children().back();
        for (auto&& child : node->children()) {
            pretty_print(stream, child, indent, child == last_child);
        }
    }

    export std::string to_string(std::shared_ptr<syntax_node> const& node) noexcept {
        auto stream = std::stringstream();
        pretty_print(stream, node);
        return std::string(stream.str());
    }
}