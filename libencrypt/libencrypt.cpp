// libencrypt.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "libencrypt.h"


// ���ǵ���������һ��ʾ��
LIBENCRYPT_API int nlibencrypt=0;

// ���ǵ���������һ��ʾ����
LIBENCRYPT_API int fnlibencrypt(void)
{
    return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� libencrypt.h
Clibencrypt::Clibencrypt()
{
    return;
}
