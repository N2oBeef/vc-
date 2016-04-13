#ifndef __X_DATA_DEFINE_WINDOWS_
#define __X_DATA_DEFINE_WINDOWS_

//
// Windows Version Build Option
//

#ifndef WINVER                      // ����ʹ�� Windows 95 �� Windows NT 4 ����߰汾���ض����ܡ�

	#ifdef _MSC_VER
		#if ( _MSC_VER > 1200 )
		#define WINVER 0x0500   //Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
		#endif
	#endif

#endif	// WINVER

#ifndef _WIN32_WINNT                // ����ʹ�� Windows NT 4 ����߰汾���ض����ܡ�
	#define _WIN32_WINNT 0x0500     //Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif						

#ifndef _WIN32_WINDOWS              // ����ʹ�� Windows 98 ����߰汾���ض����ܡ�
	#define _WIN32_WINDOWS 0x0500   //Ϊ Windows Me �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_IE                   // ����ʹ�� IE 4.0 ����߰汾���ض����ܡ�
	#define _WIN32_IE 0x0500        //Ϊ IE 5.0 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif


// ����Ҫ�Ȱ���winsock2

#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <tchar.h>
#include <mmsystem.h>


// sockets
typedef int socklen_t;

//#include <atlstr.h>
//using   ATL::CString;

#pragma warning(disable:4214)   // bit field types other than int
#pragma warning(disable:4201)   // nameless struct/union
#pragma warning(disable:4127)   // condition expression is constant
#pragma warning(disable:4115)   // named type definition in parentheses
#pragma warning(disable:4996)
#pragma warning(disable:4244)   // �ӡ�P2PHANDLE��ת������uint32�������ܶ�ʧ����
#pragma warning(disable:4311)
#pragma warning(disable:4267)	// �ӡ�size_t��ת������int�������ܶ�ʧ����



#endif	// __X_DATA_DEFINE_WINDOWS_ 
