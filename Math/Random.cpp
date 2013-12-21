// Random.cpp: 
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "Random.h"

//------------------------------------------------------------------
// Name: CRandom
// Desc: Default constructor
//------------------------------------------------------------------
template<typename T>
CRandom<T>::CRandom()
{
	time_t tTime;
	::srand(time(&tTime));
}

//------------------------------------------------------------------
// Name: ~CRandom
// Desc: Destructor
//------------------------------------------------------------------
template<typename T>
CRandom<T>::~CRandom()
{
}

//------------------------------------------------------------------
// Name: getData
// Desc: Get the random data
//------------------------------------------------------------------
template<typename T>
T CRandom<T>::getData(T tMin, T tMax)
{
	m_tData = tMin + rand() % tMax; // Compute random number

	return m_tData;
}