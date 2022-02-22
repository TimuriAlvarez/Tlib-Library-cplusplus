#pragma once

#include <iostream>

#define FUNCTION { __FILE__ , __LINE__ , __FUNCTION__ }  // NOLINT(clang-diagnostic-unused-macros)
#define SIGNATURE { __FILE__ , __LINE__ , __FUNCSIG__ }

#define LOCATION SIGNATURE

namespace tlib
{
	namespace syscalls {}

	using std::size;
	using std::cout;
	using std::cin;
	using std::string;
	using std::numeric_limits;

	typedef bool TFlag;
	typedef const char* const TMessage;

	namespace exception {}

	template <typename T> class TRange;
	template <typename T> class TCounter;
	typedef TCounter<unsigned int> TInfinity;
	class TString;

	template <typename T> T& get(TMessage, const TRange<T>*, size_t);
	template <typename T> T& get(TMessage, const TRange<T>&);
	template <typename T> T& random(const TRange<T>*, size_t, unsigned int);
	template <typename T> T& random(const TRange<T>&, unsigned int);

	template <typename T> class TMenu;
}

