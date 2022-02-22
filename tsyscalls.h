#pragma once

#include <cstdlib>

// ReSharper disable CppClangTidyConcurrencyMtUnsafe
// ReSharper disable CppInconsistentNaming

namespace tlib::syscalls
{
	enum class System
	{
		Windows,
		Linux,
		iOS,
		MacOS,
		Android,
		Undefined
	};
	static System operating_system = System::Windows;

	inline void pause()
	{
		switch (operating_system)
		{
		case System::Windows:
			system("pause");
			return;
		case System::Linux: case System::MacOS:
			system("read");
			return;
		case System::iOS: case System::Android: case System::Undefined:
			;
		}
	}
	inline void clear()
	{
		switch (operating_system)
		{
		case System::Windows:
			system("cls");
			return;
		case System::Linux:
			system("clear");
			return;
		case System::iOS: case System::MacOS: case System::Android: case System::Undefined:
			;
		}
	}
	inline void update()
	{
		pause();
		clear();
	}
}
