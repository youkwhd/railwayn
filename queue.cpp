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

void stations_queue_debug(stations_queue_t &st)
{
	stations_queue_elm_t *elm = st.head;
	while (elm != NULL) {
		std::cout << "stations: " << elm->info->info << std::endl;
		elm = elm->next;
	}
}
