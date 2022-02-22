#pragma once

#include <numeric>

#include "texception.h"

namespace tlib::exception
{
	class ERange : public IException
	{
	public:
		explicit ERange(const TCodeLocation location, TMessage about)
			: IException("TRange exception", location, about) {}
	};
	class ERangeBoundariesFailure final : public ERange
	{
	public:
		explicit ERangeBoundariesFailure(const TCodeLocation location, const TFlag min_equals_max)
			: ERange(location, min_equals_max ? "Min boundary equals max one but this value is excluded from range" : "Min boundary is greater than max one") {}
		[[nodiscard]] TFlag is_critical() const noexcept override { return false; }
	};
	class ERangeViolation final : public ERange
	{
	public:
		explicit ERangeViolation(const TCodeLocation location)
			: ERange(location, "Range must contain provided value but it doesn't") {}
		[[nodiscard]] TFlag is_critical() const noexcept override { return true; }
	};
}
template <typename T> class tlib::TRange
{
public:
	TRange()
		: data_({ numeric_limits<T>::min(), numeric_limits<T>::max(), true, false })
	{
		if (data_.min > data_.max || equal_boundaries())
			throw exception::ERangeBoundariesFailure(LOCATION, equal_boundaries());
	}
	explicit TRange(const T& min, const T& max, const TFlag include_min = true, const TFlag include_max = true)
		: data_({ min, max, include_min, include_max })
	{
		if (data_.min > data_.max || (!include_min || !include_max) && equal_boundaries())
			throw exception::ERangeBoundariesFailure(LOCATION, equal_boundaries());
	}
	[[nodiscard]] TFlag contains(const T& value, const TFlag must_contain = false) const
	{
		TFlag result;
		if (data_.include_min && data_.include_max) result = (value >= data_.min && value <= data_.max);
		/*	If all conditions are false - the value is valid:
		 *	!	min value is acceptable, the current value is less then min one
		 *	!	min value is not acceptable, the current value is less then min one or equals it
		 *	!	max value is acceptable, the current value is greater then max one
		 *	!	max value is not acceptable, the current value is greater then max one or equals it
		 */
		else result = !(data_.include_min && value < data_.min || !data_.include_min && value <= data_.min ||
			data_.include_max && value > data_.max || !data_.include_max && value >= data_.max);
		if (must_contain && !result) throw exception::ERangeViolation(LOCATION);
		return result;
	}
	friend std::ostream& operator<<(std::ostream& stream, const TRange<T>& range)
	{
		stream << (range.data_.include_min ? '[' : '(') << range.data_.min << "; "
			<< range.data_.max << (range.data_.include_max ? ']' : ')');
		return stream;
	}

	[[nodiscard]] const T& min() const
	{
		return data_.min;
	}
	[[nodiscard]] const T& max() const
	{
		return data_.max;
	}
	[[nodiscard]] TFlag equal_boundaries() const
	{
		return !(min() > max()) && !(min() < max());
	}

protected:
	const struct
	{
		const T min;
		const T max;
		const TFlag include_min;
		const TFlag include_max;
	} data_;
};