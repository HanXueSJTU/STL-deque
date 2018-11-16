#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>

namespace sjtuMy { 

template<class T>
class deque {
public:
	struct Node;
	struct node
	{
		node* next;
		node* prev;
		T* data;
		node(const T &x,node *pre = NULL, node  *nex = NULL)
			:data(new T(x)), next(nex), prev(pre) {}
		node() :next(NULL), prev(NULL),data(NULL){}
		~node() { if (data != NULL) delete data; data = NULL; }
	};
	typedef node* link_type;
	class const_iterator;
	class iterator {
	private:
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		const deque* container; //容器指针
		link_type node;  //节点指针
	public:
		iterator(const deque* pointer=NULL) :container(pointer),node(NULL) {};
		iterator(const link_type &p, const deque* pointer) :container(pointer), node(p) {}
		iterator(const iterator &other) :container(other.getContainer()), node(other.getNode()) {}
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, the behaviour is **undefined**.
		 * as well as operator-
		 */
		iterator operator+(const int &n) const {
			iterator tmp = *this;
			if (n >= 0)
				for (int i = 0; i < n; i++) ++tmp;
			else
				for (int i = 0; i > n; i--) --tmp;	
			return tmp;
		}
		iterator operator-(const int &n) const {
			iterator tmp = *this;
			if (n >= 0)
				for (int i = 0; i < n; i++) --tmp;
			else
				for (int i = 0; i > n; i--) ++tmp;
			return tmp;
		}
		// return th distance between two iterator,
		// if these two iterators points to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) const 
		{
			if (this->getContainer() != rhs.getContainer()) throw invalid_iterator();
			iterator tmp = *this;
			int num = 0;
			while (tmp != rhs && tmp != tmp.getContainer()->begin())
			{
				--tmp;
				num++;
			}
			if (tmp == tmp.getContainer()->begin() && tmp != rhs)
			{
				num = 0;
				tmp = rhs;
				while (tmp != *this)
				{
					--tmp;
					num--;
				}
			}
			return num;
		}
		iterator operator+=(const int &n) {
			iterator tmp = *this;
			if (n >= 0)
				for (int i = 0; i < n; i++) ++tmp;
			else
				for (int i = 0; i > n; i--) --tmp;
			node=tmp.getNode();
			return *this;
		}
		iterator operator-=(const int &n) {
			iterator tmp = *this;
			if (n >= 0)
				for (int i = 0; i < n; i++) --tmp;
			else
				for (int i = 0; i > n; i--) ++tmp;
			node = tmp.getNode();
			return *this;
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) 
		{
			if (*this == container->end()) throw invalid_iterator();
			iterator tmp = *this;
			node = node->next;
			return tmp;
		}
		/**
		 * TODO ++iter
		 */
		iterator& operator++() 
		{
			if (*this == container->end()) throw invalid_iterator();
			node = node->next;
			return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) 
		{
			if (*this == container->begin()) throw invalid_iterator();
			iterator tmp = *this;
			node=node->prev;
			return tmp;
		}
		/**
		 * TODO --iter
		 */
		iterator& operator--() 
		{
			if (*this == container->begin()) throw invalid_iterator();
			node = node->prev;
			return *this;
		}
		/**
		 * TODO *it
		 */
		T& operator*() const 
		{
			if (*this == container->end()) throw invalid_iterator();
			return *(node->data);
		}
		/**
		 * TODO it->field
		 */
		T* operator->() const noexcept 
		{
			if (*this == container->end()) throw invalid_iterator();
			return (node->data);
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		bool operator==(const iterator &rhs) const
		{
			return (node == rhs.getNode());
		};
		bool operator==(const const_iterator &rhs) const 
		{ return (node == rhs.getNode()); }
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const { return (node != rhs.node); }
		bool operator!=(const const_iterator &rhs) const { return (node != rhs.node); }

		link_type getNode() const { return node; }
		const deque* getContainer() const { return container; }
		void clear() { if (node != NULL) delete node;  node = NULL; }
	};
	class const_iterator {
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.
		private:
			// data members.
			const deque* container; //容器指针
			link_type node;  //节点指针
		public:
			const_iterator(const deque* pointer = NULL) :container(pointer), node(NULL) {};
			const_iterator(const link_type &p, const deque* pointer)
				:container(pointer), node(p) {}
			const_iterator(const const_iterator &other)
				:container(other.getContainer()), node(other.getNode()) {}
			const_iterator(const iterator &other) 
				:container(other.getContainer()), node(other.getNode()) {}
			int operator-(const const_iterator &rhs) const
			{
				if (this->getContainer() != rhs.getContainer()) throw invalid_iterator();
				const_iterator tmp = *this;
				int num = 0;
				while (tmp != rhs && tmp != tmp.getContainer()->cbegin())
				{
					--tmp;
					num++;
				}
				if (tmp == tmp.getContainer()->cbegin() && tmp != rhs)
				{
					num = 0;
					tmp = rhs;
					while (tmp != *this)
					{
						--tmp;
						num--;
					}
				}
				return num;
			}
			const_iterator operator+(const int &n) const {
				const_iterator tmp = *this;
				if (n >= 0)
					for (int i = 0; i < n; i++) ++tmp;
				else
					for (int i = 0; i > n; i--) --tmp;
				return tmp;
			}
			const_iterator operator-(const int &n) const {
				const_iterator tmp = *this;
				if (n >= 0)
					for (int i = 0; i < n; i++) --tmp;
				else
					for (int i = 0; i > n; i--) ++tmp;
				return tmp;
			}
			// return th distance between two iterator,
			// if these two iterators points to different vectors, throw invaild_iterator.
			const_iterator operator+=(const int &n) {
				const_iterator tmp = *this;
				if (n >= 0)
					for (int i = 0; i < n; i++) ++tmp;
				else
					for (int i = 0; i > n; i--) --tmp;
				node = tmp.getNode();
				return *this;
			}
			const_iterator operator-=(const int &n) {
				const_iterator tmp = *this;
				if (n >= 0)
					for (int i = 0; i < n; i++) --tmp;
				else
					for (int i = 0; i > n; i--) ++tmp;
				node = tmp.getNode();
				return *this;
			}
			/**
			* TODO iter++
			*/
			const_iterator operator++(int)
			{
				if (*this == container->end()) throw invalid_iterator();
				const_iterator tmp = *this;
				node = node->next;
				return tmp;
			}
			/**
			* TODO ++iter
			*/
			const_iterator& operator++()
			{
				if (*this == container->end()) throw invalid_iterator();
				node = node->next;
				return *this;
			}
			/**
			* TODO iter--
			*/
			const_iterator operator--(int)
			{
				if (*this == container->begin()) throw invalid_iterator();
				const_iterator tmp = *this;
				node = node->prev;
				return tmp;
			}
			/**
			* TODO --iter
			*/
			const_iterator& operator--()
			{
				if (*this == container->begin()) throw invalid_iterator();
				node = node->prev;
				return *this;
			}
			/**
			* TODO *it
			*/
			T& operator*() const
			{
				if (*this == container->cend()) throw invalid_iterator();
				return *(node->data);
			}
			/**
			* TODO it->field
			*/
			T* operator->() const noexcept
			{
				if (*this == container->cend()) throw invalid_iterator();
				return (node->data);
			}
			/**
			* a operator to check whether two iterators are same (pointing to the same memory).
			*/
			bool operator==(const iterator &rhs) const
			{
				return (node == rhs.getNode());
			}
			bool operator==(const const_iterator &rhs) const
			{
				return (node == rhs.getNode());
			}
			/**
			* some other operator for iterator.
			*/
			bool operator!=(const iterator &rhs) const { return (node != rhs.node); }
			bool operator!=(const const_iterator &rhs) const { return (node != rhs.node); }

			link_type getNode() const { return node; }
			const deque* getContainer() const { return container; }
			// And other methods in iterator.
	};
	size_t length;
	link_type head, tail;
	/**
	 * TODO Constructors
	 */
	
	deque():length(0)
	{
		head = new node;
		tail = new node;
		head->next = tail;
		tail->prev = head;
	}
	deque(const deque &other)
	{
		if (&other == this) return;
		head = new node;
		tail = new node;
		head->next = tail;
		tail->prev = head;
		length = other.size();
		if (other.empty()) return;
		iterator pos(other.begin());
		link_type tmp;
		while (pos != other.end())
		{
			tmp = new node(*(pos.getNode()->data), tail->prev, tail);
			tail->prev->next = tmp;
			tail->prev = tmp;
			++pos;
		}
	}
	/**
	 * TODO Deconstructor
	 */
	
	~deque() 
	{ 
		clear();
		delete head;
		delete tail;
		head = NULL;
		tail = NULL;
	}
	/**
	 * TODO assignment operator
	 */
	deque &operator=(const deque &other) 
	{
		if (&other == this) return *this;
		clear();
		length = other.size();
		if (other.empty()) return *this;
		iterator pos(other.begin());
		link_type tmp;
		while (pos != other.end())
		{
			tmp = new node(*(pos.getNode()->data), tail->prev, tail);
			tail->prev->next = tmp;
			tail->prev = tmp;
			++pos;
		}
		return *this;
	}
	/**
	 * access specified element with bounds checking
	 * throw index_out_of_bound if out of bound.
	 */
	T & at(const size_t &pos) 
	{
		if (empty()) throw container_is_empty();
		iterator now(begin());
		size_t num = pos;
		while (num-- > 0)
		{
			if (++now == end()) throw index_out_of_bound();
		}
		return *(now.getNode()->data);
	}
	const T & at(const size_t &pos) const 
	{
		if (empty()) throw container_is_empty();
		const_iterator now(cbegin());
		size_t num = pos;
		while (num-- > 0)
		{
			if (++now == end()) throw index_out_of_bound();
		}
		return *(now.getNode()->data);
	}
	T & operator[](const size_t &pos) 
	{
		if (empty()) throw container_is_empty();
		iterator now(begin());
		size_t num = pos;
		while (num-- > 0)
		{
			if (++now == end()) throw index_out_of_bound();
		}
		return *(now.getNode()->data);
	}
	const T & operator[](const size_t &pos) const 
	{
		if (empty()) throw container_is_empty();
		const_iterator now(cbegin());
		size_t num = pos;
		while (num-- > 0)
		{
			if (++now == end()) throw index_out_of_bound();
		}
		return *(now.getNode()->data);
	}
	/**
	 * access the first element
	 * throw container_is_empty when the container is empty.
	 */
	const T & front() const 
	{
		if (empty()) throw container_is_empty();
		return *(cbegin().getNode()->data);
	}
	/**
	 * access the last element
	 * throw container_is_empty when the container is empty.
	 */
	const T & back() const 
	{
		if (empty()) throw container_is_empty();
		return *((--cend()).getNode()->data);
	}
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin() const { return iterator(head->next,this); }
	const_iterator cbegin() const { return const_iterator(head->next,this); }
	/**
	 * returns an iterator to the end.
	 */
	iterator end() const { return iterator(tail,this); }
	const_iterator cend() const { return const_iterator(tail,this); }
	/**
	 * checks whether the container is empty.
	 */
	bool empty() const { return begin()==end(); }
	/**
	 * returns the number of elements
	 */
	size_t size() const { return length; }
	/**
	 * clears the contents
	 */
	void clear()
	{
		if (head == NULL || tail == NULL) return;
		link_type pos = head->next, tmp;
		while (pos != tail)
		{
			tmp = pos->next;
			delete pos;
			pos = tmp;
		}
		length = 0;
		head->next = tail;
		tail->prev = head;
	}
	/**
	 * inserts elements at the specified locat on in the container.
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value
	 *     throw if the iterator is invalid or it point to a wrong place.
	 */
	iterator insert(iterator pos, const T &value) 
	{
		if (pos.getContainer() != this) throw invalid_iterator();
		//if (pos!=begin() && pos!=end()) throw invalid_iterator();
		iterator tmp(new node(value, pos.getNode()->prev, pos.getNode()),pos.getContainer());
		pos.getNode()->prev->next = tmp.getNode();
		pos.getNode()->prev = tmp.getNode();
		length++;
		return tmp;
	}
	/**
	 * removes specified element at pos.
	 * removes the element at pos.
	 * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
	 * throw if the container is empty, the iterator is invalid or it points to a wrong place.
	 */
	iterator erase(iterator pos) 
	{
		if (pos.getContainer() != this) throw invalid_iterator();
		if (empty()) throw container_is_empty();
	    //if (pos != begin() && pos != --end()) throw invalid_iterator();
		if(pos==end()) throw invalid_iterator();
		iterator tmp = pos;
		++tmp;
		pos.getNode()->next->prev = pos.getNode()->prev;
		pos.getNode()->prev->next = pos.getNode()->next;
		pos.clear();
		length--;
		return tmp;
	}
	/**
	 * adds an element to the end
	 */
	void push_back(const T &value) 
	{
		iterator tmp = insert(end(), value);
	}
	/**
	 * removes the last element
	 *     throw when the container is empty.
	 */
	void pop_back() 
	{
		if (empty()) throw container_is_empty();
		iterator t = end();
		--t;
		iterator tmp = erase(t);
	}
	/**
	 * inserts an element to the beginning.
	 */
	void push_front(const T &value) 
	{
		iterator tmp = insert(begin(), value);
	}
	/**
	 * removes the first element.
	 *     throw when the container is empty.
	 */
	void pop_front() 
	{
		if (empty()) throw container_is_empty();
		iterator tmp = erase(begin());
	}
};

}

#endif