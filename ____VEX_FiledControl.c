
#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    agl_claw,       sensorAnalog)
#pragma config(Sensor, in8,    Gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  hgt_limit,      sensorDigitalIn)
#pragma config(Sensor, dgtl2,  enc_moveR,      sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  enc_updown,     sensorQuadEncoder)
#pragma config(Sensor, dgtl11, enc_moveL,      sensorQuadEncoder)
#pragma config(Motor,  port1,           mtr_UpD_R_D,   tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           mtr_UpD_L_U,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           mtr_LF,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           mtr_LB,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           mtr_claw_left, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           mtr_UpD_R_U,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           mtr_RF,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           mtr_RB,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           mtr_claw_right, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          mtr_UpD_L_D,   tmotyttttttttttttttttttttyyorVex393_HBridge, openLoop)

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)


#include "includes.c"
#include "___Vex_Competition_Includes_Main.c"
