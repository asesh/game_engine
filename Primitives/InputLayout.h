// InputLayout.h : Declarations of input elements and their corresponding data
// Copyright (C) 2007-2012 Asesh Shrestha. All rights reserved

#ifndef INPUTLAYOUT_H
#define INPUTLAYOUT_H

// CInputLayout class
class CInputLayout
{
public:
	CInputLayout(); // Default constructor
	~CInputLayout(); // Destructor

	HRESULT create(ID3D11Device *pD3DDevice, CShader *pEffect); // Create input layouts
	HRESULT create(ID3D11Device *pD3DDevice, BYTE *pbtInputSignature, SIZE_T stInputSignatureSize); // Create input layouts
	HRESULT create(D3D11_INPUT_ELEMENT_DESC *&rD3DInputElementDesc, UINT uiNumOfInputElements, ID3D11InputLayout *pD3DInputLayout, CShader *pEffect); // Create input layouts

	HRESULT init(ID3D11Device *pD3DDevice); // Initialize the input layouts

	// Get methods
	ID3D11InputLayout *getPos() const; // Get an input layout with position
	ID3D11InputLayout *getPosInstanced() const; // Get an input layout with position and instancing
	ID3D11InputLayout *getPosNorm() const; // Get an input layout with position and normal
	ID3D11InputLayout *getPosNormInstanced() const; // Get an input layout with position, normal and instancing
	ID3D11InputLayout *getPosTex() const; // Get an input layout with position and texure
	ID3D11InputLayout *getPosTexInstanced() const; // Get an input layout with position, texture and instancing
	ID3D11InputLayout *getPosCol() const; // Get an input layout with position and color
	ID3D11InputLayout *getPosColInstanced() const; // Get an input layout with position, color and instancing
	ID3D11InputLayout *getPosNormTex() const; // Get an input layout with position, normal and texture
	ID3D11InputLayout *getPosNormTexInstanced() const; // Get an input layout with position, normal, texture and instancing

	// Set methods
	void setPos(ID3D11DeviceContext *pD3DDevContext); // Set an input layout with position
	void setPosInstanced(ID3D11DeviceContext *pD3DDevContext); // Set an input layout with position and instancing
	void setPosNorm(ID3D11DeviceContext *pD3DDevContext); // Set an input layout with position and normal
	void setPosNormInstanced(ID3D11DeviceContext *pD3DDevContext); // Set an input layout with position, normal and instancing
	void setPosTex(ID3D11DeviceContext *pD3DDevContext); // Set an input layout with position and texture
	void setPosTexInstanced(ID3D11DeviceContext *pD3DDevContext); // Set an input layout with position, texture and instancing
	void setPosCol(ID3D11DeviceContext *pD3DDevContext); // Set an input layout with position and color
	void setPosColInstanced(ID3D11DeviceContext *pD3DDevContext); // Set an input layout with position, color and instancing
	void setPosNormTex(ID3D11DeviceContext *pD3DDevContext); // Set an input layout with position, normal and texture
	void setPosNormTexInstanced(ID3D11DeviceContext *pD3DDevContext); // Set an input layout with position, normal, texture and instancing

	// Overloaded operators
	bool operator==(CInputLayout &) const; // Tests if the two objects are equal
	bool operator!() const; // Test if the input layouts were successfully created

private:
	ID3D11InputLayout *m_pD3DPosInputLayout; // Position
	ID3D11InputLayout *m_pD3DPosInstInputLayout; // Position and instancing
	ID3D11InputLayout *m_pD3DPosNormInputLayout; // Position and normal
	ID3D11InputLayout *m_pD3DPosNormInstInputLayout; // Position, normal and instancing
	ID3D11InputLayout *m_pD3DPosTexInputLayout; // Position and texture
	ID3D11InputLayout *m_pD3DPosTexInstInputLayout; // Position, texture and instancing
	ID3D11InputLayout *m_pD3DPosColInputLayout; // Position and color
	ID3D11InputLayout *m_pD3DPosColInstInputLayout; // Position, color and instancing
	ID3D11InputLayout *m_pD3DPosNormTexInputLayout; // Position, normal and texture
	ID3D11InputLayout *m_pD3DPosNormTexInstInputLayout; // Position, normal, texture and instancing
	ID3D11InputLayout *m_pD3DPosNormCubeTexInputLayout; // Position, normal and cube texture
	ID3D11InputLayout *m_pD3DPosNormVolTexInputLayout; // Position, normal and volume texture
	ID3D11InputLayout *m_pD3DPosNormTexBinormTangentLayout; // Position, normal, texture, binormal and tangent

	HRESULT m_hResult; // Will be used for checking errors
};

extern CInputLayout *g_pInputLayout;

#endif // INPUTLAYOUT_H