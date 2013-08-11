#include "physics.h"

Physics::Physics()
{
    // Kollisionskonfiguration
    collisionConfiguration = new btDefaultCollisionConfiguration();
    
    // Använd standard dispatcher ?. Man kan använda en annan om man tillexempel vill skrive flertrådigt
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    
    overlappingPairCache = new btDbvtBroadphase();
    
    // Constraint solver. Standard
    
    solver = new btSequentialImpulseConstraintSolver;
    
    dynamicWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    
    
    // ---------------------------------------
    
    dynamicWorld->setGravity(btVector3(0,-1,0));
    
    // ------------------ Skapar lite former ------------------------
    
    /*
    
    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50)));
    
    collisionShapes.push_back(groundShape);
    
    btTransform groundTranform;
    groundTranform.setIdentity();
    groundTranform.setOrigin(btVector3(0,-56,0));
    
    
    // Skapa en odynamisk rigidbody (marken)
    {
        btScalar mass(0.);
        
        // En "rigidbody" är dynamisk om och endast om massan inte är lika med noll. Annars är den statisk
        bool isDynamic = (mass != 0.f);
        
        btVector3 localInertia(0,0,0);
        if (isDynamic){
            groundShape->calculateLocalInertia(mass, localInertia);
        }
        
        // Det är rekomenderat att använda motionstate, Man använder dem för att göra interpolation, men framförallt
        // för att ta reda på vilken kropp som har flyttat på sig. Man använder dem alltså för att ta reda på koordinater
        // För var man ska rendera, eller för positioner i allmänhet, t.ex om man vill kommunicera positioner över ett nätverk
        btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTranform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);
        //Lägg till kroppen i världen
        dynamicWorld->addRigidBody(body);
        
    }
    */
    /*
    // Skapa en dynamisk rigidbody (något som rör sig)
    {
        btCollisionShape* colShape = new btSphereShape(btScalar(1.));
        
        collisionShapes.push_back(colShape);
        
        btTransform startTransform;
        startTransform.setIdentity();
        
        btScalar mass (1.);
        
        bool isDynamic = (mass != 0.f);
        
        btVector3 localInertia(0,0,0);
        
        if (isDynamic){
            colShape->calculateLocalInertia(mass,localInertia);
        }
        
        startTransform.setOrigin(btVector3(2,10,0));

        // motionstate
        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);
        
        dynamicWorld->addRigidBody(body);
        
    }*/
    
    //CreateRigidBox(btVector3(2,10,0), 1, btVector3(1,1,1));
}

Box * Physics::CreateRigidBox(btVector3 position, btScalar mass, btVector3 boxHalfExtent)
{
    btCollisionShape* colShape = new btBoxShape(boxHalfExtent);
    
    collisionShapes.push_back(colShape);
    
    btTransform startTransform;
    startTransform.setIdentity();
    
    bool isDynamic = (mass != 0.f);
    
    btVector3 localInertia(0,0,0);
    
    if (isDynamic){
        colShape->calculateLocalInertia(mass,localInertia);
    }
    
    startTransform.setOrigin(position);

    // motionstate
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
    btRigidBody* body = new btRigidBody(rbInfo);
    
    dynamicWorld->addRigidBody(body);
    
    return new Box(body, boxHalfExtent);
}

Physics::~Physics(){
    
    // ----- Rensa bort sakerna
    
    for (int i = 0; i<collisionShapes.size(); i++){
        btCollisionShape* shape = collisionShapes[i];
        collisionShapes[i] = 0;
        delete shape;
        
    }
    
    delete dynamicWorld;
    
    delete solver;
    
    delete overlappingPairCache;
    
    delete dispatcher;
    
    delete collisionConfiguration;
}

void Physics::Step(btScalar t)
{
    dynamicWorld->stepSimulation(t, 10);
}

void Physics::PointConstraint(Box *a, Box *b, btVector3 va, btVector3 vb, bool disableCollisionsBetweenLinkedBodies){
    dynamicWorld->addConstraint(new btPoint2PointConstraint(*a->body, *b->body, va, vb), disableCollisionsBetweenLinkedBodies);
}
