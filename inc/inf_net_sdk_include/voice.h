#ifndef __VOICE_CODEC_H__
#define __VOICE_CODEC_H__
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef Word16
   typedef short Word16;
#endif

#ifndef Word32
   typedef int Word32;
#endif

#ifndef word16
   typedef short word16;
#endif

#ifndef word32
   typedef int word32;
#endif

#ifndef word32
   typedef int     HI_RET;
#endif

#ifndef NULL
   #define NULL   (word32)0x0L
#endif

#ifndef HI_API
   #define HI_API
#endif



/* max decode/encode frame size, 60ms at 8k samperate or 10ms at 48k samplerate */
/* max decode/encode frame size, 60ms at 8k samperate or 10ms at 48k samplerate */
#define HI_VOICE_MAX_FRAME_SIZE       (480+1)    /* dont change it */

/* HISI_VOICE codec type */

/* Real-time transport protocol(RTP) */
#define G711_A                        0x01  /* 64kbps G.711 A, see RFC3551.txt  4.5.14 PCMA */
#define G711_U                        0x02  /* 64kbps G.711 U, see RFC3551.txt  4.5.14 PCMU */
#define ADPCM_DVI4                    0x03  /* 32kbps ADPCM(DVI4) for RTP; see DVI4 diiffers in three 
                                               respects from the IMA ADPCM at RFC3551.txt 4.5.1 DVI4 */
#define G726_16KBPS                   0x04  /* 16kbps G.726, see RFC3551.txt  4.5.4 G726-16 */
#define G726_24KBPS                   0x05  /* 24kbps G.726, see RFC3551.txt  4.5.4 G726-24 */
#define G726_32KBPS                   0x06  /* 32kbps G.726, see RFC3551.txt  4.5.4 G726-32 */
#define G726_40KBPS                   0x07  /* 40kbps G.726, see RFC3551.txt  4.5.4 G726-40 */

/* IMA ADPCM wave type  */	
#define ADPCM_IMA                     0x23  /* 32kbps ADPCM(IMA) */
/*
An example of the packing scheme for G726-32 codewords is as shown, and bit A3 is the least significant bit of the first codeword: 
RTP G726-32:
0                   1
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
|B B B B|A A A A|D D D D|C C C C| ...
|0 1 2 3|0 1 2 3|0 1 2 3|0 1 2 3|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

MEDIA G726-32:
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
|A A A A|B B B B|C C C C|D D D D| ...
|3 2 1 0|3 2 1 0|3 2 1 0|3 2 1 0|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
*/
#define MEDIA_G726_16KBPS             0x24  /* G726 16kbps for ASF ... */
#define MEDIA_G726_24KBPS             0x25  /* G726 24kbps for ASF ... */
#define MEDIA_G726_32KBPS             0x26  /* G726 32kbps for ASF ... */
#define MEDIA_G726_40KBPS             0x27  /* G726 40kbps for ASF ... */

/* HISI_VOICE FRAME  type */
#define HI_NORMAL_FRAME               0x01


/* HISI_VOICE right code */
#define HI_SUCCESS                    0

#define HI_ERR_VOICE_PREFIX           0xA1222000

/* HISI_VOICE error code */
#define HI_ERR_VOICE_ENC_TYPE         (HI_ERR_VOICE_PREFIX | 0x0001)
#define HI_ERR_VOICE_ENC_FRAMESIZE    (HI_ERR_VOICE_PREFIX | 0x0002)

#define HI_ERR_VOICE_DEC_TYPE         (HI_ERR_VOICE_PREFIX | 0x0011)
#define HI_ERR_VOICE_DEC_FRAMESIZE    (HI_ERR_VOICE_PREFIX | 0x0012)
#define HI_ERR_VOICE_DEC_FRAMETYPE    (HI_ERR_VOICE_PREFIX | 0x0013)


#define HI_ERR_VOICE_INVALID_DEVICE   (HI_ERR_VOICE_PREFIX | 0x0101)
#define HI_ERR_VOICE_INVALID_INBUF    (HI_ERR_VOICE_PREFIX | 0x0102)
#define HI_ERR_VOICE_INVALID_OUTBUF   (HI_ERR_VOICE_PREFIX | 0x0103)



/********************************************************************************
|                                                                               |
|	   HISI VOCIE FRAME Description                                             | 
|	                                                                            |
|	   Paramater 	    bit        Description                                  |
|	   word16 0         15:8       Frame Flag                                   |
|	                               01B  :  normal voice frame                   |
|	                               other:  invalid                              |
|	   word16 0         07:0       reseverd                                     |
|	                                                                            |
|	   word16 1         15:8       Frame Counter                                |
|	                               00 ~ 255                                     |
|	   word16 1         07:0       Raw Frame Data Length(word16)                |
|	                                                                            |
|	   word16 2         15:0       Raw data 0                                   |
|      word16 3         15:0       Raw data 1                                   |
|	     .                                                                      |
|		 .                                                                      |
|		 .                                                                      |
|       word16 2+n       15:0       Raw data n   n==Raw Frame Data Length       |
|                                                                               |
|                                                                               |
********************************************************************************/




/***************************************************************************
* Function:      HI_VOICE_EncReset
* Description:   encoder reset  
* Input:         * pEncState:     encoder device handle
*                  coder:         encoder typeption 
* Output:        none
* Return:        HI_SUCCESS                          success
*                HI_ERR_VOICE_INVALID_DEVICE         invalid encoder device handle
*                HI_ERR_VOICE_ENC_TYPE               invalid encoder typeption 
******************************************************************************/
HI_API HI_RET HI_VOICE_EncReset(void *pEncState, Word16 coder);


/***************************************************************************
* Function:      HI_VOICE_EncReset
* Description:   decoder reset  
* Input:         * pDecState:     decoder device handle
*                  coder:         decoder typeption 
* Output:        none
* Return:        HI_SUCCESS                          success
*                HI_ERR_VOICE_INVALID_DEVICE         invalid decoder device handle
*                HI_ERR_VOICE_DEC_TYPE               invalid decoder typeption 
******************************************************************************/
HI_API HI_RET HI_VOICE_DecReset(void *pDecState, Word16 coder);

/***************************************************************************
* Function:      HI_VOICE_EncodeFrame
* Description:   encode one frame speech data  
* Input:         * pEncState:     encoder device handle
*                * pInputBuf:     input speech data addr 
*                  len:           input speech data count(unit: word16) 
                                  len = n*80 (n*80>0 && n*80<MAX_FRAME_SIZE ) 
*                  coder:         encoder typeption 
* Output:        * pOutputBuf     output addr of compressed speech data buffer
* Return:        HI_SUCCESS                          success
*                HI_ERR_VOICE_INVALID_DEVICE         invalid encoder device handle
*                HI_ERR_VOICE_INVALID_INBUF          invalid input speech data addr
*                HI_ERR_VOICE_INVALID_OUTBUF         invalid output addr
*                HI_ERR_VOICE_ENC_FRAMESIZE          invalid encoder FrameSize
*                HI_ERR_VOICE_ENC_TYPE               invalid encoder typeption 
******************************************************************************/
HI_API HI_RET HI_VOICE_EncodeFrame(void *pEncState, Word16 *pInputBuf, Word16 *pOutputBuf, Word16 coder);//Word16 len, 

/***************************************************************************
* Function:      HI_VOICE_DecodeFrame
* Description:   decode one frame compressed speech data  
* Input:         * pDecState:     decoder device handle
*                * pInputBuf:     input addr of one frame compress speech data buffer 
*                  coder:         encoder typeption 
* Output:        * pOutputBuf£º   output addr of decompressed speech data buffer
                 * pLen:          output speech data count(unit: word16) 
                                  *pPen = n*80 (n*80>0 && n*80<MAX_FRAME_SIZE ) 
* Return:        HI_SUCCESS                          success
*                HI_ERR_VOICE_INVALID_DEVICE         invalid decoder device handle
*                HI_ERR_VOICE_INVALID_INBUF          invalid input addr of one frame compress 
                                                     speech data buffer
*                HI_ERR_VOICE_INVALID_OUTBUF         invalid utput addr of decompressed speech data buffer
*                HI_ERR_VOICE_DEC_FRAMESIZE          invalid decoder FrameSize
*                HI_ERR_VOICE_DEC_FRAMETYPE          invalid frame of compress speech data 
******************************************************************************/

HI_API HI_RET HI_VOICE_DecodeFrame(void *pDecState, Word16 *pInputBuf,  Word16 *pOutputBuf, Word16 *pLen);//Word16 coder, 

/***************************************************************************
* Function:      HI_VOICE_GetVersionNumber
* Description:   get 32bit version number  
* Input:  
* Output:
* Return:        version number
******************************************************************************/
HI_API word32 HI_VOICE_GetVersionNumber();

#define	SIGN_BIT	(0x80)		/* Sign bit for a A-law byte. */
#define	QUANT_MASK	(0xf)		/* Quantization field mask. */
#define	NSEGS		(8)		/* Number of A-law segments. */
#define	SEG_SHIFT	(4)		/* Left shift for segment number. */
#define	SEG_MASK	(0x70)		/* Segment field mask. */

#define	BIAS		(0x84)		/* Bias for linear code. */
static int	search(	int	val,short *table,int size)
{
	int		i;

	for (i = 0; i < size; i++) {
		if (val <= *table++)
			return (i);
	}
	return (size);
}

static short seg_end[8] = {0xFF, 0x1FF, 0x3FF, 0x7FF,
0xFFF, 0x1FFF, 0x3FFF, 0x7FFF};

/* copy from CCITT G.711 specifications */
unsigned char _u2a[128] = {			/* u- to A-law conversions */
	1,	1,	2,	2,	3,	3,	4,	4,
		5,	5,	6,	6,	7,	7,	8,	8,
		9,	10,	11,	12,	13,	14,	15,	16,
		17,	18,	19,	20,	21,	22,	23,	24,
		25,	27,	29,	31,	33,	34,	35,	36,
		37,	38,	39,	40,	41,	42,	43,	44,
		46,	48,	49,	50,	51,	52,	53,	54,
		55,	56,	57,	58,	59,	60,	61,	62,
		64,	65,	66,	67,	68,	69,	70,	71,
		72,	73,	74,	75,	76,	77,	78,	79,
		81,	82,	83,	84,	85,	86,	87,	88,
		89,	90,	91,	92,	93,	94,	95,	96,
		97,	98,	99,	100,	101,	102,	103,	104,
		105,	106,	107,	108,	109,	110,	111,	112,
		113,	114,	115,	116,	117,	118,	119,	120,
		121,	122,	123,	124,	125,	126,	127,	128};

	//
	unsigned char _a2u[128] = {			/* A- to u-law conversions */
		1,	3,	5,	7,	9,	11,	13,	15,
			16,	17,	18,	19,	20,	21,	22,	23,
			24,	25,	26,	27,	28,	29,	30,	31,
			32,	32,	33,	33,	34,	34,	35,	35,
			36,	37,	38,	39,	40,	41,	42,	43,
			44,	45,	46,	47,	48,	48,	49,	49,
			50,	51,	52,	53,	54,	55,	56,	57,
			58,	59,	60,	61,	62,	63,	64,	64,
			65,	66,	67,	68,	69,	70,	71,	72,
			73,	74,	75,	76,	77,	78,	79,	79,
			80,	81,	82,	83,	84,	85,	86,	87,
			88,	89,	90,	91,	92,	93,	94,	95,
			96,	97,	98,	99,	100,	101,	102,	103,
			104,	105,	106,	107,	108,	109,	110,	111,
			112,	113,	114,	115,	116,	117,	118,	119,
			120,	121,	122,	123,	124,	125,	126,	127};
		

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif 
