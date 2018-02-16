
// ClientDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CClientDlg 对话框



CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CLIENT_DIALOG, pParent)
	, m_checkClassID(FALSE)
	, m_checkClassName(FALSE)
	, m_checkCourseID(FALSE)
	, m_checkCourseName(FALSE)
	, m_checkGrade(FALSE)
	, m_checkStudentID(FALSE)
	, m_checkStudentName(FALSE)
	, m_checkStudentSex(FALSE)
	, m_checkStudentTel(FALSE)
	, m_strClassID(_T(""))
	, m_strClassName(_T(""))
	, m_strCourseID(_T(""))
	, m_strCourseName(_T(""))
	, m_strGrade(_T(""))
	, m_strStudentID(_T(""))
	, m_strStudentName(_T(""))
	, m_strStudentTel(_T(""))
	, m_selectTable(0)
	, m_strStudentSex(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strings.push_back(&m_strClassID);
	m_strings.push_back(&m_strClassName);
	m_strings.push_back(&m_strCourseID);
	m_strings.push_back(&m_strCourseName);
	m_strings.push_back(&m_strGrade);
	m_strings.push_back(&m_strStudentID);
	m_strings.push_back(&m_strStudentName);
	m_strings.push_back(&m_strStudentTel);
	m_strings.push_back(&m_strStudentSex);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_classID, m_checkClassID);
	DDX_Check(pDX, IDC_CHECK_className, m_checkClassName);
	DDX_Check(pDX, IDC_CHECK_courseID, m_checkCourseID);
	DDX_Check(pDX, IDC_CHECK_courseName, m_checkCourseName);
	DDX_Check(pDX, IDC_CHECK_grade, m_checkGrade);
	DDX_Check(pDX, IDC_CHECK_studentID, m_checkStudentID);
	DDX_Check(pDX, IDC_CHECK_studentName, m_checkStudentName);
	DDX_Check(pDX, IDC_CHECK_studentSex, m_checkStudentSex);
	DDX_Check(pDX, IDC_CHECK_studentTel, m_checkStudentTel);
	DDX_Text(pDX, IDC_EDIT_classID, m_strClassID);
	DDX_Text(pDX, IDC_EDIT_className, m_strClassName);
	DDX_Text(pDX, IDC_EDIT_courseID, m_strCourseID);
	DDX_Text(pDX, IDC_EDIT_courseName, m_strCourseName);
	DDX_Text(pDX, IDC_EDIT_grade, m_strGrade);
	DDX_Text(pDX, IDC_EDIT_studentID, m_strStudentID);
	DDX_Text(pDX, IDC_EDIT_studentName, m_strStudentName);
	DDX_Text(pDX, IDC_EDIT_studentTel, m_strStudentTel);
	DDX_Control(pDX, IDC_LIST_ANS, m_listAns);
	DDX_Radio(pDX, IDC_RADIO_student, m_selectTable);
	DDX_Text(pDX, IDC_EDIT_studentSex, m_strStudentSex);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_clear, &CClientDlg::OnBnClickedButtonclear)
	ON_BN_CLICKED(IDC_BUTTON_add, &CClientDlg::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTON_delete, &CClientDlg::OnBnClickedButtondelete)
	ON_BN_CLICKED(IDC_BUTTON_modify, &CClientDlg::OnBnClickedButtonmodify)
	ON_BN_CLICKED(IDC_BUTTON_query, &CClientDlg::OnBnClickedButtonquery)
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

BOOL CClientDlg::OnInitDialog()
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
	if (m_StatBar.Create(this))
	{
		// 状态行指示器对应 ID
		static UINT indicators[] =
		{
			ID_SEPARATOR,
		};

		// 设置状态栏指示器 ID 和指示器个数
		m_StatBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

		// 设置状态栏指示器文本
		m_StatBar.SetPaneText(0, L"", 0);

		// 设置状态栏指示器属性
		m_StatBar.SetPaneInfo(0, ID_SEPARATOR, SBPS_NORMAL, 100);



		//设置状态栏高度
		m_StatBar.GetStatusBarCtrl().SetMinHeight(20);

		/* 前期准备工作 *************************************************************************/
		CRect rcClientOld;
		CRect rcClientNew;
		// 用 rcClientOld 获取客户区间
		GetClientRect(rcClientOld);
		// 用 rcClientNew 获得除了 CStatusBar 区的对话框客户区

		RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, rcClientNew);
		/* 这里要注意下如果你在对话框中添加了工具栏和状态栏,那么这里获得的是这些控制栏的矩形区,即高度是控制栏(工具栏加状态栏)的总和,宽度是控制栏中最宽的那个..********/

		/* 重新设置对话框的窗体区间 *************************************************************/
		// 得到对话框窗体区间 
		CRect rcWindow;
		GetWindowRect(rcWindow);
		// 修改对话框宽度和高度,即让对话框添加上 CStatusBar 的高度和适应 CStatusBar 的宽度
		rcWindow.right += rcClientOld.Width() - rcClientNew.Width();
		rcWindow.bottom += rcClientOld.Height() - rcClientNew.Height();
		// 移动对话框
		MoveWindow(rcWindow, FALSE);

		// 显示状态栏
		RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	}

	TcpClient::GlobalInit();
	m_client = new TcpClient(10086, "127.0.0.1");
	m_client->SetReceiveCallback(ReceiveCallback, nullptr);
	TcpClient::MessageData message;
	message.length = 0;
	message.type = TcpClient::MessageType::Nop;
	message.data = nullptr;
	m_client->Send(message);
	m_StatBar.SetPaneText(0, L"就绪", 0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDlg::OnPaint()
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CClientDlg::ReceiveCallback(TcpClient::MessageData* message, void* uesrParam)
{
	CClientDlg* thisDlg = (CClientDlg*)uesrParam;
	TcpClient::MessageData *newMessage = new TcpClient::MessageData;
	newMessage->length = message->length;
	newMessage->data = new char[newMessage->length];
	memcpy_s(newMessage->data, newMessage->length, message->data, message->length);
	newMessage->type = message->type;
	switch (message->type)
	{

	}

	return 0;
}


void CClientDlg::OnBnClickedButtonclear()
{
	// TODO: 在此添加控件通知处理程序代码
	for (auto i = m_strings.begin(); i < m_strings.end(); i++)
	{
		**i = "";
	}
	UpdateData(FALSE);
}


void CClientDlg::OnBnClickedButtonadd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	TcpClient::MessageData message;
	message.length = 0;
	message.type = TcpClient::MessageType::Add;
	message.data = nullptr;
	switch (m_selectTable)
	{
	case SelectTable::tb_student:
	{
		CStringA str;
		str += m_strStudentID;
		str += "\n";
		str += m_strStudentName;
		str += "\n";
		str += m_strStudentSex;
		str += "\n";
		str += m_strStudentTel;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length+1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data+1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_course:
	{
		CStringA str;
		str += m_strCourseID;
		str += "\n";
		str += m_strCourseName;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_class:
	{
		CStringA str;
		str += m_strClassID;
		str += "\n";
		str += m_strClassName;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_studentCourse:
	{
		CStringA str;
		str += m_strStudentID;
		str += "\n";
		str += m_strCourseID;
		str += "\n";
		str += m_strGrade;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_studentClass:
	{
		CStringA str;
		str += m_strStudentID;
		str += "\n";
		str += m_strClassID;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	}
	m_client->Send(message);
	m_StatBar.SetWindowText(L"正在执行");
}


void CClientDlg::OnBnClickedButtondelete()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	TcpClient::MessageData message;
	message.length = 0;
	message.type = TcpClient::MessageType::Delete;
	message.data = nullptr;
	switch (m_selectTable)
	{
	case SelectTable::tb_student:
	{
		CStringA str;
		str += m_strStudentID;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_course:
	{
		CStringA str;
		str += m_strCourseID;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_class:
	{
		CStringA str;
		str += m_strClassID;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_studentCourse:
	{
		CStringA str;
		str += m_strStudentID;
		str += "\n";
		str += m_strCourseID;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_studentClass:
	{
		CStringA str;
		str += m_strStudentID;
		str += "\n";
		str += m_strClassID;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	}
	m_client->Send(message);
	m_StatBar.SetWindowText(L"正在执行");
}


void CClientDlg::OnBnClickedButtonmodify()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	TcpClient::MessageData message;
	message.length = 0;
	message.type = TcpClient::MessageType::Modify;
	message.data = nullptr;
	switch (m_selectTable)
	{
	case SelectTable::tb_student:
	{
		CStringA str;
		str += m_strStudentID;
		str += "\n";
		str += m_strStudentName;
		str += "\n";
		str += m_strStudentSex;
		str += "\n";
		str += m_strStudentTel;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_course:
	{
		CStringA str;
		str += m_strCourseID;
		str += "\n";
		str += m_strCourseName;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_class:
	{
		CStringA str;
		str += m_strClassID;
		str += "\n";
		str += m_strClassName;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_studentCourse:
	{
		CStringA str;
		str += m_strStudentID;
		str += "\n";
		str += m_strCourseID;
		str += "\n";
		str += m_strGrade;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_studentClass:
	{
		CStringA str;
		str += m_strStudentID;
		str += "\n";
		str += m_strClassID;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	}
	m_client->Send(message);
	m_StatBar.SetWindowText(L"正在执行");
}


void CClientDlg::OnBnClickedButtonquery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	TcpClient::MessageData message;
	message.length = 0;
	message.type = TcpClient::MessageType::Query;
	message.data = nullptr;
	switch (m_selectTable)
	{
	case SelectTable::tb_student:
	{
		CStringA str;
		str += m_strStudentID;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_course:
	{
		CStringA str;
		str += m_strCourseID;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_class:
	{
		CStringA str;
		str += m_strClassID;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_studentCourse:
	{
		CStringA str;
		str += m_strStudentID;
		str += "\n";
		str += m_strCourseID;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	case SelectTable::tb_studentClass:
	{
		CStringA str;
		str += m_strStudentID;
		str += "\n";
		str += m_strClassID;
		str += "\n";
		message.length = str.GetLength();
		message.data = new char[message.length + 1];
		message.data[0] = (char)m_selectTable;
		CopyMemory(message.data + 1, str.GetBuffer(), message.length);
	}
	break;
	}

	m_client->Send(message);
	m_StatBar.SetWindowText(L"正在执行");
}
