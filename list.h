#pragma once
namespace bit {
	template<class T>
	struct ListNode
	{
		//����ǽڵ�Ķ���
		ListNode<T>* _next;
		ListNode<T>* _prev;
		T _val;
		ListNode(const T& val=T())
			:_next(nullptr),
			_prev(nullptr),
			_val(val)
		{}
	};
	template <class T,class Ref,class Ptr>
	struct __list_iterator
	{
		//list������������ԭ��ָ�룬��Ϊ����ռ䲻����
		//���Կ���ʹ���Զ�������
		//��������� ++��*
		typedef ListNode<T> Node;
		typedef __list_iterator<T, Ref,Ptr> self;
		Node* _node;
		__list_iterator(Node* x)
			:_node(x)
		{}

		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		self& operator++(int)
		{
			self tmp = self(_node);
			_node = _node->_next;
			return tmp;
		}
		bool operator!=(const self& lit) const
		{
			return lit._node != _node;
		}
		Ref operator*()
		{
			return _node->_val;
		}
		Ptr operator->()
		{
			return &_node->_val;
		}
	};
	template <class T>
	class list
		//��ͷ˫��ѭ������
	{
		typedef ListNode<T> Node;
	public:
		typedef __list_iterator<T,T&,T*> iterator;
		typedef __list_iterator<T, const T&,const T*> const_iterator;
		list()
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
		}
		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		void push_back(const T& val)
		{
			insert(end(), val);
		}
		void push_front(const T& val)
		{
			insert(begin(), val);
		}
		iterator insert(iterator pos, const T& val)
		{
			//��posǰ�����val
			Node* _pos = pos._node;
			Node* before = _pos->_prev;
			Node* newNode = new Node(val);
			newNode->_prev = before;
			newNode->_next = _pos;
			before->_next = newNode;
			_pos->_prev = newNode;
			return iterator(newNode);
		}
		iterator erase(iterator pos)
		{
			assert(pos != end());
			//ɾȥposλ�õĽڵ�
			Node* cur = pos._node;
			Node* before = cur->_prev;
			Node* after = cur->_next;
			before->_next = after;
			after->_prev = before;
			delete cur;
			return iterator(after);
		}
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}
		~list()
		{
			clear();
			delete _head;
		}
		list(const list<T>& lt)
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
			list<T> tmp(lt.begin(), lt.end());
			std::swap(_head, tmp._head);
		}
		list<T>& operator=(list<T> lt)
		{
			std::swap(_head, lt._head);
			return *this;
		}
		void pop_front()
		{
			erase(begin());
		}
		void pop_back()
		{
			erase(end()._node->_prev);
		}
		iterator begin()
		{
			return iterator(_head->_next);
		}
		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		const_iterator end() const
		{
			return const_iterator(_head);
		}
		void print() const
		{
			list<int>::const_iterator lit = begin();
			//����������Ҫ�����Ĭ��ǳ����������������
			//ͬʱҲ����Ҫ��������Ϊ�ڵ㲻���ڵ����������������ڹ���
			while (lit != end())
			{
				//++*lit;
				cout << *lit << " ";
				++lit;
			}
			cout << endl;
		}
	private:
		Node* _head;//�ڲ�ֻ��һ��ͷָ��
	};
	struct Date
	{
		int _year;
		int _month;
		int _day;
		Date(int year = 1, int month = 1, int day = 1)
			:_year(year),
			_month(month),
			_day(day)
		{}
		
	};
	void test_list_1()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		lt.print();
	}
	void test_list_2()
	{
		list<Date>lt;
		lt.push_back(Date(2023, 2, 5));
		lt.push_back(Date(2023, 2, 6));
		lt.push_back(Date(2023, 2, 7));
		lt.push_back(Date(2023, 2, 8));
		//list<Date>::const_iterator lit = lt.begin();
		//Ϊʲô����ĳ�const_iterator�ͻᱨ��
		//������ʾ��lt.begin()���õ��Ƿ�const�İ汾��Ϊʲô��������
		for (list<Date>::iterator lit = lt.begin(); lit != lt.end(); ++lit)
		{
			cout << lit->_year << "/" << lit->_month << "/" << lit->_day << endl;
		}
		
	}

	void test_list_3()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		lt.insert(lt.begin(), 100);
		lt.print();
		lt.pop_back();
		lt.print();
		lt.pop_front();
		lt.print();
		lt.clear();
		lt.print();
		lt.push_back(1);
		lt.push_back(1);
		lt.push_back(1);
		lt.push_back(1);
		lt.print();
	}
	void test_list_4()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		list<int> lt2(lt);
		lt2.print();
		list<int>lt3;
		lt3.push_back(10);
		lt3.push_back(10);
		lt3.push_back(10);
		lt = lt3;
		lt.print();
	}
}