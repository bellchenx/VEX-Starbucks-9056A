
task claw_control_task()
{
	clearTimer(T4);
	if(claw.dir==claw_dir_open)
		claw_func(pwr_claw_open);
	else
		claw_func(pwr_claw_close);

	while(1)
	{
		if(time1[T4] > 1500)
		{
			if(claw.dir==claw_dir_open)
				claw_func(pwr_claw_hold_open);
			else
				claw_func(pwr_claw_powerful_hold_close);
		}
		else
		{
			if(claw.dir==claw_dir_open)
				claw_func(pwr_claw_open);
			else
				claw_func(pwr_claw_close);
		}
		wait1Msec(claw_ctrl_time);
	}
}

void claw_handle()
{
	bool openhold = false;
	if(SensorValue[agl_claw] < 1350 && !encoderoff)
	{
		claw_func(25);
		openhold = true;
	}
	else if(SensorValue[agl_claw] < 1400 && !encoderoff)
	{
		claw_func(pwr_claw_hold_close);
		openhold = true;
	}
  if(key_claw_close  &&  !key_claw_open)//close
	{
		//claw_func(pwr_claw_close);
		claw.dir=claw_dir_close;
		startTask(claw_control_task);
	  lockclaw = 1;
		while(key_claw_close  &&  !key_claw_open)
		{
			manual_handle();
		}
		lockclaw = 0;
		stopTask(claw_control_task);
		//if(claw_keep)
		//	claw_func(pwr_claw_hold_close);
		//else
		claw_func(0);
		wait1Msec(10);
		claw_func(pwr_claw_hold_close);
	}
	else if(key_claw_open &&  !key_claw_close && SensorValue[agl_claw] >= 1400 && !encoderoff)//open
	{
		//claw_func(pwr_claw_open);
		claw.dir=claw_dir_open;
		//claw_keep = false;
		startTask(claw_control_task);
		lockclaw = 1;
		while(key_claw_open &&  !key_claw_close && SensorValue[agl_claw] >= 1400 && !encoderoff)
		{
			manual_handle();
		}
		lockclaw = 0;
		stopTask(claw_control_task);
		claw_func(0);
		wait1Msec(10);
		claw_func(pwr_claw_hold_open);
	}
	else if(key_claw_open &&  !key_claw_close && encoderoff)//open
	{
		//claw_func(pwr_claw_open);
		claw.dir=claw_dir_open;
		//claw_keep = false;
		startTask(claw_control_task);
		lockclaw = 1;
		while(key_claw_open &&  !key_claw_close)
		{
			manual_handle();
		}
		lockclaw = 0;
		stopTask(claw_control_task);
		claw_func(0);
		wait1Msec(10);
		claw_func(pwr_claw_hold_open);
	}
	else claw.dir=0;
	if(SensorValue[agl_claw] >= 1400 && !encoderoff && openhold)
	{
		claw_func(pwr_claw_hold_open);
		openhold = false;
	}
}
