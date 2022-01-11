
// Assecor-MFC-ApplicationDlg.h: Headerdatei
//

#pragma once

#include "../Assecor-C++Test-Static Library/CustomerRepositoryManager.h"

// CAssecorMFCApplicationDlg-Dialogfeld
class CAssecorMFCApplicationDlg : public CDialogEx
{
// Konstruktion
public:
	CAssecorMFCApplicationDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ASSECORMFCAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	std::wstring stringToWstring(const std::string& str) const;

public:
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonForward();

private:
	unsigned int _CurrentCustomerCounter = 0;
	MyAssecorLibrary::CustomerRepositoryManager _CustomerRepositoryManager;

};
