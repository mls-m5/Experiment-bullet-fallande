
#include "vector.h"

enum Commands{
    CMD_FIRE,
    CMD_FORWARD,
    CMD_BACKWARD,
    CMD_LEFT,
    CMD_RIGHT,
    CMD_MAX
};

const int MappingKeys[CMD_MAX] = {
    ' ',
    228,
    'o',
    'a',
    'e',
};

class Ship{
private:
    Vector pos;
    double angle;
    Vector vel;
    
    bool activeCmd[CMD_MAX];
    
public:
    Ship(vec position, double a);
    void Update(double t);
    void Render();
    
    void Turn(double a);
    void Command(Commands cmd, bool state);
};
