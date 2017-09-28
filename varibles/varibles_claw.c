
#define claw_ctrl_time     50
#define claw_dir_open   -1
#define claw_dir_close  1


#define pwr_claw_open      (100*claw_dir_open)
#define pwr_claw_close     (100*claw_dir_close)

#define pwr_claw_hold_open  					(12*claw_dir_open)
#define pwr_claw_powerful_hold_close  (30*claw_dir_close)
#define pwr_claw_hold_close					  (12*claw_dir_close)


typedef struct
{
	int     spd_now;
	int     dist_now;
	int     dist_last;
	int     dir;
	int     pwr;
	int     protect;
} claw_Struct;

claw_Struct claw;

void claw_Struct_init()
{

}
