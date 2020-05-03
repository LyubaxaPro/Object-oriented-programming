//
// Created by lyubaxapro on 02.05.20.
//

#ifndef OOP_SECOND_LIST_BASE_H
#define OOP_SECOND_LIST_BASE_H

#include <cstdlib>

class ListBase {
public:
    virtual void clear() = 0;
    virtual bool is_empty() const = 0;
    virtual size_t get_length() const = 0;
};

#endif //OOP_SECOND_LIST_BASE_H
