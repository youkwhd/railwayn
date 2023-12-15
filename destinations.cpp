#include "destinations.h"

void destinations_create(destinations_t &st) 
{
    st.head = NULL;
    st.tail = NULL;
}

destinations_elm_t *destinations_create_elm(destinations_infotype_t info) 
{
    destinations_elm_t *elm = new destinations_elm_t;
    elm->info = info;
    elm->next = NULL;
    return elm;
}

bool destinations_is_empty(destinations_t &st)
{
    return st.head == NULL && st.tail == NULL;
}

size_t destinations_length(destinations_t &st)
{
    size_t length = 0;

    for (destinations_elm_t *elm = st.head; elm != NULL; elm = elm->next) {
        length++;
    }

    return length;
}

size_t destinations_total_passengers(destinations_t &st)
{
    size_t total = 0;

    for (destinations_elm_t *elm = st.head; elm != NULL; elm = elm->next) {
        total += elm->info.passengers;
    }

    return total;
}

void destinations_delete_first(destinations_t &st)
{
    destinations_dequeue(st);
}

void destinations_delete_last(destinations_t &st)
{
    destinations_elm_t *elm = st.head;

    if (elm->next == NULL) {
        return destinations_delete_first(st);
    }

    while (elm->next->next != NULL) {
        elm = elm->next;
    }

    elm->next = NULL;
    delete st.tail;
    st.tail = elm;
}

void destinations_delete(destinations_t &st, destinations_elm_t *elm)
{
    if (st.head == elm) {
        return destinations_delete_first(st);
    }

    if (st.tail == elm) {
        return destinations_delete_last(st);
    }

    destinations_elm_t *__elm = st.head;

    while (__elm->next != elm) {
        __elm = __elm->next;
    }

    __elm->next = __elm->next->next;
    delete elm;
}

void destinations_enqueue(destinations_t &st, destinations_infotype_t info) 
{
    destinations_elm_t *elm = destinations_create_elm(info);

    if (destinations_is_empty(st)) {
        st.head = elm;
        st.tail = elm;
        return;
    }

    st.tail->next = elm;
    st.tail = elm;
}

destinations_infotype_t destinations_dequeue(destinations_t &st) 
{
    destinations_elm_t *elm = st.head;
    st.head = st.head->next;

    if (st.head == NULL) {
        st.tail = NULL;
    }

    destinations_infotype_t __info = elm->info;
    delete elm;
    return __info;
}

void destinations_cleanup(destinations_t &st)
{
    destinations_elm_t *elm = st.head;

    while (elm != NULL) {
        destinations_elm_t *tmp = elm;
        elm = elm->next;
        delete tmp;
    }
}

void destinations_debug(destinations_t &st)
{
    destinations_elm_t *elm = st.head;

    std::cout << "Tickets: " << std::endl;

    while (elm != NULL) {
        std::cout << "  - Passengers: " << elm->info.passengers << std::endl;
        std::cout << "  - Dest: " << elm->info.dest->info.name << std::endl;

        if (elm->next != NULL) {
            std::cout << std::endl;
        }

        elm = elm->next;
    }
}

destinations_elm_t *destinations_find(destinations_t &st, std::string station_name)
{
    for (destinations_elm_t *elm = st.head; elm != NULL; elm = elm->next) {
        if (elm->info.dest->info.name == station_name) {
            return elm;
        }
    }

    return NULL;
}
