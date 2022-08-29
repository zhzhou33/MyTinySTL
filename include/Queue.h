#pragma once

#include "Deque.h"
#include "Functional.h"
#include "Vector.h"

namespace MyTinySTL
{
	template<class T,class Container = MyTinySTL::deque<T>>
	class queue
	{
	public:
		using value_type = T;
		using container_type = Container;
		using reference = typename Container::reference;
		using const_reference = typename Container::const_reference;
		using size_type = typename Container::size_type;
	private:
		Container container_;
	public:
		queue(){}
		explicit queue(const container_type& ctnr) :container_(ctnr) {}

		bool empty() const { return container_.empty(); }
		size_type size() const { return container_.size(); }
		reference front() { return container_.front(); }
		const_reference front() const { return container_.front(); }
		reference back() { return container_.back(); }
		const_reference back() const { return container_.back(); }

		void push(const value_type& val) { container_.push_back(val); }
		void pop() { container_.pop_front(); }
		void swap(queue& x) { container_.swap(x.container_); }
	public:
		//template<class T,class Container>
		friend bool operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
		{
			return lhs.container_ == rhs.container_;
		}

		//友元函数如果需要在类内声明，类外实现，需要添加
		// template<class T>

		//template<class T, class Container>
		friend bool operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
		{
			return lhs.container_ != rhs.container_;
		}
		//template<class T,class Container>
		friend void swap<>(queue<T, Container>& x, queue<T, Container>& y);
	};
	/*template<class T,class Container>
	bool operator==(const queue<T, Container>&lhs, const queue<T, Container>& rhs)
	{
		return lhs.container_ == rhs.container_;
	}*/
	/*template<class T, class Container>
	bool operator!=(const queue<T, Container>&lhs, const queue<T, Container>& rhs)
	{
		return lhs.container_ != rhs.container_;
	}*/

	template<class T,class Container = MyTinySTL::vector<T>,class Compare = MyTinySTL::less<typename Container::value_type>>
	class priority_queue
	{
	public:
		using value_type = T;
		using container_type = Container;
		using reference = typename Container::reference;
		using const_reference = typename Container::const_reference;
		using size_type = typename Container::size_type;
	private:
		container_type container_;
		Compare compare_;
	public:
		explicit priority_queue(const Compare& compare = Compare(), const Container& ctnr = Container())
			:container_(ctnr), compare_(compare) {}
		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last, const Compare& compare = Compare(), const Container& ctnr = Container())
			: container_(ctnr), compare_(compare)
		{
			container_.insert(container_.end(), first, last);
			MyTinySTL::make_heap(container_.begin(), container_.end());
		}

		bool empty() const { return container_.empty(); }
		size_type size() const { return container_.size(); }
		reference top() { return container_.front(); }
		void push(const value_type& val)
		{
			container_.push_back(val);
			MyTinySTL::push_heap(container_.begin(), container_.end(), compare_);
		}

		void pop()
		{
			//将堆顶元素移动到末尾，之后调整堆
			MyTinySTL::pop_heap(container_.begin(), container_.end(), compare_);
			//弹出末尾的元素
			container_.pop_back();
		}

		void swap(priority_queue& x)
		{
			MyTinySTL::swap(container_, x.container_);
			MyTinySTL::swap(compare_, x.compare_);
		}

	public:
		//template<class T1,class Container1,class Compare1>
		friend void swap(priority_queue<T, Container, Compare>& x, priority_queue<T, Container, Compare>& y)
		{
			x.swap(y);
		}
	};
}