#pragma once

#include <iostream>
#include <ctime>

namespace tdev
{
	class TTimer
	{
	public:
		TTimer()
			: data_({ clock() , clock() }) {}

		void start()
		{
			data_.start = clock();
		}
		void end()
		{
			data_.end = clock();
		}
		[[nodiscard]] long double duration() const
		{
			return (static_cast<long double>(data_.end) - static_cast<long double>(data_.start)) / static_cast<long double>(CLOCKS_PER_SEC);
		}

		friend std::ostream& operator<<(std::ostream& stream, const TTimer& timer)
		{
			return stream << timer.duration() << " seconds";
		}
	private:
		struct
		{
			clock_t start;
			clock_t end;
		} data_;
	};
}
