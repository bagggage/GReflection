#include "reflection-builder.h"

using namespace GR;

bool isReflectionBuilderInitializedStatic = false;

bool GR::IsReflectionBuilderInitializedStatic() 
{
	return isReflectionBuilderInitializedStatic;
}

void GR::SetIsReflectionBuilderInitializedStatic(bool value) 
{
	isReflectionBuilderInitializedStatic = value;
}

std::unordered_map<size_t, MetaType>& GR::ReflectionBuilder::GetTypes()
{
	static std::unordered_map<size_t, MetaType> types;

	return types;
}

std::unordered_map<size_t, MetaFunction>& GR::ReflectionBuilder::GetFunctions()
{
	static std::unordered_map<size_t, MetaFunction> functions;

	return functions;
}

//std::unordered_map<size_t, MetaType> ReflectionBuilder::types = isReflectionBuilderInitializedStatic ? types : std::unordered_map<size_t, MetaType>();
//std::unordered_map<size_t, MetaFunction> ReflectionBuilder::functions = isReflectionBuilderInitializedStatic ? functions : std::unordered_map<size_t, MetaFunction>();
