#pragma once

#include <iostream>
#include "stations.h"

typedef ticket_t destinations_infotype_t;

typedef struct destinations_elm_t destinations_elm_t;
struct destinations_elm_t {
    destinations_infotype_t info;
    destinations_elm_t *next;
};

typedef struct destinations_t {
    destinations_elm_t *head, *tail;
} destinations_t; 

void destinations_create(destinations_t &st);
destinations_elm_t *destinations_create_elm(destinations_infotype_t info);
void destinations_delete_first(destinations_t &st);
void destinations_delete_last(destinations_t &st);
void destinations_delete(destinations_t &st, destinations_elm_t *elm);
bool destinations_is_empty(destinations_t &st);
/* 3. 7 */
void destinations_enqueue(destinations_t &st, destinations_infotype_t info);
/* 3. 11 */
size_t destinations_length(destinations_t &st);
size_t destinations_total_passengers(destinations_t &st);
destinations_infotype_t destinations_dequeue(destinations_t &st);
void destinations_cleanup(destinations_t &st);
void destinations_debug(destinations_t &st);
destinations_elm_t *destinations_find(destinations_t &st, std::string station_name);
