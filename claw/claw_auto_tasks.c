#define claw_Pwr_Lock -10

#define claw_init_delta 0

typedef struct
{
	int aim;
	int max_spd;
	int lock_pwr;

	int exit_time;
	TTimers timer;
} claw_task_Struct;

typedef enum claw_agl_Types
{
	claw_closed                    = 3820+claw_init_delta,
	claw_push_mid_stars            = 2000+claw_init_delta,    //updown = 1650
	claw_get_pillows               = 2550+claw_init_delta,
	claw_normal                    = 3400+claw_init_delta,

	claw_push_sides_stars          = 2300+claw_init_delta,    //updown = 2500
	claw_widest_open               = 1850+claw_init_delta,
	claw_get_stars_by_the_wall     = 3000+claw_init_delta,
	claw_open_to_throw             = 2500+claw_init_delta,

	claw_open_to_get_two_stars_corner         = 2800+claw_init_delta,
	claw_close_to_take_off_stars_on_the_fence = 3500+claw_init_delta,
	claw_close_to_get_two_stars_corner        = 3500+claw_init_delta,
	claw_close_to_get_pillow                  = 3300+claw_init_delta,

} claw_agl_Types;

claw_task_Struct claw_task;

task claw_open_agl_task()
{
	int Err=0;
	int temp;
	int output;
	int dir;


	clearTimer(claw_task.timer);

	if(SensorValue[agl_claw]>claw_task.aim)
		dir=-1;
	else
		dir=1;

	claw_func(claw_task.max_spd*dir);


	while(1)
	{
		temp=SensorValue[agl_claw];
		////////////////////////////////////////// RightEncoder Ctrl Distance
		Err=claw_task.aim-temp;

		if(abs(Err)<10) Err=0;

		output=0.8*Err;

		if(abs(output)>claw_task.max_spd)
			output=sgn(output)*claw_task.max_spd;

		claw_func(output);



		//exit
		if( Err==0 )
		{
			writeDebugStream("claw:OK aim:%d, final:%d T:%d\n",claw_task.aim,SensorValue[agl_claw],time1[claw_task.timer]);
			break;
		}

		if(time1[claw_task.timer]>claw_task.exit_time)
		{
			writeDebugStream("TYPE:1 claw: time out aim:%d, final:%d T:%d\n",claw_task.aim,SensorValue[agl_claw],time1[claw_task.timer]);
			break;
		}

		if(dir==-1 && temp<claw_task.aim)
		{
			writeDebugStream("claw: angle out aim:%d, final:%d T:%d\n",claw_task.aim,SensorValue[agl_claw],time1[claw_task.timer]);
			break;
		}
		if(dir==1 && temp>claw_task.aim)
		{
			writeDebugStream("claw: angle out aim:%d, final:%d T:%d\n",claw_task.aim,SensorValue[agl_claw],time1[claw_task.timer]);
			break;
		}
		wait1Msec(10);
	}//while
	claw_func(-10);//lock
}

//
void claw_open_agl_FUNC_TASK(claw_agl_Types agl,int spd_max,TTimers Timer_x,int time,int lock_pwr=-7)
{
	if(slip)
		return;

	claw_task.aim=agl;
	claw_task.max_spd=spd_max;
	claw_task.lock_pwr=lock_pwr;

	claw_task.timer=Timer_x;
	claw_task.exit_time=time;
	stopTask(claw_control_task);
	startTask(claw_open_agl_task);
}


void wait_for_claw_OK()
{
	while(getTaskState(claw_open_agl_task)!=taskStateStopped)
		wait1Msec(5);
}
