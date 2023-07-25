module;

#ifdef _DEBUG
#include <crtdbg.h>
#endif // DEBUG

export module compiler.main;

import std;

import compiler.argument_solver;
import compiler.command_user_interface;

/**
 * @brief Allocate an console, on windows, it enables virtual terminal.
*/
void initialize_console() noexcept
{
#ifdef _WIN32
	compiler::launch_windows();
#endif // _WIN32
}

export int main(int argument_count, char* arguments[]) noexcept
{
#if defined(_DEBUG) && __has_include(<crtdbg.h>)
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
#endif
	auto startup_arguments{ std::vector<std::string_view>{} };
	for (auto i{ 1 }; i < argument_count; ++i)
	{
		startup_arguments.push_back(arguments[i]);
	}

	if (argument_count == 1) [[unlikely]]
	{
		std::println("Usage: source_files=path");
		std::println("-h [Human]");
		return 0;
	}

	auto solved_arguments = compiler::solve_arguments(startup_arguments);
	if (solved_arguments.contains("h")) [[unlikely]]
	{
		initialize_console();
		std::println("Welcome to Jvav!");
		std::println("Jvav is a programming language first proposed by Dr. Haoyang Zhang and implemented by Mr. Rick Astley.");
		compiler::command_user_interface::launch();
#ifdef DEBUG
		_CrtDumpMemoryLeaks();
#endif // DEBUG
		return 0;
	}

	const auto source_files_iterator = solved_arguments.find("source_files");
	if (source_files_iterator == solved_arguments.end()) [[unlikely]]
	{
		std::println(std::cerr, "Error: No source files");
		return 0;
	}

	return 0;
}
