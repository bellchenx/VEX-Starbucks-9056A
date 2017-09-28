#define dead_k 7
#define updown_speed_dead 5

int initial_chx;

int power_down()
{
	if(key_updown_hold) return 0;
	if(pwr_off)
	{
		updown_func(0);
		return 0;
	}
	if(updown.chx_updown >= 0) return 0;

	if( updown.chx_updown < 0 )
		if(SensorValue[enc_updown] < updown_lowest_hgt + 600)
			if(abs(updown.spd_now) < updown_speed_dead)
			{
				if(lockupdown == 0 && abs(motor[mtr_UpD_L_U]) >= 18)
					return 1;
				if(lockupdown == 1)
				{
					if(abs(initial_chx-vexRT[Ch2]) > 1) return 0;
					else if(abs(vexRT[Ch2]) < 80) return 1;
					else return 0;
				}
			}
	return 0;
}
int might_be_dead()
{
	if(key_updown_hold) return 0; ///DEBUG
	if(pwr_off)
		return 0;

	if(power_down() == 1) return 0;

	if(abs(motor[mtr_UpD_L_U])>15 && updown.spd_now<updown_speed_dead && updown.chx_updown > 0)
		return 1;
	return 0;
}

void updown_protect_ctrl()
{
	if(!key_updown_hold)
		updown_func(0);
	else
	{
		if(updown.chx_updown<0)
			updown_func(-10);
		else if(updown.chx_updown>0)
			updown_func(11);
		else
			updown_func(0);
	}
}


task updown_protect_task()
{
	updown.dead_times=0;
	updown.is_protceted=0;
	lockupdown = 0;
	while( 1 )
	{
		if( power_down()  == 1)
		{
			while(1)
			{
				if( power_down()  == 1)//still dead
				{
						updown.dead_times++;
						initial_chx = vexRT[Ch2];
				}
				else
				{
					updown.dead_times=0;
					updown.is_protceted=0;
					lockupdown = 0;
					break;
				}
				if(updown.dead_times>=8)//dead for too long
				{

					//protect updown
					updown.is_protceted=1;
					lockupdown = 1;
					writeDebugStream("updown power down\n");
				  if(updown.dead_times == 8) warning_func(1,233);

				  updown_func(-18);
					//resume updown

				}
				wait1Msec(100);
			}
		}


		if( might_be_dead())
		{
			//continuous check dead or not
			while(1)
			{
				if( might_be_dead()  )//still dead
					updown.dead_times++;
				else 																				//alive again
				{
					updown.dead_times=0;
					updown.is_protceted=0;
					lockupdown = 0;
					break;
				}

				if(updown.dead_times==dead_k)//dead for too long
				{
					//protect updown
					updown.is_protceted=1;
					lockupdown = 1;
					writeDebugStream("updown dead\n");

					updown_protect_ctrl();
				  playTone(233,50);
					wait1Msec(1000);

					//resume updown
					updown.is_protceted=0;
					updown.dead_times=0;
					lockupdown = 0;
				}
				wait1Msec(100);//dead checking period
			}
		}
		else
		{
			updown.dead_times=0;
			lockupdown = 0;
			updown.is_protceted=0;
		}
		wait1Msec(50);//normal checking period
	}
}
