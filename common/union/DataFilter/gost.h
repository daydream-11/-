#ifndef __RB_GOST_H__
#define __RB_GOST_H__

#ifndef _TYPE_WORD32
    typedef unsigned int word32;
#endif

#ifdef __cplusplus
extern "C" 
{
#endif


void kboxinit(void) ;
void gostcrypt(word32 const in[2], word32 out[2], word32 const key[8]) ;
void gostdecrypt(word32 const in[2], word32 out[2], word32 const key[8]) ;


#ifdef __cplusplus
}
#endif

#endif