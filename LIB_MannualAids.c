//task Turn_Aids()
//{
//	lockmove = 1;

//	int temp = SensorValue[Gyro];
//	short output;
//	short pwr = 80;
//	int aim;

//	int enc_last;
//	int enc_now;
//	float kp=6;

//	if(slip)
//		return;

//	aim = 0;
//	int dir;

//	if(temp > 0 && temp <= 1800)
//	{
//		set_move_pwr(pwr,-pwr);
//		aim = 1800;
//		dir=1;
//	}
//	if(temp > 1800)
//	{
//		set_move_pwr(-pwr,pwr);
//		aim = 1800;
//		dir=-1;
//	}
//	if(temp <= -1800)
//	{
//		set_move_pwr(pwr,-pwr);
//		aim = 1800;
//		dir=1;
//	}
//	if(temp <= 0 && temp > -1800)
//	{
//		set_move_pwr(-pwr,pwr);
//		aim = -1800;
//		dir=-1;
//	}

//	while(1)
//	{
//		temp=SensorValue[Gyro];
//		if(abs(temp-aim)<10)
//		{
////		writeDebugStream("\nturn:aim:%d, final:%d T:%d\n",aim,SensorValue[Gyro],time1[Timer_x]);
//			break;
//		}
//		wait1Msec(1);
//	}
//	wait1Msec(20);
//	int last_err = 0;
//	TTimers temp_pid;
//	clearTimer(temp_pid);
//	while(1)
//	{
//		float para = 0.1;
//		int current_err = SensorValue[Gyro]-aim;
//		if(abs(last_err - current_err) < 10 || temp_pid > 200)
//		{
//			move(0,0);
//			break;
//		}
//		if(abs(current_err * para)>=pwr) output = pwr * sgn(current_err);
//		else output = current_err * para;

//		set_move_pwr(-output,output);
//		last_err = current_err;
//		wait1Msec(5);
//	}
//	lockmove = 0;
//}

//void manual_aids()
//{
//	/*if(getTaskState(Turn_Aids) == taskStateStopped)
//			lockmove = 0;
//	if(key_pwr_off)
//	{
//		lockclaw = 0;
//		lockmove = 0;
//		lockupdown = 0;
//		if(getTaskState(Turn_Aids) != taskStateStopped)
//			stopTask(Turn_Aids);
//	}
//	if(key_initialize_dir)
//	{
//		lockmove = 1;
//		startTask(Turn_Aids);
//	}*/
//}
