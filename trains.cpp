#include "trains.h"

void trains_create(trains_t &tr)
{
    tr.head = NULL;
    tr.tail = NULL;
}

trains_elm_t *trains_create_elm(trains_infotype_t info)
{
    trains_elm_t *elm = new trains_elm_t;
    info.__transfered_passengers_total = 0;
    elm->info = info;
    elm->next = NULL;
    destinations_create(elm->destinations);
    return elm;
}

bool trains_is_empty(trains_t &tr)
{
    return tr.head == NULL && tr.tail == NULL;
}

trains_elm_t *trains_insert_first(trains_t &tr, trains_infotype_t info)
{
    trains_elm_t *elm = trains_create_elm(info);

    if (trains_is_empty(tr)) {
        tr.head = elm;
        tr.tail = elm;
        return elm;
    }

    elm->next = tr.head;
    tr.head = elm;
    return elm;
}

trains_elm_t *trains_insert_last(trains_t &tr, trains_infotype_t info)
{
    trains_elm_t *elm = trains_create_elm(info);

    if (trains_is_empty(tr)) {
        tr.head = elm;
        tr.tail = elm;
        return elm;
    }

    tr.tail->next = elm;
    tr.tail = elm;
    return elm;
}

trains_infotype_t trains_delete_first(trains_t &tr)
{
    trains_elm_t *elm = tr.head;
    tr.head = tr.head->next;

    if (tr.head == NULL) {
        tr.tail = NULL;
    }

    trains_infotype_t __info = elm->info;
    destinations_cleanup(elm->destinations);
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

    trains_infotype_t __info = tr.tail->info;
    destinations_cleanup(tr.tail->destinations);
    delete tr.tail;
    tr.tail = elm;
    return __info;
}

void trains_debug(trains_t &tr, bool show_queue)
{
    for (trains_elm_t *elm = tr.head; elm != NULL; elm = elm->next) {
        std::cout << "Train: " << elm->info.train_name << std::endl;

        if (show_queue)
            destinations_debug(elm->destinations);

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
        elm = elm->next;
        destinations_cleanup(tmp->destinations);
        delete tmp;
    }
}

stations_elm_t *trains_find_station_dest(trains_elm_t *train, std::string station_name)
{
    destinations_elm_t *elm = destinations_find(train->destinations, station_name);
    return elm == NULL ? NULL : elm->info.dest;
}

void __trains_delete_station_entirely(trains_t &tr, stations_t &st, trains_elm_t *train, std::string station_name)
{
    for (trains_elm_t *elm = tr.head; elm != NULL; elm = elm->next) {
        destinations_elm_t *queue_elm = destinations_find(elm->destinations, station_name);

        while (queue_elm != NULL) {
            destinations_delete(elm->destinations, queue_elm);
            queue_elm = destinations_find(elm->destinations, station_name);
        }
    }

    stations_delete(st, stations_find(st, station_name));
}

void trains_simulate_run(trains_t &tr, stations_t &st)
{
    direction dir = DIRECTION_RIGHT;
    stations_elm_t *station = st.first;

    while (station != NULL && stations_tickets_count(st) != 0) {
        /* trains has arrived to a station, remove
         * corrensponding tickets from trains.
         */
        for (trains_elm_t *train = tr.head; train != NULL; train = train->next) {
            /* while (!destinations_is_empty(train->destinations)) { */
            /*     ticket_t ticket = destinations_dequeue(train->destinations); */
            /*     #ifdef __DEBUG */
            /*     std::cout << "Dropped passengers: " << ticket.passengers << std::endl; */
            /*     #endif */
            /* } */
        }

        /* assign trains new tickets
         */
        for (trains_elm_t *train = tr.head; train != NULL; train = train->next) {
            size_t total_passengers = destinations_total_passengers(train->destinations);

            for (auto ticket = station->info.tickets.begin(); ticket != station->info.tickets.end(); ticket++) {
                /* TODO: only add tickets that 
                 * goes the same direction as the train
                 */

                if (total_passengers + ticket->passengers > TRAIN_PASSENGGERS_MAX) {
                    break;
                }

                destinations_enqueue(train->destinations, *ticket);
                total_passengers += ticket->passengers;
            }
        }

        if (station == st.first) {
            dir = DIRECTION_RIGHT;
        }

        if (station == st.last) {
            dir = DIRECTION_LEFT;
        }

        station = DIRECTION_RIGHT ? station->next : station->prev;
    }
}
