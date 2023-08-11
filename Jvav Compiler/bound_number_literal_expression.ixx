export module compiler.bound_number_literal_expression;

import std;

import compiler.bound_expression;

namespace compiler
{
	export class bound_number_literal_expression final : public bound_expression
	{
	public:
		using super = bound_expression;
	};
}