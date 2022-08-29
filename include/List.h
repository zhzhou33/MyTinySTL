#pragma once
#include "Allocator.h"
#include "Iterator.h"
#include "UninitializedFunctions.h"

namespace MyTinySTL
{
	template<class T>
	class list;

	template<class T>
	struct node
	{
		T data;
		node* prev;
		node* next;
		list<T>* container;
		node(const T& dt, node* p, node* n, list<T>* l)
			:data(dt), prev(p), next(n), container(l) {}
		bool operator==(const node& nd)
		{
			return data == nd.data && prev == nd.prev &&
				next == nd.next && container == nd.container;
		}
	};

	template<class T>
	class listIterator :public iterator<bidirectional_iterator_tag, T>
	{
	public:
		//template<class T>
		friend class list<T>;
	public:
		using nodePtr = node<T>*;
		nodePtr p;
	public:
		explicit listIterator(nodePtr ptr = nullptr) :p(ptr) {}

		//++i
		listIterator& operator++()
		{
			p = p->next;
			return *this;
		}
		//i++
		listIterator operator++(int)
		{
			auto res = *this;
			++*this;
			return res;
		}
		listIterator& operator--()
		{
			p = p->prev;
			return *this;
		}
		listIterator operator--(int)
		{
			auto res = *this;
			--*this;
			return res;
		}

		T& operator*() { return p->data; }
		T* operator->() { return &(operator*()); }

		//template<class T>
		friend bool operator==(const listIterator& lhs, const listIterator& rhs)
		{
			return lhs.p == rhs.p;
		}
		
		//template<class T>
		friend bool operator!=(const listIterator& lhs, const listIterator& rhs)
		{
			return !(lhs == rhs);
		}
		
	};


	template<class T>
	class list
	{
		//template<class T>
		friend class listIterator<T>;
	private:
		using nodeAllocator = allocator<node<T>>;
		using nodePtr = node<T>*;
	public:
		using value_type = T;
		using iterator = listIterator<T>;
		using const_iterator = listIterator<const T>;
		using reference = T & ;
		using size_type = size_t;
	private:
		iterator head;
		//end:最后一个节点的下一个位置
		iterator tail;
	public:
		list();
		explicit list(size_type n, const value_type& val = value_type());
		template<class InputIterator>
		list(InputIterator first, InputIterator last);
		list(const list& l);
		list& operator=(const list& l);
		~list();

		bool empty() const { return head == tail; }
		size_type size() const;
		reference front() { return (head.p->data); }
		reference back() { return (tail.p->prev->data); }

		void push_front(const value_type& val);
		void pop_front();
		void push_back(const value_type& val);
		void pop_back();

		iterator begin() { return head; }
		iterator end() { return tail; }
		const_iterator begin() const { return head; }
		const_iterator end() const { return tail; }

		iterator insert(iterator pos, const value_type& val);
		void insert(iterator pos, size_type n, const value_type& val);
		template<class InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last);
		iterator erase(iterator pos);
		iterator erase(iterator first, iterator last);
		void swap(list& x);
		void clear();

		void splice(iterator pos, list& x);
		void splice(iterator pos, list& x, iterator i);
		void splice(iterator pos, list& x, iterator first, iterator last);

		void remove(const value_type& val);
		template<class Predicate>
		void remove_if(Predicate pred);

		void unique();
		template<class BinaryPredicate>
		void unique(BinaryPredicate binary_pred);

		void merge(list& x);
		template<class Compare>
		void merge(list& x, Compare comp);
		void sort();
		template<class Compare>
		void sort(Compare comp);
		void reverse();
	private:

		nodePtr newNode(const T& val = T());
		void deleteNode(nodePtr p);
		void ctorAux(size_type n, const value_type& val, std::true_type);
		template<class InputIterator>
		void ctorAux(InputIterator first, InputIterator last, std::false_type);
		
		void insert_aux(iterator pos, size_type n, const T& val, std::true_type);
		template<class InputIterator>
		void insert_aux(iterator pos, InputIterator first, InputIterator last, std::false_type);
	public:
		//template<class T>
		friend bool operator==(const list<T>& lhs, const list<T>& rhs)
		{
			auto node1 = lhs.head.p, node2 = rhs.head.p;
			for (; node1 != lhs.tail.p && node2 != rhs.tail.p; node1 = node1->next, node2 = node2->next)
			{
				if (node1->data != node2->data)
					break;
			}
			if (node1 == lhs.tail.p && node2 == rhs.tail.p)
				return true;
			return false;
		}
		
		//template<class T>
		friend bool operator!=(const list<T>& lhs, const list<T>& rhs)
		{
			return !(lhs == rhs);
		}
	};
}

#include "ListImpl.h"