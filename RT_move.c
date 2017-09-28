int moveR_previous = 0;
int moveL_previous = 0;
int gyro_previous = 0;
int angleR = 0;
int angleL = 0;
//int one_round = 1350;

task para_calc_task()
{
	while(1)
	{
		//calculate duration
		wait1Msec(50);

		//move speed calculate
		moveL_spd = SensorValue[enc_moveL] - moveL_previous;
		moveR_spd = SensorValue[enc_moveR] - moveR_previous;
		moveL_previous = SensorValue[enc_moveL];
		moveR_previous = SensorValue[enc_moveR];

		claw.dist_now=SensorValue[agl_claw];
		claw.spd_now=claw.dist_now-claw.dist_last;
		claw.dist_last=claw.dist_now;

		updown.dist_now=SensorValue[enc_updown];
		updown.spd_now=updown.dist_now-updown.dist_last;
		updown.dist_last=updown.dist_now;

		//debug
	  //writeDebugStream("UPDOWN = %d L = %d R = %d\n",updown.spd_now,moveL_spd,moveR_spd);

		//gyro speed calculate
		gyro_spd = SensorValue[Gyro] - gyro_previous;
		gyro_previous = SensorValue[Gyro];

		//anti-slip
		if(sgn(moveL_spd - moveR_spd)!= sgn(gyro_spd) && abs(gyro_spd) > 3 && abs(moveL_spd - moveR_spd) > 3)
		{
			//moveL_spd = 0;
			//moveR_spd = 0;
			//writeDebugStream("Slip!!!  Type:1\n");
			//continue;
		}
		else if(abs(gyro_spd) < 2 && abs(moveL_spd - moveR_spd) > 5)
		{
			//moveL_spd = 0;
			//moveR_spd = 0;
			//writeDebugStream("Slip!!!  Type:2\n");
			//continue;
		}

		//angle adjust
		angleL += moveL_spd;
		angleR += moveR_spd;
		angle = angleL - angleR;

	 	writeDebugStream("UPDOWN = %d Gyro Speed = %d Angle = %d\n",updown.spd_now, gyro_spd, angle);
	}
}


void Robot_Move(int vy,int turn,float vy_max_speed,float turn_max_speed,float abs_max_speed)
{
	float vl;
	float vr;

	if(abs(vy)<=20)
		vy=0;
	if(abs(turn)<=20)
		turn=0;

	if(abs(vy)<vy_max_speed)
		vy=vy*vy_max_speed/127.0;

	if(abs(turn)<turn_max_speed)
		turn=turn*turn_max_speed/127.0;

	vl=vy+turn;
	vr=vy-turn;

	//anti slip
	///*if(abs(vl - vr) > 50)
	//{
	//	if(vl > vr) vr = vl * sgn(vr);
	//	else vl = vr * sgn(vl);
	//}
	//else */
	if(abs(vl) < 20)
	{
		int pwr_plus = 20 - abs(vl);
		pwr_plus *= sgn(vl);
		vl += pwr_plus;
		vr += pwr_plus;
	}
	else if(abs(vr) < 20)
	{
		int pwr_plus = 20 - abs(vr);
		pwr_plus *= sgn(vr);
		vl += pwr_plus;
		vr += pwr_plus;
	}

	if(move_protect_start && abs(vl - vr) < 25 && sgn(vl) != sgn(vr) && !encoderoff)
	{
		if(abs(moveL_spd) < 3)
		{

			if(vl <= 25) vl *= 1;
			else if(vl > 25 && vl <= 45) vl *= 0.85;
			else if(vl > 45 && vl < 90) vl = 45;
			else if(vl >= 90) vl = 50;
			//writeDebugStream("SPEED DOWN: SPD_L:%d PWR_L:%d\n",moveL_spd, vl);
		}
		else if(abs(moveL_spd) <15 && abs(motor[mtr_LB]) > 20)
		{
			vl *= 0.9;
			//writeDebugStream("SPEED DOWN: SPD_L:%d PWR_L:%d\n",moveL_spd, vl);
		}

		if(abs(moveR_spd) < 3)
		{
			if(vr <= 25) vr *= 1;
			else if(vr > 25 && vr <= 45) vr *= 0.85;
			else if(vr > 45 && vr < 90) vr = 45;
			else if(vr >= 90) vr = 50;
		//	writeDebugStream("SPEED DOWN: SPD_R:%d PWR_R:%d\n",moveR_spd, vr);
		}
		else if(abs(moveR_spd) < 15 && abs(motor[mtr_RB]) > 20)
		{
			vr *= 0.9;
			//writeDebugStream("SPEED DOWN: SPD_R:%d PWR_R:%d\n",moveR_spd, vr);
		}
		//else writeDebugStream("OK: SPD_R:%d PWR_R:%d\n",moveR_spd, vr);
	}

	if(abs(vl)>=abs_max_speed)
		vl=sgn(vl)*abs_max_speed;

	if(abs(vr)>=abs_max_speed)
		vr=sgn(vr)*abs_max_speed;

	//writeDebugStream("NORMAL: SPD_R:%d PWR_R:%d\n",moveR_spd, vr);
	if(encoderoff)
	{
		vl *= 0.85;
		vr *= 0.85;
	}

	motor[mtr_LF]=vl;
	motor[mtr_RF]=vr;
	motor[mtr_LB]=vl;
	motor[mtr_RB]=vr;
}


void RT_MOVE()
{
	if(move_power_down == 1)
		return;
	if(abs(vexRT[Ch4]) > 123 && abs(vexRT[Ch3]) < 123) Robot_Move(vexRT[Ch3] ,90*sgn(vexRT[Ch4]),75,127,100);
	else if(abs(vexRT[Ch4]) < 123 && abs(vexRT[Ch3]) > 123) Robot_Move(100*sgn(vexRT[Ch3]) ,vexRT[Ch4],127,70,100);
	else if(abs(vexRT[Ch4]) > 123 && abs(vexRT[Ch3]) > 123) Robot_Move(vexRT[Ch3] ,vexRT[Ch4],100,90,100);
	else if(abs(vexRT[Ch3]) > 110 && abs(vexRT[Ch3]) <= 123 && abs(vexRT[Ch4]) < 123) Robot_Move(75*sgn(vexRT[Ch3]) ,vexRT[Ch4],127,70,75);
	else if(abs(vexRT[Ch4]) > 110 && abs(vexRT[Ch4]) <= 123 && abs(vexRT[Ch3]) < 123) Robot_Move(vexRT[Ch3] ,70*sgn(vexRT[Ch4]),75,127,75);
	else Robot_Move(vexRT[Ch3],vexRT[Ch4],75,70,75);
}



unsigned int endtime;

task move_control_task()
{
	endtime = time1[T4];
	while(1)
	{
	//anti slip
		if(motor[mtr_LF] == 0 && motor[mtr_RF] == 0 && (abs(moveR_spd) > 20 || abs(moveL_spd) > 20) && abs(moveR_spd + moveL_spd) < 20 && sgn(moveR_spd)!=sgn(moveL_spd))
		{
			stop_moving();
		}
		wait1Msec(10);
	}
}

void stop_moving()
{
			int max_pi_spd = 20;
			int min_pi_spd = 5;
			int vy = vexRT[Ch3];
			int turn = vexRT[Ch4];
			//float p_para = 0.4;
			float i_para = 0.75;
			//int Rstart = SensorValue[enc_moveR];
			//int Lstart = SensorValue[enc_moveL];
			unsigned int starttime = time1[T4];
			/*
			int pwr_R = moveR_spd*pi_para;
			int pwr_L = moveL_spd*pi_para;
			if(abs(pwr_R) > max_pi_spd) pwr_R = max_pi_spd*sgn(pwr_R);
			if(abs(pwr_L) > max_pi_spd) pwr_L = max_pi_spd*sgn(pwr_L);
			if(abs(pwr_R) > min_pi_spd) pwr_R = min_pi_spd*sgn(pwr_R);
			if(abs(pwr_L) > min_pi_spd) pwr_L = min_pi_spd*sgn(pwr_L);
			set_move_pwr(pwr_L, pwr_R);
			*/
			writeDebugStream("\n\nStart :: MoveL = %d MoveR = %d\n",moveL_spd, moveR_spd);
			lockmove = 1;
			set_move_pwr(0,0);
			wait1Msec(30);
			while(1)
			{
				if(vy > 20 || turn > 20) break;
				if(abs(moveR_spd) < 15 && abs(moveL_spd) < 15) break;
				if(time1[T4] - starttime > 400) break;
				int pwr_R = moveR_spd*i_para;
				int pwr_L = moveL_spd*i_para;
				//int pwr_R = moveR_spd*i_para + abs(SensorValue[enc_moveR] - Rstart)*p_para*sgn(moveR_spd);
				//int pwr_L = moveL_spd*i_para + abs(SensorValue[enc_moveL] - Lstart)*p_para*sgn(moveR_spd);

				if(abs(pwr_R) > max_pi_spd) pwr_R = max_pi_spd*sgn(pwr_R);
				if(abs(pwr_L) > max_pi_spd) pwr_L = max_pi_spd*sgn(pwr_L);
				if(abs(pwr_R) < min_pi_spd) pwr_R = min_pi_spd*sgn(pwr_R);
				if(abs(pwr_L) < min_pi_spd) pwr_L = min_pi_spd*sgn(pwr_L);
				writeDebugStream("pwrL = %d pwrR = %d SpdL = %d SpdR = %d\n", -pwr_L,-pwr_R, moveL_spd, moveR_spd);
				set_move_pwr(-pwr_L, -pwr_R);
				wait1Msec(10);
			}
			set_move_pwr(0,0);
			lockmove = 0;
			endtime = time1[T4];
		  writeDebugStream("OK:: Time = %d MoveL = %d MoveR = %d\n\n",time1[T4]-starttime, moveL_spd, moveR_spd);
}

int move_pwr_L, move_pwr_R;
int moveL_power_down, moveR_power_down;
int move_protect_func()
{
	  if(abs(moveL_spd)<= 2 && abs(motor[mtr_LB]) > 20)
		{
			move_pwr_L = 0;
			moveL_power_down = 1;
		}

		if(abs(moveR_spd) <= 2 && abs(motor[mtr_RB]) > 20)
		{
			move_pwr_R = 0;
			moveR_power_down = 1;
		}

		if(moveL_power_down == 1 || moveR_power_down == 1)
		{
			//writeDebugStream("MOVE STOP: SPD_L:%d SPD_R:%d PWR_L:%d PWR_R:%d\n",moveL_spd, moveR_spd, move_pwr_L, move_pwr_R);
			return 0;
		}
		else return 0;
}

int move_protect_time = 0;
task move_protect_task()
{
	move_protect_start = true;
	while(1)
	{
		int move_protect_type = move_protect_func();
		if(move_protect_type == 1)
		{
			move_protect_time ++;
		}
		else
		{
			move_protect_time = 0;
		}
		if(move_protect_time > 10)
		{
			move_power_down = 1;
			warning_func(1,400);
			while(1)
			{
				//writeDebugStream("MOVE STOP: SPD_L:%d SPD_R:%d PWR_L:%d PWR_R:%d\n",moveL_spd, moveR_spd, move_pwr_L, move_pwr_R);
				if(abs(vexRT[Ch3]) > 60 || abs(vexRT[Ch4]) > 60)
					break;
				if(moveL_power_down == 1) move_pwr_L = 0;
				if(moveR_power_down == 1) move_pwr_R = 0;
				set_move_pwr(move_pwr_L, move_pwr_R);
				wait1Msec(20);
			}
			moveL_power_down = 0;
			moveR_power_down = 0;
			move_protect_time = 0;
		}
		move_power_down = 0;
		wait1Msec(100);
	}
}
