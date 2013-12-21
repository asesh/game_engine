// HUD.h: 
// Copyright (C) 2010-2011 Asesh Shrestha. All rights reserved

#ifndef HUD
#define HUD

// CHUD class
class CHUD
{
public:
	CHUD(); // Default constructor
	~CHUD(); // Destructor

	void showInitEngine();
	void showSettingsMenu(float fSeconds);

private:
	BOOL m_bShowOptions;

	float m_fScaleX, m_fScaleY;
};

#endif // HUD