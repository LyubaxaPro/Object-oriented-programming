#include <iostream>
#include "list.h"
int main()
{
    List<int> List1;
//    std::cout << List1.get_lenght() << std::endl;
//    std::cout << List1.is_empty() << std::endl;
//    List1.push_front(1);
//    List1.push_front(2);
//    std::cout << List1.pop_front() << std::endl;
//    std::cout << List1.pop_front() << std::endl;

//    List<int> List2;
//
//    List2.push_back(3);
//    List2.push_back(4);
//    List1.push_range_front(List2);
    int a[6] = {0,1,2,3,4,5};
    List1.push_range_back(a, 6);
    List1.remove_elem(3);
    return 0;
}
