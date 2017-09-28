///////////////////////////////////////////////////////////////////////////////////////
void move_auto_func(int EndL, int EndR, int dir, int Pwr_ABS_max, int Exit_Time,TTimers Timer_x,int brake)
{
	if(dir == -1)
	{
		int swap = EndL;
		EndL = EndR;
		EndR = swap;
	}
	if(dir == -1 || dir == 1)
		clr_enc();

	int tempL, tempR;
	int initialL = SensorValue[enc_moveL], initialR = SensorValue[enc_moveR];
	//int goL, goR;
	int pwrL, pwrR;

	if(slip)
		return;

	clearTimer(Timer_x);

	if(SensorValue[enc_moveL] < EndL)
	{
		if((EndL-initialL+EndR-initialR) == 0)
			pwrL = Pwr_ABS_max * abs(EndL - initialL + 1)/abs(EndL-initialL+EndR-initialR + 1)*2;
		else
			pwrL = Pwr_ABS_max * abs(EndL - initialL)/abs(EndL-initialL+EndR-initialR)*2;
	}
	else if(SensorValue[enc_moveL] > EndL)
	{
		if((EndL-initialL+EndR-initialR) == 0)
			pwrL = -Pwr_ABS_max * abs(EndL - initialL + 1)/abs(EndL-initialL+EndR-initialR + 1)*2;
		else
			pwrL = -Pwr_ABS_max * abs(EndL - initialL)/abs(EndL-initialL+EndR-initialR)*2;
	}
	else pwrL = 0;

	if(SensorValue[enc_moveR] < EndR)
	{
		if((EndL-initialL+EndR-initialR) == 0)
			pwrR = Pwr_ABS_max * abs(EndR - initialR + 1)/abs(EndL-initialL+EndR-initialR + 1)*2;
		else
			pwrR = Pwr_ABS_max * abs(EndR - initialR)/abs(EndL-initialL+EndR-initialR)*2;
	}
	else if(SensorValue[enc_moveR] > EndR)
	{
		if((EndL-initialL+EndR-initialR) == 0)
			pwrR = -Pwr_ABS_max * abs(EndR - initialR + 1)/abs(EndL-initialL+EndR-initialR + 1)*2;
		else
			pwrR = -Pwr_ABS_max * abs(EndR - initialR)/abs(EndL-initialL+EndR-initialR)*2;
	}
	else pwrR = 0;

	if(abs(pwrL) > 120) pwrL = 120*sgn(pwrL);
	if(abs(pwrR) > 120) pwrR = 120*sgn(pwrR);

	set_move_pwr(pwrL, pwrR);

	writeDebugStream("START____forward:start PwrL:%d PwrR:%d SpeedL:%d SpeedR:%d T:%d \n",pwrL,pwrR,moveL_spd,moveR_spd,time1[Timer_x]);
	/*
	wait1Msec(150);
	while(1)
	{
		tempL=SensorValue[enc_moveL];
		tempR=SensorValue[enc_moveR];
		goL=tempL - initialL;
		goR=tempR - initialR;

		double ratio_dis;
		if(EndR-goR == 0) ratio_dis = (EndL-goL + 1)/(EndR-goR + 1);
		else ratio_dis = (EndL-goL)/(EndR-goR);

		double ratio_speed;
		if(moveR_spd == 0)	ratio_speed = (moveL_spd + 1)/(moveR_spd + 1);
		else ratio_speed = moveL_spd/moveR_spd;

		if(time1[Timer_x]>Exit_Time)
		{
			writeDebugStream("forward:time-out aimL:%d, finalL:%d aimR:%d, finalR:%d T:%d \n",EndL,tempL,EndR,tempR,time1[Timer_x]);
			break;
		}
		if(abs(ratio_dis - ratio_speed) < 0.005 && sgn(PwrL- PwrR) == sgn(moveL_spd - moveR_spd)
		{
			writeDebugStream("OK____forward:adjust speed OK PwrL:%d PwrR:%d SpeedL:%d SpeedR:%d T:%d \n\n",PwrL,PwrR,moveL_spd,moveR_spd,time1[Timer_x]);
			break;
		}
		else
		{
			pwrL *= 1.05;
			pwrR *= 0.95;
			set_move_pwr(pwrL, pwrR);
			writeDebugStream("forward:speed adjusting PwrL:%d PwrR:%d SpeedL:%d SpeedR:%d T:%d \n",PwrL,PwrR,moveL_spd,moveR_spd,time1[Timer_x]);
		}
		wait1Msec(50);
	}
	*/
	while(1)
	{
		tempL=SensorValue[enc_moveL];
		tempR=SensorValue[enc_moveR];

		if(time1[Timer_x]>Exit_Time )
		{
			writeDebugStream("forward:time-out aimL:%d, finalL:%d aimR:%d, finalR:%d T:%d \n",EndL,tempL,EndR,tempR,time1[Timer_x]);
			break;
		}
		if(abs(tempL-EndL)<10 || abs(tempR-EndR)<10)
		{
			writeDebugStream("OK____forward:OK aimL:%d, finalL:%d aimR:%d, finalR:%d T:%d \n\n\n",EndL,tempL,EndR,tempR,time1[Timer_x]);
			break;
		}
	//	if(abs(tempL-EndL) < 10) PwrL *= 0.5;
	//	if(abs(tempR-EndR) < 10) PwrR *= 0.5;

		if(abs(pwrL) > 120) pwrL = 120*sgn(pwrL);
		if(abs(pwrR) > 120) pwrR = 120*sgn(pwrR);
		set_move_pwr(pwrL, pwrR);
		wait1Msec(5);
	}
	//after break;
	if(brake==BRAKE)
	{
		if(Pwr_ABS_max > 40)
		{
			pwrL = -0.5*moveL_spd;
			pwrR = -0.5*moveR_spd;
			set_move_pwr(pwrL, pwrR);
			wait1Msec(150);
		}
	}
	Move_Stop();
}

void Forward_Dist(int Enc_tick, int Pwr_ABS,int turn, int Exit_Time,TTimers Timer_x,int brake)
{
	Enc_tick=Enc_tick/1.5;
	int temp;
	int dir=1;

	if(slip)
		return;

	clearTimer(Timer_x);

	if(SensorValue[enc_moveL]<= Enc_tick )
	{
		move(Pwr_ABS,turn);
		dir=1;
	}
	else
	{
		move(-Pwr_ABS,turn);
		dir=-1;
	}


	while(1)
	{
		temp=SensorValue[enc_moveL];

		if(time1[Timer_x]>Exit_Time )
		{
			writeDebugStream("****forward:time-out aim:%d, final:%d T:%d \n",Enc_tick,temp,time1[Timer_x]);
			break;
		}
		if(abs(temp-Enc_tick)<10)
		{
			writeDebugStream("****forward: OK aim:%d, final:%d T:%d\n",Enc_tick,temp,time1[Timer_x] );
			break;
		}
		wait1Msec(5);
	}
	//after break;
	if(brake==BRAKE)
	{
		if(Pwr_ABS>50)
		{
			move(-dir*20,0);
			wait1Msec(150);
		}
		else
		{
				move(-dir*15,0);
			wait1Msec(150);
		}
	}
	Move_Stop();
}

//void Forward_PID_Straight_Dist_Gyro(int Enc_tick,int aim_gyro, int Pwr_ABS,int Exit_Time,TTimers Timer_x )
//{
//	int dir;
//	float kp_enc=0.2, ki_enc=0.00005;
//	int Intergral_enc=0;

//	float kp_gyro=0.4,ki_gyro=0.005;
//	int Intergral_gyro=0;

//	int temp_enc,temp_gyro;

//	int err_gyro,err_enc;

//	int output_gyro,output_enc;

//	ClearTimer(Timer_x);

//	if(SensorValue[enc_moveL]>Enc_tick )
//		dir=-1;
//	else
//		dir=1;

//	while(1)
//	{
//		if(time1[Timer_x]>Exit_Time )
//		{
//			writeDebugStream("--ST forward PID:time-out T:%d ,",time1[Timer_x]);
//			break;
//		}
//		//////////enc PID

//		temp_enc=SensorValue[enc_moveL];
//		err_enc=Enc_tick-temp_enc;

//		if(abs(err_enc)>450)
//			output_enc=dir*Pwr_ABS;
//		else if(abs(err_enc)>250)
//			output_enc=dir*Pwr_ABS/4;
//		else if(abs(err_enc)>100)
//			output_enc=dir*Pwr_ABS/8;
//		else	//pid adjust <100
//		{
//			if(abs(err_enc)<10)
//			{
//				break;//
//				err_enc=0;
//			}

//			if(abs(err_enc)<50)
//				Intergral_enc+=err_enc;

//			output_enc=kp_enc*err_enc+ki_enc*Intergral_enc;

//			if(abs(output_enc)<5)
//				output_enc=sgn(output_enc)*5;
//		}
//		////////////// gyro PID
//		temp_gyro=SensorValue[Gyro];

//		err_gyro=aim_gyro-temp_gyro;

//		if(abs(err_gyro)<3)
//			err_gyro=0;

//		if(abs(err_gyro)<15)
//			Intergral_gyro+=err_gyro;

//		output_gyro=kp_gyro*err_gyro+ki_gyro*Intergral_gyro;

//		////////// ////////////////output all
//		move(output_enc,output_gyro);
//		/////////
//		wait1Msec(5);
//	}//end of while(1)
//	Move_Stop();
//	writeDebugStream("--ST forward PID:aim_enc:%d, final_enc:%d,  aim_gyro:%d, final_gyro:%d\n",Enc_tick,SensorValue[enc_moveL],aim_gyro,SensorValue[Gyro]);
//}
