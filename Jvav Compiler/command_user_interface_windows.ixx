module;

#ifdef _WIN32
#include <Windows.h>
#include <stdio.h>
#endif // _WIN32

export module compiler.command_user_interface:windows;

import std;
import std.compat;

import compiler.console_color;
import compiler.print;

namespace compiler
{
	export void launch_windows() noexcept
	{
		const auto output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (output_handle == INVALID_HANDLE_VALUE) [[unlikely]]
		{
			switch_foreground_color(console_color::dark_red, []
			{
#ifndef __INTELLISENSE__
				std::println(std::cerr, "Cannot initialize console: {}",
							 std::error_code(GetLastError(), std::system_category()).message());
#endif // !__INTELLISNESE__
			});
			return;
		}

		auto console_mode = DWORD();
		if (!GetConsoleMode(output_handle, &console_mode))
		{
			switch_foreground_color(console_color::dark_red, []
			{
#ifndef __INTELLISENSE__
				std::println(std::cerr, "Cannot initialize console: {}",
							 std::error_code(GetLastError(), std::system_category()).message());
#endif // !__INTELLISENSE__
			});
			return;
		}

		console_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		console_mode |= ENABLE_PROCESSED_OUTPUT;
		console_mode |= ENABLE_WRAP_AT_EOL_OUTPUT;
		console_mode |= DISABLE_NEWLINE_AUTO_RETURN;
		console_mode |= ENABLE_LVB_GRID_WORLDWIDE;

		if (!SetConsoleMode(output_handle, console_mode)) [[unlikely]]
		{
#ifndef __INTELLISENSE__
			std::println(std::cerr, "Cannot initialize console: {}",
						 std::error_code(GetLastError(), std::system_category()).message());
#endif // !__INTELLISENSE__
			return;
		}
	}
}
