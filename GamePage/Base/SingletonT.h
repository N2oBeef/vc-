#pragma once
/********************************************************************
	created:	2012/12/07
	created:	7:12:2012   14:46
	filename: 	SingletonT.h
	file path:	FunctionModule
	file base:	SingletonT
	file ext:	h
	author:		Pan.M
	
	purpose:	�򵥵ĵ���ģʽ���࣬����������������
				������Ҫ���������������friend, SINLGETON(ChildClass)��ʵ��
				����Ҫ�����๹�캯������Ϊprivate
*********************************************************************/

template<typename T>
class CSingletonT
{
public:
	static T * GetInstance(void)
	{
		if (s_pSinglton == NULL)
		{
			s_pSinglton = new T();
		}
		return s_pSinglton;
	}

	// must to be protected
protected:
	CSingletonT(){};

	// no implementation
private:
 	CSingletonT(const T &);
 	CSingletonT & operator= (const T & );

private:
	static T * s_pSinglton;
};

template<typename T>
T * CSingletonT<T>::s_pSinglton = NULL;

// ��������������Ԫ
#define SINGLETON(DrivedSingleton) 	friend class CSingletonT<DrivedSingleton>
