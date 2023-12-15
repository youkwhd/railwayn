#pragma once

#include <iostream>
#include <vector>

typedef struct stations_elm_t stations_elm_t;

typedef struct ticket_t {
    size_t passengers;
    stations_elm_t *dest;
} ticket_t;

typedef struct {
    std::string name;
    std::vector<ticket_t> tickets;
} stations_infotype_t;

struct stations_elm_t {
    stations_infotype_t info;
    stations_elm_t *next, *prev;
};

typedef struct stations_t {
    stations_elm_t *first, *last;
} stations_t; 

void stations_create(stations_t &st);
stations_elm_t *stations_create_elm(stations_infotype_t info);
/* 3. 6 */
stations_elm_t *stations_insert_first(stations_t &st, stations_infotype_t info);
/* 3. 6 */
stations_elm_t *stations_insert_last(stations_t &st, stations_infotype_t info);
void stations_add_ticket(stations_elm_t *station, size_t passengers, stations_elm_t *dest);
size_t stations_tickets_count(stations_t &st);
stations_infotype_t stations_delete_first(stations_t &st);
stations_infotype_t stations_delete_last(stations_t &st);
stations_infotype_t stations_delete(stations_t &st, stations_elm_t *station);
bool stations_is_empty(stations_t &st);
void stations_debug(stations_t &st);
void stations_cleanup(stations_t &st);
/* 3. 5 */
stations_elm_t *stations_find(stations_t &st, std::string name);
