#include <boost/array.hpp>
#include <algorithm>
#include <array>
/*
	性能与标准c数组相差无几
	已经被加入c++11标准中
	<array>
*/

//typedef boost::array<char, 4> array4_t;
//array4_t& vector_advance(array4_t& val);

//等价于 char ( &vector_advance( char (&var)[4] ) )[4];W


//对值增加1的函数化对象
struct add_1 : public std::unary_function<char, void>
{
	void operator() (char& c) const
	{
		c++;
	}

};


typedef boost::array<char, 4> array4_t;
array4_t& vector_advance(array4_t& val)
{
	std::for_each(val.begin(), val.end(), add_1());
	return val;
}


int main()
{
	//在c++11中，初始化boost::array可以像初始化一个数组一般
	//array4_t = {0,1,2,3};，c++03 : arrary4_t = {{0,1,2,3}}
	array4_t val = { 0,1,2,3 };

	//boost::array 的用途就像一个平常的数组
	array4_t val_res; //如果值类型支持默认的构造函数和赋值
	val_res = vector_advance(val);	//可以被默认构造，并且是可以赋值的

	assert(val.size() == 4);
	assert(val[0] == 1);

	assert(sizeof(val) == sizeof(char) * array4_t::static_size);

	return 0;
}