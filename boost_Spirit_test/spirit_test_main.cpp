#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <iostream>
#include <string>
#include "myParseTool.hpp"

struct date
{
	unsigned short year;
	unsigned short month;
	unsigned short day;
};

date parse_date_timel(const std::string& s)
{
	using boost::spirit::qi::_1;
	using boost::spirit::qi::ushort_;
	using boost::spirit::qi::char_;
	using boost::phoenix::ref;
	
	date res;
	const char* first = s.data();
	const char* const end = first + s.size();
	
	/*
		boost::spirit的语义动作写在[]里面，并且他们可以使用函数指针、
		函数对象、boost::bind、std::bind或是其他bind（）实现
		或是lambda函数编写

		ushort_ [ [&res](unsigned short s) (res.year = s;)]
		等价于
		ushort_ [ ref(res.month) = _1 ]
	
	*/

	bool success = boost::spirit::qi::parse(first, end,
		ushort_[ ref(res.year) = _1 ] >> char_('-')
		>> ushort_[ ref(res.month) = _1 ] >> char_('-')
		>> ushort_[ ref(res.day) = _1 ]);
		//*/

	/*
	bool success = boost::spirit::qi::parse(first, end,
		ushort_>>char_('-')>>ushort_>>char_('-')>>ushort_);
	//*/
	if (!success || first != end)
	{
		throw std::logic_error("Parsing failed");
	}

	return res;
}

/*
	修改版本，以便可以处理数字的计数
*/
date parse_date_timel_2(const std::string& s)
{
	using boost::spirit::qi::_1;
	using boost::spirit::qi::uint_parser;
	using boost::spirit::qi::char_;
	using boost::phoenix::ref;


	//使用 unsigned short 作为输出类型, 需要十进制，并用到2位到2位的数字
	uint_parser< unsigned short, 10, 2, 2> u2_;

	//使用 unsigned short 作为输出类型, 需要十进制，并用到4位到4位的数字
	uint_parser< unsigned short, 10, 4, 4> u4_;

	date res = {};
	const char* first = s.data();
	const char* const end = first + s.size();

	bool success = boost::spirit::qi::parse(first, end,
		u4_ [ ref(res.year) = _1 ] >> char_('-')
		>> u2_ [ ref(res.month) = _1 ] >> char_('-')
		>> u2_ [ ref(res.day) = _1 ]);

	if (!success || first != end)
	{
		throw std::logic_error("parse failed");
	}

	return res;

}

int main()
{
	//spirit 的语法和 扩展巴科斯范式(Extended Backus-Naur Form, EBNF)非常接近
	date d = parse_date_timel("2016-05-23");
	std::cout << d.year << " " << d.month << " " << d.day << std::endl;

	dateTime demo = parse_dataTime_plus("2016-05-23T19:14:00Z");
	std::cout << demo.getYear() << " "
		<< demo.getMonth() << " "
		<< demo.getDay() << " "
		<< demo.getHours() << " "
		<< demo.getMin() << " "
		<< demo.getSec() << std::endl;
	//编译spirit库可能较慢，因为其含有庞大的模板实例
	return 0;
}