#include "list.h"
#include "errors.h"
#include "iterator.h"
#include <ctime>

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
    time_t t_time = time(NULL);
    if (size < 0)
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    if (arr == nullptr)
        throw MemError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    for (size_t i = 0; i < size; i++)
    {
        push_back(arr[i]);
    }
}

template<typename T>
List<T>::List(List<T>&& lst)
{
    head = lst.head;
    tail = lst.tail;
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
List<T>::List(iterator begin, iterator end)
{
    for (auto& it = begin; end != it; ++it)
    {
        push_back(it.get());
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
void List<T>::push_back(const T& elem)
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
void List<T>:: push_front(const T& elem)
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
        time_t t_time = time(NULL);
        throw EmptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
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

        time_t t_time = time(NULL);
        throw EmptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
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
void List<T>::push_range_back(const List<T>& lst)
{
    for (const auto& it: lst)
    {
        push_back(it);
    }
}

template<typename T>
void List<T>::push_range_front(const List<T>& lst)
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
    time_t t_time = time(NULL);
    if (size < 0)
    {
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    if (arr == nullptr)
    {
        throw MemError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    for (size_t i = 0; i < size; i++)
    {
        push_back(arr[i]);
    }
}

template<typename T>
void List<T>::push_range_front(T *const arr, int size)
{
    time_t t_time = time(NULL);
    if (size < 0)
    {
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    if (arr == nullptr)
    {
        throw MemError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    for (int i = size - 1; i >= 0; i--)
    {
        push_front(arr[i]);
    }
}

template<typename T>
List<T> List<T>::combine(const List<T>& lst)
{
    List<T> result_list;
    for (const auto& it: *this)
    {
        result_list.push_back(it);
    }
    for (const auto& it: lst)
    {
        result_list.push_back(it);
    }
    return result_list;
}

template<typename T>
T* List<T>::to_array()
{
    T *array = new T[length];
    size_t i = 0;

    for (const auto& it: *this)
    {
        array[i++] = it;
    }
    return array;
}

template<typename T>
void List<T>::reverse()
{
    if (is_empty()) return;
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
std::ostream& List<T>::to_string(std::ostream& os, const List<T>& lst)
{
    os << "List ";
    for (const auto& it: lst)
    {
        os << it << "->";
    }
    os << std::endl;
    return os;
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& lst)
{
    clear();
    for (const auto& it: lst)
    {
        push_back(it);
    }
    return *this;
}


template<typename T>
List<T>& List<T>::operator=(const std::initializer_list<T>& lst)
{
    clear();
    for (const auto& it: lst)
    {
        push_back(it);
    }
    return *this;
}

template<typename T>
List<T> List<T>::operator+(const T& data) const
{
    List<T> res_list;
    res_list.push_range_back(*this);
    res_list.push_back(data);
    return res_list;
}

template<typename T>
List<T> List<T>::operator+(const List<T>& lst) const
{
    List<T> result_list;
    for (const auto& it: *this)
    {
        result_list.push_back(it);
    }
    for (const auto& it: lst)
    {
        result_list.push_back(it);
    }
    return result_list;
}

template<typename T>
List<T>& List<T>::operator+=(const List<T>& lst)
{
    push_range_back(lst);
    return *this;
}

template<typename T>
List<T>& List<T>::operator+=(const T& data)
{
    push_back(data);
    return *this;
}

template<typename T>
bool List<T>::operator==(const List<T>& lst) const
{
    if (length != lst.length) return false;
    std::shared_ptr<Node> curr_ptr = head;
    for (const auto& it: lst)
    {
        if (curr_ptr->data != it) return false;
        curr_ptr = curr_ptr->next;
    }
    return true;
}

template<typename T>
bool List<T>::operator!=(const List<T>& lst) const
{
    return !(*this == lst);
}

template<typename T>
void List<T>::remove(const List::iterator prev)
{
    if (prev == end())
    {
        time_t t_time = time(NULL);
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }

    std::weak_ptr<Node> curr = prev.get_node().lock()->next;
    prev.get_node().lock()->next = curr.lock()->next;
    curr.reset();
    --length;
}

template<typename T>
void List<T>::insert(const List::iterator prev, const T& data)
{
    if (prev == end())
    {
        time_t t_time = time(NULL);
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));
    }
    std::shared_ptr<Node> new_ptr = std::make_shared<Node>(data);
    std::shared_ptr<Node> next = prev.get_node().lock()->next;
    prev.get_node().lock()->next = new_ptr;
    new_ptr->next = next;
    ++length;
}





