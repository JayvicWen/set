
// setDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CsetDlg �Ի���
class CsetDlg : public CDialogEx
{
// ����
public:
	CsetDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SET_DIALOG };

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
    CEdit inputFrame;
    CEdit showFrame;
    afx_msg void OnBnClickedOk();
    afx_msg void OnEnUpdateEditInput();
    CComboBox chooseSet;
//    afx_msg void OnBnClickedMfclinkCopy();
    CStatic infoStatic;
    afx_msg void OnStnClickedStaticCopy();
    CStatic copyStatic;
    afx_msg void OnBnClickedButtonClear();
};
