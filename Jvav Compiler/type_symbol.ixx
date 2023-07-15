export module compiler.type_symbol;

import std;

import compiler.symbol;

namespace compiler
{
	export class type_symbol final : public symbol
	{
	public:
		using super = symbol;

		[[nodiscard]] type_symbol(const std::string& name) noexcept : super(name)
		{
		}

		virtual symbol_kind kind() const noexcept override
		{
			return symbol_kind::type;
		}
	};

	export const type_symbol error_type("?");
	export const type_symbol auto_type("auto");
	export const type_symbol bool_type("bool");
	export const type_symbol int_type("int");
	export const type_symbol string_type("string");
	export const type_symbol void_type("void");
}
