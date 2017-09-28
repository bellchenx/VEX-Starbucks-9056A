

//void updown_one_key_up()
//{
//	pwr_off=0;
//	updown.agl_val=SensorValue[enc_updown];
//	if(updown.agl_val>updown.updown_highest_hgt)//speed down: 1
//	{
//		if(updown.spd_now<120)//throw heavey stars,speed too low
//		{
//			if(updown.agl_val<updown.updown_highest_hgt+300)//more angle for throwing
//			{
//				updown_func(30);
//				if(0) writeDebugStream("highest: too slow\n");
//			}
//			else
//				updown_func(-7);
//		}
//		else if(updown.spd_now>150)//slowly speed down
//			updown_func(-8);
//		else
//			updown_func(-7);
//		if(0) writeDebugStream("d1:%d %d %.3f\n",updown.agl_val,updown.spd_now,updown.pwr);
//	}
//	else if(updown.agl_val>updown.updown_highest_hgt-100)//speed down:2
//	{
//		updown.updown_spd_aim=140;

//		if(updown.updown_spd_aim-updown.spd_now>0)
//		{
//			updown.pwr_temp=3*(updown.updown_spd_aim-updown.spd_now);
//			if(updown.pwr_temp>70)
//				updown_func( 70 );
//			else
//				updown_func( updown.pwr_temp );
//		}
//		else
//			updown_func( 35 );
//		if(0) writeDebugStream("d2:%d %d %.3f\n",updown.agl_val,updown.spd_now,updown.pwr);
//	}
//	else if(updown.agl_val>updown.updown_highest_hgt-200)//speed down:3
//	{
//		updown.updown_spd_aim=160;
//		if(updown.updown_spd_aim-updown.spd_now>0)
//		{
//			updown.pwr_temp=2.3*(updown.updown_spd_aim-updown.spd_now);
//			if(updown.pwr_temp>70)
//				updown_func( 70 );
//			else
//				updown_func( updown.pwr_temp );
//		}
//		else
//			updown_func( 45 );
//		if(0) writeDebugStream("d3:%d %d %.3f\n",updown.agl_val,updown.spd_now,updown.pwr);
//	}
//	else if(updown.agl_val>updown_lowest_hgt+600)//speed up:3
//	{
//		if(updown.spd_now>150)//throw one star
//			updown_func(70);
//		else//throw pillow
//			updown_func(72);
//		if(0) writeDebugStream("u3:%d %d %.3f\n",updown.agl_val,updown.spd_now,updown.pwr);
//	}
//	else if(updown.agl_val>updown_lowest_hgt+100)//speed up:2
//	{
//		updown_func(55);
//		if(0) writeDebugStream("u2:%d %d %.3f\n",updown.agl_val,updown.spd_now,updown.pwr);
//	}
//	else                                         //speed up:1
//	{
//		updown_func(35);
//		if(0) writeDebugStream("u1:%d %d %.3f\n",updown.agl_val,updown.spd_now,updown.pwr);
//	}
//}


task updown_one_key_throw_task()
{
	bool clawstart = false;
	long tim0=time1[T4];
	writeDebugStream("one_key_throw!\n");
	while(1)
	{
		//updown_one_key_up();
		updown_func(100);
		if(SensorValue[enc_updown]>updown_highest_hgt_normal)
		{
			writeDebugStream("throw:%d\n",SensorValue[enc_updown]);
			break;
		}
		if(SensorValue[enc_updown] > updown.throw_delta && !clawstart)
			clawstart = true;
		if(SensorValue[enc_updown] > updown.throw_delta && clawstart)
		{
			claw_open_agl_FUNC_TASK(claw_open_to_throw, 100, T_task_claw, 1000, -11);
			clawstart = false;
		}
		if(time1[T4]>tim0+2500)
		{
			writeDebugStream("throw: time out  %d %d\n",tim0,time1[T4]);
			break;
		}
	}
	updown_func(-7);
}

//void wait_for_throw()
//{
//	while(getTaskState(updown_one_key_throw_task)!=taskStateStopped)
//		wait1Msec(5);
//}
