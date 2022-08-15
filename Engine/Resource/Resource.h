#pragma once
#include <string>

namespace gooblegorb
{
	class Resource
	{
	public:
		//virtual bool Create(const std::string& name, void* data = nullptr) = 0;

		virtual bool Create(std::string name, ...) = 0;
	};
}

//int* -> address
//font* -> address

//void* vo = &i; -> address (type ???)
