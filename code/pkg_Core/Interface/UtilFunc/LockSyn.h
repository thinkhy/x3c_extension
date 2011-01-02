//! \file LockSyn.h
//! \brief ����ͬ�����Ƶĸ����� CLockCs �� CLockRW

#ifndef UTILFUNC_LOCKSYN_H_
#define UTILFUNC_LOCKSYN_H_
#pragma once

class CLockCs;
class CReaderWriterLock;
class CLockRW;

//! ���ٽ����Զ������ͽ����ĸ�����
/*! �ٽ������������� CLockCs::CS ������.
	ʹ�ñ����ں����ж���ֲ������������������÷�Χ���Զ�����
	\ingroup _GROUP_UTILFUNC
*/
class CLockCs
{
public:
	//! �ٽ�������
	struct CS : public CRITICAL_SECTION
	{
		//! ���캯��, ��ʼ���ٽ���
		CS()
		{
#if (_WIN32_WINNT >= 0x0403)
			InitializeCriticalSectionAndSpinCount(this, 400);
#else
			InitializeCriticalSection(this);
#endif
		}
		
		//! ��������, �����ٽ���
		~CS()
		{
			DeleteCriticalSection(this);
		}
	};
	
public:
	//! ���캯�����Զ������ٽ���
	/*!
		\param pCs �ٽ��������ĵ�ַ��ΪNULLʱ���ཫ��������
		\param bTry �Ƿ�����Խ����ٽ��������ȴ���Ĭ��Ϊfalse��ʾҪ�ȴ�����
			�ٽ�����true��ʾ����ٽ����������߳�����ʱ�����������������ȴ���
			��ʱ������ IsLocked() ��������Ƿ�������ٽ�����
	*/
	CLockCs(CRITICAL_SECTION* pCs, bool bTry = false) : m_pcs(pCs)
	{
		if (NULL == m_pcs)
			return;

		try
		{
#if (_WIN32_WINNT >= 0x0400)
			if (bTry)
			{
				if (!::TryEnterCriticalSection(m_pcs))
					m_pcs = NULL;
			}
			else
				::EnterCriticalSection(m_pcs);
#else
			bTry;
			::EnterCriticalSection(m_pcs);
#endif
		}
		catch (...)
		{
			m_pcs = NULL;
		}
	}

	//! �����������Զ��뿪�ٽ���
	~CLockCs()
	{
		Unlock();
	}

	//! �뿪�ٽ���
	void Unlock()
	{
		if (m_pcs != NULL)
		{
			::LeaveCriticalSection(m_pcs);
			m_pcs = NULL;
		}
	}

	//! �����Ƿ��ѽ����ٽ���
	bool IsLocked() const
	{
		return m_pcs != NULL;
	}

private:
	CRITICAL_SECTION*	m_pcs;
};

//! ����֧�ֵ���д�̺߳Ͷ�����̵߳���
/*!
	ʹ�ñ��ඨ���߳����������Ҫ����ʱʹ�� CLockRW �ں����ж���ֲ�����
	\ingroup _GROUP_UTILFUNC
	\see CLockRW
*/
class CReaderWriterLock
{
public:
	//! ���캯��, ��Ҫ���� Init() ��ʼ��������
	CReaderWriterLock()
		: hWriteWaiting(NULL), hMutex(NULL), hDataLock(NULL)
		, nReadCount(0), nWriterSeqNum(0)
	{
	}
	
	//! ��������
	~CReaderWriterLock()
	{
		if (NULL != hDataLock)
			::CloseHandle(hDataLock);
		if (NULL != hMutex)
			::CloseHandle(hMutex);
		if (NULL != hWriteWaiting)
			::CloseHandle(hWriteWaiting);
	}
	
	//! ��ʼ��������
	bool Init()
	{
		if (NULL != hMutex)		// �Ѿ���ʼ��
			return true;
		
		// ������ֵ�ź���: ���δ��ӵ�У�����һ���߳̿�������
		hDataLock = ::CreateSemaphore(NULL, 1, 1, NULL);
		if (NULL != hDataLock)
		{
			// ������ֵ�ź����������������ȴ�д
			hWriteWaiting = ::CreateSemaphore(NULL, 1, 1, NULL);
			if (NULL == hWriteWaiting)
			{
				::CloseHandle(hDataLock);
				hDataLock = NULL;
			}
			else
			{
				hMutex = ::CreateMutex(NULL, false, NULL);	// ����������
				if (NULL == hMutex)
				{
					::CloseHandle(hDataLock);
					hDataLock = NULL;
					::CloseHandle(hWriteWaiting);
					hWriteWaiting = NULL;
				}
			}
		}
		
		return (NULL != hMutex);
	}
	
	//! �����Ƿ��ʼ��
	bool IsInited() const
	{
		return (NULL != hMutex);
	}
	
	//! ��ȡ���߳���, �� CLockRW ���캯��ʹ��, ������ֱ�ӵ���
	/*!
		\param nMaxWait ��ȡ���ĵȴ�����ʱ�䣬����
		\return �Ƿ�ִ�гɹ�
	*/
	bool _AcquireReaderLock(DWORD nMaxWait = 5000)
	{
		bool bRet;
		
		// ������ȴ�д���͹����µĶ�����
		bRet = Wait(hWriteWaiting, nMaxWait);
		if (bRet)										// û�еȴ�д��
			::ReleaseSemaphore(hWriteWaiting, 1, NULL);
		
		if (bRet && Wait(hMutex, nMaxWait))			// ����������
		{
			// ���Ӷ�����. ����ǵ�һ�����������ֹд
			if (1 == InterlockedIncrement(&nReadCount))
			{
				bRet = Wait(hDataLock, nMaxWait);		// ��ֹд
				if (!bRet)								// ��ʱ������д
					InterlockedDecrement(&nReadCount);
			}
			
			::ReleaseMutex(hMutex);						// �������������
		}
		else
			bRet = false;				// ��ʱ��ǰһ�������ȴ�д�����
		
		return bRet;
	}
	
	//! �ͷŶ��߳���, �� CLockRW ʹ��, ������ֱ�ӵ���
	/*!
		\return �Ƿ�ִ�гɹ�
	*/
	bool _ReleaseReaderLock()
	{
		bool bRet = false;
		LONG lPrevCount;
		
		if (Wait(hMutex))								// ����������
		{
			bRet = true;
			if (0 == InterlockedDecrement(&nReadCount))	// ���ٶ�������û�ж�������
				bRet = ::ReleaseSemaphore(hDataLock, 1, &lPrevCount);	// ����д
			::ReleaseMutex(hMutex);						// �������������
		}
		
		return bRet;
	}
	
	//! ��ȡд�߳���, �� CLockRW ���캯��ʹ��, ������ֱ�ӵ���
	/*!
		\param nMaxWait ��ȡ���ĵȴ�����ʱ�䣬����
		\return �Ƿ�ִ�гɹ�
	*/
	bool _AcquireWriterLock(DWORD nMaxWait = 15000)
	{
		bool bRet = Wait(hWriteWaiting, nMaxWait);

		if (bRet)										// �������ȴ�д
		{
			bRet = Wait(hDataLock, nMaxWait);			// ��ֹ������д
			if (bRet)
			{
				InterlockedIncrement(&nWriterSeqNum);	// ��ȡд��ʱ�������к�
			}
			::ReleaseSemaphore(hWriteWaiting, 1, NULL);
		}

		return bRet;
	}
	
	//! �ͷ�д�߳���, �� CLockRW ʹ��, ������ֱ�ӵ���
	/*!
		\param bCancelWriterSeq �Ƿ�ȡ�����кŵ����ӣ�_AcquireWriterLock���Զ��������к�
		\return �Ƿ�ִ�гɹ�
	*/
	bool _ReleaseWriterLock(bool bCancelWriterSeq = false)
	{
		bool bRet;
		LONG lPrevCount;
		
		if (bCancelWriterSeq)
		{
			InterlockedDecrement(&nWriterSeqNum);		// ȡ�����кŵ�����
		}
		bRet = ::ReleaseSemaphore(hDataLock, 1, &lPrevCount);	// �����д
#ifdef TRACE0
		if (0 != lPrevCount)
		{
			TRACE0("ReleasingWriteLock - Semaphore was not locked!\n");
		}
#endif
		
		return bRet;
	}

	//! �����߳�������Ϊд�߳�����ʧ��ʱ���ͷŶ��߳���
	/*! �������� CLockRW ��ͬ������ʹ��, ������ֱ�ӵ���
		\param nMaxWait ��ȡд���ĵȴ�����ʱ�䣬����
		\return �Ƿ�ִ�гɹ�
	*/
	bool _UpgradeToWriterLock(DWORD nMaxWait = 15000)
	{
		bool bRet = Wait(hWriteWaiting, nMaxWait);		// ��ֹ�µĶ�д

		_ReleaseReaderLock();							// �ͷŶ��߳���

		if (bRet)										// �ѽ�ֹ�µĶ�д
		{
			bRet = Wait(hDataLock, nMaxWait);			// ��ȡд�߳���
			if (bRet)
			{
				InterlockedIncrement(&nWriterSeqNum);	// ��ȡд��ʱ�������к�
			}
			::ReleaseSemaphore(hWriteWaiting, 1, NULL);
		}

		return bRet;
	}

	//! ���̵߳���״̬��ԭΪ���� _UpgradeToWriterLock ǰ��״̬��ʧ��ʱδ�ͷ���
	/*! �������� CLockRW ��ͬ������ʹ��, ������ֱ�ӵ���
		\param nMaxWait ��ȡ�����ĵȴ�����ʱ�䣬����
		\return �Ƿ�ִ�гɹ�
	*/
	bool _DowngradeFromWriterLock(DWORD nMaxWait = 15000)
	{
		bool bRet;

		bRet = Wait(hMutex, nMaxWait);					// ����������������
		if (bRet)
		{
			VERIFY(1 == InterlockedIncrement(&nReadCount));	// ���Ӷ�����
			::ReleaseMutex(hMutex);						// �������������
		}

		return bRet;
	}
	
	//! ָʾ��ǰ�߳��Ƿ���ж��߳���
	bool IsReaderLockHeld() const
	{
		return (nReadCount > 0);
	}
	
	//! ָʾ��ǰ�߳��Ƿ����д�߳���
	bool IsWriterLockHeld() const
	{
		DWORD dwResult;
		
		// ��һ�������������ڵȴ�������������������д
		if (nReadCount > 1)
		{
			return false;
		}
		
		dwResult = ::WaitForSingleObject(hDataLock, 0);	// ������д
		if (WAIT_TIMEOUT == dwResult)					// ��û�ж���д����
		{
			return true;
		}
		
		dwResult = ReleaseSemaphore(hDataLock, 1, NULL);	// ��ԭ
#ifdef TRACE0
		if (0 == dwResult)									// ʧ��
		{
			TRACE0("IsWriterLockHeld - ReleaseSemaphore failed\n");
		}
#endif
		return false;
	}

	//! �õ���ǰд���к�
	LONG GetWriterSeqNum() const
	{
		return nWriterSeqNum;
	}

	//! ָʾ��ȡ���к�֮���Ƿ��ѽ�д�߳�������ĳ���߳�
	/*!
		\param nSecNum �ϴλ����ʱ��GetWriterSeqNum()ȡ�����к�
		\return �Ƿ��ѱ�����д�߳����������к�
	*/
	bool AnyWritersSince(LONG nSecNum) const
	{
		return nWriterSeqNum > nSecNum;
	}
	
	//! �ȴ����������������ź���
	/*!
		\param hObject ͬ�������������������ź���
		\param nMaxWait �����ĵȴ�����ʱ�䣬����
		\return �Ƿ�ִ�гɹ�
	*/
	static bool Wait(HANDLE hObject, DWORD nMaxWait = 5000)
	{
		DWORD dwResult = ::WaitForSingleObject(hObject, nMaxWait);
#ifdef TRACE0
		if (WAIT_OBJECT_0 != dwResult)
		{
			TRACE0("Wait - forgot to call release?\n");
		}
#endif
		
		return (WAIT_OBJECT_0 == dwResult);
	}

private:
	HANDLE	hMutex;			// �����������ڻ�����¶�����
	HANDLE	hDataLock;		// ��ֵ�ź���������дʱ���ܶ�����д����ʱ����д
	LONG	nReadCount;		// ��������д����ʱ����Ϊ0��1
	HANDLE	hWriteWaiting;	// ��ֵ�ź����������������ȴ�д
	LONG	nWriterSeqNum;	// ��ǰд���к�
};

//! ��д���࣬������Ͷ�ռд������������
/*!
	ʹ�ñ����ں����ж���ֲ������������������÷�Χ���Զ�����
	\ingroup _GROUP_UTILFUNC
*/
class CLockRW
{
public:
	//! ���캯�����Զ���ȡ�߳���
	/*!
		\param data �߳����������
		\param bWriter true: ��ռд, false: �����
		\param nMaxWait ��ȡ���ĵȴ�����ʱ�䣬���룬Ϊ 0 ʱȡĬ��ֵ
	*/
	CLockRW(CReaderWriterLock& data, bool bWriter, DWORD nMaxWait = 0)
		: m_pData(NULL), m_bWriter(bWriter), m_bCancelWriterSeq(false)
	{
		if (data.IsInited())
		{
			if (0 == nMaxWait)
			{
				if (bWriter && data._AcquireWriterLock()
					|| !bWriter && data._AcquireReaderLock())
				{
					m_pData = &data;
				}
			}
			else
			{
				if (bWriter && data._AcquireWriterLock(nMaxWait)
					|| !bWriter && data._AcquireReaderLock(nMaxWait))
				{
					m_pData = &data;
				}
			}
		}
	}

	//! �����������Զ��ͷ��߳���
	~CLockRW()
	{
		Unlock();
	}

	//! �ͷ��߳���
	void Unlock()
	{
		if (m_pData != NULL)
		{
			if (m_bWriter)
			{
				m_pData->_ReleaseWriterLock(m_bCancelWriterSeq);
			}
			else
			{
				m_pData->_ReleaseReaderLock();
			}
			m_pData = NULL;
		}
	}

	//! �����Ƿ��ѻ�ȡ�߳���
	bool IsLocked() const
	{
		return (m_pData != NULL);
	}

	//! �����߳����������
	CReaderWriterLock* GetData()
	{
		return m_pData;
	}

	//! �ͷ�д��ʱȡ��д���кŵ�����
	void CancelWriterSeq()
	{
		m_bCancelWriterSeq = true;
	}

	//! �����߳�������Ϊд�߳�����ʧ��ʱ���ͷŶ��߳���
	/*!
		\param nMaxWait ��ȡд���ĵȴ�����ʱ�䣬����
		\return �Ƿ�ִ�гɹ�
	*/
	bool UpgradeToWriterLock(DWORD nMaxWait = 15000)
	{
		ASSERT(m_pData != NULL);

		bool bRet = m_bWriter;

		if (!m_bWriter)
		{
			bRet = m_pData && m_pData->_UpgradeToWriterLock(nMaxWait);
			if (bRet)
			{
				m_bWriter = true;
			}
			else
			{
				m_pData = NULL;
			}
		}

		return bRet;
	}

	//! ���̵߳���״̬��ԭΪ���� _UpgradeToWriterLock ǰ��״̬��ʧ��ʱδ�ͷ���
	/*!
		\param nMaxWait ��ȡ�����ĵȴ�����ʱ�䣬����
		\return �Ƿ�ִ�гɹ�
	*/
	bool DowngradeFromWriterLock(DWORD nMaxWait = 15000)
	{
		ASSERT(m_pData != NULL);

		bool bRet = !m_bWriter;

		if (m_bWriter)
		{
			bRet = m_pData && m_pData->_DowngradeFromWriterLock(nMaxWait);
			if (bRet)
			{
				m_bWriter = false;
			}
		}

		return bRet;
	}

private:
	CReaderWriterLock*	m_pData;
	bool				m_bWriter;
	bool				m_bCancelWriterSeq;
};

#endif // UTILFUNC_LOCKSYN_H_
