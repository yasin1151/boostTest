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
		boost::spirit�����嶯��д��[]���棬�������ǿ���ʹ�ú���ָ�롢
		��������boost::bind��std::bind��������bind����ʵ��
		����lambda������д

		ushort_ [ [&res](unsigned short s) (res.year = s;)]
		�ȼ���
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
	�޸İ汾���Ա���Դ������ֵļ���
*/
date parse_date_timel_2(const std::string& s)
{
	using boost::spirit::qi::_1;
	using boost::spirit::qi::uint_parser;
	using boost::spirit::qi::char_;
	using boost::phoenix::ref;


	//ʹ�� unsigned short ��Ϊ�������, ��Ҫʮ���ƣ����õ�2λ��2λ������
	uint_parser< unsigned short, 10, 2, 2> u2_;

	//ʹ�� unsigned short ��Ϊ�������, ��Ҫʮ���ƣ����õ�4λ��4λ������
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
	//spirit ���﷨�� ��չ�Ϳ�˹��ʽ(Extended Backus-Naur Form, EBNF)�ǳ��ӽ�
	date d = parse_date_timel("2016-05-23");
	std::cout << d.year << " " << d.month << " " << d.day << std::endl;

	dateTime demo = parse_dataTime_plus("2016-05-23T19:14:00Z");
	std::cout << demo.getYear() << " "
		<< demo.getMonth() << " "
		<< demo.getDay() << " "
		<< demo.getHours() << " "
		<< demo.getMin() << " "
		<< demo.getSec() << std::endl;
	//����spirit����ܽ�������Ϊ�京���Ӵ��ģ��ʵ��
	return 0;
}