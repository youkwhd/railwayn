#include <iostream>

#include "stations.h"
#include "trains.h"

#include "list.h"

int main(void)
{
    railwayn::list<int> list;

    list.insert_first(10);
    list.insert_first(20);
    list.print();

    return 0;
}
