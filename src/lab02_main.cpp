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
	std::cout << "\tsize=" << float_list.get_size() << std::endl; // size=2
	std::cout << "\titem0=" << float_list.at(0) << std::endl; // item0=2.1
	std::cout << "\titem1=" << float_list.at(1) << std::endl; // item1=3.6
	std::cout << "test2:\n=====\n"; // test2 (insert):
	float_list.insert(1.8f, 0);		// ======
	float_list.insert(4.2f, 3);											// item0=1.8
	float_list.insert(2.0f, 1);											// item1=2
	for (int i = 0; i < float_list.get_size(); i++) {					// item2=2.1
		std::cout << "\titem" << i << "=" << float_list.at(i) << "\n"; // item3=3.6
																		// item4=4.2
	}

	std::cout << "test3:\n=====\n"; // test3 (remove):
	float_list.remove(3);												// item0=1.8
	for (int i = 0; i < float_list.get_size(); i++) {					// item1=2
		std::cout << "\titem" << i << "=" << float_list.at(i) << "\n"; // item2=2.1
																		// item3=4.2
	}
	
	std::cout << "test4:\n=====\n"; // test4 (prepend):
	float_list.prepend(8);												// item0=8
	for (int i = 0; i < float_list.get_size(); i++) {					// item1=1.8
		std::cout << "\titem" << i << "=" << float_list.at(i) << "\n"; // item2=2
																		// item3=2.1
																		// item4=4.2
	}

	std::cout << "test4.5:\n=====\n"; // test5 (remove_all):
	float_list.insert(8, 2);												// item0=8
	for (int i = 0; i < float_list.get_size(); i++) {					// item1=1.8
		std::cout << "\titem" << i << "=" << float_list.at(i) << "\n"; // item2=2
																		// item3=2.1
																		// item4=4.2
	}
	std::cout << "test5:\n=====\n";
	std::cout << "\tremoving " << float_list.remove_all(8) << " item(s)\n";		// item0=1.8
	for (int i = 0; i < float_list.get_size(); i++) {					// item1=2
		std::cout << "\titem" << i << "=" << float_list.at(i) << "\n"; // item2=2.1
																		// item3=4.2
	}


	std::cout << "test6:\n=====\n"; // test5 (string):
	//std::cout << "\t" << float_list.output();
	// Had trouble making it work
}
