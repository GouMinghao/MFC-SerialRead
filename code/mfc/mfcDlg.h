
// mfcDlg.h : ͷ�ļ�
//

#pragma once
#include "mscomm1.h"


// CmfcDlg �Ի���
class CmfcDlg : public CDialogEx
{
// ����
public:
	CmfcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	CPoint pcoor(int x, int y, CRect rect);//���ɵ�����꣺ƽ���ֳ�200�ȷ�
};
