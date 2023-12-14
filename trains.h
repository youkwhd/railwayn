#pragma once

#include <iostream>
#include "stations.h"
#include "queue.h"

#define TRAIN_PASSENGERS_MAX 128

typedef struct {
    std::string train_name;
    size_t passengers;
} trains_infotype_t;

typedef struct trains_elm_t trains_elm_t;
struct trains_elm_t {
    trains_infotype_t info;
    trains_elm_t *next;
    stations_queue_t stations_queue;
};

typedef struct trains_t {
    trains_elm_t *head, *tail;
} trains_t;

void trains_create(trains_t &tr);
trains_elm_t *trains_create_elm(trains_infotype_t info);
bool trains_is_empty(trains_t &tr);
void trains_insert_first(trains_t &tr, trains_infotype_t info);
void trains_insert_last(trains_t &tr, trains_infotype_t info);
trains_infotype_t trains_delete_first(trains_t &tr);
trains_infotype_t trains_delete_last(trains_t &tr);
trains_elm_t *trains_find(trains_t &tr, std::string name);
void trains_cleanup(trains_t &tr);
void trains_debug(trains_t &tr);
