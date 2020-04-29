//
// Created by lyubaxapro on 29.04.2020.
//

#ifndef OOP2_LIST_H
#define OOP2_LIST_H

template <class T>
class List
{
public:
    // конструктор по умолчанию
    List();

    // деструктор
    ~List();
    // получить текущий размер списка
    size_t get_lenght();

    // Проверить на пустоту
    bool is_empty();

    // добавить элемент в конец списка
    void push_back(const T& elem);

    // добавить элемент в начало списка
    void push_front(const T& elem);

    // удалить последний элемент
    T pop_back();

    // удалить первый элемент
    T pop_front();

    // добавить список элементов в конец списка
    void push_range_back(const List<T>& lst);

    // добавить список элементов в начало списка
    void push_range_front(const List<T>& lst);

    //добавить массив элементов в конец списка
    void push_range_back(T *const arr, const size_t size);

    //добавить массив элементов в начало списка
    void push_range_front(T *const arr, const size_t size);

    // изменить элемент списка по индексу
    void set_elem(const size_t index,const T& elem);

    // получить элемент списка по индексу
    T& get_elem(const size_t index);

    // удалить элемент списка по индексу
    void remove_elem(const size_t index);

    // объединение списка с другим списком (метод возвращает новый список, содержащий сначала элементы текущего списка, затем, переданного в Combine)
    List<T>& combine(const List<T>& lst);

private:
    int lenght;
    struct Node
    {
        T data;
        Node *ptr;
        explicit Node(const T& elem)
        {
            data = elem;
            ptr = nullptr;
        }

        explicit Node(const T& elem, const Node *next_ptr)
        {
            data = elem;
            ptr = new Node*;
            ptr = next_ptr;
        }

        ~Node()= default;
    };

    Node *begin;
    Node *end;

};

template<class T>
List<T>::List()
{
    lenght = 0;
    begin = nullptr;
    end = nullptr;
}

template<class T>
List<T>::~List()
{
    Node *temp_ptr = begin;
    while (begin != nullptr)
    {
        delete begin;
        temp_ptr = temp_ptr->ptr;
        begin = temp_ptr;
    }
}

template<class T>
size_t List<T>::get_lenght()
{
    return lenght;
}

template<class T>
bool List<T>::is_empty()
{
    return lenght == 0;
}

template<class T>
void List<T>::push_back(const T &elem)
{
    Node *cur_node = new Node(elem);
    if (end == nullptr)
    {
        end = cur_node;
        begin = cur_node;
    }

    else
    {
        end->ptr = cur_node;
        end = end->ptr;
    }
    lenght++;
}

template<class T>
void List<T>:: push_front(const T &elem)
{
    Node *cur_node = new Node(elem);
    if (begin == nullptr)
    {
        begin = cur_node;
        end = cur_node;
    }
    else
    {
        cur_node->ptr = begin;
        begin = cur_node;
    }
    lenght++;
}

template<class T>
T List<T>::pop_back()
{
    if (lenght == 0)
    {
        std::cout << "List is empty" << std::endl;
        throw 0;
    }
    Node *ptr = begin;
    Node *prev_ptr = begin;
    while (ptr != end)
    {
        prev_ptr = ptr;
        ptr = ptr->ptr;
    }
    T data = ptr->data;
    delete ptr;
    end = prev_ptr;
    end->ptr = nullptr;
    lenght --;
    if (lenght == 0)
    {
        begin = end = nullptr;
    }
    return data;
}

template<class T>
T List<T>::pop_front()
{
    if (lenght == 0)
    {
        std::cout << "List is empty" << std::endl;
        throw 0;
    }
    Node *cur_ptr = begin->ptr;
    T data = begin->data;
    delete begin;
    begin = cur_ptr;
    lenght--;
    if (lenght == 0)
    {
        begin = end = nullptr;
    }
    return data;
}

template<class T>
void List<T>::push_range_back(const List<T> &lst)
{
    if (begin == nullptr)
    {
        begin = lst.begin;
        end = lst.end;
    }
    else
    {
        end->ptr = lst.begin;
        if (lst.begin != nullptr)
            end = lst.end;
    }
    lenght += lst.lenght;
}
// todo: сделать так чтоб push_range_front(const List<T> &lst) не изменяла вставляемый список
template<class T>
void List<T>::push_range_front(const List<T> &lst)
{
    if (begin == nullptr)
    {
        begin = lst.begin;
        end = lst.end;
    }
    else
    {
        if (lst.end != nullptr)
        {
            Node *copy = lst.end;
            copy->ptr = begin;
            begin = lst.begin;
        }
    }
    lenght += lst.lenght;
}

template<class T>
void List<T>::push_range_back(T *const arr, const size_t size)
{
    for (int i = 0; i < size; i++)
    {
        push_back(arr[i]);
    }
}

template<class T>
void List<T>::push_range_front(T *const arr, const size_t size)
{
    for (int i = 0; i < size; i++)
    {
        push_front(arr[i]);
    }
}

template<class T>
void List<T>::set_elem(const size_t index, const T &elem)
{
    if (index >= lenght or index < 0)
    {
        std::cout << "Wrong index!" << std::endl;
        throw 0;
    }

    size_t count = 0;
    Node *cur_ptr = begin;
    while (count != index)
    {
        cur_ptr = cur_ptr->ptr;
        count++;
    }

    cur_ptr->data = elem;
}

template<class T>
T& List<T>::get_elem(const size_t index)
{
    if (index >= lenght or index < 0)
    {
        std::cout << "Wrong index!" << std::endl;
        throw 0;
    }

    size_t count = 0;
    Node *cur_ptr = begin;
    while (count != index)
    {
        cur_ptr = cur_ptr->ptr;
        count++;
    }

    return cur_ptr->data;
}

template<class T>
void List<T>::remove_elem(const size_t index)
{
    if (index >= lenght or index < 0)
    {
        std::cout << "Wrong index!" << std::endl;
        throw 0;
    }

    if (index == 0)
    {
        Node *elem = begin;
        begin = begin->ptr;
        delete elem;
    }
    else
    {
        size_t count = 0;
        Node *cur_ptr = begin;
        while (count + 1 != index) {
            cur_ptr = cur_ptr->ptr;
            count++;
        }
        Node *elem = cur_ptr->ptr;

        cur_ptr->ptr = elem->ptr;
        delete elem;
    }
    lenght--;
}

template<class T>
List<T>& List<T>::combine(const List<T> &lst)
{

}

#endif //OOP2_LIST_H
