
// Assecor-MFC-ApplicationDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "Assecor-MFC-Application.h"
#include "Assecor-MFC-ApplicationDlg.h"
#include "afxdialogex.h"

#include "../Assecor-C++Test-Static Library/Formatter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

// Implementierung
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAssecorMFCApplicationDlg-Dialogfeld



CAssecorMFCApplicationDlg::CAssecorMFCApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ASSECORMFCAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAssecorMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAssecorMFCApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CAssecorMFCApplicationDlg::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_FORWARD, &CAssecorMFCApplicationDlg::OnBnClickedButtonForward)
END_MESSAGE_MAP()


// CAssecorMFCApplicationDlg-Meldungshandler

BOOL CAssecorMFCApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen

	SetWindowText(L"Assecor C++ Developer Test");

	_CustomerRepositoryManager.createCustomerRepositoryInMemory();

	_CustomerRepositoryManager.addCustomer(CUSTOMER{ .id = 0, .first_name = "Olaf", .last_name = "Müller", .zip_code = "12209", .city = "Berlin", .favorite_color = 10 });
	_CustomerRepositoryManager.addCustomer(CUSTOMER{ .id = 1, .first_name = "Guido", .last_name = "Zahn", .zip_code = "12219", .city = "Berlin", .favorite_color = 1 });
	_CustomerRepositoryManager.addCustomer(CUSTOMER{ .id = 2, .first_name = "Peter", .last_name = "Mahn", .zip_code = "01119", .city = "Dresden", .favorite_color = 2 });
	_CustomerRepositoryManager.addCustomer(CUSTOMER{ .id = 3, .first_name = "Tina", .last_name = "Wilhelm", .zip_code = "13409", .city = "Berlin", .favorite_color = 17 });
	_CustomerRepositoryManager.addCustomer(CUSTOMER{ .id = 4, .first_name = "Sandra", .last_name = "Mauer", .zip_code = "10115", .city = "Berlin", .favorite_color = 30 });
	_CustomerRepositoryManager.addCustomer(CUSTOMER{ .id = 5, .first_name = "Eva", .last_name = "Nimmer", .zip_code = "10115", .city = "Berlin", .favorite_color = 23 });

	MyAssecorLibrary::Formatter aFormatter;
	auto[getResult, customers] = aFormatter.getAllCustomers(_CustomerRepositoryManager);
	
	if (getResult == MyAssecorLibrary::GetResult::eOk && customers.size()>0)
	{
		auto erg = stringToWstring(customers[_CurrentCustomerCounter]);
		SetDlgItemText(IDC_EDIT, erg.c_str());
	}

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

void CAssecorMFCApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CAssecorMFCApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CAssecorMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAssecorMFCApplicationDlg::OnBnClickedButtonBack()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.

	MyAssecorLibrary::Formatter aFormatter;
	auto [getResult, customers] = aFormatter.getAllCustomers(_CustomerRepositoryManager);
	if(_CurrentCustomerCounter > 0)
		--_CurrentCustomerCounter;

	if (getResult == MyAssecorLibrary::GetResult::eOk && customers.size() > 0)
	{
		auto wStr = stringToWstring(customers[_CurrentCustomerCounter]);
		SetDlgItemText(IDC_EDIT, wStr.c_str());
	}
}


void CAssecorMFCApplicationDlg::OnBnClickedButtonForward()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.

	MyAssecorLibrary::Formatter aFormatter;
	auto [getResult, customers] = aFormatter.getAllCustomers(_CustomerRepositoryManager);
	if (_CurrentCustomerCounter < customers.size()-1)
		++_CurrentCustomerCounter;

	if (getResult == MyAssecorLibrary::GetResult::eOk && customers.size() > 0)
	{
		auto wStr = stringToWstring(customers[_CurrentCustomerCounter]);
		SetDlgItemText(IDC_EDIT, wStr.c_str());
	}

}

// Convert an UTF8 string to a wide Unicode String
std::wstring CAssecorMFCApplicationDlg::stringToWstring(const std::string& str) const
{
	if (str.empty()) 
		return std::wstring();

	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

