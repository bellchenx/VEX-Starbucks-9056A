//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                       VEX Competition Control Include File
//
// This file provides control over a VEX Competition Match. It should be included in the user's
// program with the following line located near the start of the user's program
//        #include "VEX_Competition_Includes.h"
// The above statement will cause this program to be included in the user's program. There's no
// need to modify this program.
//
// The program displays status information on the new VEX LCD about the competition state. You don't
// need the LCD, the program will work fine whether or not the LCD is actually provisioned.
//
// The status information is still useful without the LCD. The ROBOTC IDE debugger has a "remote screen"
// that contains a copy of the status information on the LCD. YOu can use this to get a view of the
// status of your program. The remote screen is shown with the menu command
//   "Robot -> Debugger Windows -> VEX Remote Screen"
//
// The LCD is 2 lines x 16 characters. There are three display formats to look for:
//
//        State          Description
//
//    ----------------
//   |Disabled        |  The robot is idle. This occurs before both the autonomous and user
//   |Time mm:ss.s    |  control states. The time display is minutes and seconds it has been idle.
//    ----------------
//
//    ----------------
//   |Autonomous      |  The robot is running autonomous code.
//   |Time mm:ss.s    |  control states. The time display is minutes and seconds it has been running.
//    ----------------
//
//    ----------------
//   |User Control    |  The robot is running user control code.
//   |Time mm:ss.s    |  control states. The time display is minutes and seconds it has been running.
//    ----------------
//////////////////////////////////////////////////////////////////////////////////////////////////////


void allMotorsOff();
void allTasksStop();


#define bStopTasksBetweenModes  true

static void displayStatusAndTime();

task main()
{
	clearLCDLine(0);
	clearLCDLine(1);

	nVolume = 80;
	warning_func(2,800);
	wait_for_playtone();
	warning_func(1,666);
	wait_for_playtone();
	warning_func(1,800);
	wait_for_playtone();

	startTask(para_calc_task);
	startTask(disp_logo);

	pre_auton();

	while (true)
	{

		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDPos(0, 0);

		while (bIfiRobotDisabled)
		{
		  displayLCDPos(0, 0);
		  //displayNextLCDString("Disabled");
			while (true)
			{
				displayStatusAndTime();
				if (!bIfiRobotDisabled)
				  break;
				wait1Msec(25);

				displayStatusAndTime();
				if (!bIfiRobotDisabled)
				  break;
				wait1Msec(25);

				displayStatusAndTime();
				if (!bIfiRobotDisabled)
				  break;
				wait1Msec(25);

				displayStatusAndTime();
				if (!bIfiRobotDisabled)
				  break;
				wait1Msec(25);
			}
	  }

		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDPos(0, 0);
		if (bIfiAutonomousMode)
		{
	    //displayNextLCDString("Autonomous");
		  startTask(autonomous);

			// Waiting for autonomous phase to end
			while (bIfiAutonomousMode && !bIfiRobotDisabled)
			{
				if (!bVEXNETActive)
				{
				  if (nVexRCReceiveState == vrNoXmiters) // the transmitters are powered off!!
					  allMotorsOff();
				}
				wait1Msec(25);               // Waiting for autonomous phase to end
			}
		  allMotorsOff();
		  if(bStopTasksBetweenModes)
		  {
			  allTasksStop();
			}
		}

		else
		{
	    //displayNextLCDString("User Control");
			startTask(usercontrol);

			// Here we repeat loop waiting for user control to end and (optionally) start
			// of a new competition run
			while (!bIfiAutonomousMode && !bIfiRobotDisabled)
			{
				if (nVexRCReceiveState == vrNoXmiters) // the transmitters are powered off!!
					allMotorsOff();
				wait1Msec(25);
		  }
			allMotorsOff();
		  if(bStopTasksBetweenModes)
		  {
			  allTasksStop();
			}
		}
	}
}


void allMotorsOff()
{
	motor[port1] = 0;
	motor[port2] = 0;
	motor[port3] = 0;
	motor[port4] = 0;
	motor[port5] = 0;
	motor[port6] = 0;
	motor[port7] = 0;
	motor[port8] = 0;
#if defined(VEX2)
	motor[port9] = 0;
	motor[port10] = 0;
#endif
}

void allTasksStop()
{
  stopTask(1);
  stopTask(2);
  stopTask(3);
  stopTask(4);
#if defined(VEX2)
  stopTask(5);
  stopTask(6);
  stopTask(7);
  stopTask(8);
  stopTask(9);
  stopTask(10);
  stopTask(11);
  stopTask(12);
  stopTask(13);
  stopTask(14);
  stopTask(15);
  stopTask(16);
  stopTask(17);
  stopTask(18);
  stopTask(19);
#endif
}

static void displayStatusAndTime()
{
}
