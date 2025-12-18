/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       tling                                                     */
/*                                                                            */
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

motor left_front = motor(PORT10, true);
motor left_back = motor(PORT8, true);
motor_group left_thomas = motor_group(left_front, left_back);
motor right_front = motor(PORT5, false);
motor right_back = motor(PORT4, false);
motor_group right_thomas = motor_group(right_front, right_back);
inertial thomas = inertial(PORT9);
smartdrive not_lucas= smartdrive(left_thomas, right_thomas, thomas, 259.34, 320, 40, mm, 1);
motor collect_motor = motor(PORT3, true);
motor outtake_right = motor(PORT7, true);
motor outtake_left = motor(PORT6, false);
motor_group outtake_motor = motor_group(outtake_right, outtake_left);
brain tiya;
controller tiya_2 = controller();
drivetrain not_lucas_2= drivetrain(left_thomas, right_thomas, 259.34, 320, 40, mm, 1);


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

void autonomous_right() {
    thomas.calibrate();
  not_lucas.setTurnVelocity(25, percent);
  not_lucas.turnFor(left, 11, degrees);
  collect_motor.setVelocity(80, percent);
  collect_motor.spin(forward);
  left_thomas.spin(fwd, 70, percent);
  right_thomas.spin(fwd, 70, percent);
  wait(700, msec);
  right_thomas.stop();
  left_thomas.stop();
  wait(1, seconds);
  not_lucas.turnFor(right, 150, degrees);
  collect_motor.stop();
  left_thomas.spin(fwd, 70, percent);
  right_thomas.spin(fwd, 70, percent);
  wait(1830, msec);
  right_thomas.stop();
  left_thomas.stop();
  not_lucas.turnFor(right, 30, degrees);
  left_thomas.spin(reverse, 70, percent);
  right_thomas.spin(reverse, 70, percent);
  wait(300, msec);
  right_thomas.stop();
  left_thomas.stop();
  collect_motor.spin(forward, 80, percent);
  outtake_motor.spin(forward, 70, percent);
}

void autonomous_left() {
  thomas.calibrate();
  not_lucas.setTurnVelocity(25, percent);
  not_lucas.turnFor(left, 11, degrees);
  collect_motor.setVelocity(80, percent);
  collect_motor.spin(forward);
  left_thomas.spin(fwd, 70, percent);
  right_thomas.spin(fwd, 70, percent);
  wait(700, msec);
  right_thomas.stop();
  left_thomas.stop();
  wait(1, seconds);
  not_lucas.turnFor(left, 150, degrees);
  collect_motor.stop();
  left_thomas.spin(fwd, 70, percent);
  right_thomas.spin(fwd, 70, percent);
  wait(1830, msec);
  right_thomas.stop();
  left_thomas.stop();
  not_lucas.turnFor(left, 30, degrees);
  left_thomas.spin(reverse, 70, percent);
  right_thomas.spin(reverse, 70, percent);
  wait(300, msec);
  right_thomas.stop();
  left_thomas.stop();
  collect_motor.spin(forward, 80, percent);
  outtake_motor.spin(forward, 70, percent); 
}

void side_auton() {
  thomas.calibrate();
  not_lucas.driveFor(forward, 8, inches);
}

void autonomous(void) {
  autonomous_right();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is u\sed to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void backup_auto () {
  thomas.calibrate();
  not_lucas.setTurnVelocity(25, percent);
  not_lucas.turnFor(left, 11, degrees);
  tiya_2.rumble("....");
  collect_motor.setVelocity(80, percent);
  collect_motor.spin(forward);
  left_thomas.spin(fwd, 50, percent);
  right_thomas.spin(fwd, 50, percent);
  wait(700, msec);
  right_thomas.stop();
  left_thomas.stop();
  tiya_2.rumble("....");
  not_lucas.turnFor(right, 97, degrees);
  collect_motor.stop();
  tiya_2.rumble("....");
  wait(0.5, seconds);
  not_lucas.stop();
  left_thomas.spin(fwd, 50, percent);
  right_thomas.spin(fwd, 50, percent);
  wait(1600, msec);
  right_thomas.stop();
  left_thomas.stop();
  not_lucas.turnFor(left, 135, degrees);
  collect_motor.spin(reverse); 
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
      int leftSpeed = tiya_2.Axis3.position(percent);
      int rightSpeed = tiya_2.Axis2.position(percent);

      // right motors default reverse
      left_front.spin(fwd, leftSpeed, percent);
      left_back.spin(fwd, leftSpeed, percent);
      right_front.spin(fwd, rightSpeed, percent); 
      right_back.spin(fwd, rightSpeed, percent);
}


void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    if (tiya_2.ButtonL2.pressing()) {
      collect_outtake_button();
      drive_robot();
    } else if (tiya_2.ButtonL1.pressing()) {
      collect_reverse_button();
      drive_robot();
    } else if (tiya_2.ButtonR1.pressing()) {
      collect_only_reverse_button();
      drive_robot();
    } else if (tiya_2.ButtonR2.pressing()) {
      collect_only_button();
      drive_robot();
    } else if (tiya_2.ButtonA.pressing()) {
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
