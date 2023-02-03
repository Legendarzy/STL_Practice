#pragma once
#include<assert.h>
#include<iostream>
namespace bit{
	class string {
	public:
		typedef char* iterator;
		//string�ĵ���������ָ��
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		string(const char* str="")//ȫȱʡ�Ĺ��캯��
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
			//ע�⣬��Ҫ��������string���������ַ���
			//��������������ǽ�����������ľ���ֵ������С
			//��ֱ��std::swap(s1,s2)���ᵼ�����ο������죬���۴�
		}
		//��ͳ�Ŀ������죺����ʵʵ���ռ�
		/*string(const string& str)
			:_capacity(strlen(str._str))
			, _size(_capacity)
		{
			_str = new char[_capacity + 1];
			strcpy(_str, str._str);
		}*/
		//�ִ�д��
		string(const string& str)
			:_str(nullptr)//��һ��������Ǳ���tempָ�����ֵ�����º�����������
		{
			string tmp(str._str);
			//�����װ��ǣ�����������������ɻ�
			//����Ч���ϵ����������Ǵ��븴��
			swap(tmp);
		}
		//��ͳ��ֵ
		//string& operator=(const string& s)
		//{
		//	if (this != &s) {
		//		//ֱ��ʹ�õ�ַ�Ƚϣ����������أ�=��
		//		//��һ�����ж���Ϊ�˱����Լ����Լ���ֵ�����¿ռ䱻�ͷ�
		//		//Сϸ�ڣ��ͷſռ䲻��ʧ�ܣ������ٿռ��п���ʧ��
		//		char* tmp = new char[s._capacity + 1];
		//		strcpy(tmp, s._str);
		//		//������ʹ���ٿռ�ʧ�ܣ�                     
		//		delete[] _str;
		//		_str = tmp;
		//		_size = s._size;
		//		_capacity = s._capacity;
		//	}
		//	return *this;
		//}
		
		//�ִ�д��1
		string& operator=(const string& s)
		{
			if (this != &s) {
				string tmp(s);
				swap(tmp);
				//����Ҳ����Ҫdelete[] _str
				//��Ϊtmp�Ǿֲ���������������ֱ��������
				
			}
			return *this;
		}
		////�ִ�д��2
		//string& operator=(string s)
		//{
		//	//����ʹ�ô�ֵ������s���൱�������temp��
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
			//����
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
			//���ǵ�Ҫ���� '\0'����Ȼһֱ������ֹ
			_str[_size] = '\0';
		}
		void append(const char* str)
		{
			int n = strlen(str);
			reserve(_size + n);//���Ƿ���Ҫ����
			strcpy(_str + _size, str);//ֱ��������濪ʼ����
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
				//��һ�������ֱ�Ӽ�һ����\0��
				_str[n] = '\0';
				_size = n;
			}
		}
	private:
		char* _str;
		size_t _capacity;//�����洢����Ч�ַ��ĸ���
		size_t _size;//��Ч�ַ�����

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
		//ֱ��ʹ��Ĭ�ϵĿ�������ᵼ�±���
		//ǳ������s2ָ��ָ��ĺ�s1��һ���ط�
		//s2�������ͷſռ䣺һ��ռ䲻�ܱ��ͷ����Σ����³������
		string s2(s1);

	}
	void test2() 
	{
		string s1;
		cin >> s1;
		cout << s1;
	}
}
