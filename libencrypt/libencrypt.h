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

// �����Ǵ� libencrypt.dll ������
class LIBENCRYPT_API Clibencrypt {
public:
	Clibencrypt(void);
	// TODO:  �ڴ�������ķ�����
};

extern LIBENCRYPT_API int nlibencrypt;

LIBENCRYPT_API int fnlibencrypt(void);
