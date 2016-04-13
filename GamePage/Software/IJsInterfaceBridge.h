#pragma once

//c++ call javascript interface
#include <boost/shared_ptr.hpp>

typedef enum _tagEVENT_ID
{
	EVENT_ID_LOCAL_CONFIG_READY = 1, // �������ü�����ɣ���ҳ���ýӿڻ�ȡ��װ״̬
	EVENT_ID_DOWNLOAD_START,         // ��ʼ���������szParam1Ϊ���������ids
	EVENT_ID_DOWNLOAD_END,           // ������ɣ�nCodeΪ����״̬������0���سɹ�������ʧ�ܣ�szParam1Ϊ���������ids
	EVENT_ID_DELETE,                 // ������������ɾ���ˣ�szParam1Ϊ���������ids
	EVENT_ID_REFRESH_RANK,           // �����ֵܷ�����
}EVENT_ID;

class IJsInterfaceBridge
{
public:
	virtual void OnEvent(int nEventId, int nCode, WCHAR* szParam1, WCHAR *szParam2) = 0;
	virtual void OnProgress(WCHAR * ids, LONGLONG lTotalSize, LONGLONG lDownloadSize, int nStatus) = 0;
	virtual void JsInterface(CComPtr<IDispatch> & spScript) = 0;
};

typedef boost::shared_ptr<IJsInterfaceBridge> JsInterfaceBridgePtr;