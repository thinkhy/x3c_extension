//! \file vecfunc.h
//! \brief ����STL�����ļ��Ͷ������麯��

#ifndef __STL_VECTOR_FUNCTIONS_H
#define __STL_VECTOR_FUNCTIONS_H

#pragma warning(disable:4710)	// inline function not expanded
#pragma warning(disable:4786)	// identifier was truncated
#pragma warning (push, 3)
#pragma warning(disable:4018)	// signed/unsigned mismatch
#pragma warning(disable:4702)	// unreachable code
#include <algorithm>
#include <xstring>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <sstream>
#pragma warning (pop)

#ifdef __AFX_H__
//! ��CString��ȫ��ת��Ϊwstring������յ�ַ����
inline std::wstring towstr(const CString& str)
{
	return str.IsEmpty() ? L"" : (LPCTSTR)str;
}
#endif

//! ��������ɾ������Ԫ��
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL�������������" vector<Ix_xxx*> arr; "
	\param _P Ҫɾ�����������ʽ������" std::bind2nd(std::equal_to<Ix_xxx*>(), pObj) "
	\return �Ƿ���ɾ��
*/
template<class _Ta, class _Pr> inline
bool erase_if(_Ta& arr, _Pr _P)
{
	_Ta::iterator it = std::find_if(arr.begin(), arr.end(), _P);
	bool b = (it != arr.end());

	if (b)
	{
		arr.erase(it);
	}

	return b;
};

//! ����Ԫ��ֵɾ������Ԫ��
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL�������������Ϊvector< _Tp >������" vector<Ix_xxx*> arr; "
	\param p Ҫɾ����Ԫ��ֵ�������ͺ�arr����Ԫ��������ͬ������" Ix_xxx* pObj"
	\return �Ƿ���ɾ��
*/
template<class _Ta, class _Tp> inline
bool erase_value(_Ta& arr, _Tp& p)
{
	return erase_if(arr, std::bind2nd(std::equal_to<_Tp>(), p));
}

//! ����������������Ԫ�ص�λ��
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL�������������" vector<Ix_xxx*> arr; "
	\param _P Ҫ���ҵ��������ʽ������" std::bind2nd(std::equal_to<Ix_xxx*>(), pObj) "
	\return Ԫ��λ�ã�-1��ʾû�ҵ�
*/
template<class _Ta, class _Pr> inline
long find_if(const _Ta& arr, _Pr _P)
{
	_Ta::const_iterator it = std::find_if(arr.begin(), arr.end(), _P);
	return (it != arr.end()) ? (long)(it - arr.begin()) : -1;
}

//! ����Ԫ��ֵ��������Ԫ�ص�λ��
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL�������������Ϊvector< _Tp >������" vector<Ix_xxx*> arr; "
	\param p Ԫ��ֵ�������ͺ�arr����Ԫ��������ͬ������" Ix_xxx* pObj"
	\return Ԫ��λ�ã�-1��ʾû�ҵ�
*/
template<class _Ta, class _Tp> inline
long find_value(const _Ta& arr, const _Tp& p)
{
	return find_if(arr, std::bind2nd(std::equal_to<_Tp>(), p));
}

//! ����������ִ��ĳ���
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL����������ִ�
	\return Ԫ�ظ���
*/
template<class _Ta> inline
long GetSize(const _Ta& arr)
{
	return static_cast<long>(arr.size());
}

//! �ж�����Ԫ�������Ƿ񳬳����鷶Χ
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL�������������" vector<Ix_xxx*> arr; "
	\param index ����Ԫ���������
	\return �Ƿ񳬳����鷶Χ
*/
template<class _Ta> inline
bool IsValidIndexOf(const _Ta& arr, long index)
{
	return index >= 0 && index < static_cast<long>(arr.size());
}

#if _MSC_VER <= 1200 // VC6
#include "func_s.h"
#endif

#endif // __STL_VECTOR_FUNCTIONS_H
