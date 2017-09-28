

#define limit_unpressed 1

#define pause()    { while( !vexRT[Btn7U]){};  while( vexRT[Btn7U]){}; }
#define print 1

#warning "auto_route_1"
void auto_route_1()
{
	clearTimer(T_gbl);
	int temp_forward;
	int turn_rand;

	const int delta_agl_point_to_fence = 345 * (FIELD);
	int gyro_init = SensorValue[Gyro];
	int gyro_0 = gyro_init - delta_agl_point_to_fence;

	clr_enc();

	temp_forward = 120; // 104

	UpDown_hgt_FUNC_TASK( hgt_push_mid_stars, 100, T_task_updown, 1500, 6 );
	claw_open_agl_FUNC_TASK(claw_widest_open - 20, 100, T_task_claw, 1500, -10);

	wait1Msec(200);

	Forward_Dist( -1775, temp_forward, (120 - temp_forward) * (FIELD), 1000, T_func,  !BRAKE );

	move( -temp_forward, (120 - temp_forward) * (-FIELD) );

	//wait1Msec(550);

	wait_for_claw_OK( );
	wait_for_hgt_task_ok( );
	updown_func(8);

	clr_enc();
	//wait1Msec(180);
	claw_open_agl_FUNC_TASK(claw_closed, 100, T_task_claw, 1000, -10);
	writeDebugStream(" Forward_Time  :  %d\n", time1[T_gbl]);

	move(-20, -70 * (FIELD));

	claw_open_agl_FUNC_TASK(claw_widest_open + 100, 200, T_task_claw, 1000, -3);
	wait_for_claw_OK();
	/*
	clr_enc();
	move_auto_func(150, 150, 0, 100, 500,T_func,!BRAKE);
	clr_enc()
	move_auto_func(-150, 150, 0, 100, 500,T_func,!BRAKE);
	move(0,0);
	*/
	wait1Msec(200);
	if(abs(SensorValue[Gyro] - gyro_0) > 30)
	{
		Turn_Auto(gyro_0, 35, 0, 1000, T_func, BRAKE );
	}

	UpDown_hgt_FUNC_TASK(hgt_highest - 50,80,T_task_updown,250,10);
	move(-100, 0);
	wait1Msec(200);
	move(-10, 0);

	claw_open_agl_FUNC_TASK(claw_widest_open + 100, 200, T_task_claw, 1000, -10);
	UpDown_hgt_FUNC_TASK( hgt_defend, 60, T_task_updown, 300, -4);
	wait_for_claw_OK();
	wait_for_hgt_task_ok( );

	int defend_time = 8000 - time1[T_gbl];
	int defended = blocking( hgt_defend , 15, T_gbl, defend_time);
	writeDebugStream("defend end:%d\n", time1[T_gbl]);
	if(defended)
	{
		UpDown_hgt_FUNC_TASK( hgt_highest - 50, 90, T_task_updown, 1000, 10 );
		claw_open_agl_FUNC_TASK(claw_widest_open + 200, 100, T_task_claw, 1000, -10);
		wait_for_claw_OK( );
	}
	else
	{
		UpDown_hgt_FUNC_TASK( hgt_highest-50, 90, T_task_updown, 1000, 10 );
	}

	Move_Stop();

	UpDown_hgt_FUNC_TASK( hgt_higher_than_wall, 90, T_task_updown, 1000, -10 );
	claw_open_agl_FUNC_TASK(claw_open_to_get_two_stars_corner, 60, T_task_claw, 1000, -11);
	wait_for_hgt_task_ok();

	if(abs(SensorValue[Gyro] - gyro_0) > 30)
	{
		Turn_Auto( gyro_0, 35, 0, 1000, T_func, BRAKE );
		move(-40, 0);
		wait1Msec(300);
	}

	//move(-50,0);
	//wait1Msec(200);
	// Move_Stop();

	// if(abs(SensorValue[Gyro]-gyro_0) > 150)
	// {
	// 	Turn_Auto( gyro_0, 50, 0, 1000, T_func, BRAKE );
	// }

	updown.pwr_one_key_lowest = -90;

	startTask(updown_one_key_down_task);
	claw_open_agl_FUNC_TASK(claw_open_to_get_two_stars_corner - 350, 100, T_task_claw, 700, -11);
	wait_for_lowest_OK(1000);

	clr_enc();

	Forward_Dist( 1250, 110, 0, 1000 , T_func,  !BRAKE );
	claw_open_agl_FUNC_TASK(claw_closed, 100, T_task_claw, 700, 15);

	if(abs(SensorValue[Gyro] - gyro_0) > 50)
	{
		Turn_Auto( gyro_0, 35, 0, 150, T_func, BRAKE );
		move(-40, 0);
		wait1Msec(150);
	}

	move(-15, 0);
	wait_for_claw_OK();

	updown_func(25);
	wait1Msec(250);
	updown_func(7);


	if(abs(SensorValue[Gyro] - gyro_0) > 30)
	{
		Turn_Auto( gyro_0, 35, 0, 150, T_func, BRAKE );
	}

	clr_enc();
	turn_rand = (rand() % 3 + 3) * 6;
	writeDebugStream("turn_rand=%d\n", turn_rand);

	int delay = abs(SensorValue[Gyro] - gyro_init) * 1.0;
	delay = delay > 300 ? 300 : delay;

	updown.throw_delta = 450;

	move(-(120 - turn_rand), turn_rand * (FIELD));
	wait1Msec(delay);
	startTask(updown_one_key_throw_task);
	wait1Msec(1300 - delay);
	claw_open_agl_FUNC_TASK(claw_widest_open, 100, T_task_claw, 700, -11);

	move(-35, 0);
	wait1Msec(250);

	Move_Stop();

	end_of_auto:
	wait_for_claw_OK();
	wait_for_hgt_task_ok();
	updown_func(-7);

	writeDebugStream("auto time:%d\n", time1[T_gbl]);
	while(time1[T_gbl] < 15000) {};
	stopTask(claw_open_agl_task);
	stopTask(UpDown_hgt_task);

	claw_func(0);
	updown_func(0);
}

#warning  "auto_route_2"
void auto_route_2()
{
	clearTimer(T_gbl);
	int temp_forward;

	const int delta_agl_point_to_fence = 900*(-FIELD);
	int gyro_init = SensorValue[Gyro];
	int gyro_0 = gyro_init + delta_agl_point_to_fence;
	writeDebugStream("gyro_0: %d\n", gyro_0);

	UpDown_hgt_FUNC_TASK( hgt_higher_than_wall, 60, T_task_updown, 300, -7 );
	claw_open_agl_FUNC_TASK(claw_open_to_get_two_stars_corner, 100, T_task_claw, 700, -7);
	wait_for_claw_OK( );
	wait_for_hgt_task_ok( );

	clr_enc();
	temp_forward = 70;
	Forward_Dist( 300, temp_forward, 0 , 1000, T_func,  BRAKE );

	temp_forward = 100;
	Forward_Dist( -300, temp_forward, 0 , 1000, T_func,  BRAKE );

	clr_enc();
	temp_forward = 70;
	Forward_Dist( -400, temp_forward, 0 , 1000, T_func,  BRAKE );
	startTask(updown_one_key_down_task);
	wait_for_lowest_OK( 500);
	claw_open_agl_FUNC_TASK(claw_open_to_get_two_stars_corner, 100, T_task_claw, 700, -11);
	clr_enc();
	Forward_Dist( 4000, 90, 0, 3000 , T_func,  BRAKE );

	claw_open_agl_FUNC_TASK(claw_closed, 100, T_task_claw, 700, 15);
	move(-15, 0);
	wait_for_claw_OK();

	UpDown_hgt_FUNC_TASK( hgt_higher_than_wall, 60, T_task_updown, 300, 7 );
	Turn_Auto( gyro_0, 50, 0, 2000, T_func, BRAKE );

	move(-120, 0);
	wait1Msec(500);
	updown.throw_delta = 350;
	startTask(updown_one_key_throw_task);

	wait1Msec(1000);

	move(-35, 0);
	wait1Msec(250);

	Move_Stop();

end_of_auto:
	wait_for_claw_OK();
	wait_for_hgt_task_ok();
	updown_func(-7);

	writeDebugStream("auto time: %d\n", time1[T_gbl]);
	while(time1[T_gbl] < 15000) {};
	stopTask(claw_open_agl_task);
	stopTask(UpDown_hgt_task);
	claw_func(0);
	updown_func(0);
	SensorValue[agl_claw] = 0;
}

#warning "auto_route_3"
void auto_route_3()
{

	clearTimer(T4);
	clr_enc();

	UpDown_hgt_FUNC_TASK(hgt_higher_than_wall,70,T_task_updown,350,0);
	move_auto_func(100,100,0,80,1000,T3,!BRAKE);
	wait_for_hgt_task_ok();
	claw_open_agl_FUNC_TASK(claw_closed,120,T_task_claw,500,-11);
	wait1Msec(100);
	startTask(updown_one_key_down_task);//down to lowest


	wait_for_lowest_OK();
	claw_open_agl_FUNC_TASK(claw_get_pillows,120,T_task_claw,500,-11);

	wait_for_claw_OK();
	//updown_keep_lowest();

	move_auto_func(880,880,0,120,1000,T_gbl,!BRAKE);
	claw_open_agl_FUNC_TASK(claw_close_to_get_pillow,120,T_task_claw,150,30);
	//pause(); // DEBUG
	wait_for_claw_OK();
	claw_func(35);

	clr_enc();

	//Robot_Move(120,0,127,127,127);//keep going forward

	//pause(); // DEBUG
	UpDown_hgt_FUNC_TASK(hgt_off_ground,45,T_task_updown,1000,10);//off ground and lock hgt

	move_auto_func(650,650,0,120,1000,T_gbl,!BRAKE);
	//	Forward_Dist(920,90,0,500,T3,BRAKE);//go to the center

	//updown_func(30);//slowly throw

turn_to_fence:
	clr_gyro();
	int angle_aim = -580*FIELD;
	Turn_Auto(angle_aim,80,0,1000,T_gbl,BRAKE);//turn back against the fence,step 1

	wait1Msec(60);//wait for steady

	updown.throw_delta = 500;

	unsigned int throw_start = time1[T_task_updown];
	startTask(updown_one_key_throw_task);//throw pillow
	Robot_Move(-80,0,127,127,127);//fast go to the fence
	wait1Msec(250);

	while(SensorValue[enc_updown]< 450 && time1[T_task_updown]-throw_start < 1200){};

	claw_open_agl_FUNC_TASK(claw_widest_open+100,100,T_task_claw,1500,-11);

  UpDown_hgt_FUNC_TASK(hgt_highest,50,T_task_updown,300,15);
	wait_for_hgt_task_ok();
	wait_for_claw_OK();

	UpDown_hgt_FUNC_TASK(hgt_defend-80, 20,T_task_updown,150,10);
	int defend_time = 15000 - time1[T_gbl];
	int ifdefened = blocking(hgt_defend , 15, T_gbl, defend_time);
	writeDebugStream("defend state: %d", ifdefened);
	/*
	tim=time1[T4];
	while(  (SensorValue[agl_UpDown]<hgt_raise_up_to_throw-250)   && time1[T4]<(tim+1200)   ){};
	claw_open_agl_FUNC_TASK(claw_open_to_throw,50,T1,1500);//////open to get ready to get stars
	wait_for_claw_OK();
	Robot_Move(-110,0,127,127,127);//fast go to the fence
	wait1Msec(320);//wait for back to fence

	Robot_Move(-25,0,127,127,127);//slowly go to the fence
	wait1Msec(200);//wait for back to fence

	stopTask(updown_one_key_down_task);//down to lowest

	Robot_Move(-25,0,127,127,127);//stick to fence
	while(SensorValue[agl_UpDown]>updown_highest_hgt_normal-500){};

	Robot_Move(45,0,127,127,127);//slowly go to 3 stars by the wall !!

	tim=time1[T4];
	while( (SensorValue[agl_UpDown]>hgt_lowest+300)&& time1[T4]<(tim+1500) ){};//wait to get lower

	claw_open_agl_FUNC_TASK(claw_widest_open,50,T1,1500);//
	writeDebugStream("\n before fast go to the fence :moveL = %d  moveR = %d\n",SensorValue[enc_moveL], SensorValue[enc_moveR]);
	clr_enc();
	//	Forward_Dist(460,50,0,700,T3,BRAKE);//go to get the 3 stars by the wall//time out;
	pause();
	wait_for_lowest_OK();
	Robot_Move(20,0,127,127,127);//stick to the wall
	wait1Msec(250);

	Robot_Move(-15,0,127,127,127);//slowly back off from the wall
	claw_func(50);//fast close first
	wait1Msec(100);
	claw_func(30);//close
	tim=time1[T4];
	while( SensorValue[enc_claw]<-200 && time1[T4]<(tim+1200)  ){};
	claw_func(10);

	Robot_Move(-80,0,127,127,127);//slowly go to the fence
	wait1Msec(200);

	UpDown_hgt_FUNC_TASK(hgt_off_ground,30,T2,250,127);//lock
	wait1Msec(200);

	stopTask(updown_one_key_throw_task);//throw stars
	Robot_Move(-120,0,127,127,127);//fast go to the fence

	tim=time1[T4];
	while(  (SensorValue[agl_UpDown]<hgt_raise_up_to_throw-250)   && time1[T4]<(tim+1200)   ){};
	claw_open_agl_FUNC_TASK(claw_open_to_throw,50,T1,1000);//////open to get ready to get star
	////
	wait_for_claw_OK();


	//updown_func(-45);//updown get down a little
	//wait1Msec(450);

	UpDown_hgt_FUNC_TASK(hgt_off_ground,30,T2,1500,127);//lock

	Move_Stop();
	///////////////////////////////////////////////////
	*/
end_of_auto:
	wait_for_claw_OK();
	wait_for_hgt_task_ok();
	updown_func(-7);
	writeDebugStream("auto time:%d\n",time1[T4]);
	while(time1[T4]<15000){};
	stopTask(claw_open_agl_task);
	stopTask(UpDown_hgt_task);
	claw_func(0);
	updown_func(0);
}
