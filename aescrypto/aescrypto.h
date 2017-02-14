

#ifdef AESCRYPTO_EXPORTS
#define AESCRYPTO_API __declspec(dllexport)
#else
#define AESCRYPTO_API __declspec(dllimport)
#endif


# ifdef  __cplusplus
extern "C" {
# endif


#include "aes.h"
#include "md5.h"
#include "rand.h"




    typedef unsigned char uchar;
    typedef unsigned int uint;




    extern AESCRYPTO_API int cb_digest_md5(char *buf, uchar *md);
    extern AESCRYPTO_API int cb_salt(uchar *md, int len);

    extern AESCRYPTO_API int cb_encrypt(uchar *src, uchar *dst, uint len, uchar *key);
    extern AESCRYPTO_API int cb_decrypt(uchar *src, uchar *dst, uint len, uchar *key);


# ifdef  __cplusplus
}
# endif

