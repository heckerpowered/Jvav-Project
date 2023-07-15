import std;

import compiler.argument_solver;
import compiler.command_user_interface;

int main(int argument_count, char* arguments[]) noexcept
{
	std::vector<std::string_view> startup_arguments;
	for (auto i = 1; i < argument_count; ++i)
	{
		startup_arguments.push_back(arguments[i]);
	}

	std::cout.sync_with_stdio(false);

	if (argument_count == 1)
	{
		std::cout << "Usage: source_files=path" << std::endl;
		std::cout << "-h [Human]" << std::endl;
		return 0;
	}

	auto solved_arguments = compiler::solve_arguments(startup_arguments);
	if (solved_arguments.contains("h"))
	{
		std::cout << "Welcome to Jvav!" << std::endl;
		std::cout <<
			"Jvav is a programming language first proposed by Dr. Haoyang Zhang and implemented by Mr. Rick Astley." <<
			std::endl;
		compiler::command_user_interface::launch();
		return 0;
	}

	const auto source_files_iterator = solved_arguments.find("source_files");
	if (source_files_iterator == solved_arguments.end())
	{
		std::cout << "Error: No source files" << std::endl;
		return 0;
	}
}
