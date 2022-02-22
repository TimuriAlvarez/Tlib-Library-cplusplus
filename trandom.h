#pragma once

#include <random>

#include "tcounter.h"

namespace tlib::exception
{
	class ERandom final : public IException
	{
	public:
		explicit ERandom(const TCodeLocation location)
			: IException("TRandom exception", location, "Range contains the one and only acceptable value which is not allowed") {}
		[[nodiscard]] TFlag is_critical() const noexcept override { return false; }
	};
}
namespace tlib
{
	//	The best value according to series of experiments. DO NOT CHANGE IF YOU DON'T KNOW WHAT YOU ARE DOING
	template <typename T> T& random(const TRange<T>* ranges, const size_t size, const unsigned int divide_coefficient = 10000u)
	{
		std::random_device rd;
		// ReSharper disable once IdentifierTypo
		std::mt19937_64 mersenne(rd());
		static T value;
		TInfinity infinity;
		TFlag match = false;
		do
		{
			value = static_cast<T>(mersenne()) / divide_coefficient + static_cast<T>(mersenne() % divide_coefficient);
			for (size_t index = 0u; index < size; index++)
				if (ranges[index].contains(value)) match = true;
		} while (infinity() && !match);
		return value;
	}
	template <typename T> T& random(const TRange<T>& range = TRange<T>(), const unsigned int divide_coefficient = 10000u)
	{
		if (range.equal_boundaries()) throw exception::ERandom(SIGNATURE);
		return random(&range, 1, divide_coefficient);
	}
}