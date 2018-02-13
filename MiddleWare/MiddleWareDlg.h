
// MiddleWareDlg.h: 头文件
//

#pragma once
#include "afxcmn.h"
#include "TcpSocketManager.h"


// CMiddleWareDlg 对话框
class CMiddleWareDlg : public CDialog
{
	// 构造
	public:
	typedef struct PPPPPPQQQ
	{
		TcpClient* tcpClient;
	}TcpClientData;
	CMiddleWareDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MIDDLEWARE_DIALOG };
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
	public:
	static int AcceptCallback(TcpClient * client, void * uesrParam);
	static int ReceiveCallback(TcpClient::MessageData* message, void* uesrParam);

	DECLARE_MESSAGE_MAP()
	public:
	CListCtrl m_clientList;
	TcpServer* m_server;
	virtual BOOL DestroyWindow();
};
