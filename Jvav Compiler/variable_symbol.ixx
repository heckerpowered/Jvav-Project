export module compiler.variable_symbol;

import std;

import compiler.type_symbol;
import compiler.symbol;

namespace compiler
{
	export class variable_symbol final : public symbol
	{
	public:
		using super = symbol;

		const bool is_read_only;
		const type_symbol& type;

		[[nodiscard]] variable_symbol(const std::string& name, const bool is_read_only, const type_symbol& type)
			noexcept : super(name), is_read_only(is_read_only), type(type)
		{
		}

		symbol_kind kind() const noexcept override
		{
			return symbol_kind::local_variable;
		};
	};
}
