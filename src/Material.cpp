#include "Material.h"

//Static member 
const Material Material::DEFAULT(1.00f, 0.30f, 0.1f);
const Material Material::STONE(2.40f, 0.50f, 0.1f);
const Material Material::WOOD(0.53f, 0.40f, 0.15f);
const Material Material::AIR(0.001f, 0.90f, 0.0f);

Material::Material(float density, float friction, float restitution)
{
    this->density = density;
    this->friction = friction;
    this->restitution = restitution;
}

Material::Material()
{
    //ctor
}

Material::~Material()
{
    //dtor
}

void Material::setRestitution(float r)
{
    this->restitution = r;
}

float Material::getRestitution()
{
    return this->restitution;
}

void Material::setFriction(float f)
{
    this->restitution = f;
}

float Material::getFriction()
{
    return this->friction;
}

void Material::setDensity(float d)
{
    this->density = d;
}

float Material::getDensity()
{
    return this->density;
}