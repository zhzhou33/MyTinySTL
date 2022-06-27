#pragma once

namespace MyTinySTL
{
	template<class T>
	typename list<T>::nodePtr list<T>::newNode(const T& val)
	{
		//using nodeAllocator = allocator<node<T>>;
		nodePtr res = nodeAllocator::allocate();
		nodeAllocator::construct(res, node<T>(val, nullptr, nullptr, this));
		return res;
	}

	template<class T>
	void list<T>::deleteNode(nodePtr p)
	{
		p->prev = p->next = nullptr;
		nodeAllocator::destroy(p);
		nodeAllocator::deallocate(p);
	}

	template<class T>
	list<T>::list()
	{
		// add a dummy node
		head.p = newNode();
		tail.p = head.p;
	}
	
	template<class T>
	list<T>::list(size_type n, const value_type& val)
	{
		ctorAux(n, val, std::is_integral<value_type>());
	}

	template<class T>
	template<class InputIterator>
	list<T>::list(InputIterator first, InputIterator last)
	{
		ctorAux(first, last, std::is_integral<InputIterator>());
	}

	template<class T>
	void list<T>::ctorAux(size_type n, const value_type& val, std::true_type)
	{
		head.p = newNode();
		tail.p = head.p;
		while (n--)
			push_back(val);
	}

	template<class T>
	template<class InputIterator>
	void list<T>::ctorAux(InputIterator first, InputIterator last, std::false_type)
	{
		head.p = newNode();
		tail.p = head.p;
		for (; first != last; ++first)
			push_back(*first);
	}

	//copy-contruct
	template<class T>
	list<T>::list(const list& l)
	{
		head.p = newNode();
		tail.p = head.p;
		for (auto node = l.head.p; node != l.tail.p; node = node->next)
			push_back(node->data);
	}

	template<class T>
	list<T>& list<T>::operator=(const list& l)
	{
		if (this != &l)
			list(l).swap(*this);
		return *this;
	}

	template<class T>
	list<T>::~list()
	{
		while (head != tail)
		{
			nodeAllocator::destroy(head.p);
			nodeAllocator::deallocate(head.p);
			head++;
		}
		nodeAllocator::destroy(tail.p);
		nodeAllocator::deallocate(tail.p);
	}

	template<class T>
	void list<T>::push_front(const value_type& val)
	{
		auto node = newNode(val);
		node->next = head.p;
		head.p->prev = node;
		head.p = node;
	}

	template<class T>
	void list<T>::push_back(const value_type& val)
	{
		auto node = newNode();
		tail.p->data = val;
		tail.p->next = node;
		node->prev = tail.p;
		tail.p = node;
	}

	template<class T>
	void list<T>::pop_front()
	{
		auto oldNode = head.p;
		head.p = oldNode->next;
		head.p->prev = nullptr;
		deleteNode(oldNode);
	}

	template<class T>
	void list<T>::pop_back()
	{
		auto newTail = tail.p->prev;
		newTail->next = nullptr;
		deleteNode(tail.p);
		tail.p = newTail;
	}

	template<class T>
	typename list<T>::iterator list<T>::insert(iterator pos, const value_type& val)
	{
		if (pos == begin())
		{
			push_front(val);
			return begin();
		}
		else if (pos == end())
		{
			auto ret = pos;
			push_back(val);
			return ret;
		}
		auto node = newNode(val);
		node->next = pos.p;
		node->prev = pos.p->prev;

		pos.p->prev->next = node;
		pos.p->prev = node;
		return iterator(node);
	}

	template<class T>
	void list<T>::insert(iterator pos, size_type n, const value_type& val)
	{
		insert_aux(pos, n, val, typename std::is_integral<size_type>::type());
	}

	template<class T>
	template<class InputIterator>
	void list<T>::insert(iterator pos, InputIterator first, InputIterator last)
	{
		insert_aux(pos, first, last, typename std::is_integral<InputIterator>::type());
	}

	template<class T>
	void list<T>::insert_aux(iterator pos, size_type n, const T& val, std::true_type)
	{
		for (auto i = n; i >= 0; i--)
		{
			pos = insert(pos, val);
		}
	}

	template<class T>
	template<class InputIterator>
	void list<T>::insert_aux(iterator pos, InputIterator first, InputIterator last, std::false_type)
	{
		for (; first != last; --last)
			pos = insert(pos, *last);
		insert(pos, *last);
	}

	template<class T>
	typename list<T>::size_type list<T>::size() const
	{
		size_type length = 0;
		for (auto h = head; h != tail; ++h)
			++length;
		return length;
	}

	template<class T>
	typename list<T>::iterator list<T>::erase(iterator first, iterator last)
	{
		typename list<T>::iterator res;
		while (first != last)
		{
			res = erase(first++);
		}
		return res;
	}

	template<class T>
	typename list<T>::iterator list<T>::erase(iterator pos)
	{
		if (pos == head)
		{
			pop_front();
			return head;
		}
		auto prev = pos.p->prev;
		prev->next = pos.p->next;
		pos.p->next->prev = prev;
		deleteNode(pos.p);
		return iterator(prev->next);
	}

	template<class T>
	void list<T>::clear()
	{
		erase(begin(), end());
	}

	/*template<class T>
	bool operator ==(const listIterator<T>& lhs, const listIterator<T>& rhs) 
	{
		return lhs.p == rhs.p;
	}
	template<class T>
	bool operator !=(const listIterator<T>& lhs, const listIterator<T>& rhs) 
	{
		return !(lhs == rhs);
	}*/
}