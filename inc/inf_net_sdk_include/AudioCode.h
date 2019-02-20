/************************************************************

Copyright (C), 2008-2011, HKVision. Co., Ltd.

*************************************************************

File Name     : AudioCode.h
Version       : V1.0 
Author        : HKVision RD3
Last Modified : 2008-12-5
Description   : Audio Code Functions
Function List : 
History       :

************************************************************/

#pragma once

int AudioEncode(short *inp_buf, short *out_buf, short uLen);
int AudioDecode(short *inp_buf, short *out_buf, short *pLength);
short Alaw2Linear(unsigned char a_val);
unsigned char Linear2Alaw(short	pcm_val);
short Ulaw2Linear(unsigned char	u_val);
unsigned char Linear2Ulaw(short	pcm_val);

