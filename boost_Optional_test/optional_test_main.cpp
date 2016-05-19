#include <boost/optional.hpp>
#include <iostream>
#include <stdlib.h>

class locked_device
{
public:
	~locked_device()
	{
		//释放设备锁
	}
	
	void use()
	{
		std::cout << " success " << std::endl;
	}

	static boost::optional<locked_device> try_lock_device()
	{
		if (rand() % 2)
		{
			//未能锁定设备
			return boost::none;
		}

		return locked_device("device name");
	}

private:
	explicit locked_device(const char* rhs)
	{
		std::cout << rhs <<"设备被锁定" << std::endl;
	}
};

int main()
{
	for (int i = 0; i < 10; i++)
	{
		boost::optional<locked_device> t = locked_device::try_lock_device();
		//opetinal可以转换成bool类型
		if (t)
		{
			t->use();
			return 0;
		}
		else
		{
			std::cout << "try again..." << std::endl;
		}
	}
	std::cout << "failed" << std::endl;

	return -1;
}