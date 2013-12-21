// Timer.h: Implementation of a timer
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#ifndef TIMER_H
#define TIMER_H

// CTimer class
template<typename T>
class CTimer final
{
public:
	CTimer(); // Default constructor
	CTimer(T tTimeOutValue); // Default constructor
	CTimer(T tTimeOutValue, T tExpireTime); // Constructor
	~CTimer(); // Destructor

	T getElapsedTime() const; // Get the elapsed time
	T getExpiryTime() const; // Get the time that the timer expires in

	T operator=(T tNewTime); // Assign new time
	T operator+=(T tAdvanceTime); // Advance the current time by the specified amount
	bool operator!(); // Returns a boolean value indicating if the timer is available

	BOOL start(); // Start the timer
	BOOL end(); // End the timer
	void reset(); // Reset the timer

private:
	T m_tCurrentTime, m_tLastTime, m_tElapsedTime;
	T m_tTimeOut, m_tExpiration;

	LARGE_INTEGER m_oCurrentPerfCounterValue, m_oPreviousPerfCounterValue, m_oPerformanceFrequency;

	double m_dSecondsPerCount;
};

extern CTimer<float> g_pGlobalTimer;

#endif // TIMER_H