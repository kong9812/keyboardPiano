#ifndef _MAIN_H_
#define	_MAIN_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILE_NAME			("Data/test")	// ファイル名

#define CHANNEL				(1)				// チャンネル数
#define BIT_RATE			(16)			// ビットレート
#define SAMPLE_FREQ			(44100)			// サンプリング周波数

#define FREQ_0_DO			(131.0f)		// DO[C3]
#define FREQ_0_RE			(147.0f)		// RE[D3]
#define FREQ_0_MI			(165.0f)		// MI[E3]
#define FREQ_0_FA			(175.0f)		// FA[F3]
#define FREQ_0_SOL			(196.0f)		// SOL[G3]
#define FREQ_0_LA			(220.0f)		// LA[A4]
#define FREQ_0_SI			(247.0f)		// SI[B3]

#define FREQ_1_DO			(262.0f)		// DO[C4]
#define FREQ_1_RE			(294.0f)		// RE[D4]
#define FREQ_1_MI			(330.0f)		// MI[E4]
#define FREQ_1_FA			(370.0f)		// FA[F]
#define FREQ_1_SOL			(392.0f)		// SOL[G4]
#define FREQ_1_LA			(440.0f)		// LA[A4]
#define FREQ_1_SI			(494.0f)		// SI[B4]

#define FREQ_2_DO			(523.0f)		// DO[C5]
#define FREQ_2_RE			(587.0f)		// RE[D5]
#define FREQ_2_MI			(659.0f)		// MI[E5]
#define FREQ_2_FA			(698.0f)		// FA[F5]
#define FREQ_2_SOL			(784.0f)		// SOL[G5]
#define FREQ_2_LA			(880.0f)		// LA[A5]
#define FREQ_2_SI			(988.0f)		// SI[B5]
#define FREQ_2_DOU			(1047.0f)		// DO[C6]

//*****************************************************************************
// 定数定義
//*****************************************************************************
enum WAVE_TYPE
{
	WAVE_END,
	WAVE_SINE,
	WAVE_SQUARE,
	WAVE_SAWTOOTH
};

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct	// 波形用変数 
{
	float secPerSample;		// 1s / サンプリング周波数
	float samplePos;		// サンプリングの位置 
	float waveIndex;		// 波形番目
	float wavePos;			// 波形中の位置
	float secPerFreq;		// 1s / 周波数
	float volume;			// ボリューム

}WAVE_DATA;

#endif
