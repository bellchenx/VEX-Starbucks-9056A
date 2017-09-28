

#define max_lock_pwr 10
#define min_lock_pwr 7

typedef struct
{
	int     aim;
	int     err_now;
	int     err_last;
	int     value_now;
	int     ii;
	int     dd;
	int     output;
} Updown_lock_Struct;

Updown_lock_Struct Updown_lock;

//task updown_hgt_hold_lock_task()
//{
//	float   kp=     0.05;
//	float   ki=      0;
//	float   kd=      0;

//	Updown_lock.ii=0;

//	//if( updown_task.lock_pwr!=127 )
//	//{
//	//	Updown_lock.aim=SensorValue[agl_UpDown];
//	//}
//	//else
//	//	updown_task.lock_pwr=-127;////lock aim passed by UpDown_hgt_task();      used lock pwr

//	wait1Msec(500);
//	Updown_lock.aim=SensorValue[enc_updown];
//	while(1)
//	{
//		Updown_lock.value_now=SensorValue[enc_updown];
//		Updown_lock.err_now=Updown_lock.aim-Updown_lock.value_now;

//		if(abs(Updown_lock.err_now)<3)
//			Updown_lock.err_now=0;

//		if(abs(Updown_lock.err_now)<35)
//			Updown_lock.ii+=Updown_lock.err_now;

//		Updown_lock.dd=Updown_lock.err_now-Updown_lock.err_last;

//		Updown_lock.output=kp*Updown_lock.err_now+ki*Updown_lock.ii+kd*Updown_lock.dd;


//		if(abs(Updown_lock.output)>=max_lock_pwr)
//			Updown_lock.output=sgn(Updown_lock.output)*max_lock_pwr;
//		if(abs(Updown_lock.output)<=min_lock_pwr)
//			Updown_lock.output=sgn(Updown_lock.output)*min_lock_pwr;

//		updown_func(Updown_lock.output);

//		Updown_lock.err_last=Updown_lock.err_now;

//		wait1Msec(20);
//	}
//}
