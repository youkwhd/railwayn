#pragma once

#include <iostream>

typedef std::string stations_infotype_t;

typedef struct stations_elm_t stations_elm_t;
struct stations_elm_t {
    stations_infotype_t info;
    stations_elm_t *next, *prev;
};

typedef struct stations_t {
    stations_elm_t *first, *last;
} stations_t; 

void stations_create(stations_t &st);
stations_elm_t *stations_create_elm(stations_infotype_t info);
void stations_insert_first(stations_t &st, stations_infotype_t info);
void stations_insert_last(stations_t &st, stations_infotype_t info);
stations_infotype_t stations_delete_first(stations_t &st);
stations_infotype_t stations_delete_last(stations_t &st);
bool stations_is_empty(stations_t &st);
void stations_debug(stations_t &st);
void stations_cleanup(stations_t &st);
stations_elm_t *stations_find(stations_t &st, stations_infotype_t info);
