#pragma once

#include "IList.h"

#include <boost/function.hpp>
#include "Engine/IEngine.h"

class IItem;
typedef boost::function<void(void)> OnDownloadingCallback;

class IItem
	: public Engine::IFixCallback
{
public:
	virtual ~IItem(){}
	
	template <typename T>
	void Init(T param){};

	// ��ȡ�б���һ��item������panel
	virtual Ipanel_sitePtr STDMETHODCALLTYPE GetItemPanel(void) PURE;

	// �������
	virtual void STDMETHODCALLTYPE InsertChild(size_t nIndex, ItemPtr spChildItem)PURE;

	// �Ƴ�����
	virtual void STDMETHODCALLTYPE RemoveChild(ItemPtr spItem) PURE;

	// ��ȡ������� 
	virtual size_t  STDMETHODCALLTYPE GetChildCount(void) PURE;

	// ����������ȡ����
	virtual ItemPtr STDMETHODCALLTYPE GetChild(size_t nIdx) PURE;

	// ����id��������
	virtual ItemPtr STDMETHODCALLTYPE GetChildItem(int nID) PURE;

	// ��ȡ���id
	virtual int STDMETHODCALLTYPE GetID(void) = 0;
	virtual void STDMETHODCALLTYPE SetID(int nID) = 0;

    //����/��ȡ����
    virtual void STDMETHODCALLTYPE SetParentItem(WeakItemPtr spWeakParent) = 0;
    virtual WeakItemPtr  STDMETHODCALLTYPE GetParentItem() = 0;

	virtual void STDMETHODCALLTYPE SetIDS(const CString & szIDS) PURE;
	virtual const CString & STDMETHODCALLTYPE GetIDS(void) PURE;

	virtual Engine::IItem * STDMETHODCALLTYPE GetEngineItem(void) PURE;

	virtual void STDMETHODCALLTYPE Enable(BOOL bEnable) PURE; 
};
