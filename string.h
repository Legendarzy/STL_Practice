#pragma once
#include<assert.h>
#include<iostream>
namespace bit{
	class string {
	public:
		typedef char* iterator;
		//string的迭代器就是指针
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		string(const char* str="")//全缺省的构造函数
			:_capacity(strlen(str))
			,_size(_capacity)
		{
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_capacity, s._capacity);
			std::swap(_size, s._size);
			//注意，若要交换两个string对象，有两种方法
			//这个函数的作用是交换两个对象的具体值，代价小
			//若直接std::swap(s1,s2)，会导致三次拷贝构造，代价大
		}
		//传统的拷贝构造：老老实实开空间
		/*string(const string& str)
			:_capacity(strlen(str._str))
			, _size(_capacity)
		{
			_str = new char[_capacity + 1];
			strcpy(_str, str._str);
		}*/
		//现代写法
		string(const string& str)
			:_str(nullptr)//这一句的作用是避免temp指向随机值，导致后续析构崩溃
		{
			string tmp(str._str);
			//空手套白狼，让其他函数来帮你干活
			//不是效率上的提升，而是代码复用
			swap(tmp);
		}
		//传统赋值
		//string& operator=(const string& s)
		//{
		//	if (this != &s) {
		//		//直接使用地址比较，不用再重载！=了
		//		//这一步的判断是为了避免自己给自己赋值，导致空间被释放
		//		//小细节，释放空间不会失败，但开辟空间有可能失败
		//		char* tmp = new char[s._capacity + 1];
		//		strcpy(tmp, s._str);
		//		//这样即使开辟空间失败，                     
		//		delete[] _str;
		//		_str = tmp;
		//		_size = s._size;
		//		_capacity = s._capacity;
		//	}
		//	return *this;
		//}
		
		//现代写法1
		string& operator=(const string& s)
		{
			if (this != &s) {
				string tmp(s);
				swap(tmp);
				//这样也不需要delete[] _str
				//因为tmp是局部变量，出作用域直接析构了
				
			}
			return *this;
		}
		////现代写法2
		//string& operator=(string s)
		//{
		//	//这里使用传值，所以s就相当于上面的temp了
		//	swap(s);
		//}
		char* c_str()
		{
			return _str;
		}
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		size_t size() const
		{
			return _size;
		}
		char& operator[](size_t pos) const
		{
			assert (pos < _size);
			return _str[pos];
		}
		void reserve(size_t n)
		{
			//扩容
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}
		void push_back(char c) 
		{
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}
			_str[_size] = c;
			++_size;
			//最后记得要补上 '\0'，不然一直不会终止
			_str[_size] = '\0';
		}
		void append(const char* str)
		{
			int n = strlen(str);
			reserve(_size + n);//看是否需要扩容
			strcpy(_str + _size, str);//直接在最后面开始拷贝
			_size += n;
		}
		string& operator+=(const char* str)
		{
			if (strlen(str) == 1)
			{
				push_back(str[0]);
			}else
			{
				append(str);
			}
			return *this;
		}
		void resize(size_t n, char ch = '\0')
		{
			if (n > _size)
			{
				if (n >= _capacity)
					reserve(n);
				for (size_t i = _size;i < n;++i)
					push_back(ch);
			}
			else
			{
				//这一步很巧妙，直接加一个‘\0’
				_str[n] = '\0';
				_size = n;
			}
		}
	private:
		char* _str;
		size_t _capacity;//能最多存储的有效字符的个数
		size_t _size;//有效字符个数

	};
	ostream& operator<<(ostream& out,const string& s) 
	{
		for (size_t i = 0;i < s.size();++i)
			out << s[i];
		out << endl;
		return  out;
	}
	istream& operator>>(istream& in, string& s)
	{
		char ch = in.get();
		while (ch != ' ' && ch != '\n')
		{
			s.push_back(ch);
			ch = in.get(); 
		}
		return in;
	}
	void test1() 
	{
		string s1("hello world");
		//string s2(s1);
		//直接使用默认的拷贝构造会导致崩溃
		//浅拷贝，s2指针指向的和s1是一个地方
		//s2先析构释放空间：一块空间不能被释放两次，导致程序崩溃
		string s2(s1);

	}
	void test2() 
	{
		string s1;
		cin >> s1;
		cout << s1;
	}
}
