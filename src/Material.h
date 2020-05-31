#pragma once


class Material
{
public:
    Material();
    Material(float density, float friction, float restitution);
    virtual ~Material();
    float getDensity();
    void setDensity(float d);
    float getFriction();
    void setFriction(float f);
    float getRestitution();
    void setRestitution(float r);

    static const Material DEFAULT;
    static const Material STONE;
    static const Material WOOD;
    static const Material AIR;


private:
    float density;
    float friction;
    float restitution;
};
