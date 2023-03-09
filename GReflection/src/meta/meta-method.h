#pragma once

#include "meta-function.h"

#include <cstdlib>

namespace GR 
{
	struct MetaMethod : public MetaFunction
	{
	public:
		MetaMethod() = default;
		MetaMethod(const MetaMethod& origin)
		{
			name = origin.name;
			returnType = origin.returnType;
			arguments = origin.arguments;
			pointerSize = origin.pointerSize;

			if (origin.pointer != nullptr)
			{			
				pointer = std::malloc(pointerSize);

				std::memcpy(pointer, origin.pointer, pointerSize);
			}
		}

		~MetaMethod()
		{
			if (pointer)
				std::free(pointer);
		}

		template<typename Return, typename Owner, typename... Args>
		Return Invoke(Owner* owner, Args... args) const
		{
			return (owner->**((Return(Owner::**)(Args...))pointer))(args...);
		}
	private:
		friend class ReflectionBuilder;

		size_t pointerSize = 0;
	};
}
