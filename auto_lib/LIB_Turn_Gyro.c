void Turn_Auto(int gyro_aim,short Speed_ABS,short forward,int Exit_Time,int Timer_x,int brake)
{
	int temp;
	int aim;

	if(slip)
		return;

	aim=gyro_aim;


	clearTimer(Timer_x);
	int dir;

	if(SensorValue[Gyro]<= aim )
	{
		move(forward,Speed_ABS);
		dir=1;
	}
	else
	{
		move(forward,-Speed_ABS);
		dir=-1;
	}

	while(1)
	{
		temp=SensorValue[Gyro];

		if(time1[Timer_x]>Exit_Time )
		{
			writeDebugStream("\nturn:time-out aim:%d, final:%d T:%d\n",aim,temp,time1[Timer_x]);
			break;
		}

		if(abs(temp-aim)<10)
		{
			writeDebugStream("\nturn:aim:%d, final:%d T:%d\n",aim,SensorValue[Gyro],time1[Timer_x]);
			break;
		}
		if(temp>aim && dir==1)
		{
			writeDebugStream("\nturn:aim:%d, final:%d T:%d\n",aim,SensorValue[Gyro],time1[Timer_x]);
			break;
		}
		if(temp<aim && dir==-1)
		{
			writeDebugStream("\nturn:aim:%d, final:%d T:%d\n",aim,SensorValue[Gyro],time1[Timer_x]);
			break;
		}
		wait1Msec(1);
	}

	//after break;
	if(brake==BRAKE)
	{
			int PwrL = -0.5*moveL_spd;
			int PwrR = -0.5*moveR_spd;
			set_move_pwr(PwrL, PwrR);
			wait1Msec(100);
	}
	Move_Stop();
}
