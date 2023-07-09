export module for_statement_syntax;

import std;

import compiler.expression_syntax;
import compiler.statement_syntax;
import compiler.syntax_token;

namespace compiler {
    export class for_statement_syntax final : public statement_syntax {
    public:
        using super = statement_syntax;

        std::shared_ptr<syntax_token> keyword;
    };
}