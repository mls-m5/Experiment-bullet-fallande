#ifndef PHYSICS_H
#define PHYSICS_H


#include <btBulletDynamicsCommon.h>
#include "box.h"

class Physics
{
private:
    btDefaultCollisionConfiguration* collisionConfiguration;
    
    btCollisionDispatcher* dispatcher;
    
    btBroadphaseInterface *overlappingPairCache;
    
    btSequentialImpulseConstraintSolver * solver;
    
    btDiscreteDynamicsWorld * dynamicWorld;
    
    btAlignedObjectArray<btCollisionShape*> collisionShapes;
public:
    
    
    Physics();
    
    Box* CreateRigidBox(btVector3 position, btScalar mass = 1, btVector3 boxHalfExtent = btVector3(1, 1, 1));
    
    void Step(btScalar t);
    
    btDynamicsWorld *getWorld() { return dynamicWorld; }
    
    ~Physics();
    void PointConstraint(Box *a, Box *b, btVector3 va, btVector3 vb, bool disableCollisionsBetweenLinkedBodies = false);
};

#endif // PHYSICS_H
