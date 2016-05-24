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
	//boost::scoped_ptr<T>�����������л�����洢��ָ�����delete��
	//���׳�һ���쳣ʱ����������scoped_ptr����������
	boost::scoped_ptr<demo> p(new demo);
	fun(p.get());

}


void shared_ptr_test()
{
	//shared_ptr����һ��ԭ�����ü�������
	//�����������ǣ�����������
	//��������������������ʱ�����ü����ݼ���
	//�����ü�������0ʱ������shared_ptrָ��Ķ������delete

	//shared_ptr �� make_shared��c++11��һ���� ������ͷ�ļ�<memory>��
	boost::shared_ptr<std::string> ps =
		boost::make_shared<std::string>("hello");

	std::thread(std::bind(&ps1, ps)).detach();
	std::thread(std::bind(&ps2, ps)).detach();
}


void scoped_array_test()
{
	//������scoped_ptr�������������������õ���delete[]
	//������c++11
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
	//������c++11�İ汾
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