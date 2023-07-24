export module compiler.logger_level;

import std;

#ifdef _MSC_VER
#define novtable __declspec(novtable)
#else
#define novtable
#endif // DEBUG

namespace compiler
{
	export class novtable logger_level
	{
	public:
		[[nodiscard]] virtual std::string name() const noexcept = 0;
	};
}