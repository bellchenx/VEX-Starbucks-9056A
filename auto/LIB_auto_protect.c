/*
int acc_adjust()
{
	float kp=1;
	float output;
	int err;
	int k_time;

	k_time=0;
	while(k_time<500)
	{
		err=0-SensorValue[Acc];
		output=kp*err;
		if(output>80)
			output=sgn(output)*80;

		Robot_Move(output,0,127,127,127);

		if(abs(err)<5)
		{
			Move_Stop();
			break;
		}
		wait1Msec(20);
		k_time+=20;
	}
	Move_Stop();

	if(abs(err)<5)
		return 1;
	else
		return 0;
}

task anti_slip_task()
{
	while(1)
	{
		if(abs(SensorValue[Acc])>300)//too much to adjust
		{
			StopTask(updown_hgt_hold_lock_task);
			StopTask(claw_open_agl_task);
			StopTask(UpDown_hgt_task);
			StopTask(claw_pwr_control_task);
			StopTask(autonomous);
			stop_all_motors();
			writeDebugStream("\n\nSlip!!!!auto stopped!!! acc:%d\n\n",SensorValue[Acc]);
		}
		else if(abs(SensorValue[Acc])>100)// adjust
		{
			writeDebugStream("\n\nacc pid adjust,auto stopped!!! acc:%d\n\n",SensorValue[Acc]);
			StopTask(updown_hgt_hold_lock_task);
			StopTask(claw_open_agl_task);
			StopTask(UpDown_hgt_task);
			StopTask(claw_pwr_control_task);
			StopTask(autonomous);
			stop_all_motors();
			acc_adjust();
		}
		else
		{}
		wait1Msec(20);
	}
}
*/
