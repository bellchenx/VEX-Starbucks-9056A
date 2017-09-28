
void Choose_Field_Role_Route()
{
	string str;

	bLCDBacklight=true;
	LCD_Clear();

	bLCDBacklight=true;
	LCD_Clear();
	displayLCDString(0, 0,"Choosing Field");
	if(FIELD==Field_Right)
		displayLCDString(1, 0,"FIELD:Right");
	else
		displayLCDString(1, 0,"FIELD:Left ");
	while_pressing( key_field_choose)
	{
		if(key_field_left)
		{
			displayLCDString(1, 0,"FIELD:Left ");
			FIELD=Field_Left;
		}
		if(key_field_right)
		{
			displayLCDString(1, 0,"FIELD:Right");
			FIELD=Field_Right;
		}
		wait1Msec(50);
	}
	/////////////////////////////////////////////////////
	///////////////////////////////
	LCD_Clear();
	bLCDBacklight=true;
	displayLCDString(0, 0, "Choosing Route");
	sprintf(str,"Route:%d",Route);
	displayLCDString(1, 0, str);

	wait_for_press( key_route_choose);
	while_pressing( key_route_choose)
	{
		if(key_route_1)
			Route=1;
		if(key_route_2)
			Route=2;
		if(key_route_3)
			Route=3;
		if(key_route_4)
			Route=4;

		sprintf(str,"Route:%d",Route);
		displayLCDString(1, 0, str);

		wait1Msec(50);
	}
}

void choose_all()
{
	string lcd_str;
	string str_field;
	string str_route;
		if( 1 )
	{
		bLCDBacklight=true;
		LCD_Clear();
		displayLCDString(0,0,"ChooseStart");
		while( vexRT[Btn7R]|| vexRT[Btn7L] ){};
		Choose_Field_Role_Route();
	}

	bLCDBacklight=true;
	if( ! skip_preauto)
	{
		LCD_Clear();
		///////////
		if(FIELD==Field_Left)
			sprintf(str_field,"Left");
		if(FIELD==Field_Right)
			sprintf(str_field,"Right");
		///////////
		sprintf(str_route,"Route:%d",Route);
		/////////////
		displayLCDString(0, 0, str_field);
		displayLCDString(0, 6, str_route);
		displayLCDString(1, 0,"wait Gyro Reset");

		while_not_pressing( key_gyro_reset )
		{
			bLCDBacklight=!bLCDBacklight;
			wait1Msec(250);
		}

		wait1Msec(400);
		LCD_Clear();
		bLCDBacklight=(bool)1;
		sprintf(lcd_str,"Gyro Reset");
		displayLCDString(0, 0, lcd_str);
		wait_for_release(key_gyro_reset);
		SensorValue[Gyro]=0;
	}
}
