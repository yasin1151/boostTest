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
			//Ϊ���ڳ�Ա�����в�׽��������ʹ���������this_
			std::fclose(f);
		}BOOST_SCOPE_EXIT_END
	}
};

int main()
{
	std::FILE* f = std::fopen("exp.txt", "w+");

	BOOST_SCOPE_EXIT(f) 
	{
		//���۷���ʲô������ִ����δ���
		std::fclose(f);
	}BOOST_SCOPE_EXIT_END

	//scope_exit�ⲻ�ڶ��Ϸ����κζ�����ڴ棬���Ҳ�ʹ���麯��
}