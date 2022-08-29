/*
 * @Author: zhzhou33
 * @Date: 2022-05-31 19:40:48
 * @LastEditors: zhzhou33
 * @LastEditTime: 2022-08-27 19:00:48
 */
#pragma once
#include <cstring>
#include <utility>
// #include <functional>
#include "Functional.h"


#include "Allocator.h"
#include "Iterator.h"
#include "TypeTraits.h"

namespace MyTinySTL
{
	//************* [swap] **************
	template<class T>
	void swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	//********* [fill] ********************
	//********* [Algorithm Complexity: O(N)] ****************
	template <class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T &value)
	{
		for (; first != last; ++first)
			*first = value;
	}
	inline void fill(char *first, char *last, const char &value)
	{
		memset(first, static_cast<unsigned char>(value), last - first);
	}
	inline void fill(wchar_t *first, wchar_t *last, const wchar_t &value)
	{
		memset(first, static_cast<unsigned char>(value), (last - first) * sizeof(wchar_t));
	}
	//********* [fill_n] ********************
	//********* [Algorithm Complexity: O(N)] ****************
	//模板偏特化
	template <class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T &value)
	{
		for (; n > 0; --n, ++first)
			*first = value;
		return first;
	}
	template <class Size>
	char *fill_n(char *first, Size n, const char &value)
	{
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}
	template <class Size>
	wchar_t *fill_n(wchar_t *first, Size n, const wchar_t &value)
	{
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}

	//********** [distance] ******************************
	//********* [Algorithm Complexity: O(N)] ****************
	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		_distance(InputIterator first, InputIterator last, input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type dist = 0;
		while (first++ != last)
		{
			++dist;
		}
		return dist;
	}
	template <class RandomIterator>
	typename iterator_traits<RandomIterator>::difference_type
		_distance(RandomIterator first, RandomIterator last, random_access_iterator_tag)
	{
		auto dist = last - first;
		return dist;
	}
	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type
		distance(Iterator first, Iterator last)
	{
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		return _distance(first, last, iterator_category());
	}

	//***************************************
	template<class RandomAccessIterator, class Compare>
	void adjuctHeap(RandomAccessIterator first, RandomAccessIterator last,
		RandomAccessIterator head, Compare compare)
	{
		auto fatherIndex = first - head;
		auto childIndex = fatherIndex * 2 + 1;
		auto endIndex = last - head;

		while (childIndex <= endIndex)
		{
			//father node has right child
			if (childIndex + 1 <= endIndex)
			{
				if (compare(*(head + childIndex), *(head + childIndex + 1)))
					childIndex++;
			}
			if (compare(*(head + childIndex), *(head + fatherIndex)))
				return;
			MyTinySTL::swap(*(head + childIndex), *(head + fatherIndex));
			//交换了之后，还需要下溯，确保每个父节点都大于/小于左右子节点
			fatherIndex = childIndex;
			childIndex = fatherIndex * 2 + 1;
		}
	}
	//heap
	template<class RandomAccessIterator>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		using value_type = typename MyTinySTL::less<MyTinySTL::iterator_traits<RandomAccessIterator>>::value_type;
		//MyTinySTL::make_heap(first, last, typename MyTinySTL::less<MyTinySTL::iterator_traits<RandomAccessIterator>::value_type>());
		MyTinySTL::make_heap(first, last, value_type());
	}

	template<class RandomAccessIterator, class Compare>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
	{
		const auto range = last - first;
		for (auto cur = first + range / 2 - 1; cur >= first; --cur)
			MyTinySTL::adjuctHeap(cur, last - 1, first, compare);
	}

	
	template<class RandomAccessIterator,class Compare>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
	{
		const auto range = last - first;
		int curIndex = range / 2 - 1;
		while (curIndex >= 0)
		{
			MyTinySTL::adjuctHeap(first + curIndex, last - 1, first, compare);
			// -1 / 2 has some problems
			curIndex = (curIndex - 1) >> 1;
		}
	}

	template<class RandomAccessIterator,class Compare>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
	{
		MyTinySTL::swap(*first, *(last - 1));
		if (last - first >= 2)
			MyTinySTL::adjuctHeap(first, last - 2, first, compare);
	}
}