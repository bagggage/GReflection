#pragma once

#include <string>

#include "meta-name.h"

namespace GR 
{
	struct MetaType;

	struct MetaField : public MetaName
	{
	public:
		inline const MetaType* GetType() const
		{
			return type;
		}

		inline size_t GetOffset() const
		{
			return offset;
		}

		inline void* GetPointer(const void* owner) const
		{
			return GetPointer<void>(owner);
		}

		template <typename T>
		T* GetPointer(const void* owner) const
		{
			return (T*)(((char*)owner) + offset);
		}

		template<typename T>
		T GetValue(const void* owner) const
		{
			return *(T*)(((char*)owner) + offset);
		}

		template<typename T>
		void SetValue(const void* owner, const T& value) const 
		{
			*(T*)((char*)owner + offset) = value;
		}
	private:
		friend class ReflectionBuilder;

		MetaType* type;
		size_t offset;
	};
}
