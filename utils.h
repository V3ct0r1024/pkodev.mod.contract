#pragma once
#include <format>

namespace pkodev {

	class utils final
	{
		public:
			template<typename T, int Offset = 0x00>
			static T get(void* src) { return *reinterpret_cast<T*>(reinterpret_cast<int>(src) + Offset); }

			template<typename T, int Offset = 0x00>
			static T get(const int src) { return *reinterpret_cast<T*>(src + Offset); }

			template<typename T, int Offset = 0x00>
			static void set(void* src, const T& value) { *reinterpret_cast<T*>(reinterpret_cast<int>(src) + Offset) = value; }

			template<typename T, int Offset = 0x00>
			static void set(const int src, const T& value) { *reinterpret_cast<T*>(src + Offset) = value; }

			template<typename... Args>
			static std::string safe_format(const std::string& fmt, Args&&... args) {
				std::string ret = "<error>";
				try {
					ret = std::vformat(std::string_view{ fmt.data() }, std::make_format_args(args...));
				}
				catch (...) { }
				return ret;
			}
	};

}

