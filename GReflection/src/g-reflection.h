#pragma once

#include <cassert>

#include "meta/reflection-builder.h"
#include "macro/utils.h"

#define REGISTER_TYPE(typeName) \
const GR::MetaType* typeName::staticType = typeName::InitReflectionMeta();

#define MAKE_DECLTYPE_PREFIX(typeName, val) decltype(val)
#define MAKE_MEMBER_NAME(typeName, val) #val
#define MAKE_MEMBER_ARGUMENT(typeName, val) &typeName::val 

#define UNWRAP_ARGS(...) __VA_ARGS__

#define REGISTER_INHERITANCE(className, ...) \
	__VA_OPT__( type = GR::ReflectionBuilder::RegisterInheritance<className, __VA_ARGS__ >(); )

#define REFLECT_CLASS(className, inheritance, ...) \
private:\
	static const GR::MetaType* InitReflectionMeta() \
	{\
		static bool isRegistred = false; \
		assert(isRegistred == false); \
		\
		isRegistred = true; \
		\
		const GR::MetaType* type = GR::ReflectionBuilder::Reflect<className __VA_OPT__(,) FOR_EACH( MAKE_DECLTYPE_PREFIX, className, __VA_ARGS__ )> \
			( { FOR_EACH( MAKE_MEMBER_NAME, className, __VA_ARGS__ ) } __VA_OPT__(,) FOR_EACH( MAKE_MEMBER_ARGUMENT, className, __VA_ARGS__ ) ); \
		\
		REGISTER_INHERITANCE(className, UNWRAP_ARGS inheritance) \
		\
		return type;\
	}\
	\
	static const GR::MetaType* staticType;\
	const GR::MetaType* type = staticType;\
public:\
	static const GR::MetaType* GetStaticType()\
	{\
		return staticType;\
	}\
	\
	virtual const GR::MetaType* GetType() const\
	{\
		return type;\
	}

#define PrintMacro__(val) std::cout << #val << std::endl;
#define PrintMacro_(val) PrintMacro__( val )
#define PrintMacro(val) PrintMacro_( (val) )

#define REFLECT_FIELD(owner, field) GR::MetaField::Init<decltype(field)>(#field, offsetof(owner, field));
