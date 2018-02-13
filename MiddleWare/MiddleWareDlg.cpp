
// MiddleWareDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MiddleWare.h"
#include "MiddleWareDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static CMiddleWareDlg* g_this;

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


// CMiddleWareDlg 对话框



CMiddleWareDlg::CMiddleWareDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MIDDLEWARE_DIALOG, pParent)
	, m_server(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMiddleWareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_clientList);
}

BEGIN_MESSAGE_MAP(CMiddleWareDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMiddleWareDlg 消息处理程序

BOOL CMiddleWareDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	g_this = this;
	Socket::GlobalInit();
	m_clientList.ModifyStyle(LVS_ICON, LVS_REPORT | LVS_SINGLESEL);
	m_clientList.SetExtendedStyle(m_clientList.GetExtendedStyle() | LVS_EX_DOUBLEBUFFER | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_clientList.InsertColumn(0, _T("clientName"), LVCFMT_LEFT, 100);
	m_clientList.InsertColumn(1, _T("ip"), LVCFMT_LEFT, 100);
	m_clientList.InsertColumn(2, _T("port"), LVCFMT_LEFT, 50);

	tcpSocketManager.StartServer(10086);
	m_server = tcpSocketManager.geTcpServer();
	m_server->SetAcceptCallback(AcceptCallback, this);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMiddleWareDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMiddleWareDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMiddleWareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CMiddleWareDlg::AcceptCallback(TcpClient* client, void* uesrParam)
{
	CMiddleWareDlg* thisDlg = (CMiddleWareDlg*)uesrParam;
	TcpClientData* clientData = new TcpClientData;
	clientData->tcpClient = client;
	client->SetReceiveCallback(ReceiveCallback, clientData);
	int itemCount = thisDlg->m_clientList.GetItemCount();
	thisDlg->m_clientList.InsertItem(itemCount, L"");

	CString strIP;
	strIP = client->GetIP().c_str();
	thisDlg->m_clientList.SetItemText(itemCount, 1, strIP);
	CString strPort;
	strPort.Format(L"%d", client->GetPort());
	thisDlg->m_clientList.SetItemText(itemCount, 2, strPort);
	thisDlg->m_clientList.SetItemData(itemCount, (DWORD_PTR)clientData);

	return 0;
}

int CMiddleWareDlg::ReceiveCallback(TcpClient::MessageData * message, void * uesrParam)
{
	TcpClientData* clientData = (TcpClientData*)uesrParam;
	if (message == nullptr)
	{
		int itemCount = g_this->m_clientList.GetItemCount();
		for (int i = 0; i < itemCount; i++)
		{
			if (clientData == (TcpClientData*)g_this->m_clientList.GetItemData(i))
			{
				g_this->m_clientList.DeleteItem(i);
				return 0;
			}
		}
	}
	switch (message->type)
	{
	}
	return 0;
}


BOOL CMiddleWareDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	Socket::GlobalCleanUp();

	return CDialog::DestroyWindow();
}
