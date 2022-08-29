/*
 * @Author: zhzhou33
 * @Date: 2022-06-14 20:25:19
 * @LastEditors: zhzhou33
 * @LastEditTime: 2022-08-27 19:15:41
 */
#pragma once
#include "Allocator.h"
#include "Iterator.h"

namespace MyTinySTL
{
    template <class T, class Alloc = allocator<T>> class deque;

    template <class T>
    class deque_iterator : public iterator<bidirectional_iterator_tag, T>
    {
    private:
        template <class Alloc> friend class MyTinySTL::deque;
    private:
        using cntrPtr = const MyTinySTL::deque<T> *;
        // map块连续空间的索引，当前元素指向map的位置
        //当前迭代器所指向map中控器的元素
        size_t mapIndex;
        //当前元素所指缓冲区位置,该指针指向实际元素的位置，被迭代器所封装
        T *cur_;
        //用于访问deque容器的信息
        cntrPtr container_;
    public:
        //构造函数
        deque_iterator() : mapIndex(-1), cur_(0), container_(0) {}
        deque_iterator(size_t index, T *ptr, cntrPtr container)
            : mapIndex(index), cur_(ptr), container_(container)
        {
        }
        //拷问构造函数
        deque_iterator(const deque_iterator &it)
            : mapIndex(it.mapIndex), cur_(it.cur_), container_(it.container_)
        {
        }
        deque_iterator &operator=(const deque_iterator &it);
        void swap(deque_iterator &it);

        //指针重载
        T &operator*()
        {
            return *cur_;
        }
        const T &operator*() const
        {
            return *cur_;
        }
        T *operator->()
        {
            return &(operator*());
        }
        const T *operator->() const
        {
            return &(operator*());
        }

        //迭代器功能的实现重载
        //前置 ++i
        deque_iterator &operator++();
        //后置 i++
        deque_iterator operator++(int);
        deque_iterator &operator--();
        deque_iterator operator--(int);
        bool operator==(const deque_iterator &it) const;
        bool operator!=(const deque_iterator &it) const;
    private:
        // mapIndex对应（的）缓冲区的尾部
        T *getBuckTail(size_t mapIndex) const;
        // mapIndex对应（的）缓冲器的头部
        T *getBuckHead(size_t mapIndex) const;
        //缓冲区的大小
        size_t getBuckSize() const;
    public:
        // template <class T1>
        friend deque_iterator<T>
        operator+(const deque_iterator<T> &it,
                  typename deque_iterator<T>::difference_type n);
        // template <class T1>
        friend deque_iterator<T>
        operator+(typename deque_iterator<T>::difference_type n,
                  const deque_iterator<T> &it);
        // template <class T1>
        friend deque_iterator<T>
        operator-(const deque_iterator<T> &it,
                  typename deque_iterator<T>::difference_type n);
        // template <class T1>
        friend deque_iterator<T>
        operator-(typename deque_iterator<T>::difference_type n,
                  const deque_iterator<T> &it);
        // template <class T1>
        friend typename deque_iterator<T>::difference_type
        operator-(const deque_iterator<T> &it1, const deque_iterator<T> &it2);
        // template <class T1>
        friend void swap(deque_iterator<T> &lhs, deque_iterator<T> &rhs);
    };

    //****************************************************//
    //友元函数
    template <class T, class Alloc>
    bool operator==(const deque<T, Alloc> &lhs, const deque<T, Alloc> &rhs)
    {
        auto beg1 = lhs.begin(), beg2 = rhs.begin();

        for (; beg1 != lhs.end() && beg2 != rhs.end(); ++beg1, ++beg2) {
            if (*beg1 != *beg2)
                return false;
        }
        if (beg1 == lhs.end() && beg2 == rhs.end())
            return true;
        return false;
    }

    template <class T, class Alloc>
    bool operator!=(const deque<T, Alloc> &lhs, const deque<T, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    void swap(deque<T, Alloc> &x, deque<T, Alloc> &y)
    {
    }
    //****************************************************//
    template <class T, class Alloc> class deque
    {
    private:
        // template <class T1>
        friend class MyTinySTL::deque_iterator<T>;
    public:
        using value_type = T;
        using iterator = MyTinySTL::deque_iterator<T>;
        using const_iterator = MyTinySTL::deque_iterator<const T>;
        using reference = T &;
        using const_reference = const T &;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using allocator_type = Alloc;
    private:
        using dataAllocator = Alloc;
        //定义桶（缓冲区）大小为64
        enum class EBuckSize {
            BUCKSIZE = 64
        };
    private:
        //指向当前缓冲区第一个节点和最后一个节点
        //?指向map的首尾(ERROR) 指向实际元素的首尾,且end指向实际元素的下一个位置
        iterator beg_, end_;
        // map内指针的数目
        size_t mapSize_;
        //指向一块map，map中的每个元素都是一个指针，指向一个缓冲区
        T **map_;
    public:
        deque();
        explicit deque(size_type n, const value_type &val = value_type());
        template <class InputIterator>
        deque(InputIterator first, InputIterator last);
        deque(const deque &x);
        ~deque();

        deque &operator=(const deque &x);
        deque &operator=(deque &&x);

        iterator begin()
        {
            return beg_;
        }
        iterator end()
        {
            return end_;
        }
        iterator begin() const
        {
            return beg_;
        }
        iterator end() const
        {
            return end_;
        }
    public:
        //元素操作
        size_type size() const
        {
            return end() - begin();
        }
        bool empty() const
        {
            return begin() == end();
        }

        reference operator[](size_type n)
        {
            return *(begin() + n);
        }
        reference front()
        {
            return *begin();
        }
        reference back()
        {
            return *(end() - 1);
        }
        const_reference operator[](size_type n) const
        {
            return *(begin() + n);
        }
        const_reference front() const
        {
            return *begin();
        }
        const_reference back() const
        {
            return *(end() - 1);
        }

        void push_back(const value_type &val);
        void push_front(const value_type &val);
        void pop_back();
        void pop_front();
        void swap(deque &x);
        void clear();
    private:
        //初始化函数
        void init();
        T *getANewBuck();
        T **getANewMap(const size_t size);
        size_t getBuckSize() const;
        size_t getNewMapSize(const size_t size);

        //内部辅助函数
        bool back_full() const
        {
            // map[mapSize-1]被占用，指针指向end
            //即后面没有空间可以插入了，需要重新申请
            return map_[mapSize_ - 1] && (map_[mapSize_]) == end().cur_;
        }
        bool front_full() const
        {
            // map[0] 存在且为当前所指向缓冲区首位
            //即前方没有空间可以插入了，需要重新申请
            return map_[0] && map_[0] == begin().cur_;
        }
        // deque构造所需的辅助函数
        void deque_aux(size_t n, const value_type &val, std::true_type);
        template <class Iterator>
        void deque_aux(Iterator first, Iterator last, std::false_type);

        void reallocateAndCopy();
    public:
        // template <class T1, class Alloc1>
        friend bool operator==
            <>(const deque<T, Alloc> &lhs, const deque<T, Alloc> &rhs);
        // template <class T1, class Alloc1>
        friend bool operator!=
            <>(const deque<T, Alloc> &lhs, const deque<T, Alloc> &rhs);
        // template <class T1, class Alloc1>
        friend void swap<>(deque<T, Alloc> &x, deque<T, Alloc> &y);
    };

}   // namespace MyTinySTL

#include "DequeImpl.h"
