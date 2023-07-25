export module compiler.command:eval;

import std;

import compiler.pretty_print;
import compiler.syntax_tree;
import compiler.zero_copy;
import compiler.console_color;

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
		const auto syntax_tree{ syntax_tree::parse(code) };
#ifndef __INTELLISENSE__
		std::println("{}", compiler::to_string(syntax_tree.root));
#endif
	}

	void eval_input() noexcept
	{
		auto input_stream{ std::stringstream{} };
		while (true)
		{
			auto input{ std::string{} };
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
		auto evaluated_files{ std::vector<syntax_tree>{} };
		for (auto&& user_file_path : files)
		{
			try
			{
				auto path = std::filesystem::path(user_file_path);
				auto file_stream{ std::ifstream(path) };

				file_stream.seekg(0, file_stream.end);
				const auto file_size = file_stream.tellg();
				file_stream.seekg(0, file_stream.beg);

				auto file_content{ std::string() };
				file_content.reserve(file_size);
				file_stream.read(file_content.data(), file_size);
#ifndef __INTELLISENSE__

#endif // !__INTELLISENSE__
				evaluated_files.emplace_back(zero_copy{[&] { return syntax_tree::parse(file_content); }});
			}
			catch (const std::exception& exception)
			{
				switch_foreground_color(console_color::dark_red, [&]
				{
#ifndef __INTELLISENSE__
					std::println("Error while evaluating file: {}", user_file_path);
					std::println("{}", exception.what());
#endif // !__INTELLISENSE__

				});
			}
		}

		for (auto&& syntax_tree : evaluated_files)
		{
#ifndef __INTELLISENSE__
			compiler::to_string(syntax_tree.root);
#endif // !__INTELLISENSE__
		}
	}

	export void eval(std::vector<std::string_view>& arguments) noexcept
	{
		if (arguments.empty())
		{
			eval_input();
			return;
		}

		const auto& flag{ arguments.front() };
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
