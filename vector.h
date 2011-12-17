#ifndef VECTOR_H
#define VECTOR_H



class Vector
{
public:
    double x, y, z;
    
    Vector();
    Vector(double nx, double ny, double nz):x(nx), y(ny), z(nz){}
    Vector(const Vector& v):x(v.x), y(v.y), z(v.z){}
    
    Vector Cross(Vector v);
    
#define OPERATOR1(op) Vector &operator op (Vector v) {x op v.x; y op v.y; z op v.z; return *this;}
    
    OPERATOR1(+=)
    OPERATOR1(-=)
    OPERATOR1(*=)
    OPERATOR1(/=)
    
#define OPERATOR2(op) Vector operator op (Vector v) {return Vector(x op v.x, y op v.y, z op v.z);}
    
    OPERATOR2(+)
    OPERATOR2(-)
    OPERATOR2(/)
    
    double operator * (Vector v) {return x * v.x + y * v.y + z * v.z;}
};


typedef Vector vec;

const double pi = 3.14159;

#endif // VECTOR_H
