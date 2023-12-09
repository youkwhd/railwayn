#pragma once

#include <iostream>
#include "stations.h"

#define TRAIN_PASSENGERS_MAX 128

typedef struct {
    std::string train_name;
    size_t passengers;
} infotype;

typedef struct trains_elm_t trains_elm_t;
struct trains_elm_t {
    infotype info;
    trains_elm_t *next;
    stations_t stations_queue;
};

typedef struct trains_t {
    trains_elm_t *head, *tail;
};

void trains_create(trains_t &st);
trains_elm_t *trains_create_elm(infotype info);
bool trains_is_empty(trains_t &st);
void trains_insert_first(trains_t &st, infotype info);
void trains_insert_last(trains_t &st, infotype info);
