#pragma once

#include <string>

namespace GR 
{
	struct MetaName 
	{
	public:
		inline const std::string& GetName() const
		{
			return name;
		}
	protected:
		std::string name;
	};
}
