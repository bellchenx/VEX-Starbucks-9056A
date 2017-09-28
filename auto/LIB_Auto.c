task autonomous()
{
	srand(nSysTime);
	writeDebugStream("******autonomous******\n");

	Self_Protect=0;

	pwr_off=0;
	auto_mode=1;

	stopTask(claw_control_task);
	stopTask(move_control_task);
	stopTask(move_protect_task);
	stopTask(updown_protect_task);

	//clr_updown();

	switch(Route)
	{
		case 1:auto_route_1();break;
		case 2:auto_route_2();break;
		case 3:auto_route_3();break;
		default: break;
	}

	while(1)
		wait1Msec(500);
	writeDebugStream("******end of autonomous******\n");
}

int blocking(int aim, int max_pwr, TTimers timer,int defend_time)
{
	//int hgt_delta = 50;
	int blind_area = 3;

	int err_now;
	int output;
	int kp = 5;

	long t0 = time1[timer];
	int defended = 0;

	while(time1[T4] < t0 + defend_time)
	{

		err_now = aim - SensorValue[enc_updown];

		if(abs(err_now) < blind_area)
			err_now = 0;

		output = err_now * kp;

		if(output < 7)
			output = 7;

		//
		if(output > max_pwr)
			output = max_pwr;
		//????
		if(err_now < -50)
			output = 0;

		if(time1[T4] > t0 + 500)
		{
			if(err_now > 3 && !defended)//???
			{
				defended = 1;
				claw_open_agl_FUNC_TASK(claw_closed, 100, T2, 1000, 10);
			}
		}

		updown_func(output);
		// writeDebugStream("%d %d\n", err_now, output);
		if(1)
		{
			if(err_now > 30)
				move(-30, 0);
			else
				move(-15, 0);
		}
		wait1Msec(10);
	}
	return defended;
}
