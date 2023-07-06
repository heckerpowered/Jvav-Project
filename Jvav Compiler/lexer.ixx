export module compiler.lexer;

import std;
import compiler.syntax_token;

namespace compiler {
    export class lexical_analyzer {
    private:
        std::string const text;
        std::size_t position;

    public:
        lexical_analyzer(std::string text) noexcept : text(text) {}

    private:
        char current() noexcept {
            if (position >= text.length()) {
                return '\0';
            }

            return text.at(position);
        }

    public:
        void next() noexcept {
            ++position;
        }

        syntax_token analyze() noexcept {
            if (std::isdigit(current())) {
                auto const start = position;
                while (std::isdigit(current())) {
                    next();
                }

                auto const length = position - start;
                auto text = this->text.substr(start, length);

                auto value = 0;
                std::from_chars(text.data(), text.data() + text.length(), value);

                return syntax_token(syntax_kind::number_token, start, text, value);
            }

            if (std::isspace(current()) {
                auto const start = position;
                while (std::isspace(current())) {
                    next();
                }

                auto const length = position - start;
                auto text = this->text.substr(start, length);
                return syntax_token(syntax_kind::whitespace_token, start, text)
            }
        }

        syntax_token lex() noexcept {
            return analyze();
        }
    };

    using lexer = lexical_analyzer;
    using scanner = lexer;
}