
// ClientDlg.h: 头文件
//

#pragma once

#include "TcpClient.h"
#include "afxcmn.h"
#include <map>

// CClientDlg 对话框
class CClientDlg : public CDialog
{
// 构造
public:
	typedef struct
	{
		CStringA updateTime;
		std::map<CStringA, CStringA> dataMap;
	}LocalData;
	CClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
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
	static int ReceiveCallback(TcpClient::MessageData * message, void * uesrParam);
	DECLARE_MESSAGE_MAP()

	public:
	TcpClient * m_client;
	BOOL m_checkClassID;
	BOOL m_checkClassName;
	BOOL m_checkCourseID;
	BOOL m_checkCourseName;
	BOOL m_checkGrade;
	BOOL m_checkStudentID;
	BOOL m_checkStudentName;
	BOOL m_checkStudentSex;
	BOOL m_checkStudentTel;
	CString m_strClassID;
	CString m_strClassName;
	CString m_strCourseID;
	CString m_strCourseName;
	CString m_strGrade;
	CString m_strStudentID;
	CString m_strStudentName;
	CString m_strStudentTel;
	CListCtrl m_listAns;
	SelectTable m_selectTable;
	CString m_strStudentSex;
	std::vector<CString*> m_strings;
	afx_msg void OnBnClickedButtonclear();
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtondelete();
	afx_msg void OnBnClickedButtonmodify();
	afx_msg void OnBnClickedButtonquery();
	void AdjustColumnWidth();
	afx_msg void OnUpdatePane(CCmdUI* pCmdUI);
	CStatusBar m_StatBar;

	LocalData m_localData;
	CStringA m_currentQuery;
	afx_msg void OnRclickListAns(NMHDR *pNMHDR, LRESULT *pResult);
};
