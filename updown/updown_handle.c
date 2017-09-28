void UpDown_handle()
{
	updown.chx_updown=vexRT[Ch2];
	updown.chx_updown=abs(updown.chx_updown)>15?updown.chx_updown:0;//dead area

	if(key_updown_hgt_change_to_higher)
		updown.updown_highest_hgt=updown_highest_hgt_special;
	else
		updown.updown_highest_hgt=updown_highest_hgt_normal;

	if(key_updown_hold)
	{
		pwr_off=0;
		updown.one_key_hgt_lock=0;
		stopTask(UpDown_hgt_task);
		updown_hgt_hold();
	}
	else if(updown.chx_updown>0)//up
	{
		stopTask(UpDown_hgt_task);
		pwr_off=0;
		if(encoderoff)
		{
			updown_func(updown.chx_updown*100/127);
		}
		if(!encoderoff)
		{
			if(SensorValue[enc_updown]>updown.updown_highest_hgt)
			{
				if(updown.updown_highest_hgt==updown_highest_hgt_special)
					updown_func(-5);
				else if(updown.spd_now > 35) updown_func(-15);
				else updown_func(-10);
			}
			else
			{
				if(SensorValue[enc_updown] < updown.updown_highest_hgt - 300)
				{
					if(updown.spd_now < 10)
					{
						updown_func(updown.chx_updown*60/127 + 20);
					}
					else if(updown.spd_now < 30)
					{
						updown_func(updown.chx_updown*75/127 + 20);
					}
					else if(updown.chx_updown > 80 && updown.spd_now < 40)
					{
						updown_func(110);
					}
				}
				else if(updown.spd_now > 60)
				{
					updown_func(updown.chx_updown*70/127);
				}
				else updown_func(updown.chx_updown*110/127);
			}
		}

	}
	else if(updown.chx_updown<0)
	{
		stopTask(UpDown_hgt_task);
		pwr_off=0;
		if(!encoderoff)
		{
			if(!updown_limitSor_pressed)
			{
				//else if(updown.chx_updown > -80) updown_func(updown.chx_updown*80/127 - 15);
				if(abs(updown.spd_now)< 8) updown_func(updown.chx_updown*100/127);
				else updown_func(updown.chx_updown *120/127);
			}
			else //pressed
			{
				SensorValue[enc_updown] = 0;
				updown_keep_lowest();
			}
		}
		if(encoderoff)
		{
			if(updown_limitSor_pressed)
			{
				updown_keep_lowest();
				SensorValue[enc_updown] = 0;
			}
			else updown_func(updown.chx_updown/127*105);
		}
	}
	else//updown.chx_updown=0
	{
		//	if(updown.one_key_hgt_lock)//one_key_hgt_lock
		//		return;
		if(updown_limitSor_pressed)
			SensorValue[enc_updown] = 0;
		if(!encoderoff)
		{
			if(SensorValue[enc_updown]>updown.updown_highest_hgt)
				updown_func(-9);
			else
				updown_func(0);
		}
		if(encoderoff) updown_func(0);
	}
	if(key_pwr_off)  // updown pwr off
	{
		updown_func(0);
		claw_func(0);
		Move_Stop();
		pwr_off=1;
	}
}
