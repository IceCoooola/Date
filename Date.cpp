#include"Date.h"

//因为会频繁调用这个函数，所以设置为inline，inline函数会在调用的地方展开，减少堆栈
// 获取某年某月的天数
inline int Date::GetMonthDay(int year, int month)
{

	//设一个数组，给第一个置空，这样每个数组的下标都会对应当月的天数
	//设数组为static，因为频繁调用每次都创建销毁影响性能，static生命周期延长
	static int arr[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int day = arr[month];
	//检查2月是否为闰年
	if (month == 2)
	{
		//如果是闰年就是29天
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			day = 29;
		}
	}
	return day;
}

// 全缺省的构造函数
Date::Date(int year, int month, int day)
{
	//检查合法性
	if (year > 0 &&
		month > 0 &&
		month < 13
		&& day <= GetMonthDay(year, month))
	{
		_year = year;
		_month = month;
		_day = day;
	}
	else
	{
		std::cout << "invalid date!\n";
		assert(false);
		//此处严格用法应该用throw
	}
}

// 拷贝构造函数

// d2(d1)
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

// 赋值运算符重载

// d2 = d3 -> d2.operator=(&d2, d3)
Date& Date::operator=(const Date& d)
{
	//检查是否自己赋值给自己
	if (this != &d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	//因为退出函数时，对象不会销毁
	//返回*this指针，以便连续赋值
	return *this;
}

// 析构函数
Date::~Date()
{
	//这里完成函数清理工作，由于这个函数没有需要清理的故不写析构函数也没有问题
	;
}

// 日期+=天数
Date& Date::operator+=(int day)
{
	//检查日期是为正数
	if (day >= 0)
	{
		_day += day;
		while (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			_month++;
			if (_month > 12)
			{
				_year++;
				_month = 1;
			}
		}
	}
	//如果为负数那就走-=
	else
	{
		*this -= abs(day);
	}
	return *this;
}

// 日期+天数
Date Date::operator+(int day)
{
	Date temp = *this;
	temp += day;
	return temp;
}

// 日期-天数
Date Date::operator-(int day)
{
	Date temp = *this;
	temp -= day;
	return temp;
}

// 日期-=天数
Date& Date::operator-=(int day)
{
	//检查天数是否是正数
	if (day >= 0)
	{
		_day -= day;
		while (_day <= 0)
		{
			_month--;
			_day += GetMonthDay(_year, _month);
			if (_month <= 0)
			{
				_year--;
				_month = 12;
			}
		}
	}
	//如果为负数那就走+=
	else
	{
		*this += abs(day);
	}
	return *this;
}

// 前置++
Date& Date::operator++()
{
	*this += 1;
	return *this;
}

// 后置++
Date Date::operator++(int)
{
	Date temp = *this;
	*this += 1;
	return temp;
}

// 后置--
Date Date::operator--(int)
{
	Date temp = *this;
	*this -= 1;
	return temp;
}

// 前置--
Date& Date::operator--()
{
	*this -= 1;
	return *this;
}

// >运算符重载
bool Date::operator>(const Date& d)
{
	if (_year > d._year)
	{
		return true;
	}
	else if (_year < d._year)
	{
		return false;
	}
	else
	{
		if (_month > d._month)
		{
			return true;
		}
		else if (_month < d._month)
		{
			return false;
		}
		else
		{
			if(_day > d._day)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	
}

// ==运算符重载
bool Date::operator==(const Date& d)
{
	if (_year == d._year && _month == d._month && _day == d._day)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// >=运算符重载
bool Date::operator >= (const Date& d)
{
	return *this > d || *this == d;
}

// <运算符重载
bool Date::operator < (const Date& d)
{
	return !(*this >= d);
}

// <=运算符重载
bool Date::operator <= (const Date& d)
{
	return !(*this > d);
}

// !=运算符重载
bool Date::operator != (const Date& d)
{
	return !(*this == d);
}

// 日期-日期 返回天数
// size_t Date::operator-(const Date& d)
// {
// 	size_t countDay1 = 0;
// 	size_t countDay2 = 0;
// 	for (int i = 1; i < _year; i++)
// 	{
// 		countDay1 += GetYearDay(i);
// 	}
// 	for (int i = 1; i < _month; i++)
// 	{
// 		countDay1 += GetMonthDay(_year, i);
// 	}
// 	countDay1 += _day;
// 	for (int i = 1; i < d._year; i++)
// 	{
// 		countDay2 += GetYearDay(i);
// 	}
// 	for (int i = 1; i < d._month; i++)
// 	{
// 		countDay2 += GetMonthDay(d._year, i);
// 	}
// 	countDay2 += d._day;
// 	return countDay1 - countDay2;
// }
// 日期-日期 返回天数
size_t Date::operator-(const Date& d)
{
	Date min = *this;
	Date max = d;
	int flag = 1;
	if (min > max)
	{
		min = d;
		max = *this;
		flag = -1;
	}
	int day = 0;
	while (min != max)
	{
		min++;
		day++;
	}
	
	return day * flag;
}

std::ostream& operator<<(std::ostream& os,const Date& d)
{
	os << d._year << "-" << d._month << "-" << d._day;
	return os;
}
