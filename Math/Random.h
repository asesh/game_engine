// Random.h: Implementation of random numbers, vectors etc
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#ifndef RANDOM_H
#define RANDOM_H

// CRandom class
template<typename T>
class CRandom
{
public:
	CRandom(); // Default constructor
	~CRandom(); // Destructor

	T getData(T tMin, T tMax); // Get random data in the specified range

private:
	T m_tData;
};

#endif // RANDOM_H