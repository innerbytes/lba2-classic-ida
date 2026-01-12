// Stuck detector helps to unstuck objects in TM_GOTO_POINT commands when they sometimes collide with the environment or sprite objects

#ifndef STUCK_DETECTOR_H
#define STUCK_DETECTOR_H

namespace StuckDetector
{
    void reset();
    void resetObject(S32 objectIndex);
    bool isObjectStuck(S32 objectIndex, T_OBJET *obj, S32 distanceToTarget);
    void unstuckObject(T_OBJET *obj, S32 targetX, S32 targetY, S32 targetZ);
}

#endif // STUCK_DETECTOR_H
