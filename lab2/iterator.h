//
// Created by lyubaxapro on 02.05.20.
//

#ifndef OOP_SECOND_ITERATOR_H
#define OOP_SECOND_ITERATOR_H

#include <iostream>
#include <cstdlib>
#include <iterator>

#include "list.h"

template <typename T>
template <typename Ptr, typename Ref, typename ListPtr>
class  List<T>::Iterator : public std::iterator<std::forward_iterator_tag, T, ptrdiff_t, Ptr, Ref>
{
private:
    ListPtr list;
    std::shared_ptr<Node> curr_ptr;

public:
    Iterator(ListPtr list, bool is_begin) : list(list) {
        curr_ptr = is_begin ? (*list).head : (*list).tail->next;
    }

    Ref operator*() {
        return curr_ptr->data;
    }

    Ptr operator->() {
        return &(curr_ptr->data);
    }

    Iterator next() {
        Iterator tmp = *this;
        tmp.curr_ptr = tmp.curr_ptr->next;
        return tmp;
    }

    Iterator operator++(int) { // i++
        Iterator tmp = *this;
        curr_ptr = curr_ptr->next;
        return tmp;
    }

    Iterator& operator++() { // ++i
        curr_ptr = curr_ptr->next;
        return *this;
    }

    bool operator==(const Iterator& right)const {
        return (curr_ptr == right.curr_ptr);
    }
    bool operator!=(const Iterator& right) const {
        return curr_ptr != right.curr_ptr;
    }
};

#endif //OOP_SECOND_ITERATOR_H
