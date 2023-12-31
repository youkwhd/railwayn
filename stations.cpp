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

void stations_add_ticket(stations_elm_t *station, size_t passengers, stations_elm_t *dest)
{
    if (station->info.name == dest->info.name || passengers > TRAIN_PASSENGGERS_MAX) {
        return;
    }

    station->info.tickets.push_back({ passengers, dest });
}

size_t stations_tickets_count(stations_t &st)
{
    size_t count = 0;

    for (stations_elm_t *elm = st.first; elm != NULL; elm = elm->next) {
        count += elm->info.tickets.size();
    }

    return count;
}

stations_elm_t *stations_insert_first(stations_t &st, stations_infotype_t info) 
{
    if (stations_find(st, info.name)) {
        return NULL;
    }

    stations_elm_t *elm = stations_create_elm(info);

    if (stations_is_empty(st)) {
        st.first = elm;
        st.last = elm; 
    } else {
        elm->next = st.first;
        st.first->prev = elm;
        st.first = elm;
    }

    return elm;
}

stations_elm_t *stations_insert_last(stations_t &st, stations_infotype_t info) 
{
    if (stations_find(st, info.name)) {
        return NULL;
    }

    stations_elm_t *elm = stations_create_elm(info);

    if (stations_is_empty(st)) {
        elm = stations_insert_first(st, info);
    } else {
        elm->prev = st.last;
        st.last->next = elm;
        st.last = elm;
    }

    return elm;
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

stations_infotype_t stations_delete(stations_t &st, stations_elm_t *station)
{
    if (st.first == station) {
        return stations_delete_first(st);
    }

    if (st.last == station) {
        return stations_delete_last(st);
    }

    station->prev->next = station->next;
    station->next->prev = station->prev;

    stations_infotype_t __info = station->info;
    delete station;
    return __info;
}

void stations_debug(stations_t &st) 
{
    stations_elm_t *elm = st.first;

    while (elm != NULL) {
        std::cout << "Station: " << elm->info.name << std::endl;

        for (auto it = elm->info.tickets.begin(); it != elm->info.tickets.end(); it++) {
            std::cout << "    - Passengers: " <<  it->passengers << std::endl;
            std::cout << "    - Dest: " <<  it->dest->info.name << std::endl;
            std::cout << std::endl;
        }

        elm = elm->next;
    }
}

stations_elm_t *stations_find(stations_t &st, std::string name)
{
    stations_elm_t *elm = st.first;

    while (elm != NULL) {
        if (elm->info.name == name) {
            return elm;
        }
        elm = elm->next;
    }

    return NULL;
}

bool stations_direction_is(stations_elm_t *from, stations_elm_t *to, direction expected)
{
    for (; from != NULL; from = expected == DIRECTION_RIGHT ? from->next : from->prev) {
        if (from == to) {
            return true;
        }
    }

    return false;
}

void stations_cleanup(stations_t &st)
{
    stations_elm_t *elm = st.first;

    while (elm != NULL) {
        stations_elm_t *tmp = elm;
        elm = elm->next;
        delete tmp;
    }
}

std::string stations_print_html5(stations_t &st)
{
    std::string html5;

    if (st.first == NULL) {
        return "<p>NONE</p>";
    }

    html5 += "<ul>";
    for (stations_elm_t *station = st.first; station != NULL; station = station->next) {
        html5 += "<li>";
        html5 += station->info.name;

        if (station->info.tickets.begin() != station->info.tickets.end()) {
            html5 += "<ul>";
        }

        for (auto it = station->info.tickets.begin(); it != station->info.tickets.end(); it++) {
            html5 += "<li> Destination: ";
            html5 += it->dest->info.name;
            html5 += "</li>";
            html5 += "<li> Passengers: ";
            html5 += std::to_string(it->passengers);
            html5 += "</li>";
            html5 += "<br/>";
        }

        if (station->info.tickets.begin() != station->info.tickets.end()) {
            html5 += "</ul>";
        }

        html5 += "</li>";
    }

    html5 += "</ul>";
    return html5;
}
