#include <boost/variant.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

typedef boost::variant <int, float, std::string> cell_t;
typedef std::vector< cell_t > db_row_t;



//��ֵ�������Ĵ���
//������ǵķÿ�û�з���ֵ
//�����ṩ��ģ�������boost::static_visitor<>
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

	//����û�п�״̬��������һ��empty���������ܷ���false
	//���ȷʵ��Ҫ��ʾһ����״̬�������ڱ���֧�ֵ����͵Ŀ�ʼλ�����ĳ���򵥵�����
	//��������������͵�ʱ�򣬰�������Ϊһ����״̬

	typedef boost::variant < boost::blank, int, const char*, std::string> my_var_t_2;
	

	//Ĭ�Ϲ��캯��������һ��boost::blankʵ��
	my_var_t_2 var;

	//which()�������᷵��һ��������е����͵�����
	assert(var.which() == 0);	//��״̬

	var = "hello variant";

	assert(var.which() != 0);

	std::cout << boost::get<const char*>(var) << std::endl;
	
	//���������ַ�ʽ�����ʵ��ֵ����const char*����᷵��һ��NULLָ��
	std::cout << boost::get<int>(&var) << std::endl;
	std::cout << boost::get<const char*>(&var) << std::endl;


	//���ݿ�demo
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