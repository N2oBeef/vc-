#pragma once

#include <map>
using namespace std;

typedef void (*delayFunc_CB)(PVOID param, UINT idEvent);

//!��ʱ���ص�����
VOID _stdcall DelayTimerFunc( HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime );

struct DelayParam
{
	delayFunc_CB delayCb;
	PVOID param;
	BOOL bLoop;
};

class CDelayCall
{
protected: 
	virtual ~CDelayCall(){}
	
public:
	static CDelayCall* GetInstance()
	{
		static CDelayCall instance;
		return &instance;
	}

	typedef map<UINT, DelayParam>	DelayParamMap;
	typedef map<UINT, DelayParam>::iterator DelayParamIterator;

	//!������ʱ���ܣ��� mseconds �����ִ�к���fun
	virtual UINT Start( int mseconds , delayFunc_CB func, PVOID param = NULL, BOOL bLoop = TRUE);

	//!ֹͣ��ʱ����
	virtual void Stop(UINT &idEvent);


	DelayParamMap m_mapFunc;
	
};

