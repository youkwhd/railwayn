#include <iostream>
#include <vector>

#include "stations.h"
#include "trains.h"
#include "destinations.h"

#define STATION_1 "Ketapang (1)"
#define STATION_2 "Geurugok (2)"
#define STATION_3 "Pangkajene (3)"
#define STATION_4 "Patukan (4)"
#define STATION_5 "Binjai (5)"

#define TRAIN_A "Ambarawa Ekspres"
#define TRAIN_B "Tawang Alun"

/* 3. 12 */
int main(void)
{
    stations_t stations;
    trains_t trains;

    stations_create(stations);
    trains_create(trains);

    stations_elm_t *station_1 = stations_insert_last(stations, {STATION_1});
    stations_elm_t *station_2 = stations_insert_last(stations, {STATION_2});
    stations_elm_t *station_3 = stations_insert_last(stations, {STATION_3});
    stations_elm_t *station_4 = stations_insert_last(stations, {STATION_4});
    stations_elm_t *station_5 = stations_insert_last(stations, {STATION_5});

    stations_add_ticket(station_1, 40, station_2);
    stations_add_ticket(station_1, 20, station_3);
    stations_add_ticket(station_1, 50, station_3);

    stations_add_ticket(station_2, 40, station_3);
    stations_add_ticket(station_2, 40, station_4);
    stations_add_ticket(station_2, 50, station_5);

    stations_add_ticket(station_3, 40, station_1);
    stations_add_ticket(station_3, 30, station_4);
    stations_add_ticket(station_3, 20, station_5);

    stations_add_ticket(station_4, 40, station_5);

    stations_add_ticket(station_5, 10, station_1);
    stations_add_ticket(station_5, 10, station_2);

    trains_insert_last(trains, {TRAIN_A});
    trains_insert_last(trains, {TRAIN_B});

    trains_simulate_run(trains, stations);

    trains_cleanup(trains);
    stations_cleanup(stations);
    return 0;
}
