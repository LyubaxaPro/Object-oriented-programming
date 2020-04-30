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

    // конструктор копирования
   // List(const List<T>& lst);

    // деструктор
    ~List();
    // получить текущий размер списка
    size_t get_length() const ;

    // Проверить на пустоту
    bool is_empty() const ;

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
    T& get_elem(const size_t index) const;

    // удалить элемент списка по индексу
    void remove_elem(const size_t index);

    // объединение списка с другим списком (метод возвращает новый список, содержащий сначала элементы текущего списка, затем, переданного в Combine)
    List<T>& combine(const List<T>& lst);

    // сортировк вставками
    void sort(bool is_increase);

    // развернуть список
    void reverse();

    // создать новый массив, в который записать все элементы списка. Метод возвращает массив.
    T* to_array();

    // если содержится в списке элемент T, возвращает индекс элемента или -1 в случае если элемент не найден.
    int get_index(const T elem);

    //  очистить список
    void clear();

private:
    int length;
    struct Node
    {
        T data;
        Node *next;
        explicit Node(const T& elem);

        explicit Node(const T& elem, const Node *next_ptr);

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
    clear();
}

template<class T>
List<T>::Node:: Node(const T& elem)
{
    data = elem;
    next = nullptr;
}

template<class T>
List<T>::Node::Node(const T& elem, const Node *next_ptr)
{
    data = elem;
    next = new Node*;
    next = next_ptr;
}

template<class T>
size_t List<T>::get_length() const
{
    return length;
}

template<class T>
bool List<T>::is_empty() const
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
        tail->next = cur_node;
        tail = tail->next;
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
        cur_node->next = head;
        head = cur_node;
    }
    length++;
}

template<class T>
T List<T>::pop_back()
{
    if (length == 0)
    {
        std::cout << "List is empty" << std::endl;
        throw 0;
    }
    Node *ptr = head;
    Node *prev_ptr = head;
    while (ptr != tail)
    {
        prev_ptr = ptr;
        ptr = ptr->next;
    }
    T data = ptr->data;
    delete ptr;
    tail = prev_ptr;
    tail->next = nullptr;
    --length;
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
        std::cout << "List is empty" << std::endl;
        throw 0;
    }
    Node *cur_ptr = head->next;
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
        tail->next = lst.head;
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
            copy->next = head;
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
        std::cout << "Wrong index!" << std::endl;
        throw 0;
    }

    size_t count = 0;
    Node *cur_ptr = head;
    while (count != index)
    {
        cur_ptr = cur_ptr->next;
        count++;
    }

    cur_ptr->data = elem;
}

template<class T>
T& List<T>::get_elem(const size_t index) const 
{
    if (index >= length or index < 0)
    {
        std::cout << "Wrong index!" << std::endl;
        throw 0;
    }

    size_t count = 0;
    Node *cur_ptr = head;
    while (count != index)
    {
        cur_ptr = cur_ptr->next;
        count++;
    }
// todo копипаста
    return cur_ptr->data;
}

template<class T>
void List<T>::remove_elem(const size_t index)
{
    if (index >= length or index < 0)
    {
        std::cout << "Wrong index!" << std::endl;
        throw 0;
    }

    if (index == 0)
    {
        Node *elem = head;
        head = head->next;
        delete elem;
    }
    else
    {
        size_t count = 0;
        Node *cur_ptr = head;
        while (count + 1 != index) {
            cur_ptr = cur_ptr->next;
            count++;
        }
        Node *elem = cur_ptr->next;

        cur_ptr->next = elem->next;
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
    result_list->tail->next = lst.head;
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
        array[i++] = ptr->data;
        ptr = ptr->next;
    }
    return array;
}

template<class T>
void List<T>::sort(bool is_increase)
{
    Node *a = nullptr;
    Node *b = nullptr;
    Node *p = nullptr;
    Node *h = nullptr;
    bool condition;

    for(Node *i = head; i != NULL; )
    {
        a = i;
        i = i->next;
        b = h;

        for (p = NULL; (b != nullptr) && (a->data > b->data == is_increase); )
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

template<class T>
void List<T>::reverse()
{
    Node* new_head = nullptr;
    //читаем элементы старого списка
    for(Node *pos = head; pos;)
    {
        Node *save_next = pos->next;
        pos->next = new_head;
        new_head = pos;
        pos = save_next;
    }
    tail = head;
    tail->next = nullptr;
    head = new_head;
}

template<class T>
int List<T>::get_index(const T elem)
{
    size_t count = 0;
    Node *ptr = head;
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

template<class T>
void List<T>::clear()
{
    Node *temp_ptr = head;
    while (head != nullptr)
    {
        delete head;
        temp_ptr = temp_ptr->next;
        head = temp_ptr;
    }
    tail = nullptr;
    length = 0;
}

#endif //OOP2_LIST_H