#pragma once

#include "tsyscalls.h"
#include "tinput.h"

template <typename T> class tlib::TMenu
{
public:
	typedef void (*Actions)(T*);

	TMenu(const TMessage* const options, const size_t size, const Actions* const actions)
		: data_({ options, size + 1, actions }) {}

	[[nodiscard]] size_t action() const
	{
		cout << *this;
		return get("action", TRange<size_t>(1u, data_.size));
	}
	[[nodiscard]] size_t action(const size_t choice) const
	{
		cout << *this << "Enter the action value: " << choice << '\n';
		return choice;
	}

	void operator() (T* const parameter = nullptr) const
	{
		TInfinity infinity;
		const auto range = TRange<size_t>(1u, data_.size);
		do
		{
			if (const auto val = action(); range.contains(val, true) && val == data_.size) return;
			else try { data_.actions[val - 1](parameter); }
			catch (const exception::IException& exception)
			{
				if (exception.is_critical()) throw;
				handle(exception);
			}
			syscalls::pause();
		} while (infinity());
	}
	void operator() (const size_t* const choices, const size_t size, const T* const parameter = nullptr) const
	{
		TInfinity infinity;
		const auto range = TRange<size_t>({ 1u, data_.size });
		for (size_t i = 0; i < size && infinity(); i++)
		{
			if (const auto val = action(choices[i]); range.contains(val, true) && val == data_.size)
				return operator() (parameter);
			else try { data_.actions[val - 1](parameter); }
			catch (const exception::IException& exception) { if (exception.is_critical()) throw; }
			syscalls::pause();
		}
	}
	friend std::ostream& operator<<(std::ostream& stream, const TMenu& menu)
	{
		syscalls::clear();
		stream << "Actions:\n";
		for (auto i = 1u; i < menu.data_.size; i++)
			stream << '\t' << i << ")\t" << menu.data_.options[i - 1] << ";\n";
		stream << '\t' << menu.data_.size << ")\tQuit.\n";
		return stream;
	}

protected:
	struct
	{
		const TMessage* const options;
		const size_t size;
		const Actions* const actions;
	} data_;
};
template <> class tlib::TMenu<void>
{
public:
	TMenu(const TMessage* const options, const size_t size)
		: data_({ options, size + 1 }) {}

	[[nodiscard]] size_t action() const
	{
		cout << *this;
		return get("action", TRange<size_t>(1u, data_.size));
	}
	[[nodiscard]] size_t action(const size_t choice) const
	{
		cout << *this << "Enter the action value: " << choice << '\n';
		return choice;
	}

	size_t operator() () const
	{
		const auto val = action();
		syscalls::update();
		return val;
	}
	friend std::ostream& operator<<(std::ostream& stream, const TMenu& menu)
	{
		syscalls::clear();
		stream << "Actions:\n";
		for (auto i = 1u; i < menu.data_.size; i++)
			stream << '\t' << i << ")\t" << menu.data_.options[i - 1] << ";\n";
		stream << '\t' << menu.data_.size << ")\tQuit.\n";
		return stream;
	}

protected:
	struct
	{
		const TMessage* const options;
		const size_t size;
	} data_{};
};
