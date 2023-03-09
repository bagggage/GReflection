#pragma once

#include <vector>

#include "meta-name.h"

namespace GR 
{
	struct ReflectionBuilder;
	struct MetaType;

	struct MetaFunction : public MetaName
	{
	public:
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
			return ((Return (*)(Args...))pointer)(args...);
		}
	protected:
		friend class ReflectionBuilder;

		void* pointer = nullptr;

		MetaType* returnType;
		std::vector<MetaType*> arguments;
	};
}
