
// mfcDlg.h : 头文件
//

#pragma once
#include "mscomm1.h"


// CmfcDlg 对话框
class CmfcDlg : public CDialogEx
{
// 构造
public:
	CmfcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMscomm1 mycomm;
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnTimer(UINT nIDEvent);
	int intv1;
	int intv2;
	int intv3;
	int intv4;
	CPoint pcoor(int x, int y, CRect rect);//生成点的坐标：平均分成200等分
};
