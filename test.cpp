#include"Date.h"

int main()
{
	Date d1(2021, 6, 7);
	std::cout <<"d1: " << d1<< std::endl;
	Date d3;
	Date d2 = d1;//这里调用的是拷贝构造函数，而非赋值函数重载
	//这里调用的才是赋值函数重载
	//因为赋值函数重载要有两个都已经创建好了的对象，而拷贝构造函数是创建一个新对象
	std::cout << "d2: " << d2 << std::endl;
	std::cout << "d3: " << d3 << std::endl;
	if (d1 > d3)
	{
		std::cout << "d1 > d3\n";
	}
	else
	{
		std::cout << "d1 <= d3\n";
	}
	
	int day = d3 - d1;
	std::cout << "d3 - d1 is " << day << "days\n";
	
	return 0;
}
