
// setDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "set.h"
#include "setDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "setCalc.h"


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CsetDlg �Ի���




CsetDlg::CsetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CsetDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsetDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_INPUT, inputFrame);
    DDX_Control(pDX, IDC_EDIT_OUTPUT, showFrame);
    DDX_Control(pDX, IDC_COMBO_SET, chooseSet);
    DDX_Control(pDX, IDC_STATIC_INFO, infoStatic);
    DDX_Control(pDX, IDC_STATIC_COPY, copyStatic);
}

BEGIN_MESSAGE_MAP(CsetDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &CsetDlg::OnBnClickedOk)
    ON_EN_UPDATE(IDC_EDIT_INPUT, &CsetDlg::OnEnUpdateEditInput)
//    ON_BN_CLICKED(IDC_MFCLINK_COPY, &CsetDlg::OnBnClickedMfclinkCopy)
ON_STN_CLICKED(IDC_STATIC_COPY, &CsetDlg::OnStnClickedStaticCopy)
ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CsetDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CsetDlg ��Ϣ�������

BOOL CsetDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    //Ϊ�����˵������Ŀ
    for (TCHAR c = TCHAR('A'); c <= TCHAR('Z'); c++)
    {
        chooseSet.AddString(CString(c));
    }
    chooseSet.SetCurSel(0);

    //Ϊcopy��ť�����»���
    LOGFONT lf;
    copyStatic.GetFont()->GetLogFont(&lf);
    lf.lfUnderline = true;
    CFont *pFont = new CFont();
    pFont->CreateFontIndirect(&lf);
    copyStatic.SetFont(pFont);

    //��ʾ��
    MessageBox(CString("Ϊ�������룬����ʱ�����ã�\r\n ") + OP_INPUT_UNION + _T("     ����   ") + OP_UNION + 
        _T("\r\n ") + OP_INPUT_INTERSECTION + _T("   ����   ") + OP_INTERSECTION +
        _T("\r\n ") + OP_INPUT_SYM_DIFFERENCE + _T("   ����   ") + OP_SYMMETRIC_DIFFERENCE +
        _T("\r\n ") + OP_INPUT_DESCARTES + _T("    ����   ") + OP_DESCARTES +
        _T("\r\n ") + OP_INPUT_COMPOUND + _T("     ����   ") + OP_COMPOUND +
        _T("\r\n ") + OP_INPUT_LIMIT + _T("  ����   ") + OP_LIMIT +
        _T("\r\n ") + OP_INPUT_EMPTY_SET + _T("    ����   ") + OP_EMPTY_SET, 
        _T("Important Notification"), MB_ICONEXCLAMATION);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CsetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CsetDlg::OnPaint()
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
HCURSOR CsetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CsetDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    //CDialogEx::OnOK();
    CString sInput;
    inputFrame.GetWindowTextW(sInput);

    CString sChoose;
    chooseSet.GetLBText(chooseSet.GetCurSel(), sChoose);
    CString sResult;
    if (CalcExpression(sInput, sResult, sChoose[0]))
    {
        infoStatic.SetWindowTextW(CString(_T("�ѽ� ")) + sChoose[0] + _T(" ��ֵΪ��"));
        showFrame.SetWindowTextW(sResult);
    }
    else
    {
        MessageBox(_T("Input expression is invalid."));
    }
}


void CsetDlg::OnEnUpdateEditInput()
{
    // TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
    // ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
    // �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
    // ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    DWORD pos = inputFrame.GetSel();
    CString sInput;
    inputFrame.GetWindowTextW(sInput);
    
    //�������ַ����е�ȫ��������滻�ɰ�������
    sInput.Replace(OP_FULL_LEFT_BRACE, OP_LEFT_BRACE);
    sInput.Replace(OP_FULL_RIGHT_BRACE, OP_RIGHT_BRACE);
    sInput.Replace(OP_FULL_LEFT_ANGLE_BKT, OP_LEFT_ANGLE_BKT);
    sInput.Replace(OP_FULL_RIGHT_ANGLE_BKT, OP_RIGHT_ANGLE_BKT);
    sInput.Replace(OP_FULL_LEFT_BRACKET, OP_LEFT_BRACKET);
    sInput.Replace(OP_FULL_RIGHT_BRACKET, OP_RIGHT_BRACKET);
    sInput.Replace(OP_FULL_LEFT_PARENTHESIS, OP_LEFT_PARENTHESIS);
    sInput.Replace(OP_FULL_RIGHT_PARENTHESIS, OP_RIGHT_PARENTHESIS);
    sInput.Replace(OP_FULL_COMMA, OP_COMMA);
    sInput.Replace(OP_FULL_COMPOUND, OP_COMPOUND);
    sInput.Replace(OP_FULL_EMPTY_SET, OP_EMPTY_SET);
    //�滻���������
    sInput.Replace(OP_INPUT_UNION, OP_UNION);
    sInput.Replace(OP_INPUT_INTERSECTION, OP_INTERSECTION);
    sInput.Replace(OP_INPUT_SYM_DIFFERENCE, OP_SYMMETRIC_DIFFERENCE);
    sInput.Replace(OP_INPUT_DESCARTES, OP_DESCARTES);
    sInput.Replace(OP_INPUT_COMPOUND, OP_COMPOUND);
    sInput.Replace(OP_INPUT_LIMIT, OP_LIMIT);
    sInput.Replace(OP_INPUT_EMPTY_SET, OP_EMPTY_SET);
    //ȥ�������ַ����еĻ�����ո�
    sInput.Replace(_T("\r\n"), _T(""));
    sInput.Replace(_T("\r"), _T(""));
    sInput.Replace(_T("\n"), _T(""));
    sInput.Replace(_T(" "), _T(""));
    sInput.Replace(_T("��"), _T(""));//ȫ�ǿո�

    inputFrame.SetWindowTextW(sInput);
    inputFrame.SetSel(pos);
}


//void CsetDlg::OnBnClickedMfclinkCopy()
//{
//    // TODO: �ڴ���ӿؼ�֪ͨ����������
//    inputFrame.SetSel(0, -1);
//    inputFrame.Copy();
//    MessageBox(_T("�Ѹ��Ƶ����а�"));
//}


void CsetDlg::OnStnClickedStaticCopy()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    showFrame.SetSel(0, -1);
    showFrame.Copy();
    MessageBox(_T("�Ѹ��Ƶ����а�"));
}


void CsetDlg::OnBnClickedButtonClear()
{
    inputFrame.SetWindowTextW(_T(""));
    showFrame.SetWindowTextW(_T(""));
    // TODO: �ڴ���ӿؼ�֪ͨ����������
}
