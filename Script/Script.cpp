// Script.cpp: Implementation of scripting engine
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"

#include <Python.h> // Python

#include "Script.h"

//------------------------------------------------------------------
// Name: CScript
// Desc: Default constructor
//------------------------------------------------------------------
CScript::CScript()
{
	//m_pyResult = nullptr;
	///m_pyName = m_pyModule = nulllptr;
}

//------------------------------------------------------------------
// Name: ~CScript
// Desc: Destructor
//------------------------------------------------------------------
CScript::~CScript()
{
	//::Py_Finalize();
}

//------------------------------------------------------------------
// Name: init
// Desc: Initialize the scripting engine
//------------------------------------------------------------------
bool CScript::init()
{
	//::Py_SetPath(L"C:\\Users\\Asesh\\Documents\\Source Code\\Python-3.2.2\\Lib");

	//::Py_Initialize();

	return true;
}

//------------------------------------------------------------------
// Name: execute
// Desc: Execute the specified string
//------------------------------------------------------------------
bool CScript::execute(std::wstring oScriptNameString)
{
	//PyObject *pName = ::PyImport_Import(::Pyunicode_from

	return true;
}

//------------------------------------------------------------------
// Name: 
// Desc: 
//------------------------------------------------------------------

//------------------------------------------------------------------
// Name: 
// Desc: 
//------------------------------------------------------------------

CScript g_oScript;
CScript *g_pScript = &g_oScript;