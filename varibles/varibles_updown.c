//manual
#define  safe_updown_pwr      10
#define  updown_sample_time   50
#define  updown_ctrl_time     50

#define pwr_updown_hold             -7
#define pwr_updown_safe             40

///safe
#define pwr_updown_up_max           75//47/75
#define pwr_updown_down_max         50//43/50
#define pwr_updown_down_limit       15

#define updown_lowest_lock             0

#define updown_lowest_hgt              0////900/950
#define updown_highest_hgt_normal      (updown_lowest_hgt+600)//1800
#define updown_highest_hgt_special     (updown_lowest_hgt+600+150)

#define updown_limitSor_pressed  (SensorValue[hgt_limit]==0)



typedef struct
{
	int     spd_now;
	int     dist_now;
	int     dist_last;
	int     chx_updown;

	int     agl_val;
	int     dir;
	float   pwr;

	int     updown_spd_aim;
	int     pwr_temp;

	int     one_key_hgt_lock;
	int     updown_highest_hgt;
	int     dead_times;
	int     is_protceted;

	int     throw_delta;

	int     pwr_one_key_lowest;

} updown_Struct;

updown_Struct updown;

void updown_Struct_init()
{
	updown.updown_highest_hgt=updown_highest_hgt_normal;
	updown.throw_delta = 450;
}
//////////////////////////////////////////////////////////////////////

//auto tasks
//macro
#define Hgt_LOCK_up        1
#define Hgt_LOCK_down      -1
#define Hgt_LOCK_no        0

#define UpDown_Pwr_Lock    7

#define updown_dir_up    1
#define updown_dir_down -1


typedef enum updown_hgt_Types
{
	hgt_lowest            = 0,//ground
	hgt_unlock            = 80  + hgt_lowest,

	hgt_off_ground        = 150  + hgt_lowest,
	hgt_higher_than_pillow  = 200  + hgt_lowest,
	hgt_prevent_touching_stars_by_the_wall     = 250  + hgt_lowest,
	hgt_defend            = 635  + hgt_lowest,
	hgt_highest           = 800  + hgt_lowest,

	hgt_push_mid_stars    = 880  + hgt_lowest,
	hgt_push_side_stars   = 820  + hgt_lowest,
	hgt_raise_up_to_throw = 600  + hgt_lowest,
	hgt_delta_push_off    = 200,
	hgt_higher_than_wall  = 180

} updown_hgt_Types;
