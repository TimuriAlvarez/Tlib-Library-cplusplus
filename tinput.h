#pragma once

#include "trandom.h"

namespace tlib
{
	static TFlag auto_random = false;
	template <typename T> T& get(TMessage value_name, const TRange<T>* ranges, const size_t size)
	{
		if (value_name) cout << "Enter the " << value_name << " value: ";
		if (auto_random) return random(ranges, size);

		static T value;
		TInfinity infinity;
		do
		{
			while (!(cin >> value) && infinity())
			{
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "Incorrect value! The value must be a number!\nTry again: ";
			}
			TFlag match = false;
			for (size_t index = 0u; index < size; index++)
				if (ranges[index].contains(value)) match = true;
			if (match) break;
			cout << "Incorrect value! The value must be contains range ";
			for (size_t index = 0u; index < size; index++)
			{
				if (index != 0u) cout << " or ";
				cout << ranges[index];
			}
			cout << "!\nTry again: ";
		} while (infinity());
		return value;
	}
	template <typename T> T& get(TMessage value_name, const TRange<T>& range = TRange<T>())
	{
		return get(value_name, &range, 1);
	}
}
