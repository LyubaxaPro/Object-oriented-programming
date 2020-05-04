//
// Created by lyubaxapro on 02.05.20.
//

#include "list.h"
#include "errors.h"
#include "iterator.h"

template<typename T>
List<T>::List(const List<T>& lst)
{
    std::shared_ptr<Node> cur_ptr = lst.head;
    while(cur_ptr != nullptr)
    {
        push_back(cur_ptr->data);
        cur_ptr = cur_ptr->next;
    }
}

template<typename T>
List<T>::List(const T *arr, int size)
{
    if (size < 0)
        throw RangeError();
    if (arr == nullptr)
        throw MemError();
    for (size_t i = 0; i < size; i++)
    {
        push_back(arr[i]);
    }
}

template<typename T>
List<T>::List(const std::initializer_list<T>& lst)
{
    for (const auto& it: lst)
    {
        push_back(it);
    }
}

template<typename T>
List<T>::List(List::iterator begin, List::iterator end)
{
    if (!begin.is_valid())
        throw RangeError();

    for (auto i = begin; i != end; ++i)
    {
        push_back(*i);
    }
}

template<typename T>
size_t List<T>::get_length() const
{
    return length;
}

template<typename T>
bool List<T>::is_empty() const
{
    return length == 0;
}

template<typename T>
void List<T>::clear()
{
    size_t size = length;
    for (int i = 0; i < size; i++)
    {
        pop_front();
    }
}

template<typename T>
List<T>::~List()
{
    clear();
}

template<typename T>
void List<T>::push_back(const T &elem)
{
    std::shared_ptr<Node> cur_node = std::make_shared<Node>(elem);
    if (tail == nullptr)
    {
        tail = cur_node;
        head = cur_node;
    }
    else
    {
        tail->next = cur_node;
        tail = tail->next;
    }
    length++;
}

template<typename T>
void List<T>:: push_front(const T &elem)
{
    std::shared_ptr<Node> cur_node = std::make_shared<Node>(elem);
    if (head == nullptr)
    {
        head = cur_node;
        tail = cur_node;
    }
    else
    {
        cur_node->next = head;
        head = cur_node;
    }
    length++;
}

template<typename T>
T List<T>::pop_back()
{
    if (length == 0)
    {
        throw EmptyError();
    }
    std::shared_ptr<Node> ptr = head;
    std::shared_ptr<Node> prev_ptr = head;
    while (ptr != tail)
    {
        prev_ptr = ptr;
        ptr = ptr->next;
    }
    T data = ptr->data;
    ptr.reset();
    tail = prev_ptr;
    tail->next = nullptr;
    --length;
    if (length == 0)
    {
        head = tail = nullptr;
    }
    return data;
}

template<typename T>
T List<T>::pop_front()
{
    if (length == 0)
    {
        throw EmptyError();
    }
    std::shared_ptr<Node> cur_ptr = head->next;
    T data = head->data;
    head.reset();
    head = cur_ptr;
    length--;
    if (length == 0)
    {
        head = tail = nullptr;
    }
    return data;
}

template<typename T>
void List<T>::push_range_back(const List<T> &lst)
{
    if (lst.is_empty()) return;
    for (const auto& it: lst)
    {
        push_back(it);
    }
}

template<typename T>
void List<T>::push_range_front(const List<T> &lst)
{
    if (lst.is_empty()) return;

    List<T> list_copy(lst);
    list_copy.reverse();

    for (const auto& it: list_copy)
    {
        push_front(it);
    }
}

template<typename T>
void List<T>::push_range_back(T *const arr, int size)
{
    if (size < 0)
    {
        throw RangeError();
    }

    if (arr == nullptr)
    {
        throw MemError();
    }

    for (size_t i = 0; i < size; i++)
    {
        push_back(arr[i]);
    }
}

template<typename T>
void List<T>::push_range_front(T *const arr, int size)
{
    if (size < 0)
    {
        throw RangeError();
    }

    if (arr == nullptr)
    {
        throw MemError();
    }

    for (int i = size - 1; i >= 0; i--)
    {
        push_front(arr[i]);
    }
}

template<typename T>
void List<T>::set_elem(int index, const T &elem)
{
    std::shared_ptr<Node> cur_ptr = find_elem_ptr(index);
    cur_ptr->data = elem;
}

template<typename T>
T& List<T>::get_elem(int index) const
{
    std::shared_ptr<Node> cur_ptr = find_elem_ptr(index);
    return cur_ptr->data;
}

template<typename T>
void List<T>::remove_elem(int index)
{
    if (index >= length or index < 0)
    {
        throw RangeError();
    }

    if (index == 0)
    {
        pop_front();
    }

    else if (index == length - 1)
    {
        pop_back();
    }

    else
    {
        size_t count = 0;
        std::shared_ptr<Node> cur_ptr = head;
        while (count + 1 != index) {
            cur_ptr = cur_ptr->next;
            count++;
        }
        std::shared_ptr<Node> elem = cur_ptr->next;

        cur_ptr->next = elem->next;
        elem.reset();
        length--;
    }
}

template<typename T>
List<T> List<T>::combine(const List<T> &lst)
{
    List<T> result_list;
    for (const auto& it: *this) {
        result_list.push_back(it);
    }
    for (const auto& it: lst) {
        result_list.push_back(it);
    }
    return result_list;
}

template<typename T>
T* List<T>::to_array()
{
    T *array = new T[length];
    std::shared_ptr<Node> ptr = head;
    size_t i = 0;
    while (ptr != nullptr)
    {
        array[i++] = ptr->data;
        ptr = ptr->next;
    }
    return array;
}

template<typename T>
void List<T>::sort(bool is_increase)
{
    std::shared_ptr<Node> a;
    std::shared_ptr<Node> b;
    std::shared_ptr<Node> p;
    std::shared_ptr<Node> h = nullptr;

    for(std::shared_ptr<Node>i = head; i != nullptr; )
    {
        a = i;
        i = i->next;
        b = h;

        for (p = nullptr; (b != nullptr) && (a->data > b->data == is_increase); )
        {
            p = b;
            b = b->next;
        }

        if(p == nullptr)
        {
            a->next = h;
            h = a;
        }
        else
        {
            a->next = b;
            p->next = a;
        }
    }
    if(h != nullptr)
        head = h;
    while (h->next != nullptr)
    {
        h = h->next;
    }
    tail = h;
}

template<typename T>
void List<T>::reverse()
{
    std::shared_ptr<Node> new_head = nullptr;
    //читаем элементы старого списка
    for(std::shared_ptr<Node> pos = head; pos;)
    {
        std::shared_ptr<Node> save_next = pos->next;
        pos->next = new_head;
        new_head = pos;
        pos = save_next;
    }
    tail = head;
    tail->next = nullptr;
    head = new_head;
}

template<typename T>
int List<T>::get_index(const T elem)
{
    size_t count = 0;
    std::shared_ptr<Node> ptr = head;
    while (ptr != nullptr)
    {
        if (ptr->data == elem)
        {
            return count;
        }
        ptr = ptr->next;
        count++;
    }
    return -1;
}

template<typename T>
List<T>& List<T>::operator=(const List<T> &lst)
{
    clear();
    std::shared_ptr<Node> cur_ptr = lst.head;
    while (cur_ptr != nullptr)
    {
        push_back(cur_ptr->data);
        cur_ptr = cur_ptr->next;
    }
    return *this;
}


