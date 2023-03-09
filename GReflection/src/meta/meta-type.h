#pragma once

#include <string>
#include <vector>

#include "meta-name.h"
#include "meta-field.h"
#include "meta-method.h"

namespace GR 
{
	class ReflectionBuilder;

	struct MetaType : public MetaName
	{
	public:
		inline const std::vector<MetaType*>& GetBases() const 
		{
			return bases;
		}

		inline const std::vector<std::string>& GetNamespaces() const 
		{
			return namespaces;
		}

		inline const std::string& GetTemplate() const 
		{
			return templateValue;
		}

		inline const std::vector<MetaField>& GetFields() const 
		{
			return fields;
		}

		inline const std::vector<MetaMethod>& GetMethods() const 
		{
			return methods;
		}

		inline const bool IsPointer() const
		{
			return pointers;
		}

		inline unsigned int GetPointerDimention() const
		{
			return pointers;
		}

		inline size_t GetSize() const 
		{
			return size;
		}

		inline size_t GetHash() const 
		{
			return hash;
		}

		template<typename T>
		bool IsEquals() const;
	private:
		friend class ReflectionBuilder;
		friend struct std::hash<MetaType>;

		std::vector<MetaType*> bases;
		std::vector<std::string> namespaces;
		std::string templateValue;
		std::vector<MetaField> fields;
		std::vector<MetaMethod> methods;
		unsigned int pointers;
		size_t size;
		size_t hash;
	};
}

namespace std 
{
	inline void hash_combine(std::size_t& seed) { }

	template <typename T, typename... Rest>
	inline void hash_combine(std::size_t& seed, const T& v, Rest... rest) 
	{
		std::hash<T> hasher;
		seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		hash_combine(seed, rest...);
	}

	template<>
	struct hash<std::vector<std::string>>
	{
		size_t operator()(const std::vector<std::string>& x) const
		{
			size_t result = 0;

			for (int i = 0; i < x.size(); i++)
				hash_combine(result, x[i]);

			return result;
		}
	};

	template<>
	struct hash<GR::MetaType>
	{
		size_t operator()(const GR::MetaType& x) const
		{
			size_t result = 0;

			hash_combine(result, x.name, x.namespaces, x.templateValue);

			return result;
		}
	};
}
