#ifndef __X_FILE__
#define __X_FILE__

#include <vector>

//#include "XEvent.h"
// ��ƽ̨�ļ�Ŀ¼����

namespace XFile
{
	// ��д�ļ���ƫ�����Ǵ��ļ�ͷ��ʼ. ����ʵ�ʶ�д���ֽ�����
	int file_read(CString strFilename, __int64 nMoveOffset, void *pBuf, int nToRead);
	int file_write(CString strFilename, __int64 nMoveOffset, bool bCreate, void *pBuf, int nToWrite, bool bFlush);
	
	// �ı���ʽ
	CStringA file_read_text(CString strFilename);
	int file_read_text_lines(CString strFilename, std::vector<CStringA> &list_line);
	
	// �ļ�����
	// ʧ��Ҳ�᷵��0��ע�ⲻ��������������ж��ļ��Ƿ���ڡ�
	__int64  file_get_size(CString strFilename);

#ifdef WIN32
	enum SET_SIZE_ERROR_CODE
	{
		SETSIZE_OK = 0,			// �ɹ�
		SETSIZE_ERROR_DISK_FULL = ERROR_DISK_FULL,	// ������
		SETSIZE_ERROR_INVALID_NAME = ERROR_INVALID_NAME,	// �Ƿ��ļ���
		SETSIZE_ERROR_PATH_NOT_FOUND = ERROR_PATH_NOT_FOUND,	// �Ƿ�·����
		SETSIZE_ERROR_SHARING_VIOLATION = ERROR_SHARING_VIOLATION,	// �ļ����ڱ�ʹ��
		SETSIZE_ERROR_LOCK_VIOLATION = ERROR_LOCK_VIOLATION,	// �ļ����ڱ�ʹ��
		SETSIZE_ERROR_ACCESS_DENIED = ERROR_ACCESS_DENIED,	// �޷�д������
		SETSIZE_ERROR_USER_CANCEL = -1234,			// �û�ȡ��

	};
#else

	// LINUX ����
	enum SET_SIZE_ERROR_CODE
	{
		SETSIZE_OK = 0,			// �ɹ�
		SETSIZE_ERROR_DISK_FULL = 1,	// ������
		SETSIZE_ERROR_INVALID_NAME = 2,	// �Ƿ��ļ���
		SETSIZE_ERROR_PATH_NOT_FOUND = 3,	// �Ƿ�·����
		SETSIZE_ERROR_SHARING_VIOLATION = 4,	// �ļ����ڱ�ʹ��
		SETSIZE_ERROR_LOCK_VIOLATION = 5,	// �ļ����ڱ�ʹ��
		SETSIZE_ERROR_ACCESS_DENIED = 6,	// �޷�д������
		SETSIZE_ERROR_USER_CANCEL = -1234,			// �û�ȡ��
	};

#endif
	// ����enum SET_SIZE_ERROR_CODE�Ĵ�����
	// ����ļ������ڣ����������ɣ�
	// ����ļ����ڣ������ԭ�еĴ�С������дԭ�ļ����е�����
	// hStopEvent ������ṩ��ֹͣ�¼�������ΪNULL
	// pfHashPercent ������ṩ�Ľ�����Ϣ������ΪNULL
	//int file_set_size(CString strFilename, __int64 nSize, XEVENT_HANDLE hStopEvent, float *pfHashPercent);



	bool file_exist(CString strFilename);
	bool file_delete(CString strFilename);
	bool file_copy(CString strFrom, CString strTo);
	// ���ش����룬0��ʾ�ɹ�
	int  file_move(CString strFrom, CString strTo);


	// ��ȡ�ļ����ԣ���С������޸�ʱ�䡣windows��ʱ��ʵ��ΪFILETIME, linux���� time_t
	bool file_get_attrib(CString strFilename, __int64 &file_size, __int64 &last_write);

	// ��ȡ�ļ�ʱ����ַ�����win���� FILETIME��linux����time_t
	// ������ʷԭ��p2p�����б��õ��� FILETIME������û���޸ġ�
	CStringA file_time_string(__int64 nFiletime);

	// �����ļ�����޸�ʱ�䡣win��linux�¶���time_t
	bool file_set_last_modify(CString strFilename, time_t nFiletime);
	
	// Ŀ¼����
	bool dir_create(CString strDir, BOOL bNeedRecursive);

	// Ŀ¼���滯�����ݲ���ϵͳ�����ĩβ���� \ / ����� \ / �ȴ���
	bool dir_normalize(CString &strDir);

	bool dir_exist(CString strDir);

	// ·���ϲ�
	// ��Ϊlinux��windows��Ŀ¼б���ǲ�ͬ�ģ�����Ҫ���������ͨ�û�����
	// ��� strFilename �Ѿ���ȫ·������ֱ��ʹ�� strFilename ��Ϊ���
	CString dir_make_path (CString strBaseDir, CString strFilename);

	//ɾ���ļ��У��������ļ��У�
	bool dir_delete(CString strDir);
	
};


// ����ʱ���Զ�����Close�������Զ�����Flush()

#if ( defined(WIN32) || defined(WIN64) )
	typedef HANDLE		XFILEHANDLE;
#else
	typedef int			XFILEHANDLE;
#endif





// ��ǰ����ֻ࣬������д��־��
// ��Ϊ��ģʽ������ģʽ�кܶ࣬����д���鷳�������ö��Ƶġ�
class XFileEx
{
public:
	XFileEx() { m_file = 0; } ;
	~XFileEx(){ Close(); };

	// ע��bUnicodeText ֻ�����ļ��ǿյ������д��unicode�ļ�ͷ
	// �����뱣֤ bUnicodeText �� Write д�����ݵ�һ����
	bool OpenLog(CString strFilename, BOOL bAppend, BOOL bAutoFlush, BOOL bUnicodeText);

	bool OpenRead(CString strFilename);
	bool OpenReadWrite(CString strFilename);

	bool Seek(__int64 pos);

	// ����ʵ�ʶ������ֽ��������ܱ� nBytes ҪС��
	int Read(void *buf, int nBytes);

	int Write(const void *buf, int nBytes);

	void Flush();
	void Close();

	bool IsValid();

private:

	XFILEHANDLE m_file;
};


#endif	// __X_FILE__



