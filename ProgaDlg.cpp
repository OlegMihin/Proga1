
// ProgaDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Proga.h"
#include "ProgaDlg.h"
#include "afxdialogex.h"
#include "CNewDialog.h"
#include "Cwfc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CProgaDlg



CProgaDlg::CProgaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROGA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProgaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CProgaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CProgaDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_LOAD, &CProgaDlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_BLFT, &CProgaDlg::OnBnClickedBlft)
	ON_BN_CLICKED(IDC_BRGHT2, &CProgaDlg::OnBnClickedBrght2)
	ON_STN_CLICKED(IDC_SFILE, &CProgaDlg::OnStnClickedSfile)
	ON_EN_CHANGE(IDC_EFRMID, &CProgaDlg::OnEnChangeEfrmid)
END_MESSAGE_MAP()


// Обработчики сообщений CProgaDlg

BOOL CProgaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.
	

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	//********************************!!!!!!!!!!!!!!!!!!!!!!!!!******************************
	frameid = 0;
	framecount = 99;
	framewidth = 544;
	framehight = 512;
	framedata = (BYTE*)malloc(framewidth * framehight * sizeof(BYTE));
	//********************************!!!!!!!!!!!!!!!!!!!!!!!!!******************************

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CProgaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CProgaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CProgaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CProgaDlg::OnBnClickedButton1()
{

	
}



//********************************!!!!!!!!!!!!!!!!!!!!!!!!!******************************
void CProgaDlg::OnBnClickedLoad()
{

	SetDlgItemInt(IDC_EFRMID, frameid);
	CFileDialog fileDialog(TRUE, NULL, "*.flm");
	int result = fileDialog.DoModal();
	if (result == IDOK)
	{
		CString fnamestr = fileDialog.GetPathName();
		std::string fname(fnamestr, fnamestr.GetLength());
		SetDlgItemText(IDC_SFILE, fname.c_str());
		
		LoadFilmFrame(fname, framewidth, framehight, frameid,framedata);
		DrowFrame(this->GetDC(), 5, 5, framewidth, framehight, framedata);

	}

	// Загрузка и отображение первого фокального пятна при открытии файла
	LoadSubaperture(fname, framewidth, framehight, frameid, subapertureIndex, framedata);
	DrowSubaperture(this->GetDC(), 600, 5, 64, framedata);

}




void CProgaDlg::OnBnClickedBlft()
{
	frameid--;
	if (frameid <0) frameid = framecount;
	SetDlgItemInt(IDC_EFRMID, frameid);
	LoadFilmFrame(fname, framewidth, framehight, frameid, framedata);
	DrowFrame(this->GetDC(), 5, 5, framewidth, framehight, framedata);
	LoadSubaperture(fname, framewidth, framehight, frameid, subapertureIndex, framedata);
	DrowSubaperture(this->GetDC(), 600, 5, 64, framedata);

}


void CProgaDlg::OnBnClickedBrght2()
{
	frameid++;
	if (frameid > framecount) frameid = 0;
	SetDlgItemInt(IDC_EFRMID, frameid);
	LoadFilmFrame(fname, framewidth, framehight, frameid, framedata);
	DrowFrame(this->GetDC(), 5, 5, framewidth, framehight, framedata);
	LoadSubaperture(fname, framewidth, framehight, frameid, subapertureIndex, framedata);
	DrowSubaperture(this->GetDC(), 600, 5, 64, framedata);
}



void CProgaDlg::OnStnClickedSfile()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CProgaDlg::OnEnChangeEfrmid()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}

void CProgaDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT)
	{
		subapertureIndex--;
		if (subapertureIndex < 0) subapertureIndex = 63;
	}
	else if (nChar == VK_RIGHT)
	{
		subapertureIndex++;
		if (subapertureIndex > 63) subapertureIndex = 0;
	}

	LoadSubaperture(fname, framewidth, framehight, frameid, subapertureIndex, framedata);
	DrowSubaperture(this->GetDC(), 600, 300, 64, framedata);

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}