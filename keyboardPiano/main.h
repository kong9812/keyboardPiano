#ifndef _MAIN_H_
#define	_MAIN_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME			("Data/test")	// �t�@�C����

#define CHANNEL				(1)				// �`�����l����
#define BIT_RATE			(16)			// �r�b�g���[�g
#define SAMPLE_FREQ			(44100)			// �T���v�����O���g��

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
// �萔��`
//*****************************************************************************
enum WAVE_TYPE
{
	WAVE_END,
	WAVE_SINE,
	WAVE_SQUARE,
	WAVE_SAWTOOTH
};

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct	// �g�`�p�ϐ� 
{
	float secPerSample;		// 1s / �T���v�����O���g��
	float samplePos;		// �T���v�����O�̈ʒu 
	float waveIndex;		// �g�`�Ԗ�
	float wavePos;			// �g�`���̈ʒu
	float secPerFreq;		// 1s / ���g��
	float volume;			// �{�����[��

}WAVE_DATA;

#endif