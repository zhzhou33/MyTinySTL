/*
 * @Author: zhzhou33
 * @Date: 2022-05-30 19:34:14
 * @LastEditors: zhzhou33
 * @LastEditTime: 2022-06-14 21:40:44
 */
#pragma once
#include "Allocator.h"
#include "Algorithm.h"
#include "Iterator.h"
#include "UninitializedFunctions.h"

namespace MyTinySTL
{
    template <class T, class Alloc = allocator<T>>
    class vector
    {
    private:
        T *start;
        T *finish;
        T *endOfStorage;
        typedef Alloc dataAllocator;

    public:
        typedef T value_type;
        typedef T *iterator;
        typedef const T *const_iterator;
        // typedef reverse_iterator_t(T *) reverse_iterator;
        // typedef reverse_iterator_t<const T *> const_reverse_iterator;
        typedef iterator pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

    public:
        vector() : start(0), finish(0), endOfStorage(0) {}
        //参数必须完全匹配,不能进行隐式转换,即不希望自动类型转换
        explicit vector(const size_type n);
        vector(const size_type n, const value_type &value);
        template <class InputIterator>
        vector(InputIterator first, InputIterator last);
        vector(const vector &v);
        vector(vector &&v);
        vector &operator=(const vector &v);
        vector &operator=(vector &&v);
        ~vector();

        // compare
        bool operator==(const vector &v) const;
        bool operator!=(const vector &v) const;

        // iterator
        iterator begin() { return start; }
        const_iterator begin() const { return start; }
        const_iterator cbegin() const { return start; }
        iterator end() { return finish; }
        const_iterator end() const { return finish; }
        const_iterator cend() const { return finish; }

        // reverse_iterator rbegin(){return }

        // capacity
        difference_type size() const { return finish - start; }
        difference_type capacity() const { return endOfStorage - start; }
        bool empty() const { return start == finish; }
        void resize(size_type n, value_type val = value_type());
        void reserve(size_type n);
        void shrink_to_fit();

        // element
        reference operator[](const difference_type i) { return *(begin() + i); }
        const_reference operator[](const difference_type i) const { return *(cbegin() + i); }
        reference front() { return *(begin()); }
        reference back() { return *(end() - 1); }
        pointer data() { return start; };

        //修改容器相关的操作
        void clear();
        void swap(vector &v);
        void push_back(const value_type &value);
        void pop_back();
        iterator insert(iterator pos, const value_type &value);
        void insert(iterator pos, const size_type &n, const value_type &value);
        template <class InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last);
        iterator erase(iterator pos);
        iterator erase(iterator first, iterator last);

        //空间配置器相关
        // Alloc get_allocator() { return dataAllocator; }

    private:
        void destroyAndDeallocateAll();
        void allocateAndFillN(const size_type n, const value_type &value);
        template <class InputIterator>
        void allocateAndCopy(InputIterator first, InputIterator last);

        template <class InputIterator>
        void vector_aux(InputIterator first, InputIterator last, std::false_type);
        template <class Integer>
        void vector_aux(Integer n, const value_type &value, std::true_type);
        template <class InputIterator>
        void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
        template <class Integer>
        void insert_aux(iterator position, Integer n, const value_type &value, std::true_type);

        template <class InputIterator>
        void reallocateAndCopy(iterator position, InputIterator first, InputIterator last);
        void reallocateAndFillN(iterator position, const size_type &n, const value_type &val);
        size_type getNewCapacity(size_type len) const;

    public:
        /* template <class T, class Alloc>
        friend bool operator==(const vector<T, Alloc> &v1, const vector<T, Alloc> &v2);
        template <class T, class Alloc>
        friend bool operator!=(const vector<T, Alloc> &v1, const vector<T, Alloc> &v2); */
    };
}
#include "VectorImpl.h"