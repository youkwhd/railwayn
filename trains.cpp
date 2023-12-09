#include "trains.h"

void trains_create(trains_t &st)
{
    st.head = NULL;
    st.tail = NULL;
}

trains_elm_t *trains_create_elm(trains_infotype_t info)
{
    trains_elm_t *elm = new trains_elm_t;
    elm->info = info;
    elm->next = NULL;
    stations_create(elm->stations_queue);
    return elm;
}

bool trains_is_empty(trains_t &st)
{
    return st.head == NULL && st.tail == NULL;
}

void trains_insert_first(trains_t &st, trains_infotype_t info)
{
    trains_elm_t *elm = trains_create_elm(info);

    if (trains_is_empty(st)) {
        st.head = elm;
        st.tail = elm;
        return;
    }

    elm->next = st.head;
    st.head = elm;
}

void trains_insert_last(trains_t &st, trains_infotype_t info)
{
    trains_elm_t *elm = trains_create_elm(info);

    if (trains_is_empty(st)) {
        st.head = elm;
        st.tail = elm;
        return;
    }

    st.tail->next = elm;
    st.tail = elm;
}

trains_infotype_t trains_delete_first(trains_t &st)
{
    trains_elm_t *elm = st.head;
    st.head = st.head->next;

    if (st.head == NULL) {
        st.tail = NULL;
    }

    trains_infotype_t __info = elm->info;
    delete elm;
    return __info;
}

trains_infotype_t trains_delete_last(trains_t &st)
{
    trains_elm_t *elm = st.head;

    if (elm->next == NULL) {
        return trains_delete_first(st);
    }

    while (elm->next->next != NULL) {
        elm = elm->next;
    }

    st.tail = elm->next;

    trains_infotype_t __info = elm->next->next->info;
    delete elm->next->next;
    return __info;
}

void trains_enqueue_station(trains_elm_t &train, stations_elm_t &station)
{
    stations_insert_first(train.stations_queue, station.info);
}

infotype trains_dequeue_station(trains_elm_t &train)
{
    return stations_delete_last(train.stations_queue);
}
