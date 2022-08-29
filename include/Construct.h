/*
 * @Author: zhzhou33
 * @Date: 2022-05-30 17:57:02
 * @LastEditors: zhzhou33
 * @LastEditTime: 2022-06-10 09:54:34
 */
#pragma once
#include <new>
#include "TypeTraits.h"

namespace MyTinySTL
{
    template <class T1, class T2>
    inline void construct(T1 *ptr, const T2 &val)
    {
        // placement new 方法,在ptr内存位置进行构造
		// 调用类的拷贝构造函数
        new (ptr) T1(val);
    }

    template <class T>
    inline void destroy(T *ptr)
    {
        ptr->~T();
    }

    template <class ForwardIterator>
    inline void _destroy(ForwardIterator first, ForwardIterator last, _true_type) {}

    template <class ForwardIterator>
    inline void _destroy(ForwardIterator first, ForwardIterator last, _false_type)
    {
        for (; first != last; ++first)
        {
            destroy(&*first);
        }
    }

    template <class ForwardIterator>
    inline void destroy(ForwardIterator first, ForwardIterator last)
    {
        typedef typename _type_traits<ForwardIterator>::is_POD_type is_POD_type;
        _destroy(first, last, is_POD_type());
    }
}