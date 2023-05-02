#pragma once

#include <vector>

#include "meta-name.h"

namespace GR 
{
	struct MetaType;

	struct MetaFunction : public MetaName
	{
	public:
		MetaFunction() = default;
		MetaFunction(const MetaFunction& origin) 
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

		~MetaFunction() 
		{
			if (pointer)
				std::free(pointer);
		}

		inline const MetaType* GetReturnType() const 
		{
			return returnType;
		}

		inline const std::vector<MetaType*> GetArguments() const 
		{
			return arguments;
		}

		template<typename Return, typename... Args>
		Return Invoke(Args... args) const
		{
			return (*(Return (**)(Args...))pointer)(args...);
		}
	protected:
		friend class ReflectionBuilder;

		size_t pointerSize = 0;
		void* pointer = nullptr;

		MetaType* returnType;
		std::vector<MetaType*> arguments;

		size_t hash;
	};
}
