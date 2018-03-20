
// mfcDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CmfcDlg 对话框



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


// CmfcDlg 消息处理程序

BOOL CmfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CmfcDlg, CDialogEx)
	ON_EVENT(CmfcDlg, IDC_MSCOMM1, 1, CmfcDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CmfcDlg::OnCommMscomm1()
{
	// TODO: 在此处添加消息处理程序代码
	static unsigned int cnt = 0;
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	long len, k;
	unsigned int data[1024] = { 0 };
	byte rxdata[1024]; //设置 BYTE 数组
	CString strtemp;
	if (mycomm.get_CommEvent() == 2) //值为 2 表示接收缓冲区内有字符
	{
		int tempt1 = 0;
		int tempt2 = 0;
		int tempt3 = 0;
		int tempt4 = 0;
		cnt++;
		variant_inp = mycomm.get_Input(); //读缓冲区消息
		safearray_inp = variant_inp; ///变量转换
		len = safearray_inp.GetOneDimSize(); //得到有效的数据长度
		for (k = 0; k < len; k++)
		{
			safearray_inp.GetElement(&k, rxdata + k);
		}


		for (k = 0; k < 4; k++) //将数组转换为 CString 型变量
		{
			//strtemp.Format(_T("%x"), *(rxdata + k));
			//m_EditReceive += strtemp;
			//CString temp = _T("\r\n"); //换行
			//m_EditReceive += temp;
			tempt1 += pow(256, k) * (*(rxdata + k));
		}
		record << tempt1 << '\t';
		for (k = 4; k < 8; k++) //将数组转换为 CString 型变量
		{

			tempt2 += pow(256, k-4) * (*(rxdata + k));
		}
		record << tempt2 << '\t';
		for (k = 8; k <12 ; k++) //将数组转换为 CString 型变量
		{

			tempt3 += pow(256, k-8) * (*(rxdata + k));
		}
		record << tempt3 << '\t';
		for (k = 12; k < 16; k++) //将数组转换为 CString 型变量
		{

			tempt4 += pow(256, k-12) * (*(rxdata + k));
		}
		record << tempt4 << endl;
		intv1 = tempt1;
		intv2 = tempt2;
		intv3 = tempt3;
		intv4 = tempt4;
	}
	UpdateData(FALSE); //更新编辑框内容
}


void CmfcDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	if (mycomm.get_PortOpen()) //如果串口是打开的，则行关闭串口
	{
		mycomm.put_PortOpen(FALSE);
	}
	mycomm.put_CommPort(6); //选择COM1
	mycomm.put_InBufferSize(1024); //接收缓冲区
	mycomm.put_OutBufferSize(1024);//发送缓冲区
	mycomm.put_InputLen(0);//设置当前接收区数据长度为0,表示全部读取
	mycomm.put_InputMode(1);//以二进制方式读写数据
	mycomm.put_RThreshold(1);//接收缓冲区有1个及1个以上字符时，将引发接收数据的OnComm事件
	mycomm.put_Settings(_T("19200,e,8,1"));//波特率19200无检验位，8个数据位，1个停止位
	if (!mycomm.get_PortOpen())//如果串口没有打开则打开
	{
		mycomm.put_PortOpen(TRUE);//打开串口
		Beep(1000, 50);
		Beep(1000 * 1.05946, 50);
		Beep(1000 * 1.05946 * 1.05946, 50);
		Beep(1000 * 1.05946 * 1.05946 * 1.05946, 50);
	}
	else
	{
		mycomm.put_OutBufferCount(0);
		AfxMessageBox(_T("串口6打开失败"));
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
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	mycomm.put_PortOpen(FALSE);//关闭串口
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
		pCanvasWnd->GetClientRect(&rect); //绘制背景
		CBrush br(RGB(255, 255, 255));//绘制白色背景
		pCanvasDC->FillRect(&rect, &br); //创建画笔 
		pCanvasDC->Detach();
		pCanvasWnd->Detach();
		//2-background
		pCanvasWnd = GetDlgItem(IDC_CANVAS2);
		pCanvasDC = pCanvasWnd->GetDC();
		pCanvasWnd->GetClientRect(&rect); //绘制背景
		pCanvasDC->FillRect(&rect, &br); //创建画笔 
		pCanvasDC->Detach();
		pCanvasWnd->Detach();
		//3-background
		pCanvasWnd = GetDlgItem(IDC_CANVAS3);
		pCanvasDC = pCanvasWnd->GetDC();
		pCanvasWnd->GetClientRect(&rect); //绘制背景
		pCanvasDC->FillRect(&rect, &br); //创建画笔 
		pCanvasDC->Detach();
		pCanvasWnd->Detach();
		//4-background
		pCanvasWnd = GetDlgItem(IDC_CANVAS4);
		pCanvasDC = pCanvasWnd->GetDC();
		pCanvasWnd->GetClientRect(&rect); //绘制背景
		pCanvasDC->FillRect(&rect, &br); //创建画笔 
		pCanvasDC->Detach();
		pCanvasWnd->Detach();

		pCanvasWnd = GetDlgItem(IDC_CANVAS1);
		pCanvasDC = pCanvasWnd->GetDC();
		pCanvasWnd->GetClientRect(&rect); //绘制背景
		CPen NewPen;
		NewPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		CPen *OldPen; OldPen = pCanvasDC->SelectObject(&NewPen); //画线
		pCanvasDC->MoveTo(pcoor(400, 1024 - v1buf[399], rect).x, pcoor(400, 1024 - v1buf[399], rect).y);
		for (int k = 398; k >= 0; k--)
		{
			pCanvasDC->LineTo(pcoor(k + 1, 1024 - v1buf[k], rect).x, pcoor(k + 1, 1024 - v1buf[k], rect).y);
		}


		pCanvasWnd = GetDlgItem(IDC_CANVAS2);
		pCanvasDC = pCanvasWnd->GetDC();
		pCanvasWnd->GetClientRect(&rect); //绘制背景
		NewPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		OldPen = pCanvasDC->SelectObject(&NewPen); //画线
		pCanvasDC->MoveTo(pcoor(400, 1024 - v2buf[399], rect).x, pcoor(400, 1024 - v2buf[399], rect).y);
		for (int k = 398; k >= 0; k--)
		{
			pCanvasDC->LineTo(pcoor(k + 1, 1024 - v2buf[k], rect).x, pcoor(k + 1, 1024 - v2buf[k], rect).y);
		}


		pCanvasWnd = GetDlgItem(IDC_CANVAS3);
		pCanvasDC = pCanvasWnd->GetDC();
		pCanvasWnd->GetClientRect(&rect); //绘制背景
		NewPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		OldPen = pCanvasDC->SelectObject(&NewPen); //画线
		pCanvasDC->MoveTo(pcoor(400, 1024 - v3buf[399], rect).x, pcoor(400, 1024 - v3buf[399], rect).y);
		for (int k = 398; k >= 0; k--)
		{
			pCanvasDC->LineTo(pcoor(k + 1, 1024 - v3buf[k], rect).x, pcoor(k + 1, 1024 - v3buf[k], rect).y);
		}


		pCanvasWnd = GetDlgItem(IDC_CANVAS4);
		pCanvasDC = pCanvasWnd->GetDC();
		pCanvasWnd->GetClientRect(&rect); //绘制背景
		NewPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		OldPen = pCanvasDC->SelectObject(&NewPen); //画线
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

CPoint CmfcDlg::pcoor(int x, int y, CRect rect)//生成点的坐标：平均分成200等分
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