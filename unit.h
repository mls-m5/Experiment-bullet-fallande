#ifndef UNIT_H
#define UNIT_H

class Unit
{
public:
    virtual void Update(double t) {}
    virtual void Render() {}
    
    Unit();
};

#endif // UNIT_H
