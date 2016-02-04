// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� LIBENCRYPT_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// LIBENCRYPT_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef LIBENCRYPT_EXPORTS
#define LIBENCRYPT_API __declspec(dllexport)
#else
#define LIBENCRYPT_API __declspec(dllimport)
#endif

#include "aes.h"
#include "md5.h"
#include "rand.h"



typedef unsigned char uchar;
typedef unsigned int uint;







extern LIBENCRYPT_API int digest_md5(char *buf, uchar *md);
extern LIBENCRYPT_API int salt(uchar *md, int len);

extern LIBENCRYPT_API int encrypt(uchar *src, uchar *dst, uint len, uchar *key);
extern LIBENCRYPT_API int decrypt(uchar *src, uchar *dst, uint len, uchar *key);



