#pragma once

#include "IList.h"
#include "Engine/IEngine.h"

class CList
	: public IDispEventSimpleImpl</*nID =*/ 1, CList, &DIID_Isite_events> //�������ŵ�һ��������ǿת
	, public IList
{
public:
	CList();
	~CList();

	BEGIN_SINK_MAP(CList)
		SINK_ENTRY_INFO(/*nID =*/ 1, DIID_Isite_events, 1, on_event, &on_event_info)
	END_SINK_MAP()

	//////////////////////////////////////////////////////////////////////////
	//�¼���Ϣ��    
	BEGIN_SITE_MSG_MAP(CList)
		SITE_MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	END_SITE_MSG_MAP()
	//�¼���Ϣ�����
	//////////////////////////////////////////////////////////////////////////
	HRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, Isite* site )
	{
		return E_ABORT;
	}

	void Init(Irich_list_sitePtr spRichList);
	void Enable(BOOL bEnable);

public:
	STDMETHOD_(void,InsertItem)(int nIndexAfter, ItemPtr spItem);
	STDMETHOD_(void,RemoveItem)(ItemPtr spItem);
	STDMETHOD_(void,Clear)(void);
	STDMETHOD_(Irich_list_sitePtr,GetProxyList)(void);
	STDMETHOD_(ItemPtr,GetItem)(const CString & szIDS);
	STDMETHOD_(ItemPtr,GetItem)(int nId);
	STDMETHOD_(ItemPtr,GetItem)(Engine::IItem *pEngineItem);
	STDMETHOD_(size_t,GetChildCount)(void);
	STDMETHOD_(ItemPtr,GetChild)(size_t nIndex);
	STDMETHOD_(void,UpdateLayout)(void);
	STDMETHOD_(void,Repaint)(BOOL bEraseBkgnd);
	STDMETHOD_(Ipanel_sitePtr,GetTemplateItem)(void);
	
private:
	void ClearAll(void);
	void InitControls( void );

	void InitEvent( void );

private:
	Irich_list_sitePtr                  m_spRichList;       // ������б�
	Ipanel_sitePtr						m_sp1stLevelItem;          // ��һ������ģ��

	CAtlAdviser       m_atlAdviser;
	ItemConatiner     m_itemContainer;
};