
// mfcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc.h"
#include "mfcDlg.h"
#include "afxdialogex.h"
#include <cmath>
#include <fstream>
#include<gl\GL.h>
#include<gl\GLU.h>
#include<GLAUX.H>
int v1buf[400] = { 0 };
int v2buf[400] = { 0 };
int v3buf[400] = { 0 };
int v4buf[400] = { 0 };
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
fstream record;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CmfcDlg �Ի���



CmfcDlg::CmfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_DIALOG, pParent)
	, intv1(0)
	, intv2(0)
	, intv3(0)
	, intv4(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, mycomm);
	DDX_Text(pDX, IDC_STATIC1, intv1);
	DDX_Text(pDX, IDC_STATIC2, intv2);
	DDX_Text(pDX, IDC_STATIC3, intv3);
	DDX_Text(pDX, IDC_STATIC4, intv4);
}

BEGIN_MESSAGE_MAP(CmfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CmfcDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CmfcDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CmfcDlg ��Ϣ�������

BOOL CmfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CmfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CmfcDlg, CDialogEx)
	ON_EVENT(CmfcDlg, IDC_MSCOMM1, 1, CmfcDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CmfcDlg::OnCommMscomm1()
{
	// TODO: �ڴ˴������Ϣ����������
	static unsigned int cnt = 0;
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	long len, k;
	unsigned int data[1024] = { 0 };
	byte rxdata[1024]; //���� BYTE ����
	CString strtemp;
	if (mycomm.get_CommEvent() == 2) //ֵΪ 2 ��ʾ���ջ����������ַ�
	{
		int tempt1 = 0;
		int tempt2 = 0;
		int tempt3 = 0;
		int tempt4 = 0;
		cnt++;
		variant_inp = mycomm.get_Input(); //����������Ϣ
		safearray_inp = variant_inp; ///����ת��
		len = safearray_inp.GetOneDimSize(); //�õ���Ч�����ݳ���
		for (k = 0; k < len; k++)
		{
			safearray_inp.GetElement(&k, rxdata + k);
		}


		for (k = 0; k < 4; k++) //������ת��Ϊ CString �ͱ���
		{
			//strtemp.Format(_T("%x"), *(rxdata + k));
			//m_EditReceive += strtemp;
			//CString temp = _T("\r\n"); //����
			//m_EditReceive += temp;
			tempt1 += pow(256, k) * (*(rxdata + k));
		}
		record << tempt1 << '\t';
		for (k = 4; k < 8; k++) //������ת��Ϊ CString �ͱ���
		{

			tempt2 += pow(256, k-4) * (*(rxdata + k));
		}
		record << tempt2 << '\t';
		for (k = 8; k <12 ; k++) //������ת��Ϊ CString �ͱ���
		{

			tempt3 += pow(256, k-8) * (*(rxdata + k));
		}
		record << tempt3 << '\t';
		for (k = 12; k < 16; k++) //������ת��Ϊ CString �ͱ���
		{

			tempt4 += pow(256, k-12) * (*(rxdata + k));
		}
		record << tempt4 << endl;
		intv1 = tempt1;
		intv2 = tempt2;
		intv3 = tempt3;
		intv4 = tempt4;
	}
	UpdateData(FALSE); //���±༭������
}


void CmfcDlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (mycomm.get_PortOpen()) //��������Ǵ򿪵ģ����йرմ���
	{
		mycomm.put_PortOpen(FALSE);
	}
	mycomm.put_CommPort(6); //ѡ��COM1
	mycomm.put_InBufferSize(1024); //���ջ�����
	mycomm.put_OutBufferSize(1024);//���ͻ�����
	mycomm.put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0,��ʾȫ����ȡ
	mycomm.put_InputMode(1);//�Զ����Ʒ�ʽ��д����
	mycomm.put_RThreshold(1);//���ջ�������1����1�������ַ�ʱ���������������ݵ�OnComm�¼�
	mycomm.put_Settings(_T("19200,e,8,1"));//������19200�޼���λ��8������λ��1��ֹͣλ
	if (!mycomm.get_PortOpen())//�������û�д����
	{
		mycomm.put_PortOpen(TRUE);//�򿪴���
		Beep(1000, 50);
		Beep(1000 * 1.05946, 50);
		Beep(1000 * 1.05946 * 1.05946, 50);
		Beep(1000 * 1.05946 * 1.05946 * 1.05946, 50);
	}
	else
	{
		mycomm.put_OutBufferCount(0);
		AfxMessageBox(_T("����6��ʧ��"));
	}
	record.open("D://record.txt", ios::out);
	//for (int n = 0; n <= 99; n++)
	//{
	//	v1buf[n] = v2buf[n] = v3buf[n] = v4buf[n] = 0;
	//}
	SetTimer(1, 50, NULL);
}


void CmfcDlg::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mycomm.put_PortOpen(FALSE);//�رմ���
	KillTimer(2);
	Beep(1000 * 1.05946 * 1.05946 * 1.05946, 50);
	Beep(1000 * 1.05946 * 1.05946, 50);
	Beep(1000 * 1.05946, 50);
	Beep(1000, 50);
	record.close();
}

afx_msg void CmfcDlg::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
	{
		SetTimer(2, 50, NULL);
		KillTimer(1);
	}
	case 2:
	{
		for (int n = 0; n <= 399; n++)
		{
			v1buf[n] = v1buf[n + 1];
			v2buf[n] = v2buf[n + 1];
			v3buf[n] = v3buf[n + 1];
			v4buf[n] = v4buf[n + 1];
		}
		if ((intv1 >= 0) && (intv1 <= 1023))
		{
			v1buf[399] = intv1;
		}
		else
		{
			v1buf[399] = v1buf[398];
		}

		if ((intv2 >= 0) && (intv2 <= 1023))
		{
			v2buf[399] = intv2;
		}
		else
		{
			v2buf[399] = v2buf[398];
		}

		if ((intv3 >= 0) && (intv3 <= 1023))
		{
			v3buf[399] = intv3;
		}
		else
		{
			v3buf[399] = v3buf[398];
		}

		if ((intv4 >= 0) && (intv4 <= 1023))
		{
			v4buf[399] = intv4;
		}
		else
		{
			v4buf[399] = v4buf[398];
		}

		////1-background
		CWnd *pCanvasWnd = GetDlgItem(IDC_CANVAS1);
		CDC *pCanvasDC = pCanvasWnd->GetDC();
		CRect rect;
		pCanvasWnd->GetClientRect(&rect); //���Ʊ���
		CBrush br(RGB(255, 255, 255));//���ư�ɫ����
		pCanvasDC->FillRect(&rect, &br); //�������� 
		pCanvasDC->Detach();
		pCanvasWnd->Detach();
		//2-background
		pCanvasWnd = GetDlgItem(IDC_CANVAS2);
		pCanvasDC = pCanvasWnd->GetDC();
		pCanvasWnd->GetClientRect(&rect); //���Ʊ���
		pCanvasDC->FillRect(&rect, &br); //�������� 
		pCanvasDC->Detach();
		pCanvasWnd->Detach();
		//3-background
		pCanvasWnd = GetDlgItem(IDC_CANVAS3);
		pCanvasDC = pCanvasWnd->GetDC();
		pCanvasWnd->GetClientRect(&rect); //���Ʊ���
		pCanvasDC->FillRect(&rect, &br); //�������� 
		pCanvasDC->Detach();
		pCanvasWnd->Detach();
		//4-background
		pCanvasWnd = GetDlgItem(IDC_CANVAS4);
		pCanvasDC = pCanvasWnd->GetDC();
		pCanvasWnd->GetClientRect(&rect); //���Ʊ���
		pCanvasDC->FillRect(&rect, &br); //�������� 
		pCanvasDC->Detach();
		pCanvasWnd->Detach();

		pCanvasWnd = GetDlgItem(IDC_CANVAS1);
		pCanvasDC = pCanvasWnd->GetDC();
		pCanvasWnd->GetClientRect(&rect); //���Ʊ���
		CPen NewPen;
		NewPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		CPen *OldPen; OldPen = pCanvasDC->SelectObject(&NewPen); //����
		pCanvasDC->MoveTo(pcoor(400, 1024 - v1buf[399], rect).x, pcoor(400, 1024 - v1buf[399], rect).y);
		for (int k = 398; k >= 0; k--)
		{
			pCanvasDC->LineTo(pcoor(k + 1, 1024 - v1buf[k], rect).x, pcoor(k + 1, 1024 - v1buf[k], rect).y);
		}


		pCanvasWnd = GetDlgItem(IDC_CANVAS2);
		pCanvasDC = pCanvasWnd->GetDC();
		pCanvasWnd->GetClientRect(&rect); //���Ʊ���
		NewPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		OldPen = pCanvasDC->SelectObject(&NewPen); //����
		pCanvasDC->MoveTo(pcoor(400, 1024 - v2buf[399], rect).x, pcoor(400, 1024 - v2buf[399], rect).y);
		for (int k = 398; k >= 0; k--)
		{
			pCanvasDC->LineTo(pcoor(k + 1, 1024 - v2buf[k], rect).x, pcoor(k + 1, 1024 - v2buf[k], rect).y);
		}


		pCanvasWnd = GetDlgItem(IDC_CANVAS3);
		pCanvasDC = pCanvasWnd->GetDC();
		pCanvasWnd->GetClientRect(&rect); //���Ʊ���
		NewPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		OldPen = pCanvasDC->SelectObject(&NewPen); //����
		pCanvasDC->MoveTo(pcoor(400, 1024 - v3buf[399], rect).x, pcoor(400, 1024 - v3buf[399], rect).y);
		for (int k = 398; k >= 0; k--)
		{
			pCanvasDC->LineTo(pcoor(k + 1, 1024 - v3buf[k], rect).x, pcoor(k + 1, 1024 - v3buf[k], rect).y);
		}


		pCanvasWnd = GetDlgItem(IDC_CANVAS4);
		pCanvasDC = pCanvasWnd->GetDC();
		pCanvasWnd->GetClientRect(&rect); //���Ʊ���
		NewPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		OldPen = pCanvasDC->SelectObject(&NewPen); //����
		pCanvasDC->MoveTo(pcoor(400, 1024 - v4buf[399], rect).x, pcoor(400, 1024 - v4buf[399], rect).y);
		for (int k = 398; k >= 0; k--)
		{
			pCanvasDC->LineTo(pcoor(k + 1, 1024 - v4buf[k], rect).x, pcoor(k + 1, 1024 - v4buf[k], rect).y);
		}


		pCanvasDC->Detach();
		pCanvasWnd->Detach();
		break;
	}
	}

}

CPoint CmfcDlg::pcoor(int x, int y, CRect rect)//���ɵ�����꣺ƽ���ֳ�200�ȷ�
{
	CPoint point;
	int beginx;
	float stepx;
	beginx = rect.TopLeft().x;
	stepx = (float)(rect.BottomRight().x - rect.TopLeft().x) / (float)401;
	point.x = (int)(beginx + x*stepx);
	int beginy;
	float stepy;
	beginy = rect.TopLeft().y;
	stepy = (float)(rect.BottomRight().y - rect.TopLeft().y) / (float)1025;
	point.y = (int)(beginy + y*stepy);
	return point;
}