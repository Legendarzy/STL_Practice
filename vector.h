#pragma once
namespace bit {
	template <class T>

	class vector {
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		vector()
			:_start(nullptr),
			_finish(nullptr),
			_end_of_file(nullptr)
		{}
		//一个类模板的成员函数，又可以是一个函数模板
		template <class InputIterator>
		//迭代器构造
		vector(InputIterator first, InputIterator last)
			:_start(nullptr),
			_finish(nullptr),
			_end_of_file(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		vector(const vector<T>& t)
			:_start(nullptr),
			_finish(nullptr),
			_end_of_file(nullptr)
		{
			//这里需要const形式的迭代器
			vector<T> tmp(t.begin(), t.end());
			swap(tmp);
		}
		vector<T>& operator=(vector<T> t)
		{
			swap(t);
			return *this;
		}
		~vector()
		{
			if (_start)
			{
				delete[] _start;
			}
			_end_of_file = _finish = _start = nullptr;
		}
		size_t size()
		{
			return _finish - _start;
		}
		size_t capacity()
		{
			return _end_of_file - _start;
		}
		const_iterator begin() const
		{
			return _start;
		}
		const_iterator end() const
		{
			return _finish;
		}
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		void reserve(size_t newCapacity)
		{
			T* tmp = new T[newCapacity];
			if (_start)
			{
				//如果原vector不为空，需要转移数据
				//memcpy(tmp, _start, size() * sizeof(T));
				//这种方式会导致浅拷贝，会出现野指针
				for (size_t i = 0; i < _finish - _start; ++i)
				{
					tmp[i] = _start[i];
				}
				delete[] _start;
			}
			_finish = tmp + size();
			_start = tmp;
			_end_of_file = tmp + newCapacity;
		}
		void resize(size_t newCapacity, const T& val=T())
		{
			if (newCapacity > size())
			{
				if (newCapacity > capacity())
				{
					reserve(newCapacity);
				}
				while (_finish < _start + newCapacity)
				{
					*_finish = val;
					++_finish;
				}
			}
			else
			{
				_finish = _start + newCapacity;
			}
		}
		void push_back(const T& t)
		{
			insert(end(), t);
		}
		void insert(iterator pos, const T& val)
		{
			assert(pos >= _start);
			assert(pos <= _finish);//可以等于——finish，为之后尾插准备
			size_t delta = _finish - pos;
			if (_finish == _end_of_file)
			{
				//扩容
				size_t newCapacity = capacity() == 0 ? 4 : 2 * capacity();
				reserve(newCapacity);
			}
			//注意，扩容后，_finsh等指针都会移动到新空间，但pos没变
			//所以导致pos在空间释放后变成野指针
			iterator end = _finish;
			pos = _finish - delta;//需要在扩容后更新pos
			while (end > pos)
			{
				*end = *(end - 1);
				--end;
			}
			*end = val;
			++_finish;
		}
		iterator erase(iterator pos)
		{
			//删除指定位置的元素
			assert(pos >= _start);
			assert(pos < _finish);
			iterator it = pos;
			while (it < end())
			{
				*it = *(it + 1);
				++it;
			}
			_finish--;
			//返回删除位置元素的下一个位置
			return pos;
		}
		T& operator[](const int i)
		{
			assert(i < size());
			return *(_start + i);
		}
		void swap(vector<T>& t)
		{
			std::swap(_start, t._start);
			std::swap(_finish, t. _finish);
			std::swap(_end_of_file, t._end_of_file);
		}
	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_file;
	};
	template<class T>
	ostream& operator<<(ostream& out, const vector<T>& t)
	{
		for (auto e : t)
		{
			out << e << " ";
		}
		out << endl;
		return out;
	}

	void test_vector_1() {
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}
	
	class Solution {
	public:
		vector<vector<int>> generate(int numRows) {
			vector<vector<int>> vv;
			vv.resize(numRows);
			for (size_t i = 0;i < numRows;++i)
			{
				vv[i].resize(i + 1);
				for (size_t j = 0;j <= i;++j)
				{
					if (j == 0 || j == i)
					{
						(vv[i][j]) = 1;
					}
					else
					{
						vv[i][j] = vv[i - 1][j - 1] + vv[i - 1][j];
					}
				}
			}
			return vv;
		}
	};
	void test_vector_2()
	{
		vector<vector<int>> ret = Solution().generate(5);
		for (auto a : ret)
		{
			for (auto b : a)
			{
				cout << b << " ";
			}
			cout << endl;
		}
	}
	void test_vector_3() 
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		vector<int>v2;
		v2 = v1;
		for (auto e : v2)
		{
			cout << e << " ";
		}
		cout << endl;
	}
	void test_vector_4()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		//v1.push_back(5);
		//v1.push_back(6);
		vector<int>::iterator pos = find(v1.begin(), v1.end(), 2);
		if (pos != v1.end())
		{
			v1.insert(pos, 100);
		}
		cout << v1;
		
	}
	void test_vector_5()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		//v1.push_back(5);
		//v1.push_back(6);
		cout << v1;
		auto it = v1.begin();
		while (it < v1.end())
		{
			if (*it % 2 == 0)
			{
				it = v1.erase(it);
			}
			else
			{
				++it;
			}
		}
		cout << v1;
	}
	void test_vector_6()
	{
		vector<string> v;
		v.push_back("11111111111111111111111111111111111");
		v.push_back("1111");
		v.push_back("1111"); 
		v.push_back("1111"); 
		v.push_back("1111");
		cout << v;
	}
}