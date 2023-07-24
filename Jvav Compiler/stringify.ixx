export module compiler.stringify;

import std;

namespace compiler {
	export template<typename stream_type> concept formattable = requires(stream_type t) {
		{std::format("{}", t)}->std::same_as<std::string>;
	};

	export template<typename stream_type> concept std_to_string = requires(stream_type t) {
		{std::to_string(t)}->std::same_as<std::string>;
	};

	export template<typename stream_type> concept stream_operator = requires(stream_type t) {
		std::same_as<std::decay_t<decltype(std::declval<std::ostream>() << t)>, std::ostream>;
	};

	export template<typename stream_type> concept stream_state_modifier = requires(stream_type t) {
		{t(std::declval<std::ios_base&>())}->std::same_as<std::ios_base&>;
	};

	export template<typename stream_type> concept string_representable = formattable<stream_type> || std_to_string<stream_type> || stream_operator<stream_type>;

	export template<formattable stream_type>
		std::string to_string(const std::format_string<stream_type> format, stream_type&& t) noexcept {
		return std::format(format, std::forward<stream_type>(t));
	}

	export template<formattable stream_type>
		std::string to_string(stream_type&& t) noexcept {
		return to_string("{}", std::forward<stream_type>(t));
	}

	export template<std_to_string stream_type>
		std::string to_string(stream_type&& t) noexcept {
		return std::to_string(std::forward<stream_type>(t));
	}

	export template<stream_operator stream_type>
		std::string to_string(stream_type&& t) noexcept {
		auto stream = std::stringstream();
		stream << t;
		return stream.str();
	}

	export template<stream_operator stream_type, stream_state_modifier... modifier_type>
		std::string to_string(stream_type&& t, modifier_type&&... modifiers) noexcept {
		auto stream = std::stringstream();
		(stream << ... << std::forward<modifier_type>(modifiers));
		stream << t;
		return stream.str();
	}
}