#pragma once
using namespace std;
#include<vector>

namespace bit
{
	template<class T>
	struct Less
	{
		//a小于b返回True
		bool operator()(const T& a, const T& b)const
		{
			return a < b;
		}
	};

	template<class T>
	struct Greater
	{	//仿函数：重载括号可以像函数那样调用
		bool operator()(const T& a, const T& b)const
		{
			//a大于b返回True
			return a > b;
		}
	};
	template<class T,class Container=vector<T>,class Compare=Less<T>>
	//Container=vector<T>适配器
	class priority_queue
	{
	private:
		Container _con;
		void adjust_up(size_t child)
		{
			Compare com;
			size_t parent = (child - 1) / 2;
			while (child > 0)
			{
				if (com( _con[parent],_con[child]))
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}
		void adjust_down(size_t parent)
		{
			Compare com;
			size_t child = 2 * parent + 1;
			if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))
			{
				++child;
			}
			while (child<_con.size())
			{
				if (com(_con[parent], _con[child]))
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = 2 * parent + 1;
					if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))
					{
						++child;
					}
				}
				else
				{
					break;
				}
			}
		}
	public:
		priority_queue()
		{}

		template<class InputIterator>
		priority_queue(InputIterator first,InputIterator last)
			:_con(first,last)
			//调用自定义类型的初始化
		{
			for (int i = (_con.size - 2) / 2; i >= 0; --i)
			{
				adjust_down(i);
			}
		}
		void push(const T& val)
		{
			_con.push_back(val);
			//把child的位置传回去
			adjust_up(_con.size() - 1);
		}
		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			adjust_down(0);
		}
		T& top()
		{
			return _con[0];
		}
		size_t size()
		{
			return _con.size();
		}
		bool empty()
		{
			return _con.empty();
		}
	};
	template<class T>
	ostream& operator<<(ostream& out, priority_queue<T> pq)
	{
		while (!pq.empty())
		{
			out << pq.top() << " ";
			pq.pop();
		}
		out << endl;
		return out;
	}
	
	void test_1()
	{
		priority_queue<int> pq;
		
		pq.push(2);
		pq.push(4);
		pq.push(24);
		pq.push(1);
		pq.push(1);
		pq.push(34);
		pq.push(3);
		pq.push(4);
		
		pq.push(5);
		pq.push(3);
		cout << pq;

	}
	
}