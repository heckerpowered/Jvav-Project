module;

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

export module compiler.command_user_interface:windows;

import std;

import compiler.console_color;
import compiler.print;

namespace compiler
{
	export void launch_windows() noexcept
	{
		const auto output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (output_handle == INVALID_HANDLE_VALUE)
		{
			// perrln("init> cannot launch windows user interface");
			// perrln("init> ", std::error_code(GetLastError(), std::system_category()).message());
			return;
		}

		auto console_mode = DWORD();
		if (!GetConsoleMode(output_handle, &console_mode))
		{
			// perrln("init> cannot launch windows user interface");
			// perrln(std::error_code(GetLastError(), std::system_category()).message());
			return;
		}

		console_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		console_mode |= ENABLE_PROCESSED_OUTPUT;
		console_mode |= ENABLE_WRAP_AT_EOL_OUTPUT;
		console_mode |= DISABLE_NEWLINE_AUTO_RETURN;
		console_mode |= ENABLE_LVB_GRID_WORLDWIDE;

		if (!SetConsoleMode(output_handle, console_mode))
		{
			// perrln("init> cannot launch windows user interface");
			// perrln(std::error_code(GetLastError(), std::system_category()).message());
			return;
		}
	}
}
