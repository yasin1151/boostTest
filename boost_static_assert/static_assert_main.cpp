#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/array.hpp>

template <typename T, std::size_t BufSizeV>
void serialize(const T& value, boost::array<unsigned char, BufSizeV>& buffer)
{
	BOOST_STATIC_ASSERT(BufSizeV >= sizeof(value));
	BOOST_STATIC_ASSERT(boost::is_pos<T>::value);
	std::memcpy(&buffer[0], &value, sizeof(value));
}

int main()
{

	return 0;
}