// ProgaDlg.h
// ProgaDlg.h: файл заголовка
//

#pragma once
#include <string>


// Диалоговое окно CProgaDlg
class CProgaDlg : public CDialogEx
{
    // Создание
public:
    CProgaDlg(CWnd* pParent = nullptr);    // стандартный конструктор

    // Данные диалогового окна
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_PROGA_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV


    // Реализация
protected:
    HICON m_hIcon;

    // Созданные функции схемы сообщений
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedLoad();

    std::string fname;
    int frameid;
    int framewidth;
    int framehight;
    int framecount;
    int subapertureIndex; // Добавлено для отслеживания текущего фокального пятна
    BYTE* framedata;

    afx_msg void OnBnClickedBrght();
    afx_msg void OnBnClickedBlft();
    afx_msg void OnBnClickedBrght2();
    afx_msg void OnStnClickedSfile();
    afx_msg void OnEnChangeEfrmid();
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags); // Добавлено для обработки клавиш
};
