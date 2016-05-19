#include <boost/array.hpp>
#include <algorithm>
#include <array>
/*
	�������׼c��������޼�
	�Ѿ�������c++11��׼��
	<array>
*/

//typedef boost::array<char, 4> array4_t;
//array4_t& vector_advance(array4_t& val);

//�ȼ��� char ( &vector_advance( char (&var)[4] ) )[4];W


//��ֵ����1�ĺ���������
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
	//��c++11�У���ʼ��boost::array�������ʼ��һ������һ��
	//array4_t = {0,1,2,3};��c++03 : arrary4_t = {{0,1,2,3}}
	array4_t val = { 0,1,2,3 };

	//boost::array ����;����һ��ƽ��������
	array4_t val_res; //���ֵ����֧��Ĭ�ϵĹ��캯���͸�ֵ
	val_res = vector_advance(val);	//���Ա�Ĭ�Ϲ��죬�����ǿ��Ը�ֵ��

	assert(val.size() == 4);
	assert(val[0] == 1);

	assert(sizeof(val) == sizeof(char) * array4_t::static_size);

	return 0;
}