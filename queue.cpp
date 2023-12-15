#include "queue.h"

void stations_queue_create(stations_queue_t &st) 
{
	st.head = NULL;
	st.tail = NULL;
}

stations_queue_elm_t *stations_queue_create_elm(stations_queue_infotype_t info) 
{
	stations_queue_elm_t *elm = new stations_queue_elm_t;
	elm->info = info;
	elm->next = NULL;
	return elm;
}

bool stations_queue_is_empty(stations_queue_t &st)
{
	return st.head == NULL && st.tail == NULL;
}

size_t stations_queue_length(stations_queue_t &st)
{
    size_t length = 0;

    for (stations_queue_elm_t *elm = st.head; elm != NULL; elm = elm->next) {
        length++;
    }

    return length;
}

void stations_queue_delete_first(stations_queue_t &st)
{
    stations_queue_dequeue(st);
}

void stations_queue_delete_last(stations_queue_t &st)
{
    stations_queue_elm_t *elm = st.head;

    if (elm->next == NULL) {
        return stations_queue_delete_first(st);
    }

    while (elm->next->next != NULL) {
        elm = elm->next;
    }

    elm->next = NULL;
    delete st.tail;
    st.tail = elm;
}

void stations_queue_delete(stations_queue_t &st, stations_queue_elm_t *elm)
{
    if (st.head == elm) {
        return stations_queue_delete_first(st);
    }

    if (st.tail == elm) {
        return stations_queue_delete_last(st);
    }

    stations_queue_elm_t *__elm = st.head;

    while (__elm->next != elm) {
        __elm = __elm->next;
    }

    __elm->next = __elm->next->next;
    delete elm;
}

void stations_queue_enqueue(stations_queue_t &st, stations_queue_infotype_t info) 
{
	stations_queue_elm_t *elm = stations_queue_create_elm(info);

	if (stations_queue_is_empty(st)) {
		st.head = elm;
		st.tail = elm;
		return;
	}

	st.tail->next = elm;
	st.tail = elm;
}

stations_queue_infotype_t stations_queue_dequeue(stations_queue_t &st) 
{
	stations_queue_elm_t *elm = st.head;
	st.head = st.head->next;

	if (st.head == NULL) {
		st.tail = NULL;
	}

	stations_queue_infotype_t __info = elm->info;
	delete elm;
	return __info;
}

void stations_queue_cleanup(stations_queue_t &st)
{
    stations_queue_elm_t *elm = st.head;

    while (elm != NULL) {
        stations_queue_elm_t *tmp = elm;
        elm = elm->next;
        delete tmp;
    }
}

void stations_queue_debug(stations_queue_t &st)
{
	stations_queue_elm_t *elm = st.head;
    std::cout << "Stations: " << std::endl;
	while (elm != NULL) {
		std::cout << "  - " << elm->info->info.name << std::endl;
		elm = elm->next;
	}
}

stations_queue_elm_t *stations_queue_find(stations_queue_t &st, std::string station_name)
{
    for (stations_queue_elm_t *elm = st.head; elm != NULL; elm = elm->next) {
        if (elm->info->info.name == station_name) {
            return elm;
        }
    }

    return NULL;
}
