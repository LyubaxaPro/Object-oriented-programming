//
// Created by lyubaxapro on 03.05.2020.
//


#include "gtest/gtest.h"
#include "../list.hpp"
#include "../iterator.hpp"

TEST(ConstructorTest, constructor_from_array_size_1)
{
    int arr1[1] = {2};
    List<int> list1(arr1, 1);
    ASSERT_TRUE(*list1.begin() == 2);
}

TEST(ConstructorTest, constructor_from_array_size_n)
{
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr_size = 5;
    int i = 0;
    List<int> list1(arr1, 5);
    for (const auto& it: list1)
    {
        ASSERT_TRUE(i < arr_size);
        ASSERT_TRUE(it == arr1[i]);
        i++;
    }
    ASSERT_TRUE(true);
}

TEST(ConstructorTest, constructor_from_array_bad_size)
{
    int arr1[5] = {1, 2, 3, 4, 5};
    ASSERT_THROW(List<int> list1(arr1, -5), RangeError);
}

TEST(ConstructorTest, constructor_from_array_bad_ptr)
{
    int *arr = nullptr;
    ASSERT_THROW(List<int> list(arr, 3), MemError);
}

TEST(ConstructorTest, copy_list_constructor)
{
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr_size = 5;
    int i = 0;
    List<int> list1(arr1, 5);
    List<int> list2(list1);

    for (const auto& it: list2)
    {
        ASSERT_TRUE(i < arr_size);
        ASSERT_TRUE(it == arr1[i]);
        i++;
    }
    ASSERT_TRUE(true);
}

TEST(ConstructorTest, constructor_from_initializer_list)
{
    List<int> list1({1, 2, 3, 4});
    int arr1[4] = {1, 2, 3, 4};
    int i = 0;

    for (const auto& it: list1) {
        ASSERT_TRUE(i < 4);
        ASSERT_TRUE(it == arr1[i]);
        i++;
    }
    ASSERT_TRUE(true);
}

TEST(ConstructorTest, constructor_using_iterator)
{
    List<int> list2({1, 2, 3, 4});
    List<int> list1(list2.begin(), list2.end());
    int arr1[4] = {1, 2, 3, 4};
    int i = 0;

    for (const auto& it: list1) {
        ASSERT_TRUE(i < 4);
        ASSERT_TRUE(it == arr1[i]);
        i++;
    }
    ASSERT_TRUE(true);
}

TEST(ConstructorTest, constructor_using_iterator_with_nullptr_begin)
{
    List<int> list2({1, 2, 3, 4});
    ASSERT_THROW(List<int> list1(list2.end(), list2.begin()),RangeError);
}

TEST(Method_get_lenght, zero_lenght)
{
    List<int> List1;
    ASSERT_TRUE(List1.get_length() == 0);
}

TEST(Method_get_lenght, n_lenght)
{
    List<int> list2({1, 2, 3, 4});
    ASSERT_TRUE(list2.get_length() == 4);
}

TEST(Method_is_empty, empty_list)
{
    List<int> list1;
    ASSERT_TRUE(list1.is_empty());
}

TEST(Method_is_empty, not_empty_list)
{
    List<int> list2({1, 2, 3, 4});
    ASSERT_FALSE(list2.is_empty());
}

TEST(Method_clear, full_list)
{
    List<float> list({1, 2, 3, 4});
    list.clear();
    ASSERT_TRUE(list.get_length() == 0);
}

TEST(Method_clear, empty_list)
{
    List<char> list;
    list.clear();
    ASSERT_TRUE(list.get_length() == 0);
}

TEST(Method_push_back, in_empty_list)
{
    List<char> list;
    list.push_back('a');
    ASSERT_TRUE(list.begin().value() == 'a' && list.get_length() == 1);
}

TEST(Method_push_back, in_full_list)
{
    List<int> list({1, 1});
    list.push_back(1);
    for (const auto& it: list)
    {
        ASSERT_TRUE(it == 1);
    }
    ASSERT_TRUE(list.get_length() == 3);
}

TEST(Method_push_front, in_empty_list)
{
    List<char> list;
    list.push_front('a');
    ASSERT_TRUE(list.begin().value() == 'a' && list.get_length() == 1);
}

TEST(Method_push_front, in_full_list)
{
    List<int> list({1, 1});
    list.push_front(1);
    for (const auto& it: list)
    {
        ASSERT_TRUE(it == 1);
    }
    ASSERT_TRUE(list.get_length() == 3);
}

TEST(Method_pop_back, from_empty_list)
{
    List<int> list;
    ASSERT_THROW(list.pop_back(), EmptyError);
}

TEST(Method_pop_back, from_full_list)
{
    List<int> list({1, 2, 3});
    ASSERT_TRUE(list.pop_back() == 3 && list.get_length() == 2);
}

TEST(Method_pop_back, from_one_elem_list)
{
    List<int> list({1});
    ASSERT_TRUE(list.pop_back() == 1 && list.is_empty());
}

TEST(Method_pop_front, from_empty_list)
{
    List<int> list;
    ASSERT_THROW(list.pop_front(), EmptyError);
}

TEST(Method_pop_front, from_full_list)
{
    List<int> list({1, 2, 3});
    ASSERT_TRUE(list.pop_front() == 1 && list.get_length() == 2);
}

TEST(Method_pop_front, from_one_elem_list)
{
    List<int> list({1});
    ASSERT_TRUE(list.pop_front() == 1 && list.is_empty());
}

TEST(Method_push_range_back, push_empty_list)
{
    List<int> list({1, 2, 3});
    List<int> list2({1, 2, 3});
    List<int> list1;
    list.push_range_back(list1);
    ASSERT_TRUE(list == list2);
}

TEST(Method_push_range_back, push_in_empty_list)
{
    List<int> list({1, 2, 3});
    List<int> list2({1, 2, 3});
    List<int> list1;
    list1.push_range_back(list);
    ASSERT_TRUE(list1 == list2);
}

TEST(Method_push_range_back, push_list)
{
    List<int> list({1, 2, 3});
    List<int> list2({4, 5, 6});
    int t[6] = {1, 2, 3, 4, 5, 6};
    list.push_range_back(list2);
    size_t i = 0;
    ASSERT_TRUE(list.get_length() == 6);
    for (const auto& it: list)
    {
        ASSERT_TRUE(it == t[i]);
        i++;
    }
}

TEST(Method_push_range_front, push_empty_list)
{
    List<int> list({1, 2, 3});
    List<int> list2({1, 2, 3});
    List<int> list1;
    list.push_range_front(list1);
    ASSERT_TRUE(list == list2);
}

TEST(Method_push_range_front, push_list)
{
    List<int> list({1, 2, 3});
    List<int> list2({4, 5, 6});
    int t[6] = {4, 5, 6, 1, 2, 3};
    list.push_range_front(list2);
    size_t i = 0;
    ASSERT_TRUE(list.get_length() == 6);
    for (const auto& it: list)
    {
        ASSERT_TRUE(it == t[i]);
        i++;
    }
}

TEST(Method_push_range_front, push_in_empty_list)
{
    List<int> list({1, 2, 3});
    List<int> list2({1, 2, 3});
    List<int> list1;
    list1.push_range_front(list);
    ASSERT_TRUE(list1 == list2);
}

TEST(Method_push_range_back, push_arr_with_bad_size)
{
    int arr[3] = {3, 3, 3};
    List<int> list;
    ASSERT_THROW(list.push_range_back(arr, -3), RangeError);
}

TEST(Method_push_range_back, push_arr_with_bad_ptr)
{
    List<int> list;
    ASSERT_THROW(list.push_range_back(nullptr, 3), MemError);
}

TEST(Method_push_range_back, push_arr)
{
    List<int> list({3});
    int arr[3] = {4, 5, 6};
    int new_arr[4] = {3, 4, 5, 6};
    list.push_range_back(arr, 3);
    ASSERT_TRUE(list.get_length() == 4);
    size_t i = 0;
    for (const auto& it: list)
    {
        ASSERT_TRUE(it == new_arr[i]);
        i++;
    }
}

TEST(Method_push_range_front, push_arr_with_bad_size)
{
    int arr[3] = {3, 3, 3};
    List<int> list;
    ASSERT_THROW(list.push_range_front(arr, -3), RangeError);
}

TEST(Method_push_range_front, push_arr_with_bad_ptr)
{
    List<int> list;
    ASSERT_THROW(list.push_range_front(nullptr, 3), MemError);
}

TEST(Method_push_range_front, push_arr)
{
    List<int> list({3});
    int arr[3] = {4, 5, 6};
    int new_arr[4] = {4, 5, 6, 3};
    list.push_range_front(arr, 3);
    ASSERT_TRUE(list.get_length() == 4);
    size_t i = 0;
    for (const auto& it: list)
    {
        ASSERT_TRUE(it == new_arr[i]);
        i++;
    }
}

TEST(Method_set_elem, index_is_negative)
{
    List<int> list;
    ASSERT_THROW(list.set_elem(-4, 3), RangeError);
}

TEST(Method_set_elem, index_out_of_list)
{
    List<int> list;
    ASSERT_THROW(list.set_elem(4, 3), RangeError);
}

TEST(Method_set_elem, set_elem)
{
    List<int> list({4, 5, 6, 7, 8});
    list.set_elem(3, 0);

    List<int> right_list({4, 5, 6, 0, 8});

    ASSERT_TRUE(right_list == list);
}

TEST(Method_get_elem, index_is_negative)
{
    List<int> list;
    ASSERT_THROW(list.get_elem(-4), RangeError);
}

TEST(Method_get_elem, index_out_of_list)
{
    List<int> list;
    ASSERT_THROW(list.get_elem(4), RangeError);
}

TEST(Method_get_elem, get_elem)
{
    List<int> list({4, 5, 6, 7, 8});
    int elem = list.get_elem(3);
    List<int> right_list({4, 5, 6, 7, 8});

    ASSERT_TRUE(right_list == list && elem == 7);
}

TEST(Method_remove_elem, index_is_negative)
{
    List<int> list;
    ASSERT_THROW(list.remove_elem(-4), RangeError);
}

TEST(Method_remove_elem, index_out_of_list)
{
    List<int> list;
    ASSERT_THROW(list.remove_elem(4), RangeError);
}

TEST(Method_remove_elem, remove_elem)
{
    List<int> list({4, 5, 6, 7, 8});
    list.remove_elem(3);
    List<int> right_list({4, 5, 6, 8});

    ASSERT_TRUE(right_list == list );
}

TEST(Method_combine, both_empty)
{
    List<int> list;
    List<int> list_a;
    List<int> list_b;

    List<int> list_res;
    list = list_a.combine(list_b);
    ASSERT_TRUE(list_res == list);
}

TEST(Method_combine, this_empty)
{
    List<int> list;
    List<int> list_a;
    List<int> list_b({1, 2, 3});

    list = list_a.combine(list_b);
    ASSERT_TRUE(list == list_b);
}

TEST(Method_combine, arg_empty)
{
    List<int> list;
    List<int> list_b;
    List<int> list_a({1, 2, 3});

    list = list_a.combine(list_b);
    ASSERT_TRUE(list == list_a);
}

TEST(Method_combine, both_full)
{
    List<int> list;
    List<int> list_b({4, 5, 6});
    List<int> list_a({1, 2, 3});

    int a[6] = {1, 2, 3, 4, 5, 6};
    List<int> list_res;
    list = list_a.combine(list_b);
    size_t i = 0;
    for (const auto& it: list)
    {
        ASSERT_TRUE(it == a[i]);
        i++;
    }
}

TEST(Method_to_array, list_to_array)
{
    List<int> list({1, 2, 3});
    int *arr = list.to_array();
    size_t i = 0;

    for (const auto& it: list)
    {
        ASSERT_TRUE(arr[i] == it);
        i++;
    }
    delete arr;
}

TEST(Method_sort, sort_empty_list)
{
    List<int> list;
    List<int> list_res;
    list.sort(true);
    ASSERT_TRUE(list == list_res);
}

TEST(Method_sort, is_increase)
{
    List<int> list({1, 4, 2, 3, 5});
    List<int> list_res({1, 2, 3, 4, 5});
    list.sort(true);
    ASSERT_TRUE(list == list_res);
}

TEST(Method_sort, is_not_increase)
{
    List<int> list({1, 4, 2, 3, 5});
    List<int> list_res({5, 4, 3, 2, 1});
    list.sort(false);
    ASSERT_TRUE(list == list_res);
}

TEST(Method_sort, list_have_dublicates)
{
    List<int> list({1, 2, 1, 2, 1, 2});
    List<int> list_res({1, 1, 1, 2, 2, 2});
    list.sort(true);
    ASSERT_TRUE(list_res == list);
}

TEST(Method_reverse, empty_list)
{
    List<int> list;
    List<int> result;
    list.reverse();
    ASSERT_TRUE(list == result);
}

TEST(Method_reverse, reverse_list)
{
    List<int> list({1, 2, 3});
    List<int> result({3, 2, 1});
    list.reverse();
    ASSERT_TRUE(list == result);
}

TEST(Method_get_index, empty_list)
{
    List<int> list;
    int index = list.get_index(5);
    ASSERT_TRUE(index == -1);
}

TEST(Method_get_index, list_do_not_have_this_elem)
{
    List<int> list({1, 2, 3});
    int index = list.get_index(5);
    ASSERT_TRUE(index == -1);
}

TEST(Method_get_index, list_have_this_elem)
{
    List<int> list({1, 2, 3});
    int index = list.get_index(2);
    ASSERT_TRUE(index == 1);
}

TEST(Operator_assignment , empty_list)
{
    List<int> list;
    List<int> res = list;
    ASSERT_TRUE(list == res);
}

TEST(Operator_assignment ,  full_list)
{
    List<int> list({1, 2, 3});
    List<int> res = list;
    ASSERT_TRUE(list == res);
}

TEST(Operator_plus_two_arg, both_empty)
{
    List<int> list;
    List<int> list_a;
    List<int> list_b;

    List<int> list_res;
    list = list_a + list_b;
    ASSERT_TRUE(list_res == list);
}

TEST(Operator_plus_two_arg, one_empty)
{
    List<int> list;
    List<int> list_a;
    List<int> list_b({1, 2, 3});

    list = list_a + list_b;
    ASSERT_TRUE(list == list_b);
}

TEST(Operator_plus_two_arg, both_full)
{
    List<int> list;
    List<int> list_b({4, 5, 6});
    List<int> list_a({1, 2, 3});

    int a[6] = {1, 2, 3, 4, 5, 6};
    List<int> list_res;
    list = list_a + list_b;
    size_t i = 0;
    for (const auto& it: list)
    {
        ASSERT_TRUE(it == a[i]);
        i++;
    }
}

TEST(Operator_plus_T_elem, plus)
{
    List<int> list;
    List<int> list1;
    list1 = list + 5;
    ASSERT_TRUE(list1.get_length() == 1 && list1.get_elem(0) == 5);
}

TEST(Operator_plus_one_arg, both_full)
{
    List<int> list;
    List<int> list_b({4, 5, 6});
    List<int> list_a({1, 2, 3});

    int a[6] = {1, 2, 3, 4, 5, 6};
    List<int> list_res;
    list = list_a + list_b;
    size_t i = 0;
    for (const auto& it: list)
    {
        ASSERT_TRUE(it == a[i]);
        i++;
    }
}

TEST(Operator_plus_assignment, plus_to_empty_empty)
{
    List<int> list;
    List<int> list1;
    List<int> res;

    list += list1;
    ASSERT_TRUE(list == res);
}

TEST(Operator_plus_assignment, plus_to_full_empty)
{
    List<int> list({1, 2, 3});
    List<int> list1;
    List<int> res({1, 2, 3});

    list += list1;
    ASSERT_TRUE(list == res);
}

TEST(Operator_plus_assignment, plus_assigment)
{
    List<int> list({1, 2, 3});
    List<int> list1({4, 5 ,6});
    List<int> res({1, 2, 3, 4, 5, 6});

    list += list1;
    ASSERT_TRUE(list == res);
}

TEST(Operator_equal, empty_list)
{
    List<int> list;
    List<int> list1;
    ASSERT_TRUE(list == list1);
}

TEST(Operator_equal, equal)
{
    List<int> list({1, 2});
    List<int> list1({1, 2});
    ASSERT_TRUE(list == list1);
}

TEST(Operator_equal, not_equal)
{
    List<int> list({2, 2});
    List<int> list1({1, 2});
    ASSERT_FALSE(list == list1);
}

TEST(Operator_not_equal, empty_list)
{
    List<int> list;
    List<int> list1;
    ASSERT_FALSE(list != list1);
}

TEST(Operator_not_equal, equal)
{
    List<int> list({1, 2});
    List<int> list1({1, 2});
    ASSERT_FALSE(list != list1);
}

TEST(Operator_not_equal, not_equal)
{
    List<int> list({2, 2});
    List<int> list1({1, 2});
    ASSERT_TRUE(list != list1);
}




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
