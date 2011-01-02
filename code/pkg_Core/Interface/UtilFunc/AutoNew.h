// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// https://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//! \file AutoNew.h
//! \brief �����Զ��ͷ��ڴ�ĸ����� KAutoNew, KAutoNewArr, KAutoMalloc, KAutoNewArr2d

#ifndef __AUTOFREE_NEW_H
#define __AUTOFREE_NEW_H

// KAutoNew:
// T* p = new T(); => KAutoNew<T> p (new T());
//
// KAutoNewArr:
// T* p = new T[5]; => KAutoNewArr<T> p (5);
//
// KAutoMalloc:
// T* p = (T*)malloc(5 * sizeof(T)); => KAutoMalloc<T> p (5);
//
// KAutoNewArr2d:
// T arr[100][200]; => KAutoNewArr2d<T> arr (100, 200);
//


//! �Զ��ͷ��ڴ�ĸ����࣬�Բ��� new �����ڴ�Ĵ�����и���
/*! ���� T* p = new T; ������Ϊ�� KAutoNew<T> p (new T); ��
	\ingroup _GROUP_UTILFUNC
*/
template<typename T>
struct KAutoNew
{
	T*	ptr;

	KAutoNew() : ptr(NULL) {}
	KAutoNew(T* p) : ptr(p) {}
	~KAutoNew() { delete ptr; }
	void Free() { if (ptr) { delete ptr; ptr = NULL; } }

	operator T* () { return ptr; }
	operator const T* () const { return ptr; }

	operator bool() const { return ptr != NULL; }
	bool operator!() const { return ptr == NULL; }

	T* operator->() const { return ptr; }
};

//! �Զ��ͷ�����ĸ����࣬�Բ��� new[] �����ڴ�Ĵ�����и���
/*! ���� T* p = new T[5]; ������Ϊ�� KAutoNewArr<T> p (5); ��
	\ingroup _GROUP_UTILFUNC
*/
template<typename T>
struct KAutoNewArr
{
	T*		ptr;
	size_t	count;

	KAutoNewArr() : count(0), ptr(NULL) {}
	KAutoNewArr(size_t _count) : count(_count), ptr(new T[_count]) {}
	~KAutoNewArr() { delete[] ptr; }

	void Free()
	{
		if (ptr)
		{
			delete[] ptr;
			ptr = NULL;
		}
		count = 0;
	}

	bool Realloc(size_t _count)
	{
		ptr = new T[_count];
		count = _count;
		return true;
	}

	KAutoNewArr<T>& operator=(const KAutoNewArr<T>& src)
	{
		if (this != &src)
		{
			if (count == src.count || Realloc(src.count))
			{
				for (size_t i = 0; i < count; i++)
				{
					ptr[i] = src.ptr[i];
				}
			}
		}
		return *this;
	}

	T& at(size_t index)
	{
		ASSERT(index >= 0 && index < count);
		return ptr[index];
	}

	T& operator[](size_t index)
	{
		ASSERT(index >= 0 && index < count);
		return ptr[index];
	}

	const T& operator[](size_t index) const
	{
		ASSERT(index >= 0 && index < count);
		return ptr[index];
	}

	operator bool() const { return ptr != NULL; }
	bool operator!() const { return ptr == NULL; }
};

//! �Զ��ͷ�����ĸ����࣬���� malloc ��������
/*! ���� T* p = (T*)malloc(5 * sizeof(T)); ������Ϊ�� KAutoMalloc<T> p (5); ��\n
	���໹�������ڽ���̬һά���鶨���Ϊ��̬�ڴ���ʽ��
	����ԡ�double a[10000]���Ż�Ϊ��KAutoMalloc< double> a(10000)����\n
	�Զ�ά��̬�����ʹ�� KAutoNewArr2d ���Ż������硰double a[1000][1000]��
	\ingroup _GROUP_UTILFUNC
*/
template<typename T>
struct KAutoMalloc
{
	T*		ptr;
	size_t	count;

	KAutoMalloc() : count(0), ptr(NULL) {}
	~KAutoMalloc() { if (ptr) free(ptr); }

	KAutoMalloc(size_t _count)
		: count(_count)
		, ptr((T*)malloc(sizeof(T)*_count))
	{
		memset(ptr, 0, sizeof(T)*_count);
	}

	void Free()
	{
		if (ptr)
		{
			free(ptr);
			ptr = NULL;
		}
		count = 0;
	}

	bool Realloc(size_t _count)
	{
		T* p = (T*)realloc(ptr, sizeof(T)*_count);
		if (p)
		{
			ptr = p;
			count = _count;
			memset(ptr, 0, sizeof(T)*_count);
		}
		return p != NULL;
	}

	KAutoMalloc<T>& operator=(const KAutoMalloc<T>& src)
	{
		if (this != &src)
		{
			if (count == src.count || Realloc(src.count))
			{
				memcpy(ptr, src.ptr, sizeof(T)*count);
			}
		}
		return *this;
	}

	T& at(size_t index)
	{
		ASSERT(index >= 0 && index < count);
		return ptr[index];
	}

	T& operator[](size_t index)
	{
		ASSERT(index >= 0 && index < count);
		return ptr[index];
	}

	const T& operator[](size_t index) const
	{
		ASSERT(index >= 0 && index < count);
		return ptr[index];
	}

	operator bool() const { return ptr != NULL; }
	bool operator!() const { return ptr == NULL; }
};

//! �Զ��ͷŶ�ά����ĸ�����
/*! ���� T arr[100][200]; ������Ϊ�� KAutoNewArr2d<T> arr (100, 200); ��\n
	���໹�������ڽ���̬��ά���鶨���Ϊ��̬�ڴ���ʽ��
	����ԡ�double a[1000][1000]���Ż�Ϊ��KAutoNewArr2d< double> a(1000, 1000)����\n
	��һά��̬�����ʹ�� KAutoMalloc ���Ż������硰double a[10000]��
	\ingroup _GROUP_UTILFUNC
*/
template<typename T, typename T2 = KAutoMalloc<T> >
struct KAutoNewArr2d : KAutoNewArr<T2>
{
	KAutoNewArr2d(size_t count1, size_t count2)
		: KAutoNewArr<T2>(count1)
	{
		for (size_t i = 0; i < count1; i++)
		{
			at(i).Realloc(count2);
		}
	}
};

#endif // __AUTOFREE_NEW_H
