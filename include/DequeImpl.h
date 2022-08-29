/*
 * @Author: zhzhou33
 * @Date: 2022-06-14 21:40:20
 * @LastEditors: zhzhou33
 * @LastEditTime: 2022-08-27 19:15:23
 */
#pragma once

#include "Deque.h"
namespace MyTinySTL
{
	//拷贝
	template <class T>
	deque_iterator<T> &deque_iterator<T>::operator=(const deque_iterator &it)
	{
		if (this != &it)
		{
			mapIndex = it.mapIndex;
			cur_ = it.cur_;
			container_ = it.container_;
		}
		return *this;
	}

	template <class T>
	void deque_iterator<T>::swap(deque_iterator &it)
	{
	}

	//迭代器实现，重载运算符
	template <class T>
	deque_iterator<T> &deque_iterator<T>::operator++()
	{
		//判断是否超过缓冲区大小，然后判断是否超过map大小
		if (cur_ != getBuckTail(mapIndex)) //+1后还在同一个桶buf里
			++cur_;
		else if (mapIndex + 1 < container_->mapSize_)
		{
			//+1后还在同一个map里
			++mapIndex;
			cur_ = getBuckHead(mapIndex);
		}
		// mapIndex + 1 = container_->mapSize_
		else
		{
			//+1后跳出了map
			mapIndex = container_->mapSize_;
			//越界,cur_ == end_
			cur_ = container_->map_[mapIndex];
		}
		return *this;
	}

	template <class T>
	deque_iterator<T> deque_iterator<T>::operator++(int)
	{
		auto res = *this;
		++(*this);
		return res;
	}

	template <class T>
	deque_iterator<T> &deque_iterator<T>::operator--()
	{
		if (cur_ != getBuckHead(mapIndex)) //当前不指向桶头
			--cur_;
		else if (mapIndex - 1 >= 0) // -1 后还在map里面
		{
			--mapIndex;
			cur_ = getBuckTail(mapIndex);
		}
		else
		{
			mapIndex = 0;
			cur_ = container_->map_[mapIndex]; //指向 map[0]的头
		}
		return *this;
	}

	template <class T>
	deque_iterator<T> deque_iterator<T>::operator--(int)
	{
		auto res = *this;
		--(*this);
		return res;
	}

	template <class T>
	bool deque_iterator<T>::operator==(const deque_iterator &it) const
	{
		return ((mapIndex == it.mapIndex) &&
			(cur_ == it.cur_) &&
			(container_ == it.container_));
	}

	template <class T>
	bool deque_iterator<T>::operator!=(const deque_iterator &it) const
	{
		return !(*this == it);
	}

	template <class T>
	T *deque_iterator<T>::getBuckTail(size_t mapIndex) const
	{
		return container_->map_[mapIndex] + (container_->getBuckSize() - 1);
	}

	template <class T>
	T *deque_iterator<T>::getBuckHead(size_t mapIndex) const
	{
		return container_->map_[mapIndex];
	}

	template <class T>
	size_t deque_iterator<T>::getBuckSize() const
	{
		return container_->getBuckSize();
	}

	// friend类外定义
	//实现迭代器于 int 类型数字的符号运算
	template <class T>
	deque_iterator<T> operator+(const deque_iterator<T> &it, typename deque_iterator<T>::difference_type n)
	{
		deque_iterator<T> res(it);
		//缓冲区剩余的大小
		auto m = res.getBuckTail(res.mapIndex) - res.cur_;

		if (n <= m)
			res.cur_ += n;
		else
		{
			n = n - m; //跳到当前缓冲区的tail，再开始计算
			res.mapIndex += (n / it.getBuckSize() + 1);
			auto p = res.getBuckHead(res.mapIndex);
			auto x = n % it.getBuckSize() - 1;
			res.cur_ = p + x;
		}
		return res;
	}

	//如果重载为类成员函数，因为第一个参数即左侧参数不是类对象，所以应该使用友元重载的方式(使用友元方式访问类的成员变量)
	template <class T>
	deque_iterator<T> operator+(typename deque_iterator<T>::difference_type n, const deque_iterator<T> &it)
	{
		return (it + n);
	}

	template <class T>
	deque_iterator<T> operator-(const deque_iterator<T> &it, typename deque_iterator<T>::difference_type n)
	{
		deque_iterator<T> res(it);
		auto m = res.cur_ - res.getBuckHead(res.mapIndex);
		if (n <= m) //后退 n 步还在同一个桶中
			res.cur_ -= n;
		else
		{
			n = n - m;
			res.mapIndex -= (n / res.getBuckSize() + 1);
			res.cur_ = res.getBuckTail(res.mapIndex) - (n % res.getBuckSize() - 1);
		}
		return res;
	}

	template <class T>
	deque_iterator<T> operator-(typename deque_iterator<T>::difference_type n, const deque_iterator<T> &it)
	{
		return (it - n);
	}

	//迭代器之间的运算
	template <class T>
	typename deque_iterator<T>::difference_type operator-(const deque_iterator<T> &it1, const deque_iterator<T> &it2)
	{
		if (it1.container_ == it2.container_ && it1.container_ == 0)
			return 0;
		//分3段计算
		//第一段：it1缓冲区大小 * (map[it1] - map[it2] - 1)
		//第二段：it1当前缓冲区位置 - it1缓冲区head位置
		//第三段：it2缓冲区tail位置 - it2当前缓冲区位置
		return typename deque_iterator<T>::difference_type(it1.getBuckSize()) * (it1.mapIndex - it2.mapIndex - 1) + (it1.cur_ - it1.getBuckHead(it1.mapIndex)) + (it2.getBuckTail(it2.mapIndex) - it2.cur_) + 1;
	}

	template <class T>
	void swap(deque_iterator<T> &lhs, deque_iterator<T> &rhs)
	{
	}

    //***************************************************
    //初始化init
    template <class T, class Alloc>
    void deque<T, Alloc>::init()
    {
        //初始化，申请2块内存，初始指针放在第二块的前端
        mapSize_ = 2;
        map_ = getANewMap(mapSize_);
        beg_.container_ = end_.container_ = this;
        beg_.mapIndex = end_.mapIndex = mapSize_ - 1;
        beg_.cur_ = end_.cur_ = map_[mapSize_ - 1];
    }

    template <class T, class Alloc>
    T **deque<T, Alloc>::getANewMap(const size_t size)
    {
        T **map = new T *[size];
        for (int i = 0; i != size; i++)
            map[i] = getANewBuck(); //批量获得桶(缓冲区)
        return map;
    }

    template <class T, class Alloc>
    T *deque<T, Alloc>::getANewBuck()
    {
        return dataAllocator::allocate(getBuckSize());
    }

    template <class T, class Alloc>
    size_t deque<T, Alloc>::getBuckSize() const
    {
        return (size_t)EBuckSize::BUCKSIZE; // 64
    }

    template <class T, class Alloc>
    size_t deque<T, Alloc>::getNewMapSize(const size_t size)
    {
        return (size == 0 ? 2 : size * 2);
    }

    //基本功能实现
    //构造函数
    template <class T, class Alloc>
    deque<T, Alloc>::deque() : mapSize_(0), map_(0) {}

    template <class T, class Alloc>
    deque<T, Alloc>::deque(size_type n, const value_type &val)
    {
        deque();
        deque_aux(n, val, typename std::is_integral<size_type>::type());
    }

    template <class T, class Alloc>
    template <class InputIterator>
    deque<T, Alloc>::deque(InputIterator first, InputIterator last)
    {
        deque();
        deque_aux(first, last, typename ::std::is_integral<InputIterator>::type());
    }

    template <class T, class Alloc>
    void deque<T, Alloc>::deque_aux(size_t n, const value_type &val, std::true_type)
    {
        int i = 0;
        for (; i != n / 2; i++)
            (*this).push_front(val);
        for (; i != n; i++)
            (*this).push_back(val);
    }

    template <class T, class Alloc>
    template <class Iterator>
    void deque<T, Alloc>::deque_aux(Iterator first, Iterator last, std::false_type)
    {
        difference_type mid = (last - first) / 2;
        for (auto it = first + mid; it != first - 1; --it)
            (*this).push_front(*it);
        for (auto it = first + mid + 1; it != last; ++it)
            (*this).push_back(*it);
    }

    template <class T, class Alloc>
    deque<T, Alloc>::~deque()
    {
        //先销毁缓冲区，再清除对应缓冲区的map指针，最后再销毁整个map数组
		for (auto p = beg_; p != end_; ++p)
			dataAllocator::destroy(p.cur_);
		//zhzhou33 添加 deallocate
		for (int i = 0; i < mapSize_; i++)
		{
			if (map_[i])
				dataAllocator::deallocate(map_[i], getBuckSize());
		}
        delete[] map_;
    }

    //拷贝构造
    template <class T, class Alloc>
    deque<T, Alloc>::deque(const deque &x)
    {
        mapSize_ = x.mapSize_;
        map_ = getANewMap(mapSize_);
        for (int i = 0; i + x.beg_.mapIndex != x.mapSize_; i++)
        {
            for (int j = 0; j != getBuckSize(); j++)
                map_[x.beg_.mapIndex + i][j] = x.map_[x.beg_.mapIndex + i][j];
        }
        beg_.mapIndex = x.beg_.mapIndex;
        end_.mapIndex = x.end_.mapIndex;
        beg_.cur_ = map_[beg_.mapIndex] + (x.beg_.cur_ - x.map_[x.beg_.mapIndex]);
        end_.cur_ = map_[end_.mapIndex_] + (x.end_.cur_ - x.map_[x.end_.mapIndex]);
        beg_.container_ = end_.container_ = this;
    }

    template <class T, class Alloc>
    void deque<T, Alloc>::push_back(const value_type &val)
    {
        if (empty())
            init();
        else if (back_full())
            reallocateAndCopy();
        MyTinySTL::construct(end_.cur_, val);
		//调用运算符重载，实际 == ++cur_
        ++end_;
    }

    template <class T, class Alloc>
    void deque<T, Alloc>::push_front(const value_type &val)
    {
        if (empty())
            init();
        else if (front_full())
            reallocateAndCopy();
        --beg_;
        MyTinySTL::construct(beg_.cur_, val);
    }

    template <class T, class Alloc>
    void deque<T, Alloc>::pop_front()
    {
        dataAllocator::destroy(beg_.cur_);
        ++beg_;
    }

    template <class T, class Alloc>
    void deque<T, Alloc>::pop_back()
    {
        --end_;
        dataAllocator::destroy(end_.cur_);
    }
    template <class T, class Alloc>
    void deque<T, Alloc>::reallocateAndCopy()
    {
        auto newMapSize = getNewMapSize(mapSize_); // 扩展两倍
        T **newMap = getANewMap(newMapSize);

        //重新申请2倍空间后，将原来数据copy到中间位置
        size_t startIndex = newMapSize / 4;
        for (int i = 0; i + beg_.mapIndex != mapSize_; i++)
        {
            for (int j = 0; j != getBuckSize(); j++)
                newMap[startIndex + i][j] = map_[beg_.mapIndex + i][j];
        }
        //头部缓冲区的偏移量
        size_t n = beg_.cur_ - map_[beg_.mapIndex];
        auto size = this->size();
        //析构旧地址
        clear();

        mapSize_ = newMapSize;
        map_ = newMap;
        // iterator构造函数
        beg_ = iterator(startIndex, newMap[startIndex] + n, this);
		//运算符重载
        end_ = beg_ + size;
    }

	//源代码写的有点问题，没有释放掉内存
    template <class T, class Alloc>
    void deque<T, Alloc>::clear()
    {
        
		//zhzhou33 修改此处的判断
        //for (auto p = map_[i] + 0; p && p != map_[i] + getBuckSize(); ++p)
        //    dataAllocator::destroy(p);
		for (auto p = beg_; p != end_; ++p)
			dataAllocator::destroy(p.cur_);
		//zhzhou33 添加 deallocate
		for (int i = 0; i < mapSize_; i++)
		{
			if (map_[i])
				dataAllocator::deallocate(map_[i], getBuckSize());
		}
        
        mapSize_ = 0;
        beg_.mapIndex = end_.mapIndex = mapSize_ / 2;
        beg_.cur_ = end_.cur_ = map_[mapSize_ / 2];

		//zhzhou33
		delete[] map_;
    }

    /*template <class T, class Alloc>
    typename deque<T, Alloc>::deque deque<T, Alloc>::operator=(const deque &x)
    {
        mapSize_ = x.mapSize_;
        map_ = getANewMap(mapSize_);

        for (int i = 0; i + x.beg_.mapIndex != x.mapSize_; i++)
        {
            for (int j = 0; j != getBuckSize(); j++)
                map_[x.beg_.mapIndex + i][j] = x.map_[x.beg_.mapIndex + i][j];
        }
        beg_.mapIndex = x.beg_.mapIndex;
        end_.mapIndex = x.end_.mapIndex;
        beg_.cur_ = map_[beg_.mapIndex] + (x.beg_.cur_ - x.map_[x.beg_.mapIndex]);
        end_.cur_ = map_[end_.mapIndex_] + (x.end_.cur_ - x.map_[x.end_.mapIndex]);
        beg_.container_ = end_.container_ = this;
        return *this;
    }*/


} // namespace MyTinySTL
