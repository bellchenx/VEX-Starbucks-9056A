

void updown_func(int output )
{
	if(pwr_off)
		return;

	motor[mtr_UpD_R_D]=output;
	motor[mtr_UpD_L_U]=output;
	motor[mtr_UpD_R_U]=output;
	motor[mtr_UpD_L_D]=output;

	updown.pwr=output;
}


void updown_hgt_hold()
{
	updown.chx_updown=vexRT[Ch2];
	updown.chx_updown=abs(updown.chx_updown)>20?updown.chx_updown:0;//dead area


	if(key_updown_hgt_change_to_higher)
	{
		updown_func(20);
		return;
	}

	if(updown.chx_updown == 0)
	{
		updown_func(-7);
	}
	else if(updown.chx_updown < 0)
	{
		if(updown_limitSor_pressed) updown_keep_lowest();
		else updown_func(updown.chx_updown/127*105);
	}
	else if(SensorValue[enc_updown] > updown_highest_hgt_normal)
	{
		updown_func(updown.chx_updown/127.0*50+ 20);
	}
	else
	{
		updown_func(updown.chx_updown/127*100);
	}
}

//////////////
