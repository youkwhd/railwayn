#include "trains.h"

void trains_create(trains_t &tr)
{
    tr.head = NULL;
    tr.tail = NULL;
}

trains_elm_t *trains_create_elm(trains_infotype_t info)
{
    trains_elm_t *elm = new trains_elm_t;
    elm->info = info;
    elm->next = NULL;
    stations_queue_create(elm->stations_queue);
    return elm;
}

bool trains_is_empty(trains_t &tr)
{
    return tr.head == NULL && tr.tail == NULL;
}

void trains_insert_first(trains_t &tr, trains_infotype_t info)
{
    trains_elm_t *elm = trains_create_elm(info);

    if (trains_is_empty(tr)) {
        tr.head = elm;
        tr.tail = elm;
        return;
    }

    elm->next = tr.head;
    tr.head = elm;
}

void trains_insert_last(trains_t &tr, trains_infotype_t info)
{
    trains_elm_t *elm = trains_create_elm(info);

    if (trains_is_empty(tr)) {
        tr.head = elm;
        tr.tail = elm;
        return;
    }

    tr.tail->next = elm;
    tr.tail = elm;
}

trains_infotype_t trains_delete_first(trains_t &tr)
{
    trains_elm_t *elm = tr.head;
    tr.head = tr.head->next;

    if (tr.head == NULL) {
        tr.tail = NULL;
    }

    trains_infotype_t __info = elm->info;
    delete elm;
    return __info;
}

trains_infotype_t trains_delete_last(trains_t &tr)
{
    trains_elm_t *elm = tr.head;

    if (elm->next == NULL) {
        return trains_delete_first(tr);
    }

    while (elm->next->next != NULL) {
        elm = elm->next;
    }

    tr.tail = elm->next;

    trains_infotype_t __info = elm->next->next->info;
    delete elm->next->next;
    return __info;
}

void trains_debug(trains_t &tr, bool show_queue)
{
    for (trains_elm_t *elm = tr.head; elm != NULL; elm = elm->next) {
        std::cout << "Train: " << elm->info.train_name << std::endl;
        std::cout << "Passengers: " << elm->info.passengers << std::endl;

        if (show_queue)
            stations_queue_debug(elm->stations_queue);

        if (elm->next != NULL)
            std::cout << std::endl;
    }
}

trains_elm_t *trains_find(trains_t &tr, std::string name) 
{
    for (trains_elm_t *elm = tr.head; elm != NULL; elm = elm->next) {
        if (elm->info.train_name == name) {
            return elm;
        }
    }

    return NULL;
}

void trains_cleanup(trains_t &tr)
{
    trains_elm_t *elm = tr.head;

    while (elm != NULL) {
        trains_elm_t *tmp = elm;
        stations_queue_cleanup(elm->stations_queue);
        elm = elm->next;
        delete tmp;
    }
}
