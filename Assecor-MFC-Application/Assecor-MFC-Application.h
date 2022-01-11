
// Assecor-MFC-Application.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CAssecorMFCApplicationApp:
// Siehe Assecor-MFC-Application.cpp für die Implementierung dieser Klasse
//

class CAssecorMFCApplicationApp : public CWinApp
{
public:
	CAssecorMFCApplicationApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CAssecorMFCApplicationApp theApp;
