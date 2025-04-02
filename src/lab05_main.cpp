//#pragma warning(disable:4275)
#include <array_list.h>
#include <array_list_utility.h>
#include <iostream>
#include <random>
//#include <iostream>

int main(int argc, char** argv)
{
    std::random_device device;
    std::uniform_real_distribution<float> distribution(0.1f, 100.0f);
    std::mt19937 generator(device());


    ssuds::ArrayList<float> sample_list;

    for (int i = 0; i < 10; i++) {
        float num = distribution(generator);
        sample_list.append(num);
    }
    std::cout << "Unsorted List: " << sample_list << std::endl;
    
    ssuds::ArrayListSortOrder sort_order = ssuds::ArrayListSortOrder::ASCENDING;
    
    ssuds::quicksort(sample_list, sort_order, 0, 3);
    std::cout << "Sorted List: " << sample_list << std::endl;
}