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

void trains_debug(trains_t &tr)
{
    for (trains_elm_t *elm = tr.head; elm != NULL; elm = elm->next) {
        std::cout << "train name: " << elm->info.train_name << std::endl;
        std::cout << "passengers: " << elm->info.passengers << std::endl;
        std::cout << std::endl;
    }
}

trains_elm_t *trains_find(trains_t &tr, std::string name) 
{
    trains_elm_t *elm = tr.head;
    while (elm != NULL) {
        if (elm->info.train_name == name) {
            return elm;
        }
        elm = elm->next;
    }
    return NULL;
}
