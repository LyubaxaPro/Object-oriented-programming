#include "iterator.h"
#include <time.h>
template <typename T>
template<typename Ptr, typename Ref>
List<T>::Iterator<Ptr, Ref>::Iterator(std::shared_ptr<Node> node_ptr)
{
    curr_ptr = node_ptr;
}

template <typename T>
template<typename Ptr, typename Ref>
Ref List<T>::Iterator<Ptr, Ref>::operator*()
{
    return curr_ptr.lock()->data;
}

template <typename T>
template<typename Ptr, typename Ref>
Ptr List<T>::Iterator<Ptr, Ref>::operator->()
{
    return &(curr_ptr.lock()->data);
}

template<typename T>
template<typename Ptr, typename Ref>
typename List<T>::template Iterator<Ptr, Ref> List<T>::Iterator<Ptr, Ref>::next()
{
    Iterator tmp = *this;
    tmp.curr_ptr = tmp.curr_ptr.lock()->next;
    return tmp;
}

template <typename T>
template<typename Ptr, typename Ref>
std::weak_ptr<typename List<T>::Node> List<T>::Iterator<Ptr, Ref>::get_node() const
{
    return curr_ptr;
}

template <typename T>
template<typename Ptr, typename Ref>
T List<T>::Iterator<Ptr, Ref>::get()
{
    if (curr_ptr.lock() == nullptr)
    {
        time_t t_time = time(NULL);
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }
    return curr_ptr.lock()->data;
}

template <typename T>
template<typename Ptr, typename Ref>
T List<T>::Iterator<Ptr, Ref>::get_next()
{
    if (curr_ptr.lock() == end() || curr_ptr.next().lock() == end())
    {
        time_t t_time = time(NULL);
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }
    return curr_ptr.next().lock()->data;
}

template<typename T>
template<typename Ptr, typename Ref>
typename List<T>::template Iterator<Ptr, Ref> List<T>::Iterator<Ptr, Ref>::operator++(int)
{
    //i++
    Iterator tmp = *this;
    curr_ptr = curr_ptr.lock()->next;
    return tmp;
}

template<typename T>
template<typename Ptr, typename Ref>
typename List<T>::template Iterator<Ptr, Ref>& List<T>::Iterator<Ptr, Ref>::operator++()
{ // ++i
    curr_ptr = curr_ptr.lock()->next;
    return *this;
}

template <typename T>
template<typename Ptr, typename Ref>
bool List<T>::Iterator<Ptr, Ref>::operator==(const Iterator &right) const
{
    return (curr_ptr.lock() == right.curr_ptr.lock());
}

template <typename T>
template<typename Ptr, typename Ref>
bool List<T>::Iterator<Ptr, Ref>::operator!=(const Iterator &right) const
{
    return curr_ptr.lock() != right.curr_ptr.lock();
}

template <typename T>
template<typename Ptr, typename Ref>
List<T>::Iterator<Ptr, Ref>::operator bool() const
{
    return curr_ptr.expired();
}

template <typename T>
typename List<T>::iterator List<T>::begin()
{
    return iterator(head);
}

template <typename T>
typename List<T>::iterator List<T>::end()
{
    return iterator(nullptr);
}

template <typename T>
const typename List<T>::const_iterator List<T>::cbegin() const
{
    return const_iterator(head);
}

template <typename T>
const typename List<T>::const_iterator List<T>::cend() const
{
    return const_iterator(nullptr);
}

template <typename T>
const typename List<T>::const_iterator List<T>::begin()  const
{
    return cbegin();
}

template <typename T>
const typename List<T>::const_iterator List<T>::end() const
{
    return cend();
}

