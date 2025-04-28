//#pragma warning(disable:4275)
#include <linked_list.h>
#include <iostream>
#include <random>
//#include <iostream>

int main(int argc, char** argv)
{
    ssuds::LinkedList<float> test_list;

    std::cout << test_list.getSize() << std::endl;

    test_list.append(4.5);

    std::cout << test_list.getSize() << std::endl;
}