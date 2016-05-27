#include <iostream>
#include <boost/ptr_container/ptr_set.hpp>

class demo
{
private:
	int mVal;
public:
	demo(int val = 0) :mVal(val) {}
	~demo() { std::cout << "destructed " << mVal<< std::endl; }
	friend bool operator < (const demo& lhs, const demo& rhs);
};

bool operator < (const demo& lhs, const demo& rhs)
{
	return lhs.mVal < rhs.mVal;
}




void test1()
{
	/*
	boost::ptr_set<int> s;
	s.insert(new int(1));
	s.insert(new int(2));
	*/
	boost::ptr_set<demo> s;
	s.insert(new demo(2));
	s.insert(new demo(1));
	s.insert(new demo(2));
	//资源会被容器本身所释放
}

int main()
{
	test1();
}