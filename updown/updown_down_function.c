
void updown_keep_lowest()
{
	//writeDebugStream("KEEP\n");
	updown_func(-17);
}


void updown_one_key_down()
{
	updown.agl_val=SensorValue[enc_updown];
	if(!updown_limitSor_pressed)
	{
		updown_func(-120);
	}
	else
	{
		SensorValue[enc_updown] = 0;
		updown_keep_lowest();
	}
}

task updown_one_key_down_task()
{
	while(SensorValue[hgt_limit]==1)
	{
		updown_one_key_down();
	}
	updown_func(-17);
}
