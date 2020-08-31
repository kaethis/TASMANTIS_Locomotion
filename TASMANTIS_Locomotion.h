#ifndef _TASMANTIS_LOCOMOTION_H_

#define _TASMANTIS_LOCOMOTION_H_


#include <Arduino.h>

#include "TASMANTIS_StepperMotor.h"

#include "TASMANTIS_Locomotion.h"


class TASMANTIS_Locomotion { /* ------------------------------------------------------------------------------------------------
* This CLASS ...
----------------------------------------------------------------------------------------------------------------------------- */

  public:

    const static float WHEEL_CIRC_CM = (10.16 * 3.14159);   // C = (d * PI)

    const float AXLE_CIRC_CM = (23.90 * 3.14159);

    const float CM_PER_STEP = (WHEEL_CIRC_CM / TASMANTIS_StepperMotor::STEPS_PER_REV);

    const float CM_PER_DEG = (AXLE_CIRC_CM / 360.0);


    TASMANTIS_Locomotion(TASMANTIS_StepperMotor*, TASMANTIS_StepperMotor*);

    void setDirection(bool);

    void setSpeed(int);

    float distanceToSteps(float dist)   { return (dist / CM_PER_STEP); }

    float stepsToDistance(float steps)  { return (steps * CM_PER_STEP); }

    float distanceToDegrees(float dist) { return (dist / CM_PER_DEG); }

    float degreesToDistance(float deg)  { return (deg * CM_PER_DEG); }

    float getDistance(void)             { return dist; }

    bool start(void);

    bool stop(void);

    bool move(void);

    bool moveByDistance(float, bool);

    bool rotateByDegrees(float, bool);


  private:

    TASMANTIS_StepperMotor *motor_left,

                           *motor_right;

    float dist;

    bool is_cmpl,

         is_left,

         is_right;
};


#endif /* _TASMANTIS_LOCOMOTION_H_ */
