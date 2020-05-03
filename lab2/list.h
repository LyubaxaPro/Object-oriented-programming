//
// Created by lyubaxapro on 29.04.2020.
//

#ifndef OOP2_LIST_H
#define OOP2_LIST_H

#include <memory>
#include <iostream>
#include <iterator>

#include "list_base.h"

template <typename T>
class List: ListBase{

private:
    template <typename Ptr, typename Ref, typename ListPtr>
    class Iterator;

public:
    using iterator =  Iterator<T*, T&, List<T>*>;
    using const iterator =  Iterator<T*, T&, List<T>*>;

    iterator begin() {
        return iterator(this, true);
    }
    iterator end() {
        return iterator(this, false);
    }

    //Конструкторы
    // конструктор по умолчанию
    List() = default;
    // конструктор копирования
    List(const List<T>& lst);
    // список из массива
    List(const T *arr, int size);
    //явный конструктор со списком инициализации
    List(const std::initializer_list<T>& lst);
    //инициализация через итераторы
    List(iterator begin, iterator end);


    // деструктор
    ~List();

    // получить текущий размер списка
    size_t get_length() const override;

    // Проверить на пустоту
    bool is_empty() const override;

    //  очистить список
    void clear() override;

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
    void push_range_back(T *const arr, const size_t& size);

    //добавить массив элементов в начало списка
    void push_range_front(T *const arr, const size_t size);
// todo разобраться с const const&
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


    // перегрузка оператора присваивания
    List<T>& operator =(const List<T>& lst);

    // перегрузка оператора +, работает аналогично Combine.
    friend List<T> operator +(const List<T>& l1, const List<T>& l2) {
        List <T>result_list;
        auto curr_ptr = l1.head;
        while (curr_ptr != nullptr) {
            result_list->push_back(curr_ptr->data);
            curr_ptr = curr_ptr->next;
        }

        curr_ptr = l2.head;
        while (curr_ptr != nullptr) {
            result_list->push_back(curr_ptr->data);
            curr_ptr = curr_ptr->next;
        }

        return *result_list;
    }



        // перегрузка оператора +
    List<T>& operator +(const T& data) //todo T&
    {
        push_back(data);
        return *this;
    }

    List<T>& operator +(const List<T>& lst)
    {
        std::shared_ptr<Node> curr_ptr = lst.head;

        while (curr_ptr != nullptr)
        {
            push_back(curr_ptr->data);
            curr_ptr = curr_ptr->next;
        }
        return *this;
    }

    // перегрузка оператора +=, работает аналогично Combine, значение записывается в this.
    List<T>& operator +=(const List<T>& lst)
    {
        std::shared_ptr<Node> curr_ptr = lst.head;

        while (curr_ptr != nullptr)
        {
            push_back(curr_ptr->data);
            curr_ptr = curr_ptr->next;
        }
        return *this;
    }

    List<T>& operator +=(const T data)
    {
        push_back(data);
        return *this;
    }

    bool operator ==(const List<T>& lst) const
    {
        if (length != lst.length) return false;

        std::shared_ptr<Node> curr_ptr = head;
        std::shared_ptr<Node> lst_curr_ptr = lst.head;
        while(curr_ptr != nullptr && lst_curr_ptr != nullptr)
        {
            if (curr_ptr->data != lst_curr_ptr->data) return false;
        }
        return true;
    }

    bool operator != (const List<T>& lst) const
    {
        if (length != lst.length) return true;

        std::shared_ptr<Node> curr_ptr = head;
        std::shared_ptr<Node> lst_curr_ptr = lst.head;
        while(curr_ptr != nullptr && lst_curr_ptr != nullptr)
        {
            if (curr_ptr->data != lst_curr_ptr->data) return true;
        }
        return false;
    }

    friend std::ostream& operator <<(std::ostream& os, const List<T>& lst)
    {
        os << "List ";
        std::shared_ptr<Node> curr_ptr = lst.head;
        while(curr_ptr != nullptr)
        {
            os << curr_ptr->data << "->";
            curr_ptr = curr_ptr->next;
        }
        os << std::endl;
        return os;
    }

protected:
    struct Node
    {
        T data;
        std::shared_ptr<Node> next = nullptr;
        explicit Node(const T& elem) : data(elem) {};

        ~Node() = default;
    };


private:
    size_t length = 0;
    std::shared_ptr<Node> head = nullptr;
    std::shared_ptr<Node> tail = nullptr;

    std::shared_ptr<Node> find_elem_ptr(const size_t index)
    {
        if (index >= length or index < 0)
        {
            std::cout << "Wrong index!" << std::endl;
            throw 0;
        }

        size_t count = 0;
        std::shared_ptr<Node> curr_ptr = head;
        while (count != index)
        {
            curr_ptr = curr_ptr->next;
            count++;
        }

        return curr_ptr;
    }

};

#endif //OOP2_LIST_H