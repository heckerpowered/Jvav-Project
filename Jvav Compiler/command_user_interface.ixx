export module compiler.command_user_interface;

import std;
import compiler.lexical_analyzer;
import compiler.pretty_print;
import compiler.syntax_tree;
import compiler.source_text;
import compiler.parser;

namespace compiler::command_user_interface {
    constexpr bool is_empty_or_whitespace(std::string_view const& text) noexcept {
        if (text.empty()) {
            return true;
        }

        for (auto&& character : text) {
            if (character != ' ') {
                return false;
            }
        }

        return true;
    }

    void benchmark() noexcept {

    }

    void eval() noexcept {
        auto input_stream = std::stringstream();
        while (true) {
            auto input = std::string();
            std::getline(std::cin, input);
            if (is_empty_or_whitespace(input)) {
                break;
            }
            input_stream << input;
        }
        
        auto const syntax_tree = syntax_tree::parse(input_stream.str());
        std::cout << compiler::to_string(syntax_tree.root) << std::endl;
    }

    export std::unordered_map<std::string_view, std::function<void(void)>> commands{
        {"exit", [] { std::exit(0); }},
        {"benchmark", benchmark},
        {"eval", eval}
    };

    export void launch() noexcept {
        std::cin.sync_with_stdio(false);
        std::cout.sync_with_stdio(false);
        std::cout << std::endl;

        while (true) {
            std::cout << "> ";
            auto input = std::string();
            std::cin >> input;

            auto const iterator = commands.find(input);
            if (iterator == commands.end()) {
                std::cout << "Command not found" << std::endl << std::endl;
                continue;
            }
            iterator->second();
        }
    }
}