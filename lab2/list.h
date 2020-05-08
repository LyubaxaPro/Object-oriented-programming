//
// Created by lyubaxapro on 29.04.2020.
//

#ifndef OOP2_LIST_H
#define OOP2_LIST_H

#include <memory>
#include <iostream>
#include <iterator>

#include "list_base.h"
#include "errors.h"

template <typename T>
class List: public ListBase{

private:
    template <typename Ptr, typename Ref>
    class Iterator;

public:
    using iterator =  Iterator<T*, T&>;
    using const_iterator = Iterator<const T*, const T&>;

    iterator begin();
    iterator end();
    const const_iterator cbegin() const;
    const const_iterator cend() const;
    const const_iterator begin() const;
    const const_iterator end() const;


    //Конструкторы
    // конструктор по умолчанию
    List() = default;
    // конструктор копирования
    explicit List(const List<T>& lst);
    //конструктор перемещения
    List(List<T> &&lst);
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

    void remove(const iterator prev);

    void insert(const iterator prev, const T& data);

    // добавить список элементов в конец списка
    void push_range_back(const List<T>& lst);

    // добавить список элементов в начало списка
    void push_range_front(const List<T>& lst);

    //добавить массив элементов в конец списка
    void push_range_back(T *arr, int size);

    //добавить массив элементов в начало списка
    void push_range_front(T *arr, int size);

    // объединение списка с другим списком (метод возвращает новый список, содержащий сначала элементы текущего списка, затем, переданного в Combine)
    List<T> combine(const List<T>& lst);

    // развернуть список
    void reverse();

    // создать новый массив, в который записать все элементы списка. Метод возвращает массив.
    T* to_array();

    std::ostream& to_string (std::ostream& os, const List<T>& lst);

    // перегрузка оператора присваивания
    List<T>& operator =(const List<T>& lst);

    List<T>& operator =(const std::initializer_list<T>& lst);

    // перегрузка оператора +
    List<T> operator +(const T& data) const;

    List<T> operator +(const List<T>& lst) const;

    // перегрузка оператора +=, работает аналогично Combine, значение записывается в this.
    List<T>& operator +=(const List<T>& lst);

    List<T>& operator +=(const T& data);

    bool operator ==(const List<T>& lst) const;

    bool operator != (const List<T>& lst) const;

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
};

#endif //OOP2_LIST_H