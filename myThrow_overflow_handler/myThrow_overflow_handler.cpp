#include <boost/numeric/conversion/cast.hpp>
#include <iostream>

template < typename SourceT, typename TargetT>
struct mythrow_overflow_handler
{
	void operator() (boost::numeric::range_check_result r)
	{
		if (r != boost::numeric::cInRange)
		{
			throw std::logic_error("Not in range");
		}
	}
};


template < typename TargetT, typename SourceT>
TargetT my_numerice_cast(const SourceT& in)
{
	using namespace boost;
	typedef numeric::conversion_traits<TargetT, SourceT>
		conv_traits;
	typedef numeric::numeric_cast_traits<TargetT, SourceT>
		cast_traits;
	typedef boost::numeric::converter
		<
		TargetT,
		SourceT,
		conv_traits,
		mythrow_overflow_handler<SourceT, TargetT>
		>
		converter;

	return converter::convert(in);
}


int main()
{
	try
	{
		my_numerice_cast<short>(100000);
	}
	catch (const std::logic_error& e)
	{
		std::cout << "It works!" << e.what() << std::endl;
	}
	return 0;
}