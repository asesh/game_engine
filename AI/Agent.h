// Agent.h: 
// Copyright (C) 2011 Asesh Shrestha. All rights reserved

#ifndef AGENT_H
#define AGENT_H

// Forward declarations
enum EAgentType;

// CAgent class
class CAgent
{
public:
	CAgent(); // Default constructor
	CAgent(EAgentType oAgentType, short sHeight, short sWeight, short sSpeed, short sLifeSpan); // Constructor
	~CAgent(); // Destructor

	short getHeight() const; // Get the height of the agent
	short getWeight() const; // Get the weight of the agent
	short getSpeed() const; // Get the speed of the agent
	EAgentType getType() const; // Get the type of agent

	void setHeight(short sHeight); // Set the height of the agent
	void setWeight(short sWeight); // Set the weight of the agent
	void setSpeed(short sSpeed); // Set the speed of the agent
	void setType(EAgentType oAgentType); // Set the type of agent

	bool isArmed() const; // Is the agent armed

	void walk(); // Walk
	void run(); // Run

private:
	bool m_bArmed;

	short m_sHeight, m_sWeight, m_sLifeSpan, m_sSpeed, m_sStamina;

	EAgentType m_oAgentType;
};

extern CAgent *g_pHeroAgent; // Main hero agent

// EAgentType enumeration
enum EAgentType
{
	Hero = 1, // Hero
	Boss, // Boss
};

#endif // AGENT_H