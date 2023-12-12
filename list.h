#pragma once

#include <iostream>

namespace railwayn
{
    template <typename T>
    struct list_node {
        T data;
        list_node<T> *next, *prev;
    };


    template <typename T>
    struct list {
        list_node<T> *head, *tail;

        list() : head(NULL), tail(NULL) {}
        ~list() { 
            list_node<T> *node = head;

            while (node != NULL) {
                list_node<T> *tmp = node;

                node = node->next;
                delete tmp;
            }
        }

        bool empty() {
            return head == NULL && tail == NULL;
        }

        void insert_first(T data)
        {
            list_node<T> *node = new list_node<T> { data, NULL, NULL };

            if (this->empty()) {
                head = node;
                tail = node;
                return;
            }

            node->next = head;
            head->prev = node;
            head = node;
        }

        T delete_first()
        {
            list_node<T> *node = head;
            head = head->next;

            if (head == NULL) {
                tail = NULL;
                return node;
            }

            head->prev = NULL;
            T __data = node->data;
            delete node;
            return __data;
        }
    };
}
