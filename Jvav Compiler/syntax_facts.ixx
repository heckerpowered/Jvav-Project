export module compiler.syntax_facts;

import compiler.syntax_kind;
import std;

namespace compiler {
    std::unordered_map<std::string_view, syntax_kind> keyword_map{
        { "true", syntax_kind::true_keyword },
        { "false", syntax_kind::false_keyword },
        { "if", syntax_kind::if_keyword },
        { "else", syntax_kind::else_keyword },
        { "while", syntax_kind::while_keyword },
        { "for", syntax_kind::for_keyword }
    };

    export class syntax_facts final {
    private:
        syntax_facts() = delete;

    public:
        static syntax_kind get_keyword_kind(std::string_view const& text) noexcept {
            auto const result = keyword_map.find(text);
            if (result == keyword_map.end()) {
                return syntax_kind::identifier_token;
            }

            return result->second;
        }

        static std::uint_fast8_t get_unary_operator_precedence(syntax_kind const kind) noexcept {
            switch (kind)
            {
            case syntax_kind::plus_token:
            case syntax_kind::minus_token:
            case syntax_kind::bang_token:
            case syntax_kind::tilde_token:
                return 6;

            default:
                return 0;
            }
        }

        static std::uint_fast8_t get_binary_operator_precedence(syntax_kind const kind) noexcept {
            switch (kind)
            {
            case syntax_kind::multiplication_token:
            case syntax_kind::slash_token:
                return 5;

            case syntax_kind::plus_token:
            case syntax_kind::minus_token:
                return 4;

            case syntax_kind::bang_equals_token:
            case syntax_kind::equals_equals_token:
            case syntax_kind::less_token:
            case syntax_kind::less_or_equals_token:
            case syntax_kind::greater_token:
            case syntax_kind::greater_or_equals_token:
                return 3;

            case syntax_kind::ampersand_ampersand_token:
                return 2;

            case syntax_kind::pipe_pipe_token:
            case syntax_kind::pipe_token:
            case syntax_kind::hat_token:
                return 1;

            default:
                return 0;
            }
        }
    };
}