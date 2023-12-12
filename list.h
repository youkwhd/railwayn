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

        void insert_last(T data) 
        {
            list_node<T> *node = new list_node<T> { data, NULL, NULL };

            if (this->empty()) {
                head = node;
                tail = node;
                return;
            }

            node->prev = tail;
            tail->next = node;
            tail = node;
        }

        T delete_first()
        {
            list_node<T> *node = head;
            head = head->next;

            if (head == NULL) {
                tail = NULL;
                T __data = node->data;
                delete node;
                return __data;
            }

            head->prev = NULL;
            T __data = node->data;
            delete node;
            return __data;
        }

        T delete_last() 
        {
            list_node<T> *node = tail;
            tail = tail->prev;

            if (tail == NULL) {
                head = NULL;
                T __data = node->data;
                delete node;
                return __data;
            }

            tail->next = NULL;
            T __data = node->data;
            delete node;
            return __data;
        }

        void print() 
        {
            list_node<T> *node = head;

            while (node != NULL) {
                std::cout << node->data << std::endl;
                node = node->next;
            }
        }

        T *find(T data) 
        {
            list_node<T> *node = head;
            
            while (node != NULL) {
                if (node->data == data) {
                    return &node->data;
                }
                node = node->next;
            }

            return NULL;
        }
        
    };
}
