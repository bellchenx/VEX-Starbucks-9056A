bool safemode = false;
word pre_special_key;
task usercontrol()
{
	auto_mode=0;

	stopTask(claw_open_agl_task);
	stopTask(UpDown_hgt_task);
	stopTask(autonomous);

	stop_all_motors();

	startTask(para_calc_task);
	startTask(disp_logo);
	startTask(updown_protect_task);
	if(startantislip) startTask(move_control_task);
	startTask(move_protect_task);

	while(1)
	{
		manual_handle();
	}
}
void specialkeyfunc()
{
	if(key_special_key && !pre_special_key)
	{
		if(safemode) // change to normal mode
		{
			encoderoff = false;
			nVolume = 100;
			warning_func(2,800);
			nVolume = 80;
			safemode = false;
			if(getTaskState(updown_protect_task) == taskStateStopped)
				startTask(updown_protect_task);
			if(getTaskState(move_protect_task) == taskStateStopped)
				startTask(move_protect_task);
			if(startantislip && getTaskState(move_control_task) == taskStateStopped)
				startTask(move_control_task);
		}
		else if(!safemode)// change to safe mode
		{
			encoderoff = true;
			nVolume = 100;
			warning_func(3,1000);
			nVolume = 80;
			safemode = true;
		}
	}
	if(safemode)
	{
		if(getTaskState(updown_protect_task) != taskStateStopped)
			stopTask(updown_protect_task);
		if(getTaskState(move_protect_task) != taskStateStopped)
			stopTask(move_protect_task);
		if(getTaskState(move_control_task) != taskStateStopped)
			stopTask(move_control_task);
	}
	pre_special_key = key_special_key;
}
void manual_handle()
{
	if(lockmove == 0) RT_MOVE();
	if(lockupdown == 0) UpDown_handle();
	if(lockclaw == 0) claw_handle();

	ZHUANGBI();
	specialkeyfunc();
}
