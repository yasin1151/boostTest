#include <iostream>
#include <boost/scoped_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <string>
#include <thread>
#include <memory>

class demo{
public:
	~demo() { std::cout << "destructed" << std::endl; }
};

void fun(demo* d)
{
	std::cout << &d << std::endl;
}

void ps1(boost::shared_ptr<std::string> p)
{
	std::cout << p.get()->c_str() << std::endl;
}

void ps2(const boost::shared_ptr<std::string>& p)
{
	std::cout << p.get()->c_str() << std::endl;
}

void scoped_ptr_test()
{
	//boost::scoped_ptr<T>在析构函数中会对它存储的指针调用delete，
	//当抛出一个异常时，继续调用scoped_ptr的析构函数
	boost::scoped_ptr<demo> p(new demo);
	fun(p.get());

}


void shared_ptr_test()
{
	//shared_ptr中有一个原子引用计数器，
	//当他被复制是，引用器递增
	//而当调用它的析构函数时，引用计数递减。
	//当引用计数等于0时，对由shared_ptr指向的对象调用delete

	//shared_ptr 和 make_shared是c++11的一部分 它们在头文件<memory>中
	boost::shared_ptr<std::string> ps =
		boost::make_shared<std::string>("hello");

	std::thread(std::bind(&ps1, ps)).detach();
	std::thread(std::bind(&ps2, ps)).detach();
}


void scoped_array_test()
{
	//类似于scoped_ptr，不过在析构函数调用的是delete[]
	//不属于c++11
	boost::scoped_ptr<char> p(new char[10]);
}

void do_process(const char* data, std::size_t size)
{
	std::cout << data << std::endl;
}
 
void do_process_shared_prt(const boost::shared_ptr<char[]>& data, std::size_t size)
{
	do_process(data.get(), size);
}

void shared_array_test_1()
{
	int size = 255;
	const char* data = "hello wrold";
	boost::shared_ptr<char[]> data_cpy =
		boost::make_shared<char[]>(size);

	std::memcpy(data_cpy.get(), data, size);

	std::thread(std::bind(&do_process_shared_prt, data_cpy, size)).detach();
}

void do_process_shared_prt_2(const std::shared_ptr<char>& data, std::size_t size)
{
	do_process(data.get(), size);
}

void shared_array_test_2()
{
	//适用于c++11的版本
	int size = 255;
	const char* data = "hello wrold";
	std::shared_ptr<char> data_cpy(new char[size], std::default_delete< char [] >());

	std::memcpy(data_cpy.get(), data, size);

	std::thread(std::bind(&do_process_shared_prt_2, data_cpy, size)).detach();

}


int main()
{
	//scoped_ptr_test();
	//shared_ptr_test();
	//scoped_array_test();
	//shared_array_test_1();
	shared_array_test_2();
	while (1);
	return 0;
}