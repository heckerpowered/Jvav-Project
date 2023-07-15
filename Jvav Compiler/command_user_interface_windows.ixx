module;

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

import std;

export module compiler.command_user_interface:windows;

namespace compiler
{
	void launch_windows() noexcept
	{
		const auto output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (output_handle == INVALID_HANDLE_VALUE)
		{
			std::cerr << "init> cannot launch windows user interface" << std::endl
				<< "init> " << std::error_code(GetLastError(), std::system_category()).message() << std::endl;
			return;
		}

		auto console_mode = DWORD();
		if (!GetConsoleMode(output_handle, &console_mode))
		{
			std::cerr << "init> cannot launch windows user interface" << std::endl
				<< "init> " << std::error_code(GetLastError(), std::system_category()).message() << std::endl;
			return;
		}

		console_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		console_mode |= ENABLE_PROCESSED_OUTPUT;
		console_mode |= ENABLE_WRAP_AT_EOL_OUTPUT;
		console_mode |= DISABLE_NEWLINE_AUTO_RETURN;
		console_mode |= ENABLE_LVB_GRID_WORLDWIDE;

		if (!SetConsoleMode(output_handle, console_mode))
		{
			std::cerr << "init> cannot launch windows user interface" << std::endl
				<< "init> " << std::error_code(GetLastError(), std::system_category()).message() << std::endl;
		}
	}
}
