#define RT      "9056"
#define RT_Logo "CDQZ"
#include "key.h"

////key press
//#define wait_for_press(key)      { while(!key) {wait1Msec(5);} }
//#define wait_for_release(key)    { while( key) { RT_MOVE(); } }

//#define while_not_pressing(key)   while(! key )  // no ;   here
//#define while_pressing(key)       while(  key )  // no ;   here

int  pwr_off=1;
bool encoderoff = false;
//auto varibles
int Self_Protect;
int slip=0;
int AutoRoute_1_where_to_throw;//-1:back off  0:do nothing   1:forward

int lockupdown = 0;
int lockmove = 0;
int lockclaw = 0;

// move variables
int moveR_spd;
int moveL_spd;
int gyro_spd;
int angle;

//simplified move
void  set_move_pwr(int L,int R)  {	motor[mtr_LF]=L;motor[mtr_LB]=L; motor[mtr_RF]=R;motor[mtr_RB]=R;}
#define move(forward,turn)   set_move_pwr((forward)+(turn), (forward)-(turn) )

//main
void pre_auton();
task autonomous();
task usercontrol();

////LCD
void LCD_Clear();

//claw
task claw_control_task();
task claw_open_agl_task();
void claw_func(int output );

//updown
task UpDown_hgt_task();
task updown_protect_task();
void updown_func(int output );
void updown_keep_lowest();
void updown_one_key_down();
//void updown_one_key_up();
void updown_hgt_hold();
void updown_protect_ctrl();

//auto lib
void move_auto_func(int EndL, int EndR, int dir, int Pwr_ABS_max, int Exit_Time,TTimers Timer_x,int brake);
void Forward_Dist(int Enc_tick, int Pwr_ABS,int turn, int Exit_Time,TTimers Timer_x,int brake);
void Turn_Auto(int gyro_aim,short Speed_ABS,short forward,int Exit_Time,int Timer_x,int brake);
int blocking(int aim, int max_pwr, TTimers timer,int defend_time);

#define clr_enc()  {SensorValue[enc_moveL]=0;SensorValue[enc_moveR]=0;}
#define clr_gyro() {SensorValue[Gyro]=0; angle = 0;}
#define clr_updown() {SensorValue[enc_updown] = 0;}

//auto
void auto_route_1();
void auto_route_2();
void auto_route_3();

//Timer
#define T_gbl           T4

#define T_task_updown   T1
#define T_task_claw     T2
#define T_func          T3

//robot_move
void RT_MOVE();
void Robot_Move(int vy,int turn,float vy_max_speed,float turn_max_speed,float abs_max_speed);
void stop_moving();
task para_calc_task();
task move_protect_task();

int move_power_down;
bool move_protect_start;

bool startantislip = true;
//#define RT_MOVE()     Robot_Move(vexRT[Ch3],vexRT[Ch4],80,80,110)
#define Move_Stop() 	Robot_Move(0,0,0,0,0)

//handle
void UpDown_handle();
void claw_handle();
void manual_handle();

//zhuangbi
task playtone_warning_task();
void warning_func(int playtimes, int frequency);
void wait_for_playtone();
void ZHUANGBI();


#define check_slip  if(!slip)

enum field_x
{
 Field_Left  =-1,
 Field_Right =1,
};

field_x FIELD=Field_Left;

int Route=1;
int auto_mode=0;

#define BRAKE 1

#define stop_all_motors()  \
{\
	Move_Stop();\
	updown_func(0);\
	claw_func(0);\
}

/////////////


#include "varibles\varibles_claw.c"
#include "varibles\varibles_updown.c"

#include "______normal______.h"
#include "claw\______claw______.h"
#include "updown\______updown______.h"

#include "pre_auto\______pre_auto______.h"
#include "auto\______auto______.h"
#include "auto_lib\______auto_lib______.h"
