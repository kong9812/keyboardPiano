//=============================================================================
// < KEYBOARD PIANO v1.0 >
// Main処理 [main.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#define _USE_MATH_DEFINES
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#pragma comment(lib, "winmm.lib")
#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/* 初期化 */
void Init(void);
/* 更新処理 */
void Update(void);
/* ファイルの書き出し */
void SetWavFile(int type, float freq);
/* 正弦波 */
void SetSineWave(WAVE_DATA waveData);
/* 矩形波 */
void SetSquareWave(WAVE_DATA waveData);
/* のこぎり波 */
void SetSawtooth(WAVE_DATA waveData);
/* 曲モード(dear you) */
void SetMusic(void);

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
WAVEFORMATEX	wave;						// 私の好み(wave構造体)
WAVE_DATA		waveData;					// 波形データ
FILE			*fp;						// ファイル構造体							

bool			loop;						// ループ用							
							
char			*work;						// ファイルワーク

short			*buf;						// 波形のバッファ

int				fileSize;					// ファイルサイズ															
int				waveSize;					// 波形サイズ
int				waveType = WAVE_SINE;	// 波形種類(音色)
int				noteNo;						// ファイル番号

//=============================================================================
// メイン関数
//=============================================================================
int main(void)
{
	/* 初期化 */
	printf("キーボード　ピアノ～");
	printf("初期化中");
	Init();
	Sleep(1000);
	printf(".");
	Sleep(1000);
	printf(".");
	Sleep(1000);
	printf(".\n");

	/* ウィンドウズのロックオン */
	PlaySound("WindowsLogon", NULL, SND_ALIAS | SND_NODEFAULT | SND_ASYNC);
	
	/* チュトリアル */
	printf("Q～Iキー [C3～B3]\n");
	printf("A～Kキー [C4～B4]\n");
	printf("Z～,キー [C5～C6]\n");
	printf("1キー Dear Youを再生する\n");

	/* ループ */
	while (loop)
	{
		/* 更新 */
		Update();
	}

	/* 画面クリア */
	system("cls");
	
	/* 任意キー */
	printf("bye bye～ press ANY KEY for exit～");

	/* キー押したら終了 */
	getchar();
	
	return 0;
}

//=============================================================================
// 初期化
//=============================================================================
void Init(void)
{
	/* ループ開始 */
	loop = true;

	{/* 波形データ */
		waveData.samplePos		= 0;
		waveData.secPerFreq		= 0;
		waveData.secPerSample	= 0;
		waveData.volume			= 0;
		waveData.waveIndex		= 0;
		waveData.wavePos		= 0;
	}

	/* ファイル番目 */
	noteNo = 0;
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	int	key = _getch();

	switch (key)
	{
	case 'q':
		printf("C3 \n");
		SetWavFile(waveType, FREQ_0_DO);
		break;
	case 'w':
		printf("D3 \n");
		SetWavFile(waveType, FREQ_0_RE);
		break;
	case 'e':
		printf("E3 \n");
		SetWavFile(waveType, FREQ_0_MI);
		break;
	case 'r':
		printf("F3 \n");
		SetWavFile(waveType, FREQ_0_FA);
		break;
	case 't':
		printf("G3 \n");
		SetWavFile(waveType, FREQ_0_SOL);
		break;
	case 'y':
		printf("A4 \n");
		SetWavFile(waveType, FREQ_0_LA);
		break;
	case 'u':
		printf("B3 \n");
		SetWavFile(waveType, FREQ_0_SI);
		break;
	case 'i':
	case 'a':
		printf("C4 \n");
		SetWavFile(waveType, FREQ_1_DO);
		break;
	case 's':
		printf("D4 \n");
		SetWavFile(waveType, FREQ_1_RE);
		break;
	case 'd':
		printf("E4 \n");
		SetWavFile(waveType, FREQ_1_MI);
		break;
	case 'f':
		printf("F4 \n");
		SetWavFile(waveType, FREQ_1_FA);
		break;
	case 'g':
		printf("G4 \n");
		SetWavFile(waveType, FREQ_1_SOL);
		break;
	case 'h':
		printf("A4 \n");
		SetWavFile(waveType, FREQ_1_LA);
		break;
	case 'j':
		printf("B4 \n");
		SetWavFile(waveType, FREQ_1_SI);
		break;
	case 'k':
	case 'z':
		printf("C5 \n");
		SetWavFile(waveType, FREQ_2_DO);
		break;
	case 'x':
		printf("D5 \n");
		SetWavFile(waveType, FREQ_2_RE);
		break;
	case 'c':
		printf("E5 \n");
		SetWavFile(waveType, FREQ_2_MI);
		break;
	case 'v':
		printf("F5 \n");
		SetWavFile(waveType, FREQ_2_FA);
		break;
	case 'b':
		printf("G5 \n");
		SetWavFile(waveType, FREQ_2_SOL);
		break;
	case 'n':
		printf("A5 \n");
		SetWavFile(waveType, FREQ_2_LA);
		break;
	case 'm':
		printf("B5 \n");
		SetWavFile(waveType, FREQ_2_SI);
		break;
	case ',':
		printf("C6 \n");
		SetWavFile(waveType, FREQ_2_DOU);
		break;
	case '1':
		SetMusic();
		break;
	case 27:
		loop = false;
		/* ウィンドウズのロックオン */
		PlaySound("WindowsLogoff", NULL, SND_ALIAS | SND_NODEFAULT | SND_ASYNC);
		break;
	default:
		break;
	}
}

//=============================================================================
// ファイルの書き出し
//=============================================================================
void SetWavFile(int type,float freq)
{
	int channel = CHANNEL;					// チャンネル数
	int bitRate = BIT_RATE;					// ビットレート
	int sf		= SAMPLE_FREQ;				// サンプリング周波数
	char fileName[CHAR_MAX] = FILE_NAME;	// ファイル名
	noteNo++;
	/* ファイル名 */
	sprintf_s(fileName, "%s%d", fileName, noteNo);
	strcat_s(fileName, CHAR_MAX, ".wav");

	/* ファイルの準備 */
	fopen_s(&fp, fileName, "wb");

	/* wav構造体の初期化 */
	wave.cbSize = 0;
	wave.nChannels = channel;
	wave.wBitsPerSample = bitRate;
	wave.nSamplesPerSec = sf;
	wave.wFormatTag = WAVE_FORMAT_PCM;
	wave.nBlockAlign = (wave.nChannels*wave.wBitsPerSample) / 8;
	wave.nAvgBytesPerSec = wave.nSamplesPerSec*wave.nBlockAlign;

	/* ファイルサイズの初期化 */
	waveSize = (wave.nSamplesPerSec*(wave.wBitsPerSample / 8));

	/* ファイルサイズの初期化 */
	fileSize = 44 + (waveSize);

	/* ワークのメモリー確保 */
	work = (char *)malloc(fileSize);

	/* [4 byte]riff */
	memcpy(work, "RIFF", 4);

	/* [4 byte]これ以降のファイルサイズ */
	work[4] = (fileSize - 8) >> 0 & 0xff;
	work[5] = (fileSize - 8) >> 8 & 0xff;
	work[6] = (fileSize - 8) >> 16 & 0xff;
	work[7] = (fileSize - 8) >> 24 & 0xff;

	/* [4 byte]wave */
	memcpy(work + 8, "WAVE", 4);

	/* [4 byte]fmt  */
	memcpy(work + 12, "fmt ", 4);

	/* [4 byte]バイト数 */
	work[16] = 16;
	work[17] = 0;
	work[18] = 0;
	work[19] = 0;

	/* [2 byte]フォーマットID */
	work[20] = 1;
	work[21] = 0;

	/* [2 byte]チャンネル数 */
	work[22] = (char)wave.nChannels;
	work[23] = 0;

	/* [4 byte]サンプリングレート */
	work[24] = wave.nSamplesPerSec >> 0 & 0xff;
	work[25] = wave.nSamplesPerSec >> 8 & 0Xff;
	work[26] = wave.nSamplesPerSec >> 16 & 0xff;
	work[27] = wave.nSamplesPerSec >> 24 & 0xff;

	/* [4 byte]データ速度(Byte/sec) */
	work[28] = (wave.nSamplesPerSec*(wave.wBitsPerSample / 8)) >> 0 & 0xff;
	work[29] = (wave.nSamplesPerSec*(wave.wBitsPerSample / 8)) >> 8 & 0xff;
	work[30] = (wave.nSamplesPerSec*(wave.wBitsPerSample / 8)) >> 16 & 0xff;
	work[31] = (wave.nSamplesPerSec*(wave.wBitsPerSample / 8)) >> 14 & 0xff;

	/* [2 byte]プロックサイズ(Byte/sample*チャンネル数) */
	work[32] = (wave.wBitsPerSample / 8) >> 0 & 0xff;
	work[33] = (wave.wBitsPerSample / 8) >> 8 & 0xff;

	/* [2 byte]サンプリングあたりのビット数 */
	work[34] = wave.wBitsPerSample >> 0 & 0xff;
	work[35] = wave.wBitsPerSample >> 8 & 0xff;

	/* [4 byte]data */
	memcpy(work + 36, "data", 4);

	/* [4 byte]サウンド全体のバイト数n */
	work[40] = waveSize >> 0 & 0xff;
	work[41] = waveSize >> 8 & 0xff;
	work[42] = waveSize >> 16 & 0xff;
	work[43] = waveSize >> 24 & 0xff;

	{/* 初期化 */
		waveData.secPerSample = 1.0f / wave.nSamplesPerSec;
		waveData.secPerFreq = 1.0f / freq;
	}

	/* 波形生成 */
	buf = (short *)malloc(waveSize * sizeof(short));

	/* 波形の分岐 */
	switch (type)
	{
	case WAVE_SINE:
		SetSineWave(waveData);		// 正弦波
		break;
	case WAVE_SQUARE:
		SetSquareWave(waveData);	// 矩形波
		break;
	case WAVE_SAWTOOTH:
		SetSawtooth(waveData);		// のこぎり波
		break;
	default:
		break;
	}

	/* [n byte]波形情報 */
	memcpy(work + 44, buf, waveSize);

	/* 書き出し */
	fwrite(work, fileSize, 1, fp);

	{/* またね～処理 */
		free(buf);
		fclose(fp);
		free(work);
	}
	
	/* 再生 */
	PlaySound(fileName, NULL, SND_FILENAME | SND_ASYNC);
}

//=============================================================================
// 正弦波
//=============================================================================
void SetSineWave(WAVE_DATA waveData)
{
	for (int i = 0; i < waveSize; i++)
	{
		/* 正弦波 */
		waveData.samplePos = waveData.secPerSample * i;
		waveData.waveIndex = waveData.samplePos / waveData.secPerFreq;
		waveData.wavePos = fmodf(waveData.waveIndex, 1.0);
		waveData.volume = (float)i/waveSize;
		buf[i] = (short)((float)(SHRT_MAX) * sinf((float)(2.0f*M_PI*waveData.wavePos)));
	}
}

//=============================================================================
// 矩形波
//=============================================================================
void SetSquareWave(WAVE_DATA waveData)
{
	for (int i = 0; i < waveSize; i++)
	{
		/* 矩形波 */
		waveData.samplePos = waveData.secPerSample * i;
		waveData.waveIndex = waveData.samplePos / waveData.secPerFreq;
		waveData.wavePos = fmodf(waveData.waveIndex, 1.0);
		waveData.volume = (float)i / waveSize;
		if (waveData.wavePos < 0.5f)
		{
			buf[i] = (short)(SHRT_MAX);
		}
		else
		{
			buf[i] = (short)(SHRT_MIN);
		}
	}
}

//=============================================================================
// のこぎり波
//=============================================================================
void SetSawtooth(WAVE_DATA waveData)
{
	for (int i = 0; i < waveSize; i++)
	{
		/* のこぎり波 */
		waveData.samplePos = waveData.secPerSample * i;
		waveData.waveIndex = waveData.samplePos / (waveData.secPerFreq/2);
		waveData.volume = (float)i / waveSize;
		buf[i] = (short)((short)(((float)SHRT_MAX + 1) * waveData.waveIndex));
	}
}

//=============================================================================
// 曲(dear you)
//=============================================================================
void SetMusic(void)
{
	// 1
	printf("1\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(1000);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);

	// 2
	printf("2\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(500);
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);

	// 3
	printf("3\n");
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(1000);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);

	// 4
	printf("4\n");
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);
	SetWavFile(waveType, 880.00f);	// A5
	Sleep(500);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(1000);

	// 5
	printf("5\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(1000);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);

	// 6
	printf("6\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(500);
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);

	// 7
	printf("7\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(750);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);


	// 8
	printf("8\n");
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(2000);

	// 9
	printf("9\n");
	SetWavFile(waveType, 123.47f);	// B2
	Sleep(500);
	SetWavFile(waveType, 174.61f);	// F3
	Sleep(500);
	SetWavFile(waveType, 220.00f);	// A3
	Sleep(1000);

	// 10
	printf("10\n");
	SetWavFile(waveType, 98.00f);	// G2
	Sleep(500);
	SetWavFile(waveType, 146.83f);	// D3
	Sleep(500);
	SetWavFile(waveType, 174.61f);	// G3
	Sleep(1000);
	 
	// 11
	printf("11\n");
	SetWavFile(waveType, 110.00f);	// A2
	Sleep(500);
	SetWavFile(waveType, 164.81f);	// E3
	Sleep(500);
	SetWavFile(waveType, 196.00f);	// G3
	Sleep(1000);

	// 12
	printf("12\n");
	SetWavFile(waveType, 146.83f);	// D3
	Sleep(500);
	SetWavFile(waveType, 220.00f);	// A3
	Sleep(500);
	SetWavFile(waveType, 261.62f);	// C4
	Sleep(1000);

	// 13
	printf("13\n");
	SetWavFile(waveType, 123.47f);	// B2
	Sleep(500);
	SetWavFile(waveType, 174.61f);	// F3
	Sleep(500);
	SetWavFile(waveType, 220.00f);	// A3
	Sleep(1000);

	// 14
	printf("14\n");
	SetWavFile(waveType, 98.00f);	// G2
	Sleep(500);
	SetWavFile(waveType, 146.83f);	// D3
	Sleep(500);
	SetWavFile(waveType, 174.61f);	// G3
	Sleep(1000);

	// 15
	printf("15\n");
	SetWavFile(waveType, 110.00f);	// A2
	Sleep(500);
	SetWavFile(waveType, 164.81f);	// E3
	Sleep(500);
	SetWavFile(waveType, 196.00f);	// G3
	Sleep(1000);

	// 16
	printf("16\n");
	SetWavFile(waveType, 146.83f);	// D3
	Sleep(500);
	SetWavFile(waveType, 220.00f);	// A3
	Sleep(500);
	SetWavFile(waveType, 130.81f);	// C3
	Sleep(500);
	SetWavFile(waveType, 220.00f);	// A3
	Sleep(500);


	// 17
	printf("17\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(1000);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);

	// 18
	printf("18\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(500);
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);

	// 19
	printf("19\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(750);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);

	// 20
	printf("20\n");
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);
	SetWavFile(waveType, 880.00f);	// A5
	Sleep(500);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(1000);

	// 21
	printf("21\n");
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(1000);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);

	// 22
	printf("22\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(1000);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);

	// 23
	printf("23\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(1000);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(750);


	// 24
	printf("24\n");
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(2000);

	// 25
	printf("25\n");
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(1000);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);

	// 26
	printf("26\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(500);
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);

	// 27
	printf("27\n");
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(1000);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(250);

	// 28
	printf("28\n");
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);
	SetWavFile(waveType, 880.00f);	// A5
	Sleep(500);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(1000);

	// 29
	printf("29\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(1000);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);

	// 30
	printf("30\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(500);
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);


	// 31
	printf("31\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(750);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(250);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(250);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);

	// 32
	printf("32\n");
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(1500);
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(250);
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(250);

	// 33
	printf("33\n");
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);
	SetWavFile(waveType, 349.23f);	// F4
	Sleep(1000);
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);

	// 34
	printf("34\n");
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(1000);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(500);

	// 35
	printf("35\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(500);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(500);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(500);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(500);

	// 36
	printf("36\n");
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(1500);
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);

	// 37
	printf("37\n");
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);

	// 38
	printf("38\n");
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(1500);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(500);


	// 39
	printf("39\n");
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(500);
	SetWavFile(waveType, 659.25f);	// E5
	Sleep(500);
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(500);
	SetWavFile(waveType, 880.0f);	// A5
	Sleep(500);

	// 40
	printf("40\n");
	SetWavFile(waveType, 698.46f);	// F5
	Sleep(2000);

	// 41
	printf("41\n");
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);
	SetWavFile(waveType, 349.23f);	// F4
	Sleep(1000);
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);

	// 42
	printf("42\n");
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(1000);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(500);

	// 43
	printf("43\n");
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(500);
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(1000);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(500);

	// 44
	printf("44\n");
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(2000);

	// 45
	printf("45\n");
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);
	SetWavFile(waveType, 349.23f);	// F4
	Sleep(1000);
	SetWavFile(waveType, 440.00f);	// A4
	Sleep(500);

	// 46
	printf("46\n");
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(500);

	// 47
	printf("47\n");
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(500);
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(500);
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(500);
	SetWavFile(waveType, 880.0f);	// A5
	Sleep(500);

	// 48
	printf("48\n");
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(1500);
	SetWavFile(waveType, 880.0f);	// A5
	Sleep(500);

	// 49
	printf("49\n");
	SetWavFile(waveType, 880.0f);	// A5
	Sleep(500);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(1000);
	SetWavFile(waveType, 880.0f);	// A5
	Sleep(500);

	// 50
	printf("50\n");
	SetWavFile(waveType, 880.0f);	// A5
	Sleep(500);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(1000);
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(500);

	// 51
	printf("51\n");
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(500);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(500);
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(500);

	// 52
	printf("52\n");
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(500);
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(500);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(500);
	SetWavFile(waveType, 880.0f);	// A5
	Sleep(500);

	// 53
	printf("53\n");
	SetWavFile(waveType, 880.0f);	// A5
	Sleep(500);
	SetWavFile(waveType, 698.45f);	// F5
	Sleep(1000);
	SetWavFile(waveType, 880.0f);	// A5
	Sleep(500);

	// 54
	printf("54\n");
	SetWavFile(waveType, 880.0f);	// A5
	Sleep(500);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(1000);
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(500);

	// 55
	printf("55\n");
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(500);
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(500);
	SetWavFile(waveType, 659.26f);	// E5
	Sleep(1000);

	// 56
	printf("56\n");
	SetWavFile(waveType, 587.33f);	// D5
	Sleep(2000);
}