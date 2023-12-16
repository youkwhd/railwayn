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

void menu(stations_t &stations, trains_t &trains) {
    int poin;
    stations_elm_t *station_1;
    stations_elm_t *station_2;
    stations_elm_t *station_3;
    stations_elm_t *station_4;
    stations_elm_t *station_5;

    trains_elm_t *train_a;
    trains_elm_t *train_b;
    
    do {
        std::cout << "=========== Main Menu ===========" << std::endl;
        std::cout << "1. Insert trains" << std::endl;
        std::cout << "2. Show all trains" << std::endl;
        std::cout << "3. Delete train" << std::endl;
        std::cout << "4. Search train" << std::endl;
        std::cout << "5. Search station" << std::endl;
        std::cout << "6. Insert stations" << std::endl;
        std::cout << "7. Assign ticket to train" << std::endl;
        std::cout << "8. Show all trains with tickets" << std::endl;
        std::cout << "9. Search ticket within train" << std::endl;
        std::cout << "10. Delete tickets within train" << std::endl;
        std::cout << "11. Count tickets within train"<<std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << ">> ";
        std::cin >> poin;
        switch (poin)
        {
        case 1: {
            train_a = trains_insert_last(trains, {TRAIN_A});
            train_b = trains_insert_last(trains, {TRAIN_B});
            break;
        }
        case 2: {
            trains_debug(trains, false);
            break;
        }
        case 3: {
            trains_delete(trains, trains_find(trains, TRAIN_A));
            break;
        }
        case 4: {
            trains_find(trains, TRAIN_A);
            break;
        }
        case 5: {
            stations_find(stations, STATION_1);
            break;
        }
        case 6: {
            station_1 = stations_insert_last(stations, {STATION_1});
            station_2 = stations_insert_last(stations, {STATION_2});
            station_3 = stations_insert_last(stations, {STATION_3});
            station_4 = stations_insert_last(stations, {STATION_4});
            station_5 = stations_insert_last(stations, {STATION_5});
            break;
        }
        case 7: {
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
            break;
        }
        case 8: {
            trains_debug(trains, true);
            break;
        }
        case 9: {
            trains_find_station_dest(train_a, STATION_1);
            break;
        }
        case 10: {
            __trains_delete_station_entirely(trains, stations, train_a, STATION_1);
            break;
        }
        case 11: {
            destinations_length(train_a->destinations);
            break;
        }
        default:
            std::cout << "Invalid options" << std::endl;
            break;
        }
    } while (poin != 0);
}

/* 3. 12 */
int main(void)
{
    stations_t stations;
    trains_t trains;

    stations_create(stations);
    trains_create(trains);

    menu(stations, trains);

    trains_simulate_run(trains, stations);

    trains_cleanup(trains);
    stations_cleanup(stations);
    return 0;
}
