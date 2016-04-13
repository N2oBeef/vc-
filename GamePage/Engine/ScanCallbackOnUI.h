#pragma once

#include "IEngine.h"

namespace Engine
{
	//�������װһ���̳�IScanCallback���������麯��������ʵ�ֻص������̳�IScanCallback����
	class CScanCallbackOnUI
		: public IScanCallback
	{
	public:
		CScanCallbackOnUI();
		~CScanCallbackOnUI();
	
		void SetCallback(IScanCallback *pCallback)
		{
			ATLASSERT(pCallback);
			m_pScanCallback = pCallback;
		}
	public:
		virtual void __stdcall OnScanStart(void);
		virtual void __stdcall OnScanItemStart(IItem *pItem);
		virtual void __stdcall OnScanItemEnd(IItem *pItem);

		//nProgress��0-100
		virtual void __stdcall OnScanProgress(int nProgress);

		virtual void __stdcall OnScanEnd(void);

	private:
		void OnScanStartOnUI(void);
		void OnScanItemStartOnUI(IItem *pItem);
		void OnScanItemEndOnUI(IItem *pItem);

		//nProgress��0-100
		void OnScanProgressOnUI(int nProgress);

		void OnScanEndOnUI(void);

	private:
		IScanCallback *m_pScanCallback;
	};
}
