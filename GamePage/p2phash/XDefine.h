#ifndef __X_DATA_DEFINE__
#define __X_DATA_DEFINE__

// ͨ�õ�ͷ����ǰ�棬�����������Ͷ��壬��Ȼ����deque�����г�ͻ

// linux��֧�ִ��ļ���д
#ifndef WIN32 
	#define _LARGEFILE64_SOURCE
	#define _FILE_OFFSET_BITS 64
#endif

// timeʹ��32bit����linux����һ��
#define _USE_32BIT_TIME_T
#include <time.h>

#include <assert.h>
#include <stdio.h>

#include <list>
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <algorithm>




#ifdef WIN32 

	#include "XDefine_windows.h"

#else

	#include "XDefine_linux.h"
	
#endif // WIN32


// ��ƽ̨�������Ͷ���
//
// type defined
//
typedef unsigned long long	U64;
typedef unsigned int	U32;
typedef unsigned short	U16;
typedef unsigned char		U8;


typedef unsigned char		uchar;
typedef unsigned char		uint8;
typedef	  signed char		sint8;

typedef unsigned short		uint16;
typedef	  signed short		sint16;

typedef unsigned int		uint32;
typedef	  signed int		sint32;

typedef unsigned long long	uint64;
typedef   signed long long	sint64;


// ���ָ����0�����ǷǷ���ַ�򷵻�false��ͬʱdebug��������
// ����debug�棬�����ڸǴ���
BOOL IS_BAD_READ_PTR(const VOID* ReadPtr, UINT_PTR ucb, IN TCHAR* FileName,IN DWORD LineNumber);

#ifdef _UNICODE
	#define BAD_READ_PTR(ReadPtr, ucb) IS_BAD_READ_PTR(ReadPtr, ucb, _CRT_WIDE(__FILE__), __LINE__)
#else
	#define BAD_READ_PTR(ReadPtr, ucb) IS_BAD_READ_PTR(ReadPtr, ucb, (__FILE__), __LINE__)
#endif




#define P2P_ASSERT assert

#ifndef ASSERT
	#define ASSERT assert
#endif

#endif
