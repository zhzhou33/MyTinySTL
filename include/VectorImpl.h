/*
 * @Author: zhzhou33
 * @Date: 2022-05-30 20:19:50
 * @LastEditors: zhzhou33
 * @LastEditTime: 2022-09-01 21:34:45
 */
#pragma once
// #include "Vector.h"
#include "Vector.h"
#include <assert.h>
namespace MyTinySTL
{
    template <class T, class Alloc>
    vector<T, Alloc>::~vector()
    {
        destroyAndDeallocateAll();
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(const size_type n)
    {
        allocateAndFillN(n, value_type());
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(const size_type n, const value_type &value)
    {
        allocateAndFillN(n, value);
    }

    template <class T, class Alloc>
    template <class InputIterator>
    vector<T, Alloc>::vector(InputIterator first, InputIterator last)
    {
        //处理指针和数字间的区别的函数
        vector_aux(first, last,
                   typename std::is_integral<InputIterator>::type());
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(const vector &v)
    {
        allocateAndCopy(v.start, v.finish);
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(vector &&v)
    {
        start = v.start;
        finish = v.finish;
        endOfStorage = v.endOfStorage;
        v.start = v.endOfStorage = v.finish = 0;
    }

    template <class T, class Alloc>
    vector<T, Alloc> &vector<T, Alloc>::operator=(const vector &v)
    {
        if (this != &v)
            allocateAndCopy(v.start, v.finish);
        return *this;
    }

    template <class T, class Alloc>
    vector<T, Alloc> &vector<T, Alloc>::operator=(vector &&v)
    {
        if (this != &v)
        {
            destroyAndDeallocateAll();
            start = v.start;
            finish = v.finish;
            endOfStorage = v.endOfStorage;
            v.start = v.finish = v.endOfStorage = 0;
        }
        return *this;
    }

    // capacity
    template <class T, class Alloc>
    void vector<T, Alloc>::resize(size_type n, value_type val)
    {
        if (n < size())
        {
            dataAllocator::destroy(start + n, finish);
            finish = start + n;
        }
        else if (n > size() && n <= capacity())
        {
            auto lengthOfInsert = n - size();
        }
        else if (n > capacity())
        {
            auto lengthOfInsert = n - size();
            T *newStart =
                dataAllocator::allocate(getNewCapacity(lengthOfInsert));
            T *newFinish = uninitialized_copy(begin(), end(), newStart);
            newFinish = uninitialized_fill_n(newFinish, lengthOfInsert, val);

            destroyAndDeallocateAll();
            start = newStart;
            finish = newFinish;
            endOfStorage = start + n;
        }
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::reserve(size_type n)
    {
        if (n <= capacity())
            return;
        T *newStart = dataAllocator::allocate(n);
        T *newFinish = uninitialized_copy(begin(), end(), newStart);

        destroyAndDeallocateAll();
        start = newStart;
        finish = newFinish;
        endOfStorage = start + n;
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::shrink_to_fit()
    {
    }

    //修改容器的相关操作
    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator pos)
    {
        return erase(pos, pos + 1);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first,
                                                                iterator last)
    {
        difference_type lenOfTail = end() - last;
        difference_type lenOfRemoved = last - first;
        finish = finish - lenOfRemoved;
        for (; lenOfTail != 0; --lenOfTail)
        {
            auto temp = last - lenOfRemoved;
            *temp = *(last++);
        }
        return first;
    }

    template <class T, class Alloc>
    template <class InputIterator>
    void vector<T, Alloc>::insert_aux(iterator position, InputIterator first,
                                      InputIterator last, std::false_type)
    {
        difference_type locationLeft =
            endOfStorage - finish;                            // the size of left storage
        difference_type locationNeed = distance(first, last); // last - first;

        if (locationLeft >= locationNeed)
        {
            if (finish - position > locationNeed)
            {
                //将位置腾出来
                uninitialized_copy(finish - locationNeed, finish, finish);
                copy_backward(position, finish - locationNeed, finish);
                copy(first, last, position);
            }
            else
            {
                iterator temp = uninitialized_copy(first + (finish - position),
                                                   last, finish);
                uninitialized_copy(position, finish, temp);
                copy(first, first + (finish - position), position);
            }
            finish += locationNeed;
        }
        else
        {
            reallocateAndCopy(position, first, last);
        }
    }
    template <class T, class Alloc>
    template <class Integer>
    void vector<T, Alloc>::insert_aux(iterator position, Integer n,
                                      const value_type &value, std::true_type)
    {
        assert(n != 0);
        difference_type locationLeft =
            endOfStorage - finish; // the size of left storage
        difference_type locationNeed = n;

        if (locationLeft >= locationNeed)
        {
            auto tempPtr = end() - 1;
            for (; tempPtr - position >= 0; --tempPtr)
            {
                // move the [position, finish_) back
                //*(tempPtr + locationNeed) = *tempPtr;//bug
                construct(tempPtr + locationNeed, *tempPtr);
            }
            uninitialized_fill_n(position, n, value);
            finish += locationNeed;
        }
        else
        {
            reallocateAndFillN(position, n, value);
        }
    }

    template <class T, class Alloc>
    template <class InputIterator>
    void vector<T, Alloc>::insert(iterator position, InputIterator first,
                                  InputIterator last)
    {
        insert_aux(position, first, last,
                   typename std::is_integral<InputIterator>::type());
    }
    template <class T, class Alloc>
    void vector<T, Alloc>::insert(iterator position, const size_type &n,
                                  const value_type &val)
    {
        insert_aux(position, n, val,
                   typename std::is_integral<size_type>::type());
    }
    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator
    vector<T, Alloc>::insert(iterator position, const value_type &val)
    {
        const auto index = position - begin();
        insert(position, 1, val);
        return begin() + index;
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::push_back(const value_type &value)
    {
        insert(end(), value);
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::allocateAndFillN(const size_type n,
                                            const value_type &value)
    {
        start = dataAllocator::allocate(n);
        uninitialized_fill_n(start, n, value);
        finish = endOfStorage = start + n;
    }

    template <class T, class Alloc>
    template <class InputIterator>
    void vector<T, Alloc>::vector_aux(InputIterator first, InputIterator last,
                                      std::false_type)
    {
        allocateAndCopy(first, last);
    }
    template <class T, class Alloc>
    template <class Integer>
    void vector<T, Alloc>::vector_aux(Integer n, const value_type &value,
                                      std::true_type)
    {
        allocateAndFillN(n, value);
    }

    //逻辑运算操作
    template <class T, class Alloc>
    bool vector<T, Alloc>::operator==(const vector &v) const
    {
        if (size() != v.size())
        {
            return false;
        }
        else
        {
            auto ptr1 = start;
            auto ptr2 = v.start;
            for (; ptr1 != finish && ptr2 != v.finish; ++ptr1, ++ptr2)
            {
                if (*ptr1 != *ptr2)
                    return false;
            }
            return true;
        }
    }

    template <class T, class Alloc>
    bool vector<T, Alloc>::operator!=(const vector &v) const
    {
        return !(*this == v);
    }

    /* template <class T, class Alloc>
    bool operator==(const vector<T, Alloc> &v1, const vector<T, Alloc> &v2)
    {
        return v1.operator==(v2);
    }

    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &v1, const vector<T, Alloc> &v2)
    {
        return !(v1 == v2);
    } */

    template <class T, class Alloc>
    void vector<T, Alloc>::clear()
    {
        dataAllocator::destroy(start, finish);
        finish = start;
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::swap(vector &v)
    {
        if (this != &v)
        {
            MyTinySTL::swap(start, v.start);
            MyTinySTL::swap(finish, v.finish);
            MyTinySTL::swap(endOfStorage, v.endOfStorage);
        }
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::pop_back()
    {
        --finish;
        dataAllocator::destroy(finish);
    }

    template <class T, class Alloc>
    template <class InputIterator>
    void vector<T, Alloc>::allocateAndCopy(InputIterator first,
                                           InputIterator last)
    {
        start = dataAllocator::allocate(last - first);
        finish = uninitialized_copy(first, last, start);
        endOfStorage = finish;
    }

    template <class T, class Alloc>
    template <class InputIterator>
    void vector<T, Alloc>::reallocateAndCopy(iterator position,
                                             InputIterator first,
                                             InputIterator last)
    {
        difference_type newCapacity = getNewCapacity(last - first);

        T *newStart = dataAllocator::allocate(newCapacity);
        T *newEndOfStorage = newStart + newCapacity;
        T *newFinish = uninitialized_copy(begin(), position, newStart);
        newFinish = uninitialized_copy(first, last, newFinish);
        newFinish = uninitialized_copy(position, end(), newFinish);

        destroyAndDeallocateAll();
        start = newStart;
        finish = newFinish;
        endOfStorage = newEndOfStorage;
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::reallocateAndFillN(iterator position,
                                              const size_type &n,
                                              const value_type &val)
    {
        difference_type newCapacity = getNewCapacity(n);

        T *newStart = dataAllocator::allocate(newCapacity);
        T *newEndOfStorage = newStart + newCapacity;
        T *newFinish = uninitialized_copy(begin(), position, newStart);
        newFinish = uninitialized_fill_n(newFinish, n, val);
        newFinish = uninitialized_copy(position, end(), newFinish);

        destroyAndDeallocateAll();
        start = newStart;
        finish = newFinish;
        endOfStorage = newEndOfStorage;
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::destroyAndDeallocateAll()
    {
        if (capacity() != 0)
        {
            dataAllocator::destroy(start, finish);
            dataAllocator::deallocate(start, capacity());
        }
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::size_type
    vector<T, Alloc>::getNewCapacity(size_type len) const
    {
        size_type oldCapacity = endOfStorage - start;
        auto res = oldCapacity > len ? oldCapacity : len;
        // 旧长度的2倍 或者 旧长度 + 新增元素个数
        size_type newCapacity = (oldCapacity != 0 ? (oldCapacity + res) : len);
        return newCapacity;
    }
} // namespace MyTinySTL