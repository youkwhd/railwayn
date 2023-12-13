#pragma once

#include <iostream>
#include "stations.h"

typedef stations_elm_t* stations_queue_infotype_t;

typedef struct stations_queue_elm_t stations_queue_elm_t;
struct stations_queue_elm_t {
    stations_queue_infotype_t info;
    stations_queue_elm_t *next, *prev;
};

typedef struct stations_queue_t {
    stations_queue_elm_t *head, *tail;
} stations_queue_t; 

void stations_queue_create(stations_queue_t &st);
stations_queue_elm_t *stations_queue_create_elm(stations_queue_infotype_t info);
