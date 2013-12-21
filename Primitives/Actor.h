// Actor.h: Interface of an actor
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#ifndef ACTOR_H
#define ACTOR_H

// CActor class
class CActor
{
public: // Public methods
	CActor(); // Default constructor
	CActor(const std::wstring oActorName, const std::wstring oActorTag, CBasePrimitive *pBasePrimitive, CCamera *pCamera, CTransform *pTransform, CShader *pShader, CScript *pScript, CAgent *pAgent, SMaterial *pMaterial); // Constructor
	virtual ~CActor(); // Destructor

	virtual void onInit(); // Method called on initialization
	virtual void onRender(); // Method called on render

	// Set methods
	virtual bool setName(std::wstring oActorName); // Set the name of an actor
	virtual bool setTag(std::wstring oActorTag); // Set the tag of an actor
	virtual bool setPrimitive(CBasePrimitive *pBasePrimitive); // Set primitive to this actor
	virtual bool setCamera(CCamera *pCamera); // Set camera to this actor
	virtual bool setTransform(CTransform *pTransform); // Set transformation to this actor
	virtual bool setShader(CShader *pShader); // Set shader to this actor
	virtual bool setScript(CScript *pScript); // Set script to this actor
	virtual bool setAgent(CAgent *pAgent); // Set agent to this actor
	virtual bool setMaterial(SMaterial *pMaterial); // Set material to this actor
	virtual bool setEnabled(bool bEnabled); // Enable/disable this actor

	// Overloaded operators
	virtual CActor operator=(const CActor &rActor); // Assign actor to this actor instance
	virtual bool operator==(const CActor &rActor); // Check for the equality of the specified actor with the current one

	// Get methods
	virtual std::wstring getName() const; // Get actor's name
	virtual std::wstring getTag() const; // Get actor's tag
	virtual CBasePrimitive *getPrimitive() const; // Get actor's primitive
	virtual CCamera *getCamera() const; // Get actor's camera
	virtual CTransform *getTransform() const; // Get actor's transform
	virtual CShader *getShader() const; // Get actor's shader
	virtual CScript *getScript() const; // Get actor's script
	virtual CAgent *getAgent() const; // Get actor's agent
	virtual SMaterial *getMaterial() const; // Get actor's material

	virtual HRESULT render(ID3D11DeviceContext *pD3DDeviceContext); // Render this actor

	virtual bool isEnabled() const; // Returns a boolean value indicating if it's enabled/disabled

protected: // Protected attributes
	CBasePrimitive *m_pPrimitive; // Actor's primitive

	CCamera *m_pCamera; // Actor's camera

	CTransform *m_pTransform; // Actor's transformation

	CShader *m_pShader; // Actor's shader

	CScript *m_pScript; // Actor's script

	CAgent *m_pAgent; // Actor's AI

	SMaterial *m_pMaterial; // Actor's material

	std::wstring m_oActorName, m_oActorTag; // Actor's name and tag

	bool m_bActive; // Boolean value indicating if the current actor is active or not

	bool m_bEnabled; // Boolean value indicating if this actor is enabled/disabled
};

#endif // ACTOR_H