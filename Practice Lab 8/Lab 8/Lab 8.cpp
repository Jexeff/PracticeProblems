// Lab 8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Using Lab 8 " << argv[1] << " file \n";
    }

    std::ifstream istr(argv[1]);
    if (!istr) {
        std::cerr << "Could not open " << argv[1] << std::endl;
    }

    int num;
    int max = 0;
    
    std::map<int, int> MyMap;
    std::pair<std::map<int, int>::iterator, bool> MyPair;
    while (istr >> num) {
        MyPair = MyMap.insert(std::make_pair(num, 1));
        if (MyPair.second == false) {
            ++MyPair.first->second;
        }
    }

    /*
    while (istr >> num) {
        std::cout << num << std::endl;
        ++MyMap[num];
    }
    std::cout << std::endl;
    */

    std::map<int, int>::const_iterator it;
    for (it = MyMap.begin(); it != MyMap.end(); ++it) {
        std::cout << it->first << "\t" << it->second << std::endl;
        if (it->second > max) {
            max = it->second;
        }
    }
    

    
    std::cout << std::endl << "The mode(s) for this set: " << std::endl;
    for (it = MyMap.begin(); it != MyMap.end(); ++it) {
        if (it->second == max) {
            std::cout << it->first << std::endl;;
        }
    }


    return 0;

}
