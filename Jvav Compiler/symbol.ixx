export module compiler.symbol;

import std;

import compiler.symbol_kind;

namespace compiler
{
	export class symbol
	{
	public:
		const std::string name;

	protected:
		[[nodiscard]] symbol(const std::string& name) noexcept : name(name)
		{
		}

	public:
		[[nodiscard]] virtual symbol_kind kind() const noexcept = 0;
	};
}
