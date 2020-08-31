#include "TASMANTIS_Locomotion.h"


TASMANTIS_Locomotion::TASMANTIS_Locomotion(TASMANTIS_StepperMotor *motor_left, TASMANTIS_StepperMotor *motor_right) { /* -------
* This CONSTRUCTOR ...
* --------------------------------------------------------------------------------------------------------------------------- */

    this->motor_left = motor_left;

    this->motor_right = motor_right;


    is_cmpl = false;

    is_left = false;

    is_right = false;


    dist = 0.0;
}


void TASMANTIS_Locomotion::setDirection(bool is_fwd) { /* ----------------------------------------------------------------------
* This FUNCTION ...
* --------------------------------------------------------------------------------------------------------------------------- */

    motor_left->setDirection(!is_fwd);

    motor_right->setDirection(is_fwd);
}


void TASMANTIS_Locomotion::setSpeed(int speed) { /* ----------------------------------------------------------------------------
* This FUNCTION ...
* --------------------------------------------------------------------------------------------------------------------------- */

    motor_left->setSpeed(speed);

    motor_right->setSpeed(speed);
}


bool TASMANTIS_Locomotion::start() { /* ----------------------------------------------------------------------------------------
* This FUNCTION ...
* --------------------------------------------------------------------------------------------------------------------------- */

    if (is_cmpl) {

        dist = 0.0;


        is_left = is_right = false;

        is_cmpl = false;

    } else {

        if (!is_left) is_left = motor_left->start();
   
        if (!is_right) is_right = motor_right->start();


        is_cmpl = (is_left && is_right);
    }


    return is_cmpl;
}


bool TASMANTIS_Locomotion::stop() { /* -----------------------------------------------------------------------------------------
* This FUNCTION ...
* --------------------------------------------------------------------------------------------------------------------------- */

    if (is_cmpl) {

        is_left = is_right = false;

        is_cmpl = false;

    } else {

        if (!is_left) is_left = motor_left->stop();
   
        if (!is_right) is_right = motor_right->stop();


        is_cmpl = (is_left && is_right);
    }


    return is_cmpl;
}


bool TASMANTIS_Locomotion::moveByDistance(float target, bool is_fwd) { /* ------------------------------------------------------
* This FUNCTION ...
* --------------------------------------------------------------------------------------------------------------------------- */

    int steps;


    steps = distanceToSteps(target);


    if (is_cmpl) {

        dist = 0.0;


        is_left = is_right = false;

        is_cmpl = false;

    } else {

        if (!is_left) is_left = motor_left->stepBySteps(steps, !is_fwd);
 
        if (!is_right) is_right = motor_right->stepBySteps(steps, is_fwd);


        dist = stepsToDistance(float(motor_left->getSteps() + motor_right->getSteps()) / 2.0);


        is_cmpl = (is_left && is_right);
    }


    return is_cmpl;
}


bool TASMANTIS_Locomotion::rotateByDegrees(float target, bool is_ccw) { /* -----------------------------------------------------
* This FUNCTION ...
* --------------------------------------------------------------------------------------------------------------------------- */

    int steps;


    steps = distanceToSteps(degreesToDistance(target));


    if (is_cmpl) {

        dist = 0.0;


        is_left = is_right = false;

        is_cmpl = false;

    } else {

        if (!is_left) is_left = motor_left->stepBySteps(steps, is_ccw);
 
        if (!is_right) is_right = motor_right->stepBySteps(steps, is_ccw);


        dist = stepsToDistance(float(motor_left->getSteps() + motor_right->getSteps()) / 2.0);


        is_cmpl = (is_left && is_right);
    }


    return is_cmpl;
}
