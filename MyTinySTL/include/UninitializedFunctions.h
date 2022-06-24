/*
 * @Author: zhzhou33
 * @Date: 2022-05-31 16:47:32
 * @LastEditors: zhzhou33
 * @LastEditTime: 2022-06-10 09:46:21
 */
#pragma once
#include "Construct.h"
#include "Iterator.h"
#include "TypeTraits.h"
#include "Algorithm.h"

namespace MyTinySTL
{
    // uninitialized_copy
    template <class InputIterator, class ForwardIterator>
    ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
    {
        // gcc 与 vs 编译不一致
        // typedef typename _type_traits<typename iterator_traits<InputIterator>::value_type>::is_POD_type isPODType;
        using isPODType = typename _type_traits<typename iterator_traits<InputIterator>::value_type>::is_POD_type;
        return _uninitialized_copy_aux(first, last, result, isPODType());
    }

    template <class InputIterator, class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
                                            ForwardIterator result, _true_type)
    {
        memcpy(result, first, (last - first) * sizeof(*first));
        return result + (last - first);
    }
    template <class InputIterator, class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
                                            ForwardIterator result, _false_type)
    {
        int i = 0;
        for (; first != last; ++first, ++i)
            construct((result + i), *first);
        return (result + i);
    }

    // uninitialized_fill
    template <class ForwardIterator, class T>
    void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &value)
    {
        // typedef typename _type_traits<T>::is_POD_type isPODType;
        using isPODType = typename _type_traits<T>::is_POD_type;
        _uninitialized_fill_aux(first, last, value, isPODType());
    }

    template <class ForwardIterator, class T>
    void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
                                 const T &value, _true_type)
    {
        fill(first, last, value);
    }
    template <class ForwardIterator, class T>
    void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
                                 const T &value, _false_type)
    {
        for (; first != last; ++first)
            construct(first, value);
    }

    // uninitialized_fill_n
    template <class ForwardIterator, class Size, class T>
    inline ForwardIterator uninitialized_fill_n(ForwardIterator first,
                                                Size n, const T &x)
    {
        // typedef typename _type_traits<T>::is_POD_type isPODType;
        using isPODType = typename _type_traits<T>::is_POD_type;
        return _uninitialized_fill_n_aux(first, n, x, isPODType());
    }
    template <class ForwardIterator, class Size, class T>
    ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
                                              Size n, const T &x, _true_type)
    {
        return fill_n(first, n, x);
    }
    template <class ForwardIterator, class Size, class T>
    ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
                                              Size n, const T &x, _false_type)
    {
        int i = 0;
        for (; i != n; ++i)
        {
            construct((T *)(first + i), x);
        }
        return (first + i);
    }
}