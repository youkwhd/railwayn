#include "trains.h"

void trains_create(trains_t &st)
{
    st.head = NULL;
    st.tail = NULL;
}

trains_elm_t *trains_create_elm(infotype info)
{
    trains_elm_t *elm = new trains_elm_t;
    elm->info = info;
    elm->next = NULL;
    return elm;
}

bool trains_is_empty(trains_t &st)
{
    return st.head != NULL && st.tail != NULL;
}

void trains_insert_first(trains_t &st, infotype info)
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

void trains_insert_last(trains_t &st, infotype info)
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
