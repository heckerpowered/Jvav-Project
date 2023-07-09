export module compiler.command_user_interface;

import std;
import compiler.lexical_analyzer;
import compiler.pretty_print;

namespace compiler {
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

    void launch() noexcept {
        std::cin.sync_with_stdio(false);
        std::cout.sync_with_stdio(false);

        while (true) {
            std::cout << "> ";

            auto input = std::string();
            std::getline(std::cin, input, '\n');

            if (is_empty_or_whitespace(input) || input == "exit") {
                break;
            }

            auto analyzer = lexical_analyzer(input);
            while (true) {
                auto token = analyzer.analyze();
                if (token->kind() == syntax_kind::end_token || 
                    token->kind() == syntax_kind::bad_token) {
                    break;
                }

                if (token->kind() == syntax_kind::whitespace_token || 
                    token->kind() == syntax_kind::bad_token ||
                    token->kind() == syntax_kind::end_token) {
                    continue;
                }

                std::cout << compiler::to_string(token) << std::endl;
            }
        }
    }

    export class command_user_interface final {
    private:
        command_user_interface() = delete;

    public:
        static void launch() noexcept {
            compiler::launch();
        }
    };
}