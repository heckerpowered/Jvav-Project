export module compiler.logger_target;

#ifdef _MSC_VER
#define novtable __declspec(novtable)
#else
#define novtable
#endif // DEBUG

import std;

namespace compiler
{
	export class novtable target
	{
	public:
		virtual void write(std::string_view const string) const noexcept = 0;
		virtual ~target() noexcept
		{
		};
	};
}
