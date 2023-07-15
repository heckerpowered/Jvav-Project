export module compiler.command:eval;

import std;

import compiler.pretty_print;
import compiler.syntax_tree;
import compiler.zero_copy;

namespace compiler
{
	constexpr bool is_empty_or_whitespace(const std::string_view& text) noexcept
	{
		if (text.empty())
		{
			return true;
		}

		for (auto&& character : text)
		{
			if (character != ' ')
			{
				return false;
			}
		}

		return true;
	}

	void parse_and_print(const std::string& code) noexcept
	{
		const auto syntax_tree = syntax_tree::parse(code);
		std::cout << compiler::to_string(syntax_tree.root) << std::endl;
	}

	void eval_input() noexcept
	{
		auto input_stream = std::stringstream();
		while (true)
		{
			auto input = std::string();
			std::getline(std::cin, input);
			if (is_empty_or_whitespace(input))
			{
				break;
			}
			input_stream << input;
		}

		parse_and_print(input_stream.str());
	}

	void eval_files(const std::vector<std::string_view>& files) noexcept
	{
		auto evaluated_files = std::vector<syntax_tree>();

#ifndef __INTELLISENSE__
		const auto start_time = std::chrono::high_resolution_clock::now();
#endif
		for (auto&& file : files)
		{
			try
			{
				auto path = std::filesystem::path(file);
				std::cout << "eval> " << path.filename().string() << std::endl;
				auto file_stream = std::ifstream(path);

				file_stream.seekg(0, file_stream.end);
				const auto file_size = file_stream.tellg();
				file_stream.seekg(0, file_stream.beg);

				auto file_content = std::string();
				file_content.reserve(file_size);
				file_stream.read(file_content.data(), file_size);

				evaluated_files.emplace_back(zero_copy{[&] { return syntax_tree::parse(file_content); }});
			}
			catch (const std::exception& exception)
			{
				std::cout << "eval> " << "Error while evaluate file: " << file << std::endl;
				std::cout << "eval> " << exception.what() << std::endl;
				break;
			}
		}

		for (auto&& syntax_tree : evaluated_files)
		{
			std::cout << compiler::to_string(syntax_tree.root) << std::endl;
		}
	}

	export void eval(std::vector<std::string_view>& arguments) noexcept
	{
		if (arguments.empty())
		{
			eval_input();
			return;
		}

		const auto& flag = arguments.front();
		if (flag == "-f")
		{
			arguments.erase(arguments.begin());
			eval_files(arguments);
			return;
		}

		std::cout << "Usage:" << std::endl
			<< "\teval [-f] [file paths]" << std::endl
			<< "\teval [Enter] [codes]" << std::endl;
	}
}
