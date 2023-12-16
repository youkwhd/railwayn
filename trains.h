#pragma once

#include <iostream>

#include "stations.h"
#include "direction.h"
#include "destinations.h"

#define TRAIN_PASSENGGERS_MAX 100

typedef struct {
    std::string train_name;
    size_t __transfered_passengers_total;
} trains_infotype_t;

typedef struct trains_elm_t trains_elm_t;
struct trains_elm_t {
    trains_infotype_t info;
    trains_elm_t *next;
    destinations_t destinations;
};

typedef struct trains_t {
    trains_elm_t *head, *tail;
} trains_t;

void trains_create(trains_t &tr);
trains_elm_t *trains_create_elm(trains_infotype_t info);
bool trains_is_empty(trains_t &tr);
/* 3. 1 */
trains_elm_t *trains_insert_first(trains_t &tr, trains_infotype_t info);
/* 3. 1 */
trains_elm_t *trains_insert_last(trains_t &tr, trains_infotype_t info);
/* 3. 3 */
trains_infotype_t trains_delete_first(trains_t &tr);
/* 3. 3 */
trains_infotype_t trains_delete_last(trains_t &tr);
/* 3. 4 */
trains_elm_t *trains_find(trains_t &tr, std::string name);
/* 3. 3 */
void trains_cleanup(trains_t &tr);
/* 3. 2 */
/* 3. 8 */
void trains_debug(trains_t &tr, bool show_ticket);
/* 3. 9 */
stations_elm_t *trains_find_station_dest(trains_elm_t *train, std::string station_name);
/* 3. 10 */
void __trains_delete_station_entirely(trains_t &tr, stations_t &st, trains_elm_t *train, std::string station_name);
bool trains_has_tickets(trains_t &tr);
void trains_simulate_run(trains_t &tr, stations_t &st);
trains_infotype_t trains_delete(trains_t &tr, trains_elm_t *train);
