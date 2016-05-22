#include <algorithm>
#include <boost/bind.hpp>
#include <functional>
#include <boost/array.hpp>
#include <iostream>
#include <boost/ref.hpp>


void wierd_appender(std::string& to, const std::string& from)
{
	to += from;
}

int main()
{
	/*test1*/
	boost::array<int, 12> values = { 1,2,3,4,5,6,7,8,9,19,111,200 };

	//找出比5大的值
	std::size_t count0 = std::count_if(values.begin(), values.end(), std::bind1st(std::less<int>(), 5));
	std::cout << count0 << std::endl;

	std::size_t count1 = std::count_if(values.begin(), values.end(), boost::bind(std::less<int>(), 5, _1));
	std::cout << count1 << std::endl;
		
	
	//对空字符串计数方法
	boost::array<std::string, 3> str_values = { "We ", "", "the super" };

	std::size_t count2 = std::count_if(str_values.begin(), str_values.end(), std::mem_fun_ref(&std::string::empty));
	std::cout << count2 << std::endl;

	std::size_t count3 = std::count_if(str_values.begin(), str_values.end(), boost::bind(&std::string::empty, _1));
	std::cout << count3 << std::endl;


	//统计长度小于5的字符串
	std::size_t count4 = std::count_if(str_values.begin(), str_values.end(), boost::bind(std::less<std::size_t>(), boost::bind(&std::string::size, _1), 5));
	std::cout << count4 << std::endl;

	//用于字符串连接
	std::string result;
	std::for_each(str_values.rbegin(), str_values.rend(), boost::bind(&wierd_appender, boost::ref(result), _1));
	std::cout << result.c_str() << std::endl;

	return 0;

}
