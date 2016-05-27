#include <boost/scope_exit.hpp>
#include <fstream>


class demo
{
public:
	void exp()
	{
		std::FILE* f = std::fopen("exp.txt", "w+");

		BOOST_SCOPE_EXIT(f, this_)
		{
			//为了在成员函数中捕捉他，我们使用特殊符号this_
			std::fclose(f);
		}BOOST_SCOPE_EXIT_END
	}
};

int main()
{
	std::FILE* f = std::fopen("exp.txt", "w+");

	BOOST_SCOPE_EXIT(f) 
	{
		//无论发生什么，都会执行这段代码
		std::fclose(f);
	}BOOST_SCOPE_EXIT_END

	//scope_exit库不在堆上分配任何额外的内存，并且不使用虚函数
}