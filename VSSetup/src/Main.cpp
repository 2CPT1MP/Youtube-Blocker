#include <iostream>

int main()
{
	
	char i = 0;
	for ( ; ;)
	{
		if (i >= 5)
			break;
		std::cout << "Hello World!" << std::endl;
		i++;
	}

	while (i < 10)
	{
		std::cout << "Hello World!" << std::endl;
		i++;
	}

	std::cin.get();
	return 0;
}