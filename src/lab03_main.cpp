#include <iostream>
#include <person_database.h>
#include <person.h>				// <- not necessary, but OK to (re-) include
#include <array_list.h>

// These macros and functions weren't necessary, but helped de-clutter the main
#define BIG_UINT std::numeric_limits<unsigned int>::max()
#define BIG_INT std::numeric_limits<unsigned int>::max()
#define MAX_INPUT_SIZE 1000

unsigned int input_uint(std::string prompt, std::string error_msg)
{
	unsigned int result;
	std::cout << prompt;
	std::cin >> result;
	if (std::cin.fail())
	{
		std::cout << error_msg;
		std::cin.clear();
		std::cin.ignore(MAX_INPUT_SIZE, '\n');
		return BIG_UINT;
	}
	else
		return result;
}


int main(int argc, char** argv)
{
	ssuds::ArrayList<float> float_list;

	std::cout << "test1:\n=====\n"; // test1 (basics):
	float_list.append(2.1f); // ======
	float_list.append(3.6f);
	float_list.append(8.4f);
	
	auto it = float_list.begin();

	std::cout << *it << "\n"; // 2.1

	++it;

	std::cout << *it << "\n"; // 3.6

	it++;

	std::cout << *it << "\n"; // 8.4

	--it;

	std::cout << *it << "\n"; // 3.6

	it--;

	std::cout << *it << "\n"; // 2.1

	std::cout << float_list[0] << "\n"; // 2.1

	it = float_list.rbegin();
	
	std::cout << *it << "\n"; // 8.4
}
