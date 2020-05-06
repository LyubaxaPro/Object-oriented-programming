//
// Created by lyubaxapro on 04.05.2020.
//
#include "iterator.h"
template <typename T>
template<typename Ptr, typename Ref, typename ListPtr>
List<T>::Iterator<Ptr, Ref, ListPtr>::Iterator(ListPtr list, bool is_begin) : list(list)
{
    curr_ptr = is_begin ? (*list).head : nullptr;
}

template <typename T>
template<typename Ptr, typename Ref, typename ListPtr>
Ref List<T>::Iterator<Ptr, Ref, ListPtr>::operator*()
{
    return curr_ptr->data;
}

template <typename T>
template<typename Ptr, typename Ref, typename ListPtr>
Ptr List<T>::Iterator<Ptr, Ref, ListPtr>::operator->()
{
    return &(curr_ptr->data);
}

template<typename T>
template<typename Ptr, typename Ref, typename ListPtr>
typename List<T>::template Iterator<Ptr, Ref, ListPtr> List<T>::Iterator<Ptr, Ref, ListPtr>::next()
{
    Iterator tmp = *this;
    tmp.curr_ptr = tmp.curr_ptr->next;
    return tmp;
}

template <typename T>
template<typename Ptr, typename Ref, typename ListPtr>
bool List<T>::Iterator<Ptr, Ref, ListPtr>::is_valid()
{
        return curr_ptr != nullptr && list != nullptr;
}

template <typename T>
template<typename Ptr, typename Ref, typename ListPtr>
T List<T>::Iterator<Ptr, Ref, ListPtr>::value()
{
    return curr_ptr->data;
}

template<typename T>
template<typename Ptr, typename Ref, typename ListPtr>
typename List<T>::template Iterator<Ptr, Ref, ListPtr> List<T>::Iterator<Ptr, Ref, ListPtr>::operator++(int)
{
    //i++
    Iterator tmp = *this;
    curr_ptr = curr_ptr->next;
    return tmp;
}

template<typename T>
template<typename Ptr, typename Ref, typename ListPtr>
typename List<T>::template Iterator<Ptr, Ref, ListPtr>& List<T>::Iterator<Ptr, Ref, ListPtr>::operator++()
{ // ++i
    curr_ptr = curr_ptr->next;
    return *this;
}

template <typename T>
template<typename Ptr, typename Ref, typename ListPtr>
bool List<T>::Iterator<Ptr, Ref, ListPtr>::operator==(const Iterator &right) const
{
    return (curr_ptr == right.curr_ptr);
}

template <typename T>
template<typename Ptr, typename Ref, typename ListPtr>
bool List<T>::Iterator<Ptr, Ref, ListPtr>::operator!=(const Iterator &right) const
{
    return curr_ptr != right.curr_ptr;
}

template <typename T>
typename List<T>::iterator List<T>::begin()  {
    return iterator(this, true);
}

template <typename T>
typename List<T>::iterator List<T>::end() {
    return iterator(this, false);
}

template <typename T>
const typename List<T>::const_iterator List<T>::begin() const  {
    return const_iterator(this, true);
}

template <typename T>
const typename List<T>::const_iterator List<T>::end() const {
    return const_iterator(this, false);
}
