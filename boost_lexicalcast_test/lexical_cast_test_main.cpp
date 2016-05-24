#include <locale>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include "charT.hpp"


int main()
{
	//把字符串转换为整数
	int i = boost::lexical_cast<int>("100");
	std::cout << i << std::endl;

	//把数值转换为字符串
	std::string s = boost::lexical_cast<std::string>(101153145654565643);
	std::cout << s << std::endl;


	//和自定义类互相转换
	negative_number n = boost::lexical_cast<negative_number>("-100");
	std::cout << n << std::endl;

	int j = boost::lexical_cast<int>(n);
	std::cout << "j : " << j << std::endl;

	return 0;
}