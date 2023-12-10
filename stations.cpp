#include "stations.h"

void stations_create(stations_t &st)
{
    st.first = NULL;
    st.last = NULL;
}

stations_elm_t *stations_create_elm(stations_infotype_t info) 
{
    stations_elm_t *elm = new stations_elm_t;
    elm->info = info;
    elm->next = NULL;
    elm->prev = NULL;
    return elm;

}

bool stations_is_empty(stations_t &st) 
{
    return st.first == NULL && st.last == NULL;
}

void stations_insert_first(stations_t &st, stations_infotype_t info) 
{
    stations_elm_t *elm = stations_create_elm(info);
    if (stations_is_empty(st)) {
        st.first = elm;
        st.last = elm; 
    } else {
        elm->next = st.first;
        st.first->prev = elm;
        st.first = elm;
    }
}

void stations_insert_last(stations_t &st, stations_infotype_t info) 
{
    stations_elm_t *elm = stations_create_elm(info);
    if (stations_is_empty(st)) {
        stations_insert_first(st, info);
    } else {
        elm->prev = st.last;
        st.last->next = elm;
        st.last = elm;
    }
}

stations_infotype_t stations_delete_first(stations_t &st) 
{
    stations_elm_t *elm = st.first;
    if (st.first->next == NULL) {
        st.first = NULL;
        st.last = NULL;
    } else {
        st.first = elm->next;
        st.first->prev = NULL;
        elm->next = NULL;
    }
    return elm->info;
}

stations_infotype_t stations_delete_last(stations_t &st) 
{
    stations_elm_t *elm = st.last;
    if (st.first->next == NULL) {
        st.first = NULL;
        st.last = NULL;
    } else {
        st.last = elm->prev;
        st.last->next = NULL;
        elm->prev = NULL;
    }
    return elm->info;
}

void stations_debug(stations_t &st) 
{
    stations_elm_t *elm = st.first;
    while (elm != NULL) {
        std::cout << "station: " << elm->info << std::endl;
        elm = elm->next;
    }
}

stations_elm_t *stations_find(stations_t &st, stations_infotype_t info) 
{
    stations_elm_t *elm = st.first;
    while (elm != NULL) {
        if (elm->info == info) {
            return elm;
        }
        elm = elm->next;
    }
    return NULL;
}
