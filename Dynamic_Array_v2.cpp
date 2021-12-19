#include <iostream>
#include "List.h"

int main()
{
	List <std::string> list1;
	for (int i = 0; i < 6; ++i)
	{
		list1.insert("hello");
		list1.insert("wo");
	}

	for (auto it = list1.iterator(); it.hasNext(); it.next())
	{
		std::cout << it.get() << std::endl;
	}

	std::cout << "-------" << std::endl;

	for (auto it1 = list1.reverseIterator(); it1.hasNext(); it1.next())
	{
		std::cout << it1.get() << std::endl;
	}

	std::cout << "-------" << std::endl;
	return 0;
}
