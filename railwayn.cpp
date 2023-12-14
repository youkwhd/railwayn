#include <iostream>

#include "stations.h"
#include "trains.h"
#include "queue.h"

int main(void)
{
    stations_t stations;
    trains_t trains;

    stations_create(stations);
    stations_insert_last(stations, "1");
    stations_insert_last(stations, "2");
    stations_insert_last(stations, "3");
    stations_insert_last(stations, "4");
    stations_insert_last(stations, "5");

    trains_create(trains);
    trains_insert_last(trains, {"A", 20});
    trains_insert_last(trains, {"U", 30});
    trains_insert_last(trains, {"P", 10});
    trains_insert_last(trains, {"D", 40});

    trains_elm_t *trains_a = trains_find(trains, "A");
    stations_queue_enqueue(trains_a->stations_queue, stations_find(stations, "3"));
    stations_queue_enqueue(trains_a->stations_queue, stations_find(stations, "4"));

    trains_elm_t *trains_u = trains_find(trains, "U");
    stations_queue_enqueue(trains_u->stations_queue, stations_find(stations, "1"));
    stations_queue_enqueue(trains_u->stations_queue, stations_find(stations, "4"));
    stations_queue_enqueue(trains_u->stations_queue, stations_find(stations, "2"));

    trains_elm_t *trains_p = trains_find(trains, "P");
    stations_queue_enqueue(trains_p->stations_queue, stations_find(stations, "4"));

    trains_elm_t *trains_d = trains_find(trains, "D");
    stations_queue_enqueue(trains_d->stations_queue, stations_find(stations, "2"));
    stations_queue_enqueue(trains_d->stations_queue, stations_find(stations, "3"));
    stations_queue_enqueue(trains_d->stations_queue, stations_find(stations, "1"));
    trains_debug(trains);

    trains_cleanup(trains);
    stations_cleanup(stations);
    return 0;
}
