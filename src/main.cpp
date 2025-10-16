/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       tling                                                     */
/*                                                                            */
/*    Don't forget to add nuts to top of intake so it stops shaking.          */
/*    Make the rubber bands lower so the ball stops getting stuck.            */
/*    If you make the turn velocity higher in autonomous, it won't turn       */
/*    accuratly.                                                              */
/*    Line the edge of the robot up with the black line for autonoumous.      */
/*                                                                            */
/*    Created:      10/7/2025, 2:53:18 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;
// A global instance of competition
competition Competition;

motor left_front = motor(PORT1, true);
motor left_middle = motor(PORT2, true);
motor left_back = motor(PORT3, true);
motor_group left_thomas = motor_group(left_front, left_middle, left_back);
motor right_front = motor(PORT4, false);
motor right_middle = motor(PORT5, false);
motor right_back = motor(PORT6, false);
motor_group right_thomas = motor_group(right_front, right_middle, right_back);
inertial thomas = inertial(PORT10);
smartdrive not_lucas= smartdrive(left_thomas, right_thomas, thomas, 259.34, 320, 40, mm, 1);
motor collect_motor = motor(PORT8, true);
motor outtake_motor = motor(PORT9, false);
brain tiya;
controller tiya = controller();



/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  thomas.calibrate();
  not_lucas.setTurnVelocity(25, percent);
  not_lucas.turnFor(left, 11, degrees);
  not_lucas.setDriveVelocity(100, percent);
  collect_motor.setVelocity(70, percent);
  collect_motor.spin(forward);
  not_lucas.driveFor(forward, 17, inches);
  not_lucas.stop();
  wait(2, seconds);
  not_lucas.turnFor(right, 15, degrees);
  wait(20, msec);
  not_lucas.driveFor(forward, 20, inches);
  outtake_motor.stop();
  collect_motor.stop();
  not_lucas.turnFor(right, 135, degrees);
  not_lucas.driveFor(forward, 5, inches);
  collect_motor.spin(reverse); 
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void backup_auto () {
  wait(0.1, seconds);
  collect_motor.setVelocity(200, percent);
  outtake_motor.setVelocity(200, percent);
  left_front.setVelocity(80, percent);
  left_middle.setVelocity(80, percent);
  left_back.setVelocity(80, percent);
  right_front.setVelocity(80, percent);
  right_middle.setVelocity(80, percent);
  right_back.setVelocity(80, percent);

  collect_motor.spin(forward);
  outtake_motor.spin(forward);
  left_front.spin(forward);
  left_middle.spin(forward);
  left_back.spin(forward);
  right_front.spin(forward);
  right_middle.spin(forward);
  right_back.spin(forward);
  wait(1.2, seconds);

  left_front.stop();
  left_middle.stop();
  left_back.stop();
  right_front.stop();
  right_middle.stop();
  right_back.stop();
  wait(0.1, seconds);

  left_front.spin(forward);
  left_middle.spin(forward);
  left_back.spin(forward);
  right_front.spin(reverse);
  right_middle.spin(reverse);
  right_back.spin(reverse);
  wait(0.3, seconds);

  left_front.stop();
  left_middle.stop();
  left_back.stop();
  right_front.stop();
  right_middle.stop();
  right_back.stop();


}

void collect_outtake_button() {
  collect_motor.setVelocity(200, percent);
  collect_motor.spin(forward);
  outtake_motor.setVelocity(200, percent);
  outtake_motor.spin(forward);
}

void collect_reverse_button() {
  collect_motor.setVelocity(100, percent);
  collect_motor.spin(reverse);
  outtake_motor.setVelocity(100, percent);
  outtake_motor.spin(reverse);
}

void collect_only_button() {
  collect_motor.setVelocity(200, percent);
  collect_motor.spin(forward);
}

void collect_only_reverse_button() {
  collect_motor.setVelocity(200, percent);
  collect_motor.spin(reverse);
}

void slow_outtake() {
  collect_motor.setVelocity(15, percent);
  collect_motor.spin(reverse);
}

void drive_robot() {
      int leftSpeed = lucas.Axis3.position(percent);
      int rightSpeed = lucas.Axis2.position(percent);

      // right motors default reverse
      left_front.spin(fwd, leftSpeed, percent);
      left_middle.spin(fwd, leftSpeed, percent);
      left_back.spin(fwd, leftSpeed, percent);
      right_front.spin(fwd, rightSpeed, percent); 
      right_middle.spin(fwd, rightSpeed, percent);
      right_back.spin(fwd, rightSpeed, percent);
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    if (lucas.ButtonL2.pressing()) {
      collect_outtake_button();
      drive_robot();
    } else if (lucas.ButtonL1.pressing()) {
      collect_reverse_button();
      drive_robot();
    } else if (lucas.ButtonR1.pressing()) {
      collect_only_reverse_button();
      drive_robot();
    } else if (lucas.ButtonR2.pressing()) {
      collect_only_button();
      drive_robot();
    } else if (lucas.ButtonA.pressing()) {
      slow_outtake();
      drive_robot();
    } else {
      outtake_motor.stop();
      collect_motor.stop();
      drive_robot();

    }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
