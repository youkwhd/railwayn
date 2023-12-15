#pragma once

#include <iostream>
#include "stations.h"

typedef stations_elm_t* stations_queue_infotype_t;

typedef struct stations_queue_elm_t stations_queue_elm_t;
struct stations_queue_elm_t {
	stations_queue_infotype_t info;
	stations_queue_elm_t *next;
};

typedef struct stations_queue_t {
	stations_queue_elm_t *head, *tail;
} stations_queue_t; 

void stations_queue_create(stations_queue_t &st);
stations_queue_elm_t *stations_queue_create_elm(stations_queue_infotype_t info);
void stations_queue_delete_first(stations_queue_t &st);
void stations_queue_delete_last(stations_queue_t &st);
void stations_queue_delete(stations_queue_t &st, stations_queue_elm_t *elm);
bool stations_queue_is_empty(stations_queue_t &st);
/* 3. 7 */
void stations_queue_enqueue(stations_queue_t &st, stations_queue_infotype_t info);
/* 3. 11 */
size_t stations_queue_length(stations_queue_t &st);
stations_queue_infotype_t stations_queue_dequeue(stations_queue_t &st);
void stations_queue_cleanup(stations_queue_t &st);
void stations_queue_debug(stations_queue_t &st);
stations_queue_elm_t *stations_queue_find(stations_queue_t &st, std::string station_name);
