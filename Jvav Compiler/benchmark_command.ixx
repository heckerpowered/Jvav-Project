export module compiler.command:benchmark;

import std;

import compiler.console_color;

namespace compiler {
	export void benchmark(const std::vector<std::string_view>&) noexcept {
		std::cout << "Running benchmark" << std::endl;

		set_console_foreground_color(console_color::red);
		std::cout << "Red" << std::endl;
		set_console_foreground_color(console_color::white);

		set_console_foreground_color(console_color::dark_red);
		std::cout << "Dark Red" << std::endl;
		set_console_foreground_color(console_color::white);

		set_console_foreground_color(console_color::black);
		std::cout << "Black" << std::endl;
		set_console_foreground_color(console_color::white);

		set_console_foreground_color(console_color::blue);
		std::cout << "Blue" << std::endl;
		set_console_foreground_color(console_color::white);

		set_console_foreground_color(console_color::cyan);
		std::cout << "Cyan" << std::endl;
		set_console_foreground_color(console_color::white);

		set_console_foreground_color(console_color::gray);
		std::cout << "Gray" << std::endl;
		set_console_foreground_color(console_color::white);

		set_console_foreground_color(console_color::dark_gray);
		std::cout << "Dark Gray" << std::endl;
		set_console_foreground_color(console_color::white);
	}
}