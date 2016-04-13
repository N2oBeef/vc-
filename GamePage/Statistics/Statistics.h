#pragma once

#include "../Base/SingletonT.h"
#include <boost/function.hpp>
#include "../Net/IHttpTask.h"

typedef boost::function<void(BOOL)> StatUrlSendStateCallback;

class CStatistic
    : public CSingletonT<CStatistic>
    , public IHttpTaskCallback
    
{
    SINGLETON(CStatistic);

private:
    CStatistic();

public:
    // ����һ��ͳ��URL
    STDMETHOD_(BOOL, SendStatUrlEx)(LPCWSTR lpszType, LPCWSTR lpszAction, LPCWSTR lpszExtra = NULL, BOOL bUseThread = TRUE, StatUrlSendStateCallback stateCallback = NULL);
    // ���ʹ�У���ͳ��URL
    STDMETHOD_(BOOL, SendStatUrlExWithSigned)(LPCWSTR lpszType, LPCWSTR lpszAction, BOOL bUseThread = TRUE, StatUrlSendStateCallback stateCallback = NULL);
    // ����һ��ͳ��URL
    STDMETHOD_(BOOL, SendStatUrl)(LPCWSTR lpszUrl, BOOL bUseThread = TRUE, StatUrlSendStateCallback stateCallback = NULL);

protected:
    // ����һ���ļ�
    STDMETHOD_(BOOL, DownloadFile)(
        LPCWSTR lpszUrl, 
        LPCWSTR lpszLocalFile, 
        BOOL bUseMultiThread, 
        WPARAM wParam,
        StatUrlSendStateCallback stateCallback);

    // ����汾��ʽΪ��%d.%d.%d.%d
    STDMETHOD_(BOOL, GetFileVer)(LPWSTR lpFileFullPath, LPWSTR lpVer, int nVerlen);

    // ��ȡMID
    STDMETHOD_(BOOL, GetMID)(
        LPWSTR lpszBuffer, int nMaxCharCount /* ע�⣬���ǻ��������ȣ������ַ����� */);

    CString GetPID();

public:
    // �Ƿ������������
    STDMETHOD_(BOOL, HaveInternetConnection)(void);

    // �Ƿ��������
    STDMETHOD_(BOOL, IsNetGatewayExists)(void);

private:
    // static 
    static unsigned int WINAPI DownloadThreadProc(LPVOID lpParam);

    void _stdcall OnHttpStatus(IHttpTask *pTask, HTTP_INFO &inf);

private:
    void ReplacePlaceholders(CString & szUrl, const CString & szType, const CString & szAction);

    // ����һ���ļ�
    BOOL InternalDownloadFile(LPCWSTR lpszUrl, LPCWSTR lpszLocalFile, StatUrlSendStateCallback stateCallback);

private:
    CString m_szPID;
    CString m_szMID;
    CString m_szAppVer;
    CString m_szModVer;
};

