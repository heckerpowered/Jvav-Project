export module compiler.console_color;

import std;

#ifdef _WIN32
export import :windows;
#endif // _WIN32

export import :implement;

namespace compiler
{
	export void switch_foreground_color(const console_color color, std::invocable auto invocable) noexcept
	{
		set_console_foreground_color(color);
		invocable();
		set_console_foreground_color(console_color::gray);
	}
}