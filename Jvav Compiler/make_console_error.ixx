export module compiler.make_console_error;

import std;

import compiler.console_category;
import compiler.console_error;

namespace std {
	export [[nodiscard]] error_code make_error_code(const compiler::console_error error_code) noexcept {
		return std::error_code{ static_cast<int>(error_code), compiler::console_category() };
	}
}