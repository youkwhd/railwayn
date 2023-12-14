#include <iostream>

#include "stations.h"
#include "trains.h"
#include "queue.h"

#define STATION_1 "Ketapang (1)"
#define STATION_2 "Geurugok (2)"
#define STATION_3 "Pangkajene (3)"
#define STATION_4 "Patukan (4)"
#define STATION_5 "Binjai (5)"

#define TRAIN_1 "Harina"
#define TRAIN_2 "Serayu"
#define TRAIN_3 "Ambarawa Ekspres"
#define TRAIN_4 "Tawang Alun"

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
    trains_insert_last(trains, {TRAIN_1, 20});
    trains_insert_last(trains, {TRAIN_2, 30});
    trains_insert_last(trains, {TRAIN_3, 10});
    trains_insert_last(trains, {TRAIN_4, 40});

    trains_elm_t *train_1 = trains_find(trains, TRAIN_1);
    stations_queue_enqueue(train_1->stations_queue, stations_find(stations, STATION_3));
    stations_queue_enqueue(train_1->stations_queue, stations_find(stations, STATION_4));

    trains_elm_t *train_2 = trains_find(trains, TRAIN_2);
    stations_queue_enqueue(train_2->stations_queue, stations_find(stations, STATION_1));
    stations_queue_enqueue(train_2->stations_queue, stations_find(stations, STATION_4));
    stations_queue_enqueue(train_2->stations_queue, stations_find(stations, STATION_2));

    trains_elm_t *train_3 = trains_find(trains, TRAIN_3);
    stations_queue_enqueue(train_3->stations_queue, stations_find(stations, STATION_4));

    trains_elm_t *train_4 = trains_find(trains, TRAIN_4);
    stations_queue_enqueue(train_4->stations_queue, stations_find(stations, STATION_2));
    stations_queue_enqueue(train_4->stations_queue, stations_find(stations, STATION_3));
    stations_queue_enqueue(train_4->stations_queue, stations_find(stations, STATION_1));
    trains_debug(trains, 1);

    trains_cleanup(trains);
    stations_cleanup(stations);
    return 0;
}
