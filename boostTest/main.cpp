#include <iostream>
#include <boost/any.hpp>
#include <vector>
#include <string>
using namespace std;


int main()
{
	std::vector<boost::any> some_values;
	some_values.push_back(10);
	some_values.push_back("hello");
	some_values.push_back(std::string("wow"));

	std::string& s = boost::any_cast<std::string&>(some_values.back());
	std::cout << s << std::endl;

	some_values.pop_back();
	const char* s2 = boost::any_cast<const char*>(some_values.back());
	std::cout << s2 << std::endl;

	some_values.pop_back();
	int s3 = boost::any_cast<int>(some_values.back());
	std::cout << s3 << std::endl;

	return 0;

}