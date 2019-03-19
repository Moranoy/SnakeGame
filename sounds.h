#ifndef _SOUNDS_H_
#define _SOUNDS_H_
#include <Windows.h>
class Sounds
{
public:
	void playSoundCorrect()
	{
		Beep(392, 250);
		Beep(435, 250);
		Beep(523, 675);
	};
	void playSoundFail()
	{
		Beep(300, 850);
	}
	void playGameOver()
	{
		Beep(392, 250);
		Beep(435, 250);
		Beep(523, 250);
		Beep(616, 250);
		Beep(725, 250);
		Beep(860, 250);
	}
};


#endif