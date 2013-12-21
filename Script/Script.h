// Script.h: Scripting engine
// Copyright (C) 2011 Asesh Shrestha. All rights reserved

#ifndef SCRIPT_H
#define SCRIPT_H

// Forward declarations
//struct typedef _object PyObject;

// CScript
class CScript
{
public:
	CScript(); // Default constructor
	~CScript(); // Destructor

	bool init(); // Initialize the scripting engine

	bool execute(std::wstring oScriptNameString); // Execute the specified script

private:
	//PyObject *m_pyName, *m_pyModule;
	//PyObject *m_pyResult;
};

extern CScript *g_pScript;

#endif //  SCRIPT_H