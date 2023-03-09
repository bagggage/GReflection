#pragma once

#include <unordered_map>
#include <iostream>
#include <string>
#include <type_traits>
#include <cstdarg> 

#include "meta-type.h"

namespace GR 
{
	bool isReflectionBuilderInitializedStatic = false;

	class ReflectionBuilder
	{
	public:
		template<typename T, typename... Members>
		static const MetaType* Reflect(std::vector<const char*> memberNames, ...)
		{
			GetDynamicType<T>();

			int i = 0;

			va_list args;
			va_start(args, memberNames);

			(
				(ReflectMember(std::string(memberNames[i++]), va_arg(args, Members T::*)))
				,... 
			);

			va_end(args);

			return &types[typeid(T).hash_code()];
		}

		template <typename T>
		static const MetaType* RegisterType()
		{
			MetaType type;

			std::string rawTypeName = std::string(GetTypeName<T>());

			type.templateValue = GetTemplateValue(rawTypeName);
			type.namespaces = GetTypeNamespaces(rawTypeName);
			type.name = rawTypeName;
			type.pointers = std::count(rawTypeName.begin(), rawTypeName.end(), '*');

			if constexpr (std::is_void_v<T>)
				type.size = 0;
			else
				type.size = sizeof(T);

			type.hash = std::hash<MetaType>{}(type);

			types.insert(std::pair(typeid(T).hash_code(), type));

			return &types[typeid(T).hash_code()];
		}

		template<typename T, typename... Bases>
		static const MetaType* RegisterInheritance() 
		{
			((AssertIsBase<T, Bases>()), ...);

			MetaType* type = GetDynamicType<T>();

			((type->bases.push_back(GetDynamicType<Bases>())), ...);

			return type;
		}

		template <typename T>
		static const MetaType* GetType()
		{
			return GetDynamicType<T>();
		}

		template<typename T>
		static bool IsEquals(const MetaType* type) 
		{
			return (type == &types[typeid(T).hash_code()]);
		}

		static void Destroy() 
		{
			types.clear();
		}
	private:
		static std::unordered_map<size_t, MetaType> types;

		template<typename T, typename Base>
		static void AssertIsBase() 
		{
			static_assert(std::is_base_of_v<Base, T>);
		}

		template<typename Return, typename Owner, typename... Args>
		static void ReflectMemberFunction(const std::string& name, Return (Owner::*member)(Args...)) 
		{
			MetaType* ownerType = GetDynamicType<Owner>();

			ownerType->methods.push_back(MetaMethod());
			
			MetaMethod& method = ownerType->methods.back();

			method.name = name;
			method.returnType = GetDynamicType<Return>();
			(method.arguments.push_back(GetDynamicType<Args>()), ...);
			
			method.pointerSize = sizeof(Return(Owner::*)(Args...));
			method.pointer = std::malloc(method.pointerSize);

			*(decltype(member)*)method.pointer = member;
		}

		template<typename Type, typename Owner>
		static void ReflectField(const std::string& name, Type Owner::*member)
		{
			MetaType* ownerType = GetDynamicType<Owner>();

			ownerType->fields.push_back(MetaField());

			MetaField& field = ownerType->fields.back();

			field.name = name;
			field.offset = ((char*)&((Owner*)nullptr->*member) - (char*)nullptr);
			field.type = GetDynamicType<Type>();
		}

		template <typename T>
		static MetaType* GetDynamicType()
		{
			if (isReflectionBuilderInitializedStatic == false)
			{
				types = std::unordered_map<size_t, MetaType>();
				isReflectionBuilderInitializedStatic = true;
			}

			if (types.count(typeid(T).hash_code()) == 0)
				RegisterType<T>();

			return &types[typeid(T).hash_code()];
		}

		static std::string GetTemplateValue(std::string& rawTypeName)
		{
			size_t templateStart = rawTypeName.find_first_of('<');

			if (templateStart == std::string::npos)
				return std::string();

			size_t templateEnd = rawTypeName.find_last_of('>');

			std::string result = rawTypeName.substr(templateStart + 1, templateEnd - templateStart - 1);

			rawTypeName.erase(rawTypeName.begin() + templateStart, rawTypeName.end());

			return result;
		}

		static std::vector<std::string> GetTypeNamespaces(std::string& typeName) 
		{
			std::vector<std::string> namespaces;

			size_t namespaceDivider = 0;
			size_t offset = 0;

			while ((namespaceDivider = typeName.find("::", offset)) != std::string_view::npos)
			{
				namespaces.push_back(typeName.substr(offset, namespaceDivider - offset));

				offset = namespaceDivider + 2;
			}

			if (offset != 0)
				typeName.erase(typeName.begin(), typeName.begin() + offset);

			return namespaces;
		}

		template<typename Owner, typename Member>
		static void ReflectMember(const std::string& name, Member Owner::*member) 
		{
			if constexpr (std::is_member_function_pointer_v<decltype(member)>)
				ReflectMemberFunction(name, member);
			else
				ReflectField(name, member);
		}

		template<typename T>
		static constexpr auto GetTypeName() -> std::string_view
		{
#if defined(__clang__)
			constexpr auto prefix = std::string_view{ "[T = " };
			constexpr auto suffix = "]";
			constexpr auto function = std::string_view{ __PRETTY_FUNCTION__ };
#elif defined(__GNUC__)
			constexpr auto prefix = std::string_view{ "with T = " };
			constexpr auto suffix = "; ";
			constexpr auto function = std::string_view{ __PRETTY_FUNCTION__ };
#elif defined(_MSC_VER)
			constexpr auto prefix = std::string_view{ "GetTypeName<" };
			constexpr auto suffix = ">(void)";
			constexpr auto function = std::string_view{ __FUNCSIG__ };
#else
# error Unsupported compiler
#endif
			constexpr auto start = function.find(prefix) + prefix.size();
			constexpr auto end = function.find(suffix);
			constexpr auto size = end - start;

#if defined(_MSC_VER)
			constexpr auto classPrefix = function.find("class", start);
			constexpr auto structPrefix = function.find("struct", start);
			constexpr auto enumPrefix = function.find("enum", start);
			constexpr auto unionPrefix = function.find("union", start);

			if (classPrefix != std::string_view::npos)
				return function.substr(start + sizeof("class"), size - sizeof("class"));
			else if (structPrefix != std::string_view::npos)
				return function.substr(start + sizeof("struct"), size - sizeof("struct"));
			else if (enumPrefix != std::string_view::npos)
				return function.substr(start + sizeof("enum"), size - sizeof("enum"));
			else if (unionPrefix != std::string_view::npos)
				return function.substr(start + sizeof("union"), size - sizeof("union"));
#endif

			return function.substr(start, size);
		}
	};

	template<typename T>
	bool MetaType::IsEquals() const
	{
		return GR::ReflectionBuilder::IsEquals<T>(this);
	}

	std::unordered_map<size_t, MetaType> ReflectionBuilder::types = isReflectionBuilderInitializedStatic ? types : std::unordered_map<size_t, MetaType>();
}
