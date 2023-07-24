export module compiler.symbol;

import std;

import compiler.symbol_kind;

namespace compiler
{
	export class symbol
	{
	public:
		const std::string logger_name;

	protected:
		[[nodiscard]] symbol(const std::string& logger_name) noexcept : logger_name(logger_name)
		{
		}

		virtual ~symbol() noexcept
		{
		}

	public:
		[[nodiscard]] virtual symbol_kind kind() const noexcept = 0;
	};
}
