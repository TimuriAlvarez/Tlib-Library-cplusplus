#pragma once

#include "texception.h"
#include "trange.h"

namespace tlib::exception
{
	class ECounterInfiniteLoop final : public IException
	{
	public:
		explicit ECounterInfiniteLoop(const TCodeLocation location)
			: IException("TInfinity exception", location, "Infinite loop was detected. Infinite loop protection triggered the exception") {}

		[[nodiscard]] TFlag is_critical() const noexcept override { return false; }
	};
}
template <typename T> class tlib::TCounter
{
public:
	explicit TCounter(const TRange<T>& range = TRange<T>())
		: data_({ range.min(), range }) {}
	TFlag operator() ()
	{
		if (data_.attempt == data_.range.max())
		{
			if (!data_.range.contains(data_.attempt)) throw exception::ECounterInfiniteLoop(LOCATION);
			return false;
		}
		data_.attempt += 1;
		return true;
	}
	[[nodiscard]] T attempt() const
	{
		return data_.attempt;
	}

protected:
	struct
	{
		T attempt;
		TRange<T> range;
	} data_;
};
