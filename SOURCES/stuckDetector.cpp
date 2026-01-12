#include "c_extern.h"

namespace StuckDetector 
{
	// Period to collect information, after which we evaluate if the object is stuck (in milliseconds)
    constexpr S32 detectIntervalMs = 1000;
	
    // If during the detection interval the distance of the walking actor to the target changes less than this value, we consider it stuck
    constexpr S32 stuckThreshold = 5; 

    typedef struct 
    {
        bool isDetecting;
        S32 numCollisions;
        S32 lastDistance;
        S32 lastTimerRef;
    } StuckInfo;

    static StuckInfo stuckInfos[MAX_OBJETS];

    static void resetObjectInfo(S32 objectIndex, bool isDetecting, S32 distance, S32 timerRef) 
    {
        stuckInfos[objectIndex].isDetecting = isDetecting;
        stuckInfos[objectIndex].numCollisions = 0;
        stuckInfos[objectIndex].lastDistance = distance;
        stuckInfos[objectIndex].lastTimerRef = timerRef;
    }

    void reset() 
    {
        for (S32 i = 0; i < MAX_OBJETS; ++i) 
        {
            resetObjectInfo(i, false, -1, 0);
        }
    }

    void resetObject(S32 objectIndex) 
    {
        resetObjectInfo(objectIndex, false, -1, 0);
    }

    bool isObjectStuck(S32 objectIndex, T_OBJET *obj, S32 distanceToTarget) 
    {
        StuckInfo &info = stuckInfos[objectIndex];

        // If this object has no colliders, no need to check for stuck
        if (!(obj->Flags & (CHECK_OBJ_COL | CHECK_BRICK_COL))) 
        {
            if (info.isDetecting) {
                resetObjectInfo(objectIndex, false, -1, 0);
            }

            return false;
        }

        if (!info.isDetecting) 
        {
            resetObjectInfo(objectIndex, true, distanceToTarget, TimerRefHR);
            return false;
        }

        if (obj->Col & 128 || obj->ObjCol != 255 && obj->ObjCol != NUM_PERSO && ListObjet[obj->ObjCol].Flags & SPRITE_3D) 
        {
            info.numCollisions++;
        } 

        if (TimerRefHR - info.lastTimerRef > detectIntervalMs) 
        {
			// If no collisions detected, do not check for stuck
            if (info.numCollisions == 0) 
            {
                resetObjectInfo(objectIndex, true, distanceToTarget, TimerRefHR);
                return false;
            }

            S32 deltaDistance = abs(info.lastDistance - distanceToTarget);
            if (deltaDistance < stuckThreshold) 
            {
                resetObjectInfo(objectIndex, false, -1, 0);
                return true;
            }
            else 
            {
                resetObjectInfo(objectIndex, true, distanceToTarget, TimerRefHR);
            }
        }

        return false;
    }

	// This does not guarantee to move the object to the correct position, as the collision system may still interfere.
	// But we try our best, and after this call, the walking to the point should be considered complete.
    void unstuckObject(T_OBJET *obj, S32 targetX, S32 targetY, S32 targetZ) 
    {
        obj->Obj.X = targetX;
        obj->Obj.Y = targetY;
        obj->Obj.Z = targetZ;
    }
}
