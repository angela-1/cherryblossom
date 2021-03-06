// aescrypto.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


#include "aescrypto.h"


//#pragma comment(lib, "libcrypto.lib")




AESCRYPTO_API    int cb_salt(uchar *md, int len)
    {
        char p[16];
        RAND_seed(p, 16);

        while (1)
        {
            int ret = RAND_status();
            if (ret == 1)
            {

                break;
            }
            else
            {

                RAND_poll();
            }
        }

        RAND_bytes(md, 16);

        return 0;


    }


AESCRYPTO_API    int cb_digest_md5(char *buf, uchar *md)
    {
        MD5_CTX ctx;
        MD5_Init(&ctx);
        MD5_Update(&ctx, buf, strlen(buf));
        MD5_Final(md, &ctx);
        return 0;
    }





AESCRYPTO_API    int cb_encrypt(uchar *src, uchar *dst, uint len, uchar *key)
    {
        AES_KEY aes;
        uchar iv[AES_BLOCK_SIZE];        // init vector

        uint i;



        for (i = 0; i < AES_BLOCK_SIZE; ++i) {
            iv[i] = 0;
        }
        if (AES_set_encrypt_key(key, 128, &aes) < 0) {
            //fprintf(stderr, "Unable to set encryption key in AES\n");
            //exit(-1);
            return 0;
        }


        // encrypt (iv will change)
        AES_cbc_encrypt(src, dst, len, &aes, iv, AES_ENCRYPT);

        return len;

    }


AESCRYPTO_API    int cb_decrypt(uchar *src, uchar *dst, uint len, uchar *key)
    {
        AES_KEY aes;
        uchar iv[AES_BLOCK_SIZE];        // init vector

        uint i;

        for (i = 0; i < AES_BLOCK_SIZE; ++i) {
            iv[i] = 0;
        }
        if (AES_set_decrypt_key(key, 128, &aes) < 0) {
            //fprintf(stderr, "Unable to set decryption key in AES\n");
            //exit(-1);
            return 0;
        }


        // decrypt 
        AES_cbc_encrypt(src, dst, len, &aes, iv,
            AES_DECRYPT);

        return len;


    }


