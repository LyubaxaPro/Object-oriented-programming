//
// Created by lyubaxapro on 03.05.2020.
//


#include "gtest/gtest.h"
#include "../list.h"
#include "../iterator.h"
#include "../list.cpp"
#include "../errors.h"

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
    for (auto it: list1)
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

    for (auto it: list2)
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

    for (auto it: list1) {
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

    for (auto it: list1) {
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
    for (auto it: list)
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
    for (auto it: list)
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

TEST(Method_pop_frot, from_one_elem_list)
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




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
