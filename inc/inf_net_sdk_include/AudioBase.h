/************************************************************

  Copyright (C), 2008-2011, HKVision. Co., Ltd.

*************************************************************

  File Name      : AudioBase.h
  Version          : V1.0 
  Author           : Locke Jiang
  Last Modified : 2013-12-16
  Description    : Audio Basic Functions
  Function List  : 
  History          :

************************************************************/
#pragma once

#include <alsa/asoundlib.h>
#include "Define.h"
/* WAVE fmt block constants from Microsoft mmreg.h header */
#define WAV_FMT_PCM             0x0001
#define WAV_FMT_IEEE_FLOAT      0x0003
#define WAV_FMT_DOLBY_AC3_SPDIF 0x0092
#define WAV_FMT_EXTENSIBLE      0xfffe

#define PLAY_AUDIO_FRAME_SIZE 640

#define DEFAULT_CHANNELS         (1)
#define DEFAULT_SAMPLE_RATE      (8000)
#define DEFAULT_SAMPLE_LENGTH    (16)

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define COMPOSE_ID(a,b,c,d)	((a) | ((b)<<8) | ((c)<<16) | ((d)<<24))
#define LE_SHORT(v)		      (v)
#define LE_INT(v)		        (v)
#define BE_SHORT(v)			bswap_16(v)
#define BE_INT(v)			bswap_32(v)
#elif __BYTE_ORDER == __BIG_ENDIAN
#define COMPOSE_ID(a,b,c,d)	((d) | ((c)<<8) | ((b)<<16) | ((a)<<24))
#define LE_SHORT(v)			bswap_16(v)
#define LE_INT(v)		        	bswap_32(v)
#define BE_SHORT(v)		      (v)
#define BE_INT(v)		        (v)
#else
#error "Wrong endian"
#endif

#define WAV_RIFF		COMPOSE_ID('R','I','F','F')
#define WAV_WAVE		COMPOSE_ID('W','A','V','E')
#define WAV_FMT		COMPOSE_ID('f','m','t',' ')
#define WAV_DATA		COMPOSE_ID('d','a','t','a')

typedef long long off64_t;

typedef enum{
	PLAYBACK = 0,
	CAPTURE = 1,
}OpenDevice_t;

/* Used with WAV_FMT_EXTENSIBLE format */
#define WAV_GUID_TAG		"/x00/x00/x00/x00/x10/x00/x80/x00/x00/xAA/x00/x38/x9B/x71"

/* it's in chunks like .voc and AMIGA iff, but my source say there
   are in only in this combination, so I combined them in one header;
   it works on all WAVE-file I have
 */

typedef struct WAVHeader {
	uint32_t magic;		/* 'RIFF' */
	uint32_t length;		/* filelen */
	uint32_t type;		/* 'WAVE' */
} WAVHeader_t;

typedef struct WAVFmt {
	//uint32_t magic;  /* 'FMT '*/
	//uint32_t fmt_size; /* 16 or 18 */
	uint16_t format;		/* see WAV_FMT_* */
	uint16_t channels;
	uint32_t sample_rate;	/* frequence of sample */
	uint32_t bytes_p_second;
	uint16_t blocks_align;	/* samplesize; 1 or 2 bytes */
	uint16_t sample_length;	/* 8, 12 or 16 bit */
} WAVFmt_t;

typedef struct WAVChunkHeader {
	uint32_t type;		/* 'data' */
	uint32_t length;		/* samplecount */
} WAVChunkHeader_t;


typedef struct WAVContainer{
	/*WAV Header*/
	uint32_t hd_magic;		/* 'RIFF' */
	uint32_t hd_length;		/* filelen */
	uint32_t hd_type;		/* 'WAVE' */
	
	/*WAV Format*/
	uint32_t fmt_magic;  /* 'FMT '*/
	uint32_t fmt_size; /* 16 or 18 */
	uint16_t fmt_format;		/* see WAV_FMT_* */
	uint16_t fmt_channels;
	uint32_t fmt_sample_rate;	/* frequence of sample */
	uint32_t fmt_bytes_per_second;
	uint16_t fmt_blocks_align;	/* samplesize; 1 or 2 bytes */
	uint16_t fmt_sample_length;	/* 8, 12 or 16 bit */
	
	/*WAV chunk*/
	uint32_t chk_type;		/* 'data' */
	uint32_t chk_length;		/* samplecount */
	
}WAVContainer_t;

typedef struct SNDPCMContainer {
	snd_pcm_t *handle;
	snd_output_t *log;
	snd_pcm_uframes_t chunk_size;
	snd_pcm_uframes_t buffer_size;
	snd_pcm_format_t format;
	uint16_t channels;
	size_t chunk_bytes;
	size_t bits_per_sample;
	size_t bits_per_frame;

	uint8_t *data_buf;
} SNDPCMContainer_t;

typedef struct INF_AUDIO_STREAM_GLOBAL_STRUCT {
	BOOL bIsQuit;
}INF_AUDIO_STREAM_GLOBAL_STRUCT;

ssize_t  PCM_WriteData(SNDPCMContainer_t *sndpcm, size_t wcount);
int        PCM_SetParams(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav);
void      PCM_PlayBack(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav,size_t size);
int        PCM_PrepareParams(WAVContainer_t *wav);
int        PCM_WriteHeader(int fd, WAVContainer_t *container);
