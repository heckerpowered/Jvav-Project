module;

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

export module compiler.console_color:windows;

import std;

import :implement;

import compiler.make_console_error;
import compiler.console_error;


namespace compiler
{
	template<bool is_background>
	[[nodiscard]] std::expected<std::uint_fast16_t, std::error_code>
		map_console_color_to_text_attribute(const console_color color) noexcept {
		if constexpr (is_background) {
			switch (color) {
			case console_color::black:
				return 0;
			case console_color::blue:
				return BACKGROUND_INTENSITY | BACKGROUND_BLUE;
			case console_color::cyan:
				return BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN;
			case console_color::dark_blue:
				return BACKGROUND_BLUE;
			case console_color::dark_cyan:
				return BACKGROUND_BLUE | BACKGROUND_GREEN;
			case console_color::dark_gray:
				return BACKGROUND_INTENSITY;
			case console_color::dark_green:
				return BACKGROUND_GREEN;
			case console_color::dark_magenta:
				return BACKGROUND_RED | BACKGROUND_BLUE;
			case console_color::dark_red:
				return BACKGROUND_RED;
			case console_color::dark_yellow:
				return BACKGROUND_RED | BACKGROUND_GREEN;
			case console_color::gray:
				return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
			case console_color::green:
				return BACKGROUND_INTENSITY | BACKGROUND_GREEN;
			case console_color::magenta:
				return BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE;
			case console_color::red:
				return BACKGROUND_INTENSITY | BACKGROUND_RED;
			case console_color::white:
				return BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
			case console_color::yellow:
				return BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN;
			default:
				return std::unexpected(std::make_error_code(console_error::invalid_console_color));
			}
		}
		else {
			switch (color)
			{
			case console_color::black:
				return 0;
			case console_color::blue:
				return FOREGROUND_INTENSITY | FOREGROUND_BLUE;
			case console_color::cyan:
				return FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN;
			case console_color::dark_blue:
				return FOREGROUND_BLUE;
			case console_color::dark_cyan:
				return FOREGROUND_BLUE | FOREGROUND_GREEN;
			case console_color::dark_gray:
				return FOREGROUND_INTENSITY;
			case console_color::dark_green:
				return FOREGROUND_GREEN;
			case console_color::dark_magenta:
				return FOREGROUND_RED | FOREGROUND_BLUE;
			case console_color::dark_red:
				return FOREGROUND_RED;
			case console_color::dark_yellow:
				return FOREGROUND_RED | FOREGROUND_GREEN;
			case console_color::gray:
				return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			case console_color::green:
				return FOREGROUND_INTENSITY | FOREGROUND_GREEN;
			case console_color::magenta:
				return FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE;
			case console_color::red:
				return FOREGROUND_INTENSITY | FOREGROUND_RED;
			case console_color::white:
				return FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			case console_color::yellow:
				return FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
			default:
				return std::unexpected(std::make_error_code(console_error::invalid_console_color));
			}
		}
	}

	export std::error_code set_console_foreground_color(const console_color color) noexcept {
		auto const output_handle{ GetStdHandle(STD_OUTPUT_HANDLE) };
		auto console_screen_buffer_info{ CONSOLE_SCREEN_BUFFER_INFO{} };
		if (!GetConsoleScreenBufferInfo(output_handle, &console_screen_buffer_info)) {
			return std::error_code{ static_cast<int>(GetLastError()), std::system_category()};
		}

		constexpr auto foreground_mask{ 0xF };

		auto color_attribute{ map_console_color_to_text_attribute<false>(color) };
		if (!color_attribute) {
			return color_attribute.error();
		}

		SetConsoleTextAttribute(output_handle, *color_attribute);
		return std::error_code();
	}

	export std::error_code set_error_console_foreground_color(const console_color color) noexcept {
		auto const output_handle = GetStdHandle(STD_ERROR_HANDLE);
		auto console_screen_buffer_info = CONSOLE_SCREEN_BUFFER_INFO();
		if (!GetConsoleScreenBufferInfo(output_handle, &console_screen_buffer_info)) {
			return std::error_code(GetLastError(), std::system_category());
		}

		constexpr auto foreground_mask = 0xF;

		auto color_attribute = map_console_color_to_text_attribute<false>(color);
		if (!color_attribute) {
			return color_attribute.error();
		}

		SetConsoleTextAttribute(output_handle, *color_attribute);
		return std::error_code();
	}
}
