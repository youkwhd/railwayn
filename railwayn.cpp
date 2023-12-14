#include <iostream>

#include "stations.h"
#include "trains.h"
#include "queue.h"

#define STATION_1 "Bungkaih (1)"
#define STATION_2 "Geurugok (2)"
#define STATION_3 "Krueng Geukueh (3)"
#define STATION_4 "Krueng Mane (4)"
#define STATION_5 "Kutablang (5)"

int main(void)
{
    stations_t stations;
    trains_t trains;

    stations_create(stations);
    stations_insert_last(stations, STATION_1);
    stations_insert_last(stations, STATION_2);
    stations_insert_last(stations, STATION_3);
    stations_insert_last(stations, STATION_4);
    stations_insert_last(stations, STATION_5);

    trains_create(trains);
    trains_insert_last(trains, {"A", 20});
    trains_insert_last(trains, {"U", 30});
    trains_insert_last(trains, {"P", 10});
    trains_insert_last(trains, {"D", 40});

    trains_elm_t *trains_a = trains_find(trains, "A");
    stations_queue_enqueue(trains_a->stations_queue, stations_find(stations, STATION_3));
    stations_queue_enqueue(trains_a->stations_queue, stations_find(stations, STATION_4));

    trains_elm_t *trains_u = trains_find(trains, "U");
    stations_queue_enqueue(trains_u->stations_queue, stations_find(stations, STATION_1));
    stations_queue_enqueue(trains_u->stations_queue, stations_find(stations, STATION_4));
    stations_queue_enqueue(trains_u->stations_queue, stations_find(stations, STATION_2));

    trains_elm_t *trains_p = trains_find(trains, "P");
    stations_queue_enqueue(trains_p->stations_queue, stations_find(stations, STATION_4));

    trains_elm_t *trains_d = trains_find(trains, "D");
    stations_queue_enqueue(trains_d->stations_queue, stations_find(stations, STATION_2));
    stations_queue_enqueue(trains_d->stations_queue, stations_find(stations, STATION_3));
    stations_queue_enqueue(trains_d->stations_queue, stations_find(stations, STATION_1));
    trains_debug(trains);

    trains_cleanup(trains);
    stations_cleanup(stations);
    return 0;
}
