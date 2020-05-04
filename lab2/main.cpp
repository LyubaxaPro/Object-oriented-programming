#include <iostream>

#include "list.h"
#include "list.hpp"

int main()
{
    List<int> hh;
    for(const auto& h: hh)
        std::cout << "X" << h;
    return 0;

}
