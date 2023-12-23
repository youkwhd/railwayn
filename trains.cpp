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
    if (trains_find(tr, info.train_name)) {
        return NULL;
    }

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
    if (trains_find(tr, info.train_name)) {
        return NULL;
    }

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

trains_infotype_t trains_delete(trains_t &tr, trains_elm_t *train) {
    if (tr.head == train) {
        return trains_delete_first(tr);
    }

    if (tr.tail == train) {
        return trains_delete_last(tr);
    }

    trains_elm_t *__train = tr.head;

    while (__train->next != train) {
        __train = __train->next;
    }

    __train->next = __train->next->next;
    trains_infotype_t __info = train->info;
    destinations_cleanup(train->destinations);
    delete train;
    return __info;
}

void trains_debug(trains_t &tr, bool show_ticket)
{
    for (trains_elm_t *elm = tr.head; elm != NULL; elm = elm->next) {
        std::cout << "Train: " << elm->info.train_name << std::endl;

        if (show_ticket)
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
        destinations_elm_t *dest = destinations_find(elm->destinations, station_name);

        while (dest != NULL) {
            destinations_delete(elm->destinations, dest);
            dest = destinations_find(elm->destinations, station_name);
        }
    }

    stations_delete(st, stations_find(st, station_name));
}

bool trains_has_tickets(trains_t &tr)
{
    for (trains_elm_t *train = tr.head; train != NULL; train = train->next) {
        if (!destinations_is_empty(train->destinations)) {
            return true;
        }
    }

    return false;
}

void trains_simulate_run(trains_t &tr, stations_t &st)
{
    direction dir = DIRECTION_RIGHT;
    stations_elm_t *station = st.first;

    while (stations_tickets_count(st) != 0 || trains_has_tickets(tr)) {
        if (station == st.first) {
            dir = DIRECTION_RIGHT;
        }

        if (station == st.last) {
            dir = DIRECTION_LEFT;
        }

        std::cout << "Entering station: " << station->info.name << std::endl;

        for (trains_elm_t *train = tr.head; train != NULL; train = train->next) {
            /* trains has arrived to a station, remove
             * corrensponding tickets from trains.
             */
            bool __got_output = false;
            std::cout << "    Train: " << train->info.train_name << std::endl;
            std::cout << "    Dropped passengers: " << std::endl;

            for (destinations_elm_t *ticket = destinations_find(train->destinations, station->info.name); ticket != NULL; ticket = destinations_find(train->destinations, station->info.name)) {
                __got_output = true;
                std::cout << "        - " << ticket->info.dest->info.name << " [" << ticket->info.passengers << " Passengers]" << std::endl;
                destinations_delete(train->destinations, ticket);
            }

            if (!__got_output) {
                std::cout << "       NONE" << std::endl;
            }

            __got_output = false;
            std::cout << std::endl;

            /* assign trains new tickets
             */
            std::cout << "    Getting passengers: " << std::endl;
            size_t total_passengers = destinations_total_passengers(train->destinations);

            auto ticket = station->info.tickets.begin();
            while (ticket != station->info.tickets.end()) {
                if (!stations_direction_is(station, ticket->dest, dir)) {
                    ticket++;
                    continue;
                }

                if (total_passengers + ticket->passengers > TRAIN_PASSENGGERS_MAX) {
                    break;
                }

                __got_output = true;
                std::cout << "        + " << ticket->dest->info.name << " [" << ticket->passengers << " Passengers]" << std::endl;
                destinations_insert_last(train->destinations, *ticket);
                total_passengers += ticket->passengers;
                station->info.tickets.erase(ticket);
            }

            if (!__got_output) {
                std::cout << "       NONE" << std::endl;
            }

            std::cout << std::endl;
        }

        std::cout << "Press ENTER to continue..";
        getchar();

        std::cout << std::endl;
        station = dir == DIRECTION_RIGHT ? station->next : station->prev;
        if (station == NULL) {
            break;
        }
    }
}

std::string trains_print_html5(trains_t &tr)
{
    std::string html5;

    if (tr.head == NULL) {
        return "<p>NONE</p>";
    }

    html5 += "<ul>";
    for (trains_elm_t *train = tr.head; train != NULL; train = train->next) {
        html5 += "<li>";
        html5 += train->info.train_name;
        html5 += "</li>";
    }
    html5 += "</ul>";

    return html5;
}
