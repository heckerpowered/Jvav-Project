export module compiler.stream_target;

import std;

import compiler.logger_target;

namespace compiler
{
	export template<typename stream_type> requires requires
	{ 
		stream_type{ std::move(std::declval<stream_type>()) }; 
		std::is_same_v<decltype(std::declval<stream_type>() << std::declval<std::string_view const>()), stream_type&>;
	}
	class stream_target final : target
	{
	public:
		using super = target;

		[[nodiscard]] stream_target(stream_type&& stream) noexcept : stream(std::move(stream))
		{
		}

		void write(std::string_view const string) const noexcept override
		{
			stream << string;
		}

	private:
		stream_type stream;
	};
}