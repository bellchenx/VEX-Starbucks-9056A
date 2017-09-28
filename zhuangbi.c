
word lastzhuangbikey;

struct playtone_struct{
	int times;
	int fre;
};

playtone_struct warning;
task playtone_warning_task()
{
	nVolume = 100;
	for(int i = 0; i < warning.times; i ++)
	{
		playTone(warning.fre, 20);
		wait1Msec(40);
	}
}
void warning_func(int playtimes, int frequency)
{
	warning.times = playtimes;
	warning.fre = frequency;
	if(getTaskState(playtone_warning_task) == taskStateRunning)
		stopTask(playtone_warning_task);
	startTask(playtone_warning_task);
	nVolume = 60;
}

void wait_for_playtone()
{
	while(getTaskState(playtone_warning_task) != taskStateStopped)
		wait1Msec(20);
}

void ZHUANGBI()
{
	if(key_zhuangbi && !lastzhuangbikey)
	{
		nVolume = 80;
		//playSoundFile("boy next door.wav");
	}
	lastzhuangbikey = key_zhuangbi;
}
