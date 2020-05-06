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
class  List<T>::Iterator : public std::iterator<std::forward_iterator_tag, T, ptrdiff_t, Ptr, Ref> {
private:
    ListPtr list;
    std::shared_ptr<Node> curr_ptr;

public:
    Iterator(ListPtr list, bool is_begin);

    Ref operator*();

    Ptr operator->();

    Iterator next();

    bool is_valid();

    T value();

    Iterator operator++(int);

    Iterator& operator++();
    bool operator==(const Iterator &right) const;

    bool operator!=(const Iterator &right) const;

};




#endif //OOP_SECOND_ITERATOR_H

