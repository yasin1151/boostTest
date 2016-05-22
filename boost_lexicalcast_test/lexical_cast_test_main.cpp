#include <locale>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>

int main()
{
	//���ַ���ת��Ϊ����
	int i = boost::lexical_cast<int>("100");
	std::cout << i << std::endl;

	//����ֵת��Ϊ�ַ���
	std::string s = boost::lexical_cast<std::string>(101153145654565643);
	std::cout << s << std::endl;



	return 0;
}