task time_count()
{
	int i_30=0;
	int i_10=0;
	nVolume=100;
	PlayTone(233,250);

	return;

	while(time1[T1]<105000)
	{
		if(time1[T1]>=75000&&time1[T1]<=80000)
		{
			for(;i_30<3;i_30++)
			{
				PlayTone(555,50);
				while(bSoundActive)
					wait1Msec(5);
				wait1Msec(100);
			}
		}
		if(time1[T1]>=95000&&time1[T1]<=105000)
		{
			for(;i_10<10;i_10++)
			{
				PlayTone((566+i_10*20),(105-i_10*10));
				while(bSoundActive)
					wait1Msec(5);
				wait1Msec(200);
			}
			//PlayTone(444,200);

		}
	}
}
