/*
 * @Author: zhzhou33
 * @Date: 2022-05-30 19:52:38
 * @LastEditors: zhzhou33
 * @LastEditTime: 2022-08-27 15:57:30
 */
#pragma once

#include <cstddef>
namespace MyTinySTL
{
    //以下五大空类相互继承，使用也不会有额外的负担
    //数据只读
    struct input_iterator_tag
    {
    };
    //数据只写
    struct output_iterator_tag
    {
    };
    //允许读写，但只能单方向递增
    struct forward_iterator_tag : public input_iterator_tag
    {
    };
    //允许读写，可以前后递增/递减，支持逆向
    struct bidirectional_iterator_tag : public forward_iterator_tag
    {
    };
    //涵盖所有指针的算术操作能力
    struct random_access_iterator_tag : public bidirectional_iterator_tag
    {
    };

    template <class T, class Distance>
    struct input_iterator
    {
        /* typedef input_iterator_tag iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef T *pointer;
        typedef T &reference; */
        using iterator_category = input_iterator_tag;
        using value_type = T;
        using difference_type = Distance;
        using pointer = T *;
        using reference = T &;
    };
    struct output_iterator
    {
        /* typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference; */
        using iterator_category = output_iterator_tag;
        using value_type = void;
        using difference_type = void;
        using pointer = void;
        using reference = void;
    };
    template <class T, class Distance>
    struct forward_iterator
    {
        /* typedef forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef T *pointer;
        typedef T &reference; */
        using iterator_category = forward_iterator_tag;
        using value_type = T;
        using difference_type = Distance;
        using pointer = T *;
        using reference = T &;
    };
    template <class T, class Distance>
    struct bidirectional_iterator
    {
        /* typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef T *pointer;
        typedef T &reference; */
        using iterator_category = bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = Distance;
        using pointer = T *;
        using reference = T &;
    };
    template <class T, class Distance>
    struct random_access_iterator
    {
        /* typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef T *pointer;
        typedef T &reference; */
        using iterator_category = random_access_iterator_tag;
        using value_type = T;
        using difference_type = Distance;
        using pointer = T *;
        using reference = T &;
    };

    //偏特化
    template <class Iterator>
    struct iterator_traits
    {
        // c++默认情况下，通过作用域运算符访问的名字不是类型
        //所以需要显示的告诉编译器这是一个类型，通过关键字 typename 实现
        /* typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference; */
        using iterator_category = typename Iterator::iterator_category;
        using value_type = typename Iterator::value_type;
        using difference_type = typename Iterator::difference_type;
        using pointer = typename Iterator::pointer;
        using reference = typename Iterator::reference;
    };
    //针对原生指针的特化
    template <class T>
    struct iterator_traits<T *>
    {
        /* typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference; */
        using iterator_category = random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T *;
        using reference = T &;
    };
    //针对原生const指针的特化
    template <class T>
    struct iterator_traits<const T *>
    {
        /* typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T &reference; */
        using iterator_category = random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = const T *;
        using reference = const T &;
    };
    //为了避免类型缺失，提供一个基类
    template <class Category, class T, class Distance = ptrdiff_t,
              class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef Category iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference; 
        /*using iterator_category = Category;
        using value_type = T;
        using difference_type = Distance;
        using pointer = Pointer;
        using reference = Reference;*/
    };

    //萃取
    template <class Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator &It)
    {
        // typedef typename iterator_traits<Iterator>::iterator_category category;
        using category = typename iterator_traits<Iterator>::iterator_category;
        //默认构造或偏特化
        return category();
    }
    template <class Iterator>
    inline typename iterator_traits<Iterator>::value_type *
    value_type(const Iterator &It)
    {
        return static_cast<typename iterator_traits<Iterator>::value_type *>(0);
    }
    template <class Iterator>
    inline typename iterator_traits<Iterator>::difference_type *
    difference_type(const Iterator &It)
    {
        return static_cast<typename iterator_traits<Iterator>::difference_type *>(0);
    }
}