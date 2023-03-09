#include <iostream>
#include <meta/reflection-builder.h>
#include <g-reflection.h>
#include <vector>

static const int b = 0.2f;

static int Draw() { return 0;  }

enum Five 
{
	F1,
	F2
};

enum class FiveClass
{
	g,
	b
};

namespace Some
{
	class Forward
	{
		REFLECT_CLASS(Forward, ())
	};

	class Test : public Forward
	{
	private:
		float speed;
	public:
		int a;
		int b;
		std::string c;

		int someMethod(float a, float b) 
		{
			std::cout << a << " called!!! " << b << std::endl;

			return a;
		}

		REFLECT_CLASS(Test, (Forward), speed, a, b, c, someMethod)
	};

	REGISTER_TYPE(Forward)
	REGISTER_TYPE(Test)
}

union MyUnion
{

};

using namespace Some;

int main()
{
	/*auto someMPtr = &Test::someMethod;
	void* ptr = new decltype(&Test::someMethod);

	std::memcpy(ptr, &someMPtr, sizeof(someMPtr));

	Test s;

	auto fieldPtr = &Test::a;
	auto fieldPtr2 = &Test::b;

	std::cout << *(void**)&fieldPtr << std::endl;
	std::cout << *(void**)&fieldPtr2 << std::endl;

	(s.*someMPtr)();
	(s.**((float(Test::**)(void))ptr))();*/

	std::cout << Test::GetStaticType()->GetName();

	for (int i = 0; i < Test::GetStaticType()->GetBases().size(); i++)
		std::cout << " : " << Test::GetStaticType()->GetBases()[i]->GetName() << std::endl;

	std::cout << std::endl;

	for (int i = 0; i < Test::GetStaticType()->GetFields().size(); i++)
		std::cout << "field: " << Test::GetStaticType()->GetFields()[i].GetType()->GetName() << ' ' << Test::GetStaticType()->GetFields()[i].GetType()->GetHash() << ' ' << Test::GetStaticType()->GetFields()[i].GetName() << std::endl;

	auto methods = Test::GetStaticType()->GetMethods();

	for (int i = 0; i < methods.size(); i++)
	{
		std::cout << "method: " << methods[i].GetReturnType()->GetName() << ' ' << methods[i].GetName() << std::endl;

		for (int j = 0; j < methods[i].GetArguments().size(); j++)
			std::cout << '\t' << methods[i].GetArguments()[j]->GetName() << ' ' << methods[i].GetArguments()[j]->GetHash() << std::endl;
	}

	Test a;

	a.a = 10;
	a.c = "Reflection!!!";

	std::cout << a.GetType()->GetFields()[3].GetValue<std::string>(&a) << std::endl;

	a.GetStaticType()->GetMethods()[0].Invoke<void>(&a, 615165.f, 67.f);
	a.GetStaticType()->GetFields()[0].SetValue(&a, 15.0101f);
	a.GetStaticType()->GetMethods()[0].Invoke<void>(&a, a.GetStaticType()->GetFields()[0].GetValue<float>(&a), 45.545f);

	//PrintMacro(REFLECT_CLASS(Test, a, b, c));

	return 0;
}
