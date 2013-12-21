// ParticleSystem.h:
// Copyright (C) 2011 Asesh Shrestha. All rights reserved

#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

// CParticleSystem class
class CParticleSystem
{
public:
	CParticleSystem(); // Default constructor
	virtual ~CParticleSystem(); // Destructor

private:
};

// CRain class
class CRain : public CParticleSystem
{
public:
	CRain(); // Default constructor
	~CRain(); // Destructor

private:
};

// CSmoke class
class CSmoke : public CParticleSystem
{
public:
	CSmoke(); // Default constructor
	~CSmoke(); // Destructor

private:
};

// SParticle structure
struct SParticle
{
	CVector3 m_oInitialPostionVector; // Initial position of the particle
	CVector3 m_oInitialVelocityVector; // Initial velocity of the particle
	float m_fInitialSize; // Initial size of the pixel
	float m_fLifeSpan; // Life span of the particle
	float m_fMass; // Mass of the particle
};

#endif // PARTICLESYSTEM_H