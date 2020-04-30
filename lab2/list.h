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
    size_t get_length();

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

    // отсортировать
    void sort(bool increase);

    // создать новый массив, в который записать все элементы списка. Метод возвращает массив.
    T* to_array();

    // создать новый список из элементов массива
    List<T>& to_list(T *const arr, const size_t size);

private:
    int length;
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

    Node *head;
    Node *tail;

};

template<class T>
List<T>::List()
{
    length = 0;
    head = nullptr;
    tail = nullptr;
}

template<class T>
List<T>::~List()
{
    Node *temp_ptr = head;
    while (head != nullptr)
    {
        delete head;
        temp_ptr = temp_ptr->ptr;
        head = temp_ptr;
    }
}

template<class T>
size_t List<T>::get_length()
{
    return length;
}

template<class T>
bool List<T>::is_empty()
{
    return length == 0;
}

template<class T>
void List<T>::push_back(const T &elem)
{
    Node *cur_node = new Node(elem);
    if (tail == nullptr)
    {
        tail = cur_node;
        head = cur_node;
    }

    else
    {
        tail->ptr = cur_node;
        tail = tail->ptr;
    }
    length++;
}

template<class T>
void List<T>:: push_front(const T &elem)
{
    Node *cur_node = new Node(elem);
    if (head == nullptr)
    {
        head = cur_node;
        tail = cur_node;
    }
    else
    {
        cur_node->ptr = head;
        head = cur_node;
    }
    length++;
}

template<class T>
T List<T>::pop_back()
{
    if (length == 0)
    {
        std::cout << "List is empty" << std::taill;
        throw 0;
    }
    Node *ptr = head;
    Node *prev_ptr = head;
    while (ptr != tail)
    {
        prev_ptr = ptr;
        ptr = ptr->ptr;
    }
    T data = ptr->data;
    delete ptr;
    tail = prev_ptr;
    tail->ptr = nullptr;
    length --;
    if (length == 0)
    {
        head = tail = nullptr;
    }
    return data;
}

template<class T>
T List<T>::pop_front()
{
    if (length == 0)
    {
        std::cout << "List is empty" << std::taill;
        throw 0;
    }
    Node *cur_ptr = head->ptr;
    T data = head->data;
    delete head;
    head = cur_ptr;
    length--;
    if (length == 0)
    {
        head = tail = nullptr;
    }
    return data;
}

template<class T>
void List<T>::push_range_back(const List<T> &lst)
{
    if (head == nullptr)
    {
        head = lst.head;
        tail = lst.tail;
    }
    else
    {
        tail->ptr = lst.head;
        if (lst.head != nullptr)
            tail = lst.tail;
    }
    length += lst.length;
}
// todo: сделать так чтоб push_range_front(const List<T> &lst) не изменяла вставляемый список
template<class T>
void List<T>::push_range_front(const List<T> &lst)
{
    if (head == nullptr)
    {
        head = lst.head;
        tail = lst.tail;
    }
    else
    {
        if (lst.tail != nullptr)
        {
            Node *copy = lst.tail;
            copy->ptr = head;
            head = lst.head;
        }
    }
    length += lst.length;
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
    if (index >= length or index < 0)
    {
        std::cout << "Wrong index!" << std::taill;
        throw 0;
    }

    size_t count = 0;
    Node *cur_ptr = head;
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
    if (index >= length or index < 0)
    {
        std::cout << "Wrong index!" << std::taill;
        throw 0;
    }

    size_t count = 0;
    Node *cur_ptr = head;
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
    if (index >= length or index < 0)
    {
        std::cout << "Wrong index!" << std::taill;
        throw 0;
    }

    if (index == 0)
    {
        Node *elem = head;
        head = head->ptr;
        delete elem;
    }
    else
    {
        size_t count = 0;
        Node *cur_ptr = head;
        while (count + 1 != index) {
            cur_ptr = cur_ptr->ptr;
            count++;
        }
        Node *elem = cur_ptr->ptr;

        cur_ptr->ptr = elem->ptr;
        delete elem;
    }
    length--;
}

template<class T>
List<T>& List<T>::combine(const List<T> &lst)
{
    List<T> *result_list = new List<T>;
    result_list->head = head;
    result_list->tail = tail;
    result_list->tail->ptr = lst.head;
    result_list->tail = lst.tail;
    result_list->length = length + lst.length;

    return *result_list;
}

template<class T>
T* List<T>::to_array()
{
    T *array = new T[length];
    Node *ptr = head;
    size_t i = 0;
    while (ptr != nullptr)
    {
      array[i] = ptr->data;
      ptr = ptr->ptr;
      i++;
    }
    return array;
}


//функция для сортировки по возрастанию
template <class T>
int comp_inc (const void * a, const void * b)
{
  return ( *(T*)a - *(T*)b );
}

//функция для сортировки по убыванию
template <class T>
int comp_dec (const void * a, const void * b)
{
  return ( *(T*)b - *(T*)a );
}

template <class T>
void List<T>::sort(bool increase)
{
    T* arr = this->to_array();
    if(increase)
        qsort(arr, length, sizeof(T), comp_inc<T>);
    else
        qsort(arr, length, sizeof(T), comp_dec<T>);

    List<T> = to_list(arr, length);
    delete [] arr;


}

template <class T>
List<T>& List<T>::to_list(T *const arr, const size_t size)
{
    List<T> *result_list = new List<T>;
    *result_list->length = size;
    for (size_t i = 0; i < size; i++)
    {
        *result_list->push_back(arr[i]);
    }

    return *result_list;

}


#tailif //OOP2_LIST_H
