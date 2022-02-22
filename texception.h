#pragma once

#include "tstring.h"

namespace tlib::exception
{
	constexpr auto kSuccessfulEndSignal = 0, kExceptionEndSignal = 0xFE, kFailedEndSignal = 0xFF;

	class IException : public std::exception
	{
	public:
		struct TCodeLocation
		{
			TMessage file;
			const int line;
			TMessage function;
		};

		IException(TMessage name, const TCodeLocation location, TMessage about) noexcept
			: data_({ name, location, about }) {}
		[[nodiscard]] virtual TFlag is_critical() const noexcept = 0;
		[[nodiscard]] const char* what() const override
		{
			static string message;
			message.clear();
			message += "An exception was thrown:\t" + string(data_.name ? data_.name : "Unknown");
			if (data_.about) message += ".\n" + string(data_.about);
			message += ".\nLocation:\t\t\tFile:\t\t" + string(data_.location.file ? data_.location.file : "unknown");
			message += ",\n\t\t\t\tLine:\t\t" + std::to_string(data_.location.line);
			message += ",\n\t\t\t\tFunction:\t" + string(data_.location.function ? data_.location.function : "unknown");
			message += ".\nException status:\t\t" + string(is_critical() ? "Critical.\n" : "Not critical.\n");

			return message.c_str();
		}

	protected:
		const struct
		{
			TMessage name;
			const TCodeLocation location;
			TMessage about;
		} data_;
	};

	[[noreturn]] inline terminate_handler terminate(const IException& exception)
	{
		cout << "Program was closed due to catching critical error:\n" << exception.what();
		_exit(kExceptionEndSignal);
	}
	[[noreturn]] inline unexpected_handler unexpected()
	{
		cout << "Program was closed due to catching unexpected error.\n";
		_exit(kFailedEndSignal);
	}
	inline void handle(const IException& exception)
	{
		if (exception.is_critical()) terminate(exception);
		std::cout << exception.what();
	}
}
