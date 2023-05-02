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

		inline bool IsPointer() const
		{
			return pointers;
		}

		inline bool IsConst() const 
		{
			return isConst;
		}

		inline bool IsReference() const 
		{
			return isReference;
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
		inline T* Create() const
		{
			return (T*)newOperator();
		}

		template<typename T>
		inline T* Create(const void* source) const
		{
			return (T*)copyConstructor(source);
		}

		inline void Set(void* dst, const void* src) const
		{
			if (setOperator)
				setOperator(dst, src);
		}

		inline void Delete(void* object) const
		{
			deleteOperator(object);
		}

		std::ostream& operator<<(std::ostream& stream) const
		{
			stream << "Type: ";

			streamOutFullName(stream);

			stream << '(' << hash << ')' << std::endl;

			if (bases.size() > 0)
			{
				stream << "Parents:" << std::endl;

				for (auto base : bases)
				{
					stream << '\t';

					base->streamOutFullName(stream);

					stream << std::endl;
				}
			}

			if (fields.size() > 0) 
			{
				stream << "Member fields:" << std::endl;

				for (auto& field : fields) 
				{
					stream << '\t';

					field.GetType()->streamOutFullName(stream);

					stream<< " : " << field.GetName() << std::endl;
				}
			}

			if (methods.size() > 0) 
			{
				stream << "Memder functions:" << std::endl;

				for (auto& method : methods) 
				{
					stream << '\t';

					method.GetReturnType()->streamOutFullName(stream);

					stream << ' ' << method.GetName() << '(';

					int i = 0;

					for (auto arg : method.GetArguments())
					{
						arg->streamOutFullName(stream);

						if (i + 1 < method.GetArguments().size())
							stream << ", ";

						i++;
					}

					stream << ')' << std::endl;
				}
			}

			return stream;
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

		void* (*newOperator)();
		void* (*copyConstructor)(const void*);
		void (*setOperator)(void*, const void*);
		void (*deleteOperator)(void*);

		unsigned int pointers;

		bool isConst;
		bool isReference;

		size_t size;
		size_t hash;
	private:
		void streamOutFullName(std::ostream& stream) const
		{
			if (isConst)
				stream << "const ";

			for (auto& namespaceVal : namespaces)
				stream << namespaceVal << "::";

			stream << name;

			if (templateValue.empty() == false)
				stream << '<' << templateValue << '>';

			if (isReference)
				stream << "& ";
		}
	};

	template<typename T>
	void* NewOperator()
	{
		if constexpr (std::is_void_v<T> or std::is_abstract_v<T>)
			return nullptr;
		else if constexpr (std::is_reference_v<T>)
			return NewOperator<std::remove_reference_t<T>>;
		else if constexpr (std::is_arithmetic_v<T>)
			return (void*)(new T(0));
		else
			return (void*)(new T);
	}

	template<typename T>
	void* CopyConstructor(const void* other)
	{
		if constexpr (std::is_void_v<T> or std::is_abstract_v<T>)
			return nullptr;
		else if constexpr (std::is_reference_v<T>)
			return CopyConstructor<std::remove_reference_t<T>>(other);
		else
			return (void*)(new T(*(T*)other));
	}

	template<typename T>
	void SetOperator(void* lhs, const void* rhs)
	{
		if constexpr (std::is_reference_v<T>)
			SetOperator<std::remove_reference_t<T>>(lhs, rhs);
		else if constexpr ((std::is_void_v<T> or std::is_abstract_v<T> or std::is_const_v<T>) == false)
			*(T*)lhs = *(T*)rhs;
	}

	template<typename T>
	void DeleteOperator(void* object) 
	{
		if constexpr (std::is_reference_v<T>)
			DeleteOperator<std::remove_reference_t<T>>(object);
		else if constexpr ((std::is_void_v<T> or std::is_abstract_v<T>) == false)
			delete (T*)object;
	}
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
