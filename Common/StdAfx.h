// StdAfx.h: Inclusion of the header files
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#ifndef STDAFX_H
#define STDAFX_H

#ifdef _WINDOWS // Windows

#define _WIN32_WINNT 0x600 // Vista and above

#include <windows.h> // Windows

#include <ShlObj.h>

#endif // _WINDOWS

//#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xnamath.h> // XNA collision

//#include <XAudio2.h>
//#include <XAudio2fx.h>

// Standary library
//

#include <iostream> // IO stream

#include <memory> // Memory

#include <ctime> // Time

#include <cmath> // Math

#include <vector> // Container class vector

#include <list> // Container class List

#include <string> // String

#include <fstream> // File stream

#include <algorithm> // Algorithms

#include <thread> // Thread

#include <filesystem> // File system

#include <tuple> // Tuple

#include <atomic> // Atomic

#include <mutex> // Mutex

#include <chrono> // Chrono

#include <random> // Random

//
// Standard library

#include <strsafe.h> // Safe string functions

// Boost
//

#include <boost\foreach.hpp> // FOR_EACH
//#include <boost\filesystem.hpp> // File system

//
// End Boost

//#define FBXSDK_NEW_API

//#include <fbxsdk.h> // FBX SDK

// Custom header files
//

#include "..\resource.h" // Resource

#include "..\..\common\macros.h" // Macros

#endif // STDAFX_H