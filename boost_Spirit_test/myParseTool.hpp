#ifndef _MY_PARSE_TOOL_H_
#define _MY_PARSE_TOOL_H_

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>


struct dateTime
{
	enum zone_offsets_t
	{
		OFFSET_NOT_SET,
		OFFSET_Z,
		OFFSET_UTC_PLUS,
		OFFSET_UTC_MINUS
	};

private:
	typedef unsigned short uShort;
	uShort year_;
	uShort month_;
	uShort day_;
	uShort hours_;
	uShort minutes_;
	uShort seconds_;
	zone_offsets_t zone_offset_type_;
	uShort zone_offset_in_min_;

	static void dt_assert(bool v, const char* msg)
	{
		if (!v)
		{
			throw std::logic_error("Assertion failes: " + std::string(msg));
		}
	}

public:
	dateTime()
		:year_(0),month_(0),day_(0),
		hours_(0),minutes_(0),seconds_(0),
		zone_offset_type_(OFFSET_NOT_SET),
		zone_offset_in_min_(0)
	{}

	uShort getYear() { return year_; }
	uShort getMonth() { return month_; }
	uShort getDay() { return day_; }
	uShort getHours() { return hours_; }
	uShort getMin() { return minutes_; }
	uShort getSec() { return seconds_; }
	zone_offsets_t getType() {return zone_offset_type_;}
	uShort getOffsetMin() { return zone_offset_in_min_; }

	void set_zone_offset_type(zone_offsets_t type) { zone_offset_type_ = type; }
	void set_zone_offset_in_min(unsigned short offset_min) { zone_offset_in_min_ = offset_min; }
	void setYear(uShort year) { year_ = year; }
	void setMonth(uShort mon) { month_ = mon; }
	void setDay(uShort day) { day_ = day; }
	void setHours(uShort hours) { hours_ = hours; }
	void setMin(uShort min) { minutes_ = min; }
	void setSec(uShort sec) { seconds_ = sec; }

};

void set_zone_offset(dateTime& dt, char sign, unsigned short hours, unsigned short minutes)
{
	dt.set_zone_offset_type(sign == '+' ? dateTime::OFFSET_UTC_PLUS : dateTime::OFFSET_UTC_MINUS);
	dt.set_zone_offset_in_min(hours * 60 + minutes);
}


dateTime parse_dataTime_plus(const std::string& s)
{
	using boost::spirit::qi::_1;
	using boost::spirit::qi::_2;
	using boost::spirit::qi::_3;
	using boost::spirit::qi::uint_parser;
	using boost::spirit::qi::char_;
	using boost::phoenix::bind;
	using boost::phoenix::ref;


	dateTime ret;

	uint_parser < unsigned int, 10, 2, 2> u2_;
	uint_parser < unsigned int, 10, 4, 4> u4_;

	/*
		格式
		2016-05-23T19:12:00Z
		2016-05-23T19:12:00+09:15
	*/

	boost::spirit::qi::rule<const char*, void()> timezone_parser
		= -(//一元减号表示可选规则
			//零偏移
			char_('Z')[bind(&dateTime::set_zone_offset_type,
				&ret, dateTime::OFFSET_Z)]
			| //指定时区偏移量
			((char_('+') | char_('-')) >> u2_ >> ":" >> u2_)[
				bind(&set_zone_offset, ref(ret), _1, _2, _3)]
			);

	boost::spirit::qi::rule<const char*, void()> date_parser =
		u4_[bind(&dateTime::setYear, &ret, _1)] >> char_('-')
		>> u2_[bind(&dateTime::setMonth, &ret, _1)] >> char('-')
		>> u2_[bind(&dateTime::setDay, &ret, _1)];

	boost::spirit::qi::rule<const char*, void()> time_parser =
		u2_[bind(&dateTime::setHours, &ret, _1)] >> char_(':')
		>> u2_[bind(&dateTime::setMin, &ret, _1)] >> char_(':')
		>> u2_[bind(&dateTime::setSec, &ret, _1)];

	const char* first = s.data();
	const char* const end = first + s.size();

	bool success = boost::spirit::qi::parse(first, end,
		((date_parser >> char_('T') >> time_parser) | date_parser | time_parser)
		>> timezone_parser);

	if(!success || first != end)
	{
		throw std::logic_error("parser of '" + s + "' failed");
	}

	return ret;
}




#endif
