#include <iostream>

#include "stations.h"
#include "trains.h"

#include "list.h"

int main(void)
{
    railwayn::list<int> list;
    std::cout << (list.head == NULL ? "NULL" : "head") << std::endl;

    list.insert_first(10);

    return 0;
}
