#include <iostream>

#include "stations.h"
#include "trains.h"

int main(void)
{
    /* std::cout << "Hello from C++" << std::endl; */
    stations_t stations;
    trains_t trains;

    stations_create(stations);
    stations_insert_last(stations, "1");
    stations_insert_last(stations, "2");
    stations_insert_last(stations, "3");
    stations_insert_last(stations, "4");
    stations_insert_last(stations, "5");
    // stations_debug(stations);

    trains_create(trains);
    trains_insert_last(trains, {"A", 20});
    trains_insert_last(trains, {"U", 30});
    trains_insert_last(trains, {"P", 10});
    trains_insert_last(trains, {"D", 40});
    trains_debug(trains);

    trains_elm_t *trains_a = trains_find(trains, "A");
    trains_enqueue_station(trains_a, stations_find(stations, "3"));
    trains_enqueue_station(trains_a, stations_find(stations, "4"));
    
    trains_elm_t *trains_u = trains_find(trains, "U");
    trains_enqueue_station(trains_u, stations_find(stations, "1"));
    trains_enqueue_station(trains_u, stations_find(stations, "4"));
    trains_enqueue_station(trains_u, stations_find(stations, "2"));
    
    trains_elm_t *trains_p = trains_find(trains, "P");
    trains_enqueue_station(trains_p, stations_find(stations, "4"));
    
    trains_elm_t *trains_d = trains_find(trains, "D");
    trains_enqueue_station(trains_d, stations_find(stations, "2"));
    trains_enqueue_station(trains_d, stations_find(stations, "3"));
    trains_enqueue_station(trains_d, stations_find(stations, "1"));

    stations_debug(trains_a->stations_queue);
    std::cout << std::endl;
    stations_debug(trains_u->stations_queue);
    std::cout << std::endl;
    stations_debug(trains_p->stations_queue);
    std::cout << std::endl;
    stations_debug(trains_d->stations_queue);


    return 0;
}
