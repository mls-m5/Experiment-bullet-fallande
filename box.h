#ifndef BOX_H
#define BOX_H

#include "btBulletDynamicsCommon.h"
#include "unit.h"


class Box : public Unit
{
private:
    btVector3 dimensions;
    
public:
    btRigidBody* body;
    
    Box(btRigidBody* b, btVector3 dims): body(b), dimensions(dims) {}
    
    void Render();
};

#endif // BOX_H
