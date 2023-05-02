#pragma once

#include "meta-function.h"

#include <cstdlib>

namespace GR 
{
	struct MetaMethod : public MetaFunction
	{
	public:
		template<typename Return, typename Owner, typename... Args>
		Return Invoke(Owner* owner, Args... args) const
		{
			return (owner->**((Return(Owner::**)(Args...))pointer))(args...);
		}
	private:
		friend class ReflectionBuilder;
	};
}
