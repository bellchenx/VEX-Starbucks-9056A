
#define LCD_Btn_Left    0b001 //1
#define LCD_Btn_Center  0b010 //2
#define LCD_Btn_Right   0b100 //4
#define LCD_Btn_Pressed( btn )  (  (nLCDButtons & (btn) )!=0  )

#define LCD_wait_for_press(btn)      { while( ! LCD_Btn_Pressed( btn ) ) {wait1Msec(5);} }
#define LCD_wait_for_release(btn)    { while(   LCD_Btn_Pressed( btn ) ) {wait1Msec(5);} }

#define LCD_while_not_pressing(btn)   while(! LCD_Btn_Pressed( btn ) )  // no ;   here
#define LCD_while_pressing(btn)       while(  LCD_Btn_Pressed( btn ) )  // no ;   here

void LCD_Clear()  {clearLCDLine(0);clearLCDLine(1);}


task disp_logo()
{
	string str;
	while(1)
	{
		LCD_Clear();
		displayLCDCenteredString(0,RT);
		displayLCDCenteredString(1,RT_Logo);

		wait1Msec(500);
		bLCDBacklight=!bLCDBacklight;

		//field choose
		if(LCD_Btn_Pressed(LCD_Btn_Center))
		{
			LCD_Clear();
			bLCDBacklight=true;
			LCD_while_pressing(LCD_Btn_Center)
			{
				if(1) //normal
				{
					wait1Msec(100);
					LCD_Clear();
					sprintf(str,"bat:%d",nImmediateBatteryLevel);
					displayLCDCenteredString(0,str);
				}
				////////////
				if( LCD_Btn_Pressed(LCD_Btn_Left) )//left field
				{
					LCD_Clear();
					FIELD=Field_Left;
					sprintf(str,"FIELD:left");
					displayLCDCenteredString(0,str);
					LCD_wait_for_release(LCD_Btn_Left);
				}
				////////////
				if( LCD_Btn_Pressed(LCD_Btn_Right) )//right field
				{
					LCD_Clear();
					FIELD=Field_Right;
					sprintf(str,"FIELD:Right");
					displayLCDCenteredString(0,str);
					LCD_wait_for_release(LCD_Btn_Right);
				}
				////////////
			}
		}//center

		////////
		if(LCD_Btn_Pressed(LCD_Btn_Left)) //route choose
		{
			LCD_Clear();
			bLCDBacklight=true;
			LCD_while_pressing(LCD_Btn_Left)
			{
				if(1)
				{
					sprintf(str,"G%d UD%d MR%d",SensorValue[Gyro],SensorValue[enc_updown],SensorValue[enc_moveR]);
					displayLCDCenteredString(0,str);
					sprintf(str,"G%d C%d",SensorValue[Gyro],SensorValue[agl_claw]);
					displayLCDCenteredString(1,str);
					wait1Msec(100);
				}

				////////////////
				if(LCD_Btn_Pressed(LCD_Btn_Center))//route choose
				{
					LCD_Clear();
					Route++;
					if(Route > 3)
						Route = 1;

					sprintf(str,"Route:%d ",Route);
					displayLCDCenteredString(0,str);
					LCD_wait_for_release(LCD_Btn_Center);
				}

				/////////////////////
				if(LCD_Btn_Pressed(LCD_Btn_Right))//gyro reset
				{
					LCD_Clear();
					clr_gyro();
					angle=0;
					sprintf(str,"Reset finished");
					displayLCDCenteredString(0,str);



					sprintf(str,"gyro:%d",SensorValue[Gyro]);
					displayLCDCenteredString(1,str);

					LCD_wait_for_release(LCD_Btn_Right);
				}
			}
		}//sensor


		if(LCD_Btn_Pressed(LCD_Btn_Right))
		{
			LCD_Clear();
			bLCDBacklight=true;
			LCD_while_pressing(LCD_Btn_Right)
			{
				if(FIELD==Field_Left)
					sprintf(str,"FIELD:Left");
				if(FIELD==Field_Right)
					sprintf(str,"FIELD:Right");
				displayLCDCenteredString(0,str);
				///////////
				if(Route==1)
				{
					if(AutoRoute_1_where_to_throw==-1)
						sprintf(str,"Route:%d back",Route);
					if(AutoRoute_1_where_to_throw==0)
						sprintf(str,"Route:%d center",Route);
					if(AutoRoute_1_where_to_throw==1)
						sprintf(str,"Route:%d forward",Route,);
				}
				else
					sprintf(str,"Route:%d ",Route);
				displayLCDCenteredString(1,str);
			}
		}// auto that have been chosen
	}
}
