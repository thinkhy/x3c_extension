/*! \file vecptr.h
 *  \brief ����STLָ������ĳ��ú���
 *  \author Zhang Yun Gui, C++ Plugin Framework
 *  \date   2010.10.22
 */
#ifndef UTILFUNC_VECPTR_H_
#define UTILFUNC_VECPTR_H_

#include "vecfunc.h"
#include <XComPtr.h>

//! �õ�����������ָ����ŵĶ���
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL�������������" vector<ObjPtr> arr; "
	\param index Ԫ�����
	\return �����е�Ԫ�ض��󣬻�ն����ʾԽ��
*/
template<class _Ta> inline
Cx_Ptr GetPtrIndexOf(const _Ta& arr, long index)
{
	return IsValidIndexOf(arr, index) ? Cx_Ptr(arr[index]) : Cx_Ptr();
}

//! Cx_Ptr����Ĳ����㷨����
template<class IF_Type>
struct FindByPtr : std::binary_function<Cx_Ptr, Cx_Ptr, bool>
{
	bool operator()(const Cx_Ptr& p1, const Cx_Ptr& p2) const
	{
		if (p1.P() == p2.P())
			return true;

		if (p1.IsNotNull() != p2.IsNotNull())
			return false;

		Cx_Interface<IF_Type> pIF1 (p1);
		Cx_Interface<IF_Type> pIF2 (p2);

		return pIF1 == pIF2;
	}
};

//! ��ֵ�Ե�����Ĳ����㷨��������ֵ�Եĵڶ���ΪCx_Ptr
template<class IF_Type, class Pair_Type>
struct FindPairByPtr : std::binary_function<Pair_Type, Pair_Type, bool>
{
	bool operator()(const Pair_Type& v1, const Pair_Type& v2) const
	{
		const Cx_Ptr& p1 = v1.second;
		const Cx_Ptr& p2 = v2.second;

		if (p1.P() == p2.P())
			return true;

		if (p1.IsNotNull() != p2.IsNotNull())
			return false;

		Cx_Interface<IF_Type> pIF1 (p1);
		Cx_Interface<IF_Type> pIF2 (p2);

		return pIF1 == pIF2;
	}
};

//! ����Ԫ��ֵɾ������Ԫ��
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL���������Ԫ������ΪCx_Ptr������ vector<Cx_Ptr>
	\param p Ҫɾ����Ԫ��ֵ
	\return �Ƿ���ɾ��
*/
template<class IF_Type, class _Ta> inline
bool erase_value(_Ta& arr, Cx_Ptr& p)
{
	return erase_if(arr, std::bind2nd(FindByPtr<IF_Type>(), p));
}

//! ����Ԫ��ֵɾ������Ԫ��
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL���������Ԫ������ΪPair_Type������ vector<Pair_Type>
	\param p Ҫɾ������ֵ�ԣ��ڶ���ΪCx_Ptr
	\return �Ƿ���ɾ��
*/
template<class IF_Type, class _Ta, class Pair_Type> inline
bool erase_pair(_Ta& arr, Pair_Type& p)
{
	return erase_if(arr, std::bind2nd(FindPairByPtr<IF_Type, Pair_Type>(), p));
}

//! ����Ԫ��ֵ��������Ԫ�ص�λ��
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL���������Ԫ������ΪCx_Ptr������ vector<Cx_Ptr>
	\param p Ԫ��ֵ
	\return Ԫ��λ�ã�-1��ʾû�ҵ�
*/
template<class IF_Type, class _Ta> inline
long find_value(const _Ta& arr, const Cx_Ptr& p)
{
	return find_if(arr, std::bind2nd(FindByPtr<IF_Type>(), p));
}

//! ����Ԫ��ֵ��������Ԫ�ص�λ��
/*!
	\ingroup _GROUP_UTILFUNC
	\param arr STL���������Ԫ������ΪPair_Type������ vector<Pair_Type>
	\param p Ԫ��ֵ����ֵ�ԣ��ڶ���ΪCx_Ptr
	\return Ԫ��λ�ã�-1��ʾû�ҵ�
*/
template<class IF_Type, class _Ta, class Pair_Type> inline
long find_pair(_Ta& arr, Pair_Type& p)
{
	return find_if(arr, std::bind2nd(FindPairByPtr<IF_Type, Pair_Type>(), p));
}

#endif // UTILFUNC_VECPTR_H_
