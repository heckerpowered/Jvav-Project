export module compiler.bound_expression;

import compiler.bound_node;
import compiler.type_symbol;

namespace compiler
{
	export class bound_expression : public bound_node
	{
	public:
		using super = bound_node;

		virtual const type_symbol& type() const noexcept = 0;
	};
}
