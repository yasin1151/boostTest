#include <boost/variant.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

typedef boost::variant <int, float, std::string> cell_t;
typedef std::vector< cell_t > db_row_t;



//对值求和所需的代码
//如果我们的访客没有返回值
//可以提供无模板参数给boost::static_visitor<>
struct db_sum_visitor : public boost::static_visitor<double>
{
	double operator()(int value) const 
	{
		return value;
	}

	double operator()(float value) const
	{
		return value;
	}

	double operator()(const std::string&) const
	{
		return 0.0;
	}

};


int main()
{

	
	typedef boost::variant <int, float, std::string> my_var_t;

	std::vector<my_var_t> some_values;

	some_values.push_back(10);
	some_values.push_back((float)1.1);
	some_values.push_back(std::string("wow"));

	/*std::string& s = boost::get<std::string>(some_values.back());
	std::cout << s << std::endl;

	some_values.pop_back();
	float s2 = boost::get<float>(some_values.back());
	std::cout << s2 << std::endl;

	some_values.pop_back();
	int s3 = boost::get<int>(some_values.back());
	std::cout << s3 << std::endl;
	*/

	//变体没有空状态，但他有一个empty函数，它总返回false
	//如果确实需要表示一个空状态，可以在变体支持的类型的开始位置添加某个简单的类型
	//当变体包含该类型的时候，把他解释为一个空状态

	typedef boost::variant < boost::blank, int, const char*, std::string> my_var_t_2;
	

	//默认构造函数将构建一个boost::blank实例
	my_var_t_2 var;

	//which()方法将会返回一个变体持有的类型的索引
	assert(var.which() == 0);	//空状态

	var = "hello variant";

	assert(var.which() != 0);

	std::cout << boost::get<const char*>(var) << std::endl;
	
	//用下面这种方式，如果实际值不是const char*，则会返回一个NULL指针
	std::cout << boost::get<int>(&var) << std::endl;
	std::cout << boost::get<const char*>(&var) << std::endl;


	//数据库demo
	double res = 0.0;
	db_row_t::const_iterator it = some_values.begin();
	db_row_t::const_iterator end = some_values.end();

	for (; it != end; it++)
	{
		res += boost::apply_visitor(db_sum_visitor(), *it);
	}

	std::cout << "res:" << res << std::endl;

	return 0;

}