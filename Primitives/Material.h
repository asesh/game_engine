// Material.h: Material's interface
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#ifndef MATERIAL_H
#define MATERIAL_H

// SMaterial structure
struct SMaterial
{
	//---------------------------------------------------------------------------
	// Name: SMaterial
	// Desc: Default constructor
	//---------------------------------------------------------------------------
	SMaterial()
	{
		m_oAmbientMaterialColor = CVector4(0.3f, 0.1f, 0.7f, 1.0f); // Material reflects 30% red light, 10% green light  and 70% blue light
		m_oAmbientLightColor = CVector4(0.4f, 0.4f, 0.4f, 1.0f); // Incoming ambient light color is 40% intensity white light
	}

	//---------------------------------------------------------------------------
	// Name: SMaterial
	// Desc: Constructor
	//---------------------------------------------------------------------------
	SMaterial(CVector4 oAmbientMaterialColor, CVector4 oAmbientLightColor)
	{
		m_oAmbientMaterialColor = oAmbientMaterialColor;
		m_oAmbientLightColor = oAmbientLightColor;
	}

	//---------------------------------------------------------------------------
	// Name: ~SMaterial
	// Desc: Destructor
	//---------------------------------------------------------------------------
	~SMaterial()
	{
	}

	//---------------------------------------------------------------------------
	// Name: operator=
	// Desc: Overloaded assignment operator
	//---------------------------------------------------------------------------
	void operator=(const SMaterial *pMaterialConstantBuffer)
	{
		::memcpy(this, pMaterialConstantBuffer, sizeof(*this)); // Copy the data from the parameter to the current structure
	}


	CVector4 m_oAmbientMaterialColor; // Ambient material color
	CVector4 m_oAmbientLightColor; // Ambient light color
};

// Diffuse material
struct SDiffuseMaterial : public SMaterial
{
	//---------------------------------------------------------------------------
	// Name: SDiffuseMaterial
	// Desc: Default constructor
	//---------------------------------------------------------------------------
	SDiffuseMaterial()
	{
		m_oDiffuseMaterialColor = CVector4(0.5f, 1.0f, 0.75, 1.0f); // Material reflect 50% incoming red light, 100% green light and 75% blue light
		m_oDiffuseLightColor = CVector4(0.8f, 0.8f, 0.8f, 1.0f); // Incoming light color is 80% intensity white light
	}

	//---------------------------------------------------------------------------
	// Name: SDiffuseMaterial
	// Desc: Constructor
	//---------------------------------------------------------------------------
	SDiffuseMaterial(CVector4 oAmbientMaterialColor, CVector4 oAmbientLightColor, CVector4 oDiffuseMaterialColor, CVector4 oDiffuseLightColor)
	{
		m_oDiffuseMaterialColor = oDiffuseMaterialColor;
		m_oDiffuseLightColor = oDiffuseLightColor;
		m_oAmbientMaterialColor = oAmbientMaterialColor;
		m_oAmbientLightColor = oAmbientLightColor;
	}

	CVector4 m_oDiffuseMaterialColor; // Diffuse material color
	CVector4 m_oDiffuseLightColor; // Diffuse light color
};

// SSpecularMaterial structure
struct SSpecularMaterial : public SDiffuseMaterial
{
	//---------------------------------------------------------------------------
	// Name: SSpecularMaterial
	// Desc: Default constructor
	//---------------------------------------------------------------------------
	SSpecularMaterial()
	{
	}

	//---------------------------------------------------------------------------
	// Name: SSpecularMaterial
	// Desc: Constructor
	//---------------------------------------------------------------------------
	SSpecularMaterial(CVector4 oAmbientMaterialColor, CVector4 oAmbientLightColor, CVector4 oDiffuseMaterialColor, CVector4 oDiffuseLightColor, CVector4 oSpecularMaterialColor, CVector4 oSpecularLightColor, float fSpecularIntesity)
	{
		m_oDiffuseMaterialColor = oDiffuseMaterialColor;
		m_oDiffuseLightColor = oDiffuseLightColor;
		m_oAmbientMaterialColor = oAmbientMaterialColor;
		m_oAmbientLightColor = oAmbientLightColor;
		m_oSpecularMaterialColor = oSpecularMaterialColor;
		m_oSpecularLightColor = oSpecularLightColor;
		m_fSpecularIntesity = fSpecularIntesity;
	}

	CVector4 m_oSpecularMaterialColor; // Specular material color
	CVector4 m_oSpecularLightColor; // Specular light color
	float m_fSpecularIntesity; // Specular intensity
};

#endif // MATERIAL_H