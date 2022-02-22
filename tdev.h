#pragma once

#include "tlib"
#include "tdev"

namespace tdev
{
	using namespace tlib;
	inline int sandbox()
	{
		try
		{
			
		}
		catch (exception::IException& exception)
		{
			handle(exception);
			return exception::kExceptionEndSignal;
		}
		catch (...) { return exception::kFailedEndSignal; }
		return exception::kSuccessfulEndSignal;
	}
}
