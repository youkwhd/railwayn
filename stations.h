#pragma once

#include <iostream>

typedef std::string infotype;

typedef struct stations_elm_t stations_elm_t;
struct stations_elm_t {
    infotype info;
    stations_elm_t *next, *prev;
};

typedef struct stations_t {
    stations_elm_t *head, *tail;
};

void stations_create(stations_t &st);
stations_elm_t *stations_create_new_elm(infotype info);
void stations_insert_first(stations_t &st, infotype info);
void stations_insert_last(stations_t &st, infotype info);
infotype stations_delete_first(stations_t &st);
infotype stations_delete_last(stations_t &st);
bool stations_is_empty(stations_t &st);
