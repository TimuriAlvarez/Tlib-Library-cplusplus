#pragma once

#include <string>

#include "tlib.h"

class tlib::TString
{
public:
	explicit TString() = default;
	static string get(TMessage name, const TFlag can_be_empty = false)
	{
		if (name) cout << "Enter the " << name << ": ";
		string result;
		do
		{
			cin.sync();
			std::getline(cin, result);
		} while (!can_be_empty && result.empty());
		return result;
	}
	string operator() (TMessage name, const TFlag can_be_empty = false) const
	{
		return get(name, can_be_empty);
	}
};
