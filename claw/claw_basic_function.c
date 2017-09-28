void claw_func(int output )
{
	motor[mtr_claw_left]=output;
	motor[mtr_claw_right]=output;
	claw.pwr=output;
}
