// Timer.cpp: Implementation of a timer
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "Timer.h"

// Explicit instantiations
template class CTimer<float>;

//------------------------------------------------------------------
// Name: CTimer
// Desc: Default constructor
//------------------------------------------------------------------
template<typename T>
CTimer<T>::CTimer()
{
	// Query the frequency of the high resolution performance counter
	::QueryPerformanceFrequency(&m_oPerformanceFrequency);

	m_dSecondsPerCount = 1.0f / m_oPerformanceFrequency.QuadPart; // Calculate the number of seconds per-count
}

//------------------------------------------------------------------
// Name: CTimer
// Desc: Default constructor
//------------------------------------------------------------------
template<typename T>
CTimer<T>::CTimer(T tTimeOutValue)
{
	// Query the frequency of the high resolution performance counter
	::QueryPerformanceFrequency(&m_oPerformanceFrequency);

	m_dSecondsPerCount = 1.0 / m_oPerformanceFrequency.QuadPart; // Calculate the number of seconds per-count
}

//------------------------------------------------------------------
// Name: CTimer
// Desc: Constructor
//------------------------------------------------------------------
template<typename T>
CTimer<T>::CTimer(T tTimeOutValue, T tExpireTime)
{
	// Query the frequency of the high resolution performance counter
	::QueryPerformanceFrequency(&m_oPerformanceFrequency);

	m_dSecondsPerCount = 1.0 / m_oPerformanceFrequency.QuadPart; // Calculate the number of seconds per-count
}

//------------------------------------------------------------------
// Name: ~CTimer
// Desc: Destructor
//------------------------------------------------------------------
template<typename T>
CTimer<T>::~CTimer()
{
}

//------------------------------------------------------------------
// Name: getElapsedTime
// Desc: Get the elapsed time
//------------------------------------------------------------------
template<typename T>
T CTimer<T>::getElapsedTime() const
{
	return static_cast<T>((m_oCurrentPerfCounterValue.QuadPart - m_oPreviousPerfCounterValue.QuadPart) * m_dSecondsPerCount);
}

//------------------------------------------------------------------
// Name: getExpiryTime
// Desc: Get the time at which the timer expires
//------------------------------------------------------------------
template<typename T>
T CTimer<T>::getExpiryTime() const
{
	return m_tExpiration;
}

//------------------------------------------------------------------
// Name: operator=
// Desc: Assign new time
//------------------------------------------------------------------
template<typename T>
T CTimer<T>::operator=(T tNewTime)
{
	return tNewTime;
}

//------------------------------------------------------------------
// Name: operator+=
// Desc: Advance the current time by the specified one
//------------------------------------------------------------------
template<typename T>
T CTimer<T>::operator+=(T tAdvanceTime)
{
	return m_tCurrentTime += tAdvanceTime;
}

//------------------------------------------------------------------
// Name: operator!
// Desc: Check if the timer is available
//------------------------------------------------------------------
template<typename T>
bool CTimer<T>::operator!()
{
	return true;
}

//------------------------------------------------------------------
// Name: start
// Desc: Set the starting point of the timer
//------------------------------------------------------------------
template<typename T>
BOOL CTimer<T>::start()
{
	return ::QueryPerformanceCounter(&m_oPreviousPerfCounterValue);
}

//------------------------------------------------------------------
// Name: end
// Desc: Set the ending point of the timer
//------------------------------------------------------------------
template<typename T>
BOOL CTimer<T>::end()
{
	return ::QueryPerformanceCounter(&m_oCurrentPerfCounterValue);
}

//------------------------------------------------------------------
// Name: reset
// Desc: Reset the timer
//------------------------------------------------------------------
template<typename T>
void CTimer<T>::reset()
{
	m_oPreviousPerfCounterValue = m_oCurrentPerfCounterValue; // Assign the value of the current performance counter to the previous one
}

//------------------------------------------------------------------
// Name: calculateGamePlayedTime
// Desc: Calculate the amount of time that have elapsed in the game
//------------------------------------------------------------------
//void CTimer::calculateGamePlayedTime()
//{
//	// Retrieve the no. of milliseconds that have elapsed
//	m_dwCurrentTime = 0; //::timeGetTime();
//
//	// Calculate the no. of milliseconds that have elapsed
//	// between the last and the current calls to timeGetTime API
//	m_dwDeltaTime = m_dwCurrentTime - m_dwLastTime;
//
//	// Add the no. of milliseconds that have elapsed
//	m_dwMilliSecond += m_dwDeltaTime;
//
//	// Check to see if the no. of milliseconds that have elapsed is greater than or equal to 1000
//	// If it's equal to 1000 then a second has elapsed since 1000 ms = 1 second
//	if(m_dwMilliSecond >= 1000)
//	{
//		m_dwSecond++; // Increment second
//		m_dwMilliSecond = 0; // Set millisecond to 0
//	}
//
//	// Check to see if the no. of seconds that have elapsed exceeds 59 seconds
//	if(m_dwSecond > 59)
//	{
//		m_dwMinute++; // Increment minute
//		m_dwSecond = 0; // Set second to 0
//	}
//
//	// Check to see if the amount of minutes that have elapsed exceeds 59 minutes
//	if(m_dwMinute > 59)
//	{
//		m_dwHour++; // Increment hour
//		m_dwMinute = 0;  // Set minute to 0
//	}
//
//	// Bound the hour to 12 hours
//	if(m_dwHour > 12)
//		m_dwHour = 1; // Set hour to 1
//
//	// These are for displaying 0s followed by time elapsed if the timer's value is less than 10
//	// for eg; 00:12:36
//	if(m_dwHour < 10 && m_dwMinute < 10 && m_dwSecond < 10)
//		::StringCbPrintf(m_szTimeData, ARRAY_SIZE(m_szTimeData, WCHAR), L"Time: 0%d:0%d:0%d", m_dwHour, m_dwMinute, m_dwSecond);
//	else if(m_dwHour < 10 && m_dwMinute < 10 && m_dwSecond >= 10)
//		::StringCbPrintf(m_szTimeData, ARRAY_SIZE(m_szTimeData, WCHAR), L"Time: 0%d:0%d:%d", m_dwHour, m_dwMinute, m_dwSecond);
//	else if(m_dwHour < 10 && m_dwMinute >= 10 && m_dwSecond >= 10)
//		::StringCbPrintf(m_szTimeData, ARRAY_SIZE(m_szTimeData, WCHAR), L"Time: 0%d:%d:%d", m_dwHour, m_dwMinute, m_dwSecond);
//	else if(m_dwHour >= 10 && m_dwMinute >= 10 && m_dwSecond < 10)
//		::StringCbPrintf(m_szTimeData, ARRAY_SIZE(m_szTimeData, WCHAR), L"Time: %d:%d:0%d", m_dwHour, m_dwMinute, m_dwSecond);
//	else if(m_dwHour >= 10 && m_dwMinute < 10 && m_dwSecond < 10)
//		::StringCbPrintf(m_szTimeData, ARRAY_SIZE(m_szTimeData, WCHAR), L"Time: %d:0%d:0%d", m_dwHour, m_dwMinute, m_dwSecond);
//	else if(m_dwHour >= 10 && m_dwMinute < 10 && m_dwSecond >= 10)
//		::StringCbPrintf(m_szTimeData, ARRAY_SIZE(m_szTimeData, WCHAR), L"Time: %d:0%d:%d", m_dwHour, m_dwMinute, m_dwSecond);
//	else if(m_dwHour < 10 && m_dwMinute >= 10 && m_dwSecond < 10)
//		::StringCbPrintf(m_szTimeData, ARRAY_SIZE(m_szTimeData, WCHAR), L"Time: 0%d:%d:0%d", m_dwHour, m_dwMinute, m_dwSecond);
//	else
//		::StringCbPrintf(m_szTimeData, ARRAY_SIZE(m_szTimeData, WCHAR), L"Time: %d:%d:%d", m_dwHour, m_dwMinute, m_dwSecond);
//
//	// Reset the last time value to that of the current time in milliseconds
//	m_dwLastTime = m_dwCurrentTime;
//}