// ͨ��HTTP�ϴ����ط�װ
//
// ֧�����ԣ�HTTP/HTTPS�����ύ�ϴ���Cookies���Զ���HTTPͷ��������֤�����뱣�棬
//           �����쳣�����ض������ԣ����ļ���С�����أ��������������־��
//           ֧��vc9/vc6


#pragma once
#include <vector>
#include <windows.h>
#include <cassert>

#define ASSERT(expr) assert(expr)


enum HttpStatus
{
	eHttpWait		= 0,			// �Ŷӻ�δ��ʼ��״̬
	eHttpRunning	= 1,			// ��������
	eHttpSuccess	= 2,			// �ɹ�
	eHttpFail		= 3,			// ʧ��
};

enum HttpMethod
{
	eHttpGet		= 0,			// GET
	eHttpPostSimple	= 1,			// POST ������ -- form-urlencoded
	eHttpPost		= 2,			// POST ������ -- multipart/form-data
	eHttpPostRaw	= 3,			// POST ԭʼ���� -- octet-stream
};
struct HTTP_INFO
{
	HTTP_INFO()
	{
		memset(this, 0, sizeof(HTTP_INFO));
	}
	
	DWORD		nID;				// ������id
	HttpStatus 	nStatus;			// ״̬

	DWORD		dwHttpCode;			// HTTP ״̬�룬������
	DWORD		dwErrCode;			// ������

	const char	*pHttpData;			// ���ص��ڴ�ģʽ�����ݣ�֧�ֶ����ƣ�β����\0��������ַ������������\0������dwHttpDataLen��
	const wchar_t*pHttpFile;		// ���ص��ļ�ģʽ���ļ�·��
	DWORD		dwHttpDataLen;		// �յ������ݴ�С
	BOOL		bDataCompress;		// �յ��������Ƿ���ѹ���ĸ�ʽ(gzip)

	const char *pHeaderSend;		// ԭʼ����ͷ��������
	const char *pHeaderRecv;		// ԭʼ��Ӧͷ��������

	DWORD		dwTime;				// ����ʱ��, ����
	DWORD		dwAvgSpeed;			// ƽ���ٶ� KB/s
	char		ip[64];				// ���ӵ�ip


	const char *szUrl;				// ����Ĳ�����������
	HttpMethod	nMethod;

	DWORD		dwHttpDataCntLen;	// �յ����ݵ�Ԥ�ڴ�С(����content-length)
	DWORD		dwProgress;			// ����(0~100)
	DWORD		dwCurSpeed;			// ˲ʱ�ٶ� KB/s


	char		reserved[1024];
};

// �ص���ע��ص������Ǵ��ڲ������߳��ڻص��ģ�����뿼���߳�ͬ��������
// ��ʹ�ûص�Ҳ���ԣ��������߲�ѯģʽ
class IHttpTask;

class IHttpTaskCallback
{
public:
	// ״̬�ص�
	virtual void _stdcall OnHttpStatus(IHttpTask *pTask, HTTP_INFO &inf) = 0;
};

#define IHTTP_ERR_USER_CANCEL	50001			// �û�ȡ�� -- �޽��֮ǰ����ɾ���������޻ص��ˣ�
#define IHTTP_ERR_TIMEOUT		50002			// ��ʱ

class IHttpTask
{
public:
	// ���ûص�ָ�롣���ô˺�����ʾ���ص�������NULLҲ��ȡ���ص�
	virtual void SetCallback(IHttpTaskCallback *pCallback) = 0;

	// ��ʼִ�����󣨷���������ע����������ͷ�Ȳ���Ӧ���ڵ��ñ�����ǰ�����ꡣ
	virtual BOOL Start(HttpMethod nMethod, const char *szUrl) = 0;
	virtual BOOL Start(HttpMethod nMethod, const wchar_t *szUrl) = 0;

	// ��ͣ��ɾ�����񣨷���������ɾ������󣬲�Ҫ���ô�ָ�롣
	virtual BOOL Release() = 0;
	
	// ����Զ���HTTPͷ��Ĭ��User-Agent��IE7
	// AddHeader("Cookie", "GP=1; FG=1; USERID=77992fd2f44dfb5701d6286e; LPA=2");
	// AddHeader("User-Agent", "uploader/1.1");
	// AddHeader("Referer", "http://www.360.cn/")
	virtual BOOL AddHeader(const wchar_t *szName, const wchar_t *szValue) = 0;
	virtual BOOL AddHeader(const char *szName, const char *szValue) = 0;

	// POST �ύʱ�������ַ����ֶ�
	virtual BOOL PostStr(const wchar_t *szName, const wchar_t *szValue) = 0;
	virtual BOOL PostStr(const char *szName, const char *szValue) = 0;
	
	// POST �ύʱ�����Ӷ������ֶ�
	// szFilename Ϊ��ѡ�ֶΣ���Ϊ����Ϊ���ֶ����� filename ����
	// szContentType Ϊ��ѡ�ֶΣ���Ϊ����Ϊ���ֶ����� Content-Type ����
	virtual BOOL PostBin(const char *szName, const BYTE *pData, DWORD dwDataLen, const char *szFilename, const char *szContentType) = 0;
	virtual BOOL PostBin(const wchar_t *szName, const BYTE *pData, DWORD dwDataLen, const wchar_t *szFilename, const wchar_t *szContentType) = 0;

	// ֧�����ص��ļ����������س����ļ��Ĳ�Ʒ���ã���������˴˲�����pHttpData���ǿյ�
	virtual void SetFilename(const wchar_t *lpszFilename) = 0;

	// ���ò�����������ʶ��Ĳ���������TRUE
	// SetParam("timeout", 15); // ���ó�ʱ����ʱ��ָ�����ݽ�������������������ִ��ʱ��. Ĭ��30��
	// SetParam("retry", 2);	// ����ʧ���Զ����ԡ�Ĭ�ϲ����ԡ�ֻ��������ϲŲ���callback
	// SetParam("zlib", 1);		// �����������postʱ����������zlib��compress2()ѹ��
	virtual BOOL SetParam(const char *szName, DWORD dwValue) = 0;
	virtual BOOL SetParam(const char *szName, const char *szValue) = 0;
	
	// ��ȡ״̬������ûص�ģʽ����������ô˺���������ı�����callback�Ĳ�����
	virtual BOOL GetStatus(HTTP_INFO &st) = 0;	

	// ��ȡһ����Ӧͷ������ж��еı���Set-Cookie��dwIndex��0��ʼ����ֱ������FALSE��ʾû����
	virtual BOOL GetRespHeader(const char *szName, char *szValue, DWORD &sizeInChars, DWORD dwIndex) = 0;
	virtual BOOL GetRespHeader(const wchar_t *szName, wchar_t *szValue, DWORD &sizeInChars, DWORD dwIndex) = 0;

	// ��ȡ������ID�����������������õ�ID������ͬһ��IHttpTaskManager�ڵ�����ID�����Ψһ�ģ���1��ʼ
	virtual DWORD GetID() = 0;
};

class IHttpTaskManager
{
public:
	virtual IHttpTask* CreateTask() = 0;

	// ����ѡ�������ʶ����ֶΣ�����TRUE
	// SetParam("speed_limit_up", 100);			// �ϴ����٣���λKB/s��Ĭ��0��ʾ���ޡ�ֻ�Ա���������Ч��
	// SetParam("speed_limit_down", 100);		// �������٣���λKB/s��Ĭ��0��ʾ���ޡ�
	virtual BOOL SetParam(const char *szName, DWORD dwValue) = 0;
	virtual BOOL SetParam(const char *szName, const char *szValue) = 0;

	// ��ȡ״̬��������ʶ����ֶΣ�����TRUE
	// GetParam("speed_up", dwValue);			// ��ȡ��ǰ���ϴ��ٶȡ�ָһ�������������ٶ�
	// GetParam("speed_down", dwValue);			// ��ȡ��ǰ�������ٶ�
	virtual BOOL GetParam(const char *szName, DWORD *dwValue) = 0;
	virtual BOOL GetParam(const char *szName, const char *szValue, int nValueLen) = 0;
};

// ��ʼ��ģ��
extern "C"  IHttpTaskManager* __stdcall HttpInit();
typedef IHttpTaskManager* ( __stdcall *pFUNC_HttpInit )();

// ����ʼ��ģ��
extern "C"  BOOL __stdcall HttpUninit(IHttpTaskManager* pMgr);
typedef BOOL ( __stdcall *pFUNC_HttpUninit )(IHttpTaskManager* pMgr);

// ����zlib�����ӿڣ����������뷵��ֵ��zlibһ�¡�Ψһ������compress�������ѹ����
extern "C"  int __stdcall zlib_uncompress (BYTE *dest, unsigned long *destLen, const BYTE *source, unsigned long sourceLen);
typedef int ( __stdcall *pFUNC_zlib_uncompress )(BYTE *dest, unsigned long *destLen, const BYTE *source, unsigned long sourceLen);

extern "C"  int __stdcall zlib_compress (BYTE *dest, unsigned long *destLen, const BYTE *source, unsigned long sourceLen);
typedef int ( __stdcall *pFUNC_zlib_compress )(BYTE *dest, unsigned long *destLen, const BYTE *source, unsigned long sourceLen);

extern "C"  unsigned long __stdcall zlib_compressBound (unsigned long sourceLen);
typedef unsigned long ( __stdcall *pFUNC_zlib_compressBound )(unsigned long sourceLen);

// ��������ڷ���ĵ���
class CHttpTaskWrapper
{
public:
	CHttpTaskWrapper()
	{
		m_hMoudle	= NULL;
		m_HttpInit = NULL;
		m_HttpUninit = NULL;
		m_pTaskManager = 0;
	}
	~CHttpTaskWrapper()
	{
		UnInit();
	}

	IHttpTask* CreateTask()
	{
		if(m_pTaskManager)
        {
            IHttpTask* pTask = m_pTaskManager->CreateTask();
            if (pTask)
            {
                DWORD dwValue = 0;
                pTask->SetParam("ungzip", dwValue);
                pTask->SetParam("gzip", dwValue);            // �����ϴ�ģ�飬����PostBin�Ķ��������ݣ������緢��ʱ��ѹ��
            }
            return pTask;
        }
		else
			return NULL;
	}

	BOOL   Init(LPCTSTR dllName)
	{
		if (m_hMoudle == 0)
		{
			m_hMoudle = LoadLibrary(dllName); //_SIGN_OK_
			if (m_hMoudle == NULL)
			{
				return FALSE;
			}

			m_HttpInit = (pFUNC_HttpInit)GetProcAddress(m_hMoudle,"HttpInit");
			m_HttpUninit = (pFUNC_HttpUninit)GetProcAddress(m_hMoudle,"HttpUninit");
			m_zlib_uncompress = (pFUNC_zlib_uncompress)GetProcAddress(m_hMoudle,"zlib_uncompress");
			m_zlib_compress = (pFUNC_zlib_compress)GetProcAddress(m_hMoudle,"zlib_compress");
			m_zlib_compressBound = (pFUNC_zlib_compressBound)GetProcAddress(m_hMoudle,"zlib_compressBound");

			// �ڲ���ʼ��
			if(m_HttpInit)
				m_pTaskManager = m_HttpInit();
		}

		return (m_HttpUninit && m_HttpInit && m_pTaskManager);
	}
	BOOL	UnInit()
	{
		// �ڲ�����ʼ��
		if(m_HttpUninit)
			m_HttpUninit(m_pTaskManager);

		if (m_hMoudle)
		{
			m_HttpInit = NULL;
			m_HttpUninit = NULL;
			m_zlib_uncompress = NULL;

			// �����ü���ȥ�����ͷ�dll
			FreeLibrary(m_hMoudle);
			m_hMoudle = NULL;
		}

		return TRUE;
	}

	// ��zlib��ѹ�����򵥷�װ
	int UnCompressZlib(const BYTE *source, unsigned long nSourceLen, std::vector<BYTE>& vecDest)
	{
#define Z_OK            0
#define Z_BUF_ERROR    (-5)

		ASSERT(nSourceLen > 0);
		if (nSourceLen <= 0)
		{
			return -1;
		}
		int nRet = -1;
		for (unsigned long nDestLen = nSourceLen * 2; ; nDestLen = nDestLen * 2)
		{
			vecDest.resize(nDestLen);
			nRet = zlib_uncompress(&vecDest[0], &nDestLen, source, nSourceLen);
			if (nRet != Z_BUF_ERROR)
			{
				break;
			}
		}
		return nRet;
	}

	int zlib_uncompress(BYTE *dest, unsigned long *destLen, const BYTE *source, unsigned long sourceLen)
	{
		if(m_zlib_uncompress)
			return m_zlib_uncompress(dest, destLen, source, sourceLen);
		else
			return -1;
	}

	int zlib_compress(BYTE *dest, unsigned long *destLen, const BYTE *source, unsigned long sourceLen)
	{
		if(m_zlib_compress)
			return m_zlib_compress(dest, destLen, source, sourceLen);
		else
			return -1;
	}

	unsigned long zlib_compressBound(unsigned long sourceLen)
	{
		if(m_zlib_compressBound)
			return m_zlib_compressBound(sourceLen);
		else
			return 0;
	}

private:
	HMODULE					m_hMoudle;
	pFUNC_HttpInit			m_HttpInit;
	pFUNC_HttpUninit		m_HttpUninit;
	IHttpTaskManager*		m_pTaskManager;
	pFUNC_zlib_uncompress	m_zlib_uncompress;
	pFUNC_zlib_compress		m_zlib_compress;
	pFUNC_zlib_compressBound	m_zlib_compressBound;
};
