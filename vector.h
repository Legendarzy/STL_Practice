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
		//һ����ģ��ĳ�Ա�������ֿ�����һ������ģ��
		template <class InputIterator>
		//����������
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
			//������Ҫconst��ʽ�ĵ�����
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
				//���ԭvector��Ϊ�գ���Ҫת������
				//memcpy(tmp, _start, size() * sizeof(T));
				//���ַ�ʽ�ᵼ��ǳ�����������Ұָ��
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
			assert(pos <= _finish);//���Ե��ڡ���finish��Ϊ֮��β��׼��
			size_t delta = _finish - pos;
			if (_finish == _end_of_file)
			{
				//����
				size_t newCapacity = capacity() == 0 ? 4 : 2 * capacity();
				reserve(newCapacity);
			}
			//ע�⣬���ݺ�_finsh��ָ�붼���ƶ����¿ռ䣬��posû��
			//���Ե���pos�ڿռ��ͷź���Ұָ��
			iterator end = _finish;
			pos = _finish - delta;//��Ҫ�����ݺ����pos
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
			//ɾ��ָ��λ�õ�Ԫ��
			assert(pos >= _start);
			assert(pos < _finish);
			iterator it = pos;
			while (it < end())
			{
				*it = *(it + 1);
				++it;
			}
			_finish--;
			//����ɾ��λ��Ԫ�ص���һ��λ��
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