
// Ceeel.h : main header file for the Ceeel application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols



// CCeeelApp:
// See Ceeel.cpp for the implementation of this class
//

class CCeeelApp : public CWinApp
{
public:
	CCeeelApp();
protected:
	bool is_64_bit_architecture;
	void update_game_vars();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCeeelApp theApp;
