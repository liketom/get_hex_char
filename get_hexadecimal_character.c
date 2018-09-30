#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <iconv.h>

#define OUTLEN 512
#define INPUT_CODE_UTF8 "-utf8"
#define INPUT_CODE_GB2312 "-gb2312" 

int code_convert(char *from_charset,char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
    iconv_t cd;
    int rc;
    char **pin = &inbuf;
    char **pout = &outbuf;
     
    cd = iconv_open(to_charset,from_charset);
    if (cd==0) return -1;
    memset(outbuf,0,outlen);
    if (iconv(cd,pin,&inlen,pout,&outlen)==-1) return -1;
    iconv_close(cd);
    return 0;
}

/*utf-8码转为GB2312码*/
int u2g(char *inbuf,int inlen,char *outbuf,int outlen)
{
    return code_convert("utf-8","gb2312",inbuf,inlen,outbuf,outlen);
}

/*GB2312码转为utf-8码*/
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
    return code_convert("gb2312","utf-8",inbuf,inlen,outbuf,outlen);
}

int main(int arc, char **arv)// ./get_hexadecimal_character -utf8 张
{
    int input_is_gb2312 = -1;
    int input_is_utf8 = -1;

    if( arc != 3 || 
        ( (input_is_gb2312 = strncmp(arv[1], INPUT_CODE_GB2312, strlen(arv[1]))) && 
        (input_is_utf8 = strncmp(arv[1], INPUT_CODE_UTF8, strlen(arv[1]))) ))
    {
        printf("\nformat: %s <input_code_type> <input_data>\n"
                "eg:\n"
                "\t[  %s %s str  ]\n"
                "or\n"
                "\t[  %s %s str  ]\n\n"
                "* argument 1 represents the code of argument 2 type\n\n"
                ,arv[0], arv[0], INPUT_CODE_UTF8, arv[0], INPUT_CODE_GB2312);
        return -1;
    }

    unsigned char out[OUTLEN] = {0};
    unsigned int i;
       
    if( 0 == input_is_gb2312 )
    {
        printf("input data code is [%s]\n",INPUT_CODE_GB2312);
        g2u(arv[2], strlen(arv[2]), out, OUTLEN);
        
        printf("GB2312 HEX : ");
        for(i = 0; i < strlen(arv[2]); i++ )
        {
            printf("%02x ", (*(arv[2]+i)) & 0xff);
        }
        printf("\n");
       
        printf("UTF-8  HEX : ");
        for(i = 0; i < strlen(out); i++ )
        {
            printf("%02x ", out[i]);    
        }
        printf("\n");
    }
    else if( 0 == input_is_utf8 )
    {
        printf("input data code is [%s]\n",INPUT_CODE_UTF8);
        u2g(arv[2], strlen(arv[2]), out, OUTLEN);
        
        printf("GB2312 HEX : ");
        for(i = 0; i < strlen(out); i++ )
        {
            printf("%02x ", out[i]);    
        }
        printf("\n");
       
        printf("UTF-8  HEX : ");
        for(i = 0; i < strlen(arv[2]); i++ )
        {
            printf("%02x ", (*(arv[2]+i)) & 0xff);
        }
        printf("\n");
    }
    else
    {
        printf("strncmp err\n");
        return -1;
    }

    return 0;
}
