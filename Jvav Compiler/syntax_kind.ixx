export module compiler.syntax_kind;

namespace compiler {
    export enum class syntax_kind {
        number_token,
        whitespace_token,
        plus_token,
        minus_token,
        star_token,
        slash_token,
        open_parenthesis_token,
        close_parenthesis_token,
        bad_token,
        end_of_file_token
    };
}