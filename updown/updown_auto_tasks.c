
typedef struct
{
	int aim;
	int max_spd;
	int dir;
	int lock_pwr;
	int ok;

	int exit_time;
	TTimers timer;
} updown_task_Struct;

updown_task_Struct updown_task;

////////////////////////////////////////////////////////////
task UpDown_hgt_task()
{
	int temp,Err;

	clearTimer(updown_task.timer);
	temp=SensorValue[enc_updown];
	//writeDebugStream("\n %d",temp);

		if(temp>updown_task.aim)///dir
			updown_task.dir=-1;
		if(temp<=updown_task.aim)///dir
			updown_task.dir=1;
	//else
	updown_func( updown_task.dir* updown_task.max_spd);

	while(1)
	{
		temp=SensorValue[enc_updown];

		////////////////////////////////////////// RightEncoder Ctrl Distance
		Err=updown_task.aim-temp;

		if(abs(Err)<10)
			Err=0;

		//exit
		if( updown_task.dir==1 )
		{
			if( Err==0 || temp>=updown_task.aim )
			{
				updown_task.ok=1;
				writeDebugStream("updown:OK aim: %d, final:%d T:%d\n",updown_task.aim,SensorValue[enc_updown],time1[updown_task.timer]);
				break;
			}
		}

		if( updown_task.dir==-1 )
		{
			if( Err==0 || temp<=updown_task.aim )
			{
				updown_task.ok=1;
				writeDebugStream("updown:OK aim:%d, final:%d T:%d\n",updown_task.aim,SensorValue[enc_updown],time1[updown_task.timer]);
				break;
			}
		}

		if(time1[updown_task.timer]>updown_task.exit_time)
		{
			writeDebugStream("updown: time out aim:%d, final:%d T:%d\n",updown_task.aim,SensorValue[enc_updown],time1[updown_task.timer]);
			break;
		}
		wait1Msec(10);
	}//while
	updown_func(updown_task.lock_pwr);
}

//void UpDown_hgt_FUNC_TASK(updown_hgt_Types height,int spd_max,TTimers Timer_x,int time,int hgt_lock,int updown_dir=0);

void UpDown_hgt_FUNC_TASK(updown_hgt_Types height,int spd_max,TTimers Timer_x,int time,int lock_pwr)
{
	if(slip)
		return;

	updown_task.aim=height;
	updown_task.max_spd=spd_max;
	updown_task.timer=Timer_x;
	updown_task.exit_time=time;
	updown_task.lock_pwr=lock_pwr;
	updown_task.ok=0;
	startTask(UpDown_hgt_task);
}
/////////////////
void wait_for_hgt_task_ok()
{
	while(1)
	{
		if( getTaskState(UpDown_hgt_task)==taskStateStopped )
			break;
		wait1Msec(5);
	}
}
/////////////////
void wait_for_lowest_OK(int max_time=0) //max_time:0 wait until task completed
{
	int t_start=time1[T4];

	if(max_time!=0)
	{
		while(SensorValue[hgt_limit]!=0|| time1[T4]<(max_time+t_start) )
			wait1Msec(5);
	}
	else
	{
		while(SensorValue[hgt_limit]!=0)
		{
			wait1Msec(5);
		}
	}
}
