#include <locale>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include "charT.hpp"


int main()
{
	//���ַ���ת��Ϊ����
	int i = boost::lexical_cast<int>("100");
	std::cout << i << std::endl;

	//����ֵת��Ϊ�ַ���
	std::string s = boost::lexical_cast<std::string>(101153145654565643);
	std::cout << s << std::endl;


	//���Զ����໥��ת��
	negative_number n = boost::lexical_cast<negative_number>("-100");
	std::cout << n << std::endl;

	int j = boost::lexical_cast<int>(n);
	std::cout << "j : " << j << std::endl;

	return 0;
}