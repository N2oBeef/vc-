#pragma once

//////////////////////////////////////////////////////////////////////////
//IEngineӵ�����е�IItem������Ȩ���ⲿֻ���ã�����ɾ
//////////////////////////////////////////////////////////////////////////

namespace Engine
{
	
	class IEngine;
	class IScanCallback;
	class IFixCallback;
	class IItem;

	typedef enum _FIX_EVENT_ID
	{
		FIX_EVENT_START_INST = 1, //��ʼ��װ�����治��ȡ��
	}FIX_EVENT_ID;

    class IEngine
    {
    public:
        virtual BOOL __stdcall Init(void) = 0;

        virtual void __stdcall Uninit(void) = 0;

        virtual int  __stdcall GetItemCount(void) = 0;

        virtual  IItem * __stdcall GetItem(int nIdx) = 0;

        //ȡ��֮�󣬻�����Ҫ�ص�OnScanEnd��OnFixEnd, ��OnScanEnd��OnFixEnd�ص�֮ǰ�ظ�����Scan��Fix��Ч

        //�첽ɨ��
        virtual void __stdcall ScanAsync(IScanCallback *pScanCallback) = 0;
        virtual void __stdcall CancelScan(void) = 0;

        //�����޸�
        virtual void __stdcall FixOneAsync(IItem* pItem, IFixCallback *pFixCallback) = 0;
        //һ���޸�
        virtual void __stdcall FixAllAsync(IFixCallback *pFixCallback) = 0;

        virtual void __stdcall CancelFix(void) = 0;
    };

    class IItem
    {
    public:
        virtual void __stdcall Destroy() = 0;

        virtual void __stdcall GetName(WCHAR * pszName, int nMaxCount) = 0;

        //�Ƿ�������
        virtual BOOL __stdcall HasProblem(void) = 0; 

        //�����������ڲ�ʹ��
        virtual void __stdcall Scan(IScanCallback *pCallback) = 0;
        virtual void __stdcall CancelScan(void) = 0;

        virtual void __stdcall Fix(IFixCallback *pFixCallback) = 0;
        virtual void __stdcall CancelFix(void) = 0;
    };

	//////////////////////////////////////////////////////////////////////////
	//callback ��ӵ���Init���̻߳ص�
	class IScanCallback
	{
	public:
		virtual void __stdcall OnScanStart(void) = 0;
		virtual void __stdcall OnScanItemStart(IItem *pItem) = 0;
		virtual void __stdcall OnScanItemEnd(IItem *pItem) = 0;

		//nProgress��0-100
		virtual void __stdcall OnScanProgress(int nProgress) = 0;

		virtual void __stdcall OnScanEnd(void) = 0;
	};

	//////////////////////////////////////////////////////////////////////////
	//callback ��ӵ���Init���̻߳ص�
	class IFixCallback
	{
	public:
		virtual void __stdcall OnFixStart(void) = 0;
		
		//�����޸�ʱ��Ҳȫ���ص�
		virtual void __stdcall OnFixItemStart(IItem *pItem) = 0;
		virtual void __stdcall OnFixItemEnd(IItem *pItem, BOOL bSuccess) = 0;

		virtual void __stdcall OnFixEvent(IItem *pItem, int nEvent) = 0;

		//nProgress��0-100
		virtual void __stdcall OnFixProgress(IItem *pItem, int nProgress) = 0;

		virtual void __stdcall OnFixEnd(void) = 0;
	};
};