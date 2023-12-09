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
