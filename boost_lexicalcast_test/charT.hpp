#ifndef _CHAR_T_HPP_
#define _CHAR_T_HPP_

#include <boost/lexical_cast.hpp>



//存储负数
class negative_number
{
public:
	explicit negative_number(unsigned short number)
		:number_(number) {}

	negative_number() {}

	unsigned short value_without_sign() const
	{
		return number_;
	}
private:
	unsigned short number_;
};


std::ostream& operator << (std::ostream& os, const negative_number& num)
{
	os << '-' << num.value_without_sign();
	return os;
}

std::istream& operator >>(std::istream& is, negative_number& num)
{
	char ch;
	is >> ch;
	if (ch != '-')
	{
		throw std::logic_error("negative_number class designed to store Only negative values");
	}

	unsigned short s;
	is >> s;

	num = negative_number(s);
	return is;
}

template <typename charT>
std::basic_ostream<charT>& operator << (std::basic_ostream<charT>& os,
	const negative_number& num)
{
	os << static_cast<charT>('-') << num.value_without_sign();
	return os;
}

template <typename charT>
std::basic_istream<charT>& operator >> (std::basic_istream<charT>& is,
	negative_number& num)
{
	charT ch;
	is >> ch;
	if (ch != static_cast<charT>('-'))
	{
		throw std::logic_error("类只能保存为负值");
	}
	unsigned short s;
	is >> s;
	num = negative_number(s);
	return is;
}

#endif