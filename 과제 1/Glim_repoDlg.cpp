
// Glim_repoDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Glim_repo.h"
#include "Glim_repoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CGlimrepoDlg 대화 상자



CGlimrepoDlg::CGlimrepoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIM_REPO_DIALOG, pParent)
	, StartX(100)
	, StartY(100)
	, imgtimes(11)
	, EndX(400)
	, EndY(400)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlimrepoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, StartX);
	DDX_Text(pDX, IDC_EDIT3, StartY);
	DDX_Text(pDX, IDC_EDIT5, imgtimes);
	DDX_Text(pDX, IDC_EDIT2, EndX);
	DDX_Text(pDX, IDC_EDIT4, EndY);
	DDX_Control(pDX, IDC_RES_TEXT, resText);
}

BEGIN_MESSAGE_MAP(CGlimrepoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CGlimrepoDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CGlimrepoDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CGlimrepoDlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()


// CGlimrepoDlg 메시지 처리기

BOOL CGlimrepoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0, nWidth * nHeight);

	UpdateDisplay();


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGlimrepoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGlimrepoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);  // 그리기를 위한 DC

		// 이미지가 생성되었을 때만 그리기
		if (!m_image.IsNull()) {
			m_image.Draw(dc.GetSafeHdc(), 140, 100);  // 좌표 (140, 100)에 이미지 그리기
		}
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGlimrepoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGlimrepoDlg::OnBnClickedBtnDraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_image != NULL) {
		m_image.Destroy();
	}

	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0, nWidth * nHeight);

	Radius = (rand()%150)+10;
	drawCircle(fm, (StartX - Radius), (StartY-Radius), Radius, 160);

	UpdateDisplay();

}

/*
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//AfxMessageBox(_T("hello window"));
	UpdateData(TRUE);
	int nTest = 0;
	for (int i = 0; i < m_nNum; i++) {
		std::cout << i << std::endl;
		nTest += i;
	}
	m_nNum = nTest;
	//SetDlgItemText(IDC_STATIC_RES, _T("0"));
	UpdateData(false);
}
*/


void CGlimrepoDlg::OnBnClickedBtnAction()
{
	UpdateData(TRUE);
	nSttx = (StartX - Radius);
	nStty = (StartY - Radius);
	Gebx = (EndX-StartX) /(imgtimes-1);
	Geby = (EndY-StartY) /(imgtimes-1);

	CString strFolderPath = FindPath();
	CString filename;

	for (int i = 0; i < imgtimes; i++){
		moveCircle();
		filename.Format(_T("\\save%d.bmp"), i);
		CString strFullPath = strFolderPath + filename;
		m_image.Save(strFullPath);
		Sleep(10);
	}
	UpdateData(false);
	
}


void CGlimrepoDlg::OnBnClickedBtnOpen()
{
	if (m_image != NULL) {
		m_image.Destroy();
	}
	CFileFind file; //디렉토리 탐색 시작
	CString strFolderPath = FindPath();

	//strFolderPath = strFolderPath + _T("\\savehj.bmp");//임시

	CString strPathName;
	CString str = _T("All files(*.*)|*.*|"); 
	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	dlg.m_ofn.lpstrInitialDir = strFolderPath;

	

	if (dlg.DoModal() == IDOK)
	{
		strPathName = dlg.GetPathName();
		//SetDlgItemText(IDC_EDIT1, strPathName);

		m_image.Load(strPathName);
		UpdateDisplay();

		int centerX = 100;
		int centerY = 100;
		FindCenter(centerX,centerY);
		CString centerText;
		centerText.Format(_T("  %d , %d"), centerX, centerY);
		resText.SetWindowTextW(centerText);
		DrawXOnImage(centerX, centerY);

		UpdateDisplay();
	}
	else {
		return;
	}
}

void CGlimrepoDlg::UpdateDisplay() {
	CClientDC dc(this);
	m_image.Draw(dc, 140, 100);
}

CString CGlimrepoDlg::FindPath() {
	
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);
	CString strFolderPath(chFilePath);
	strFolderPath = strFolderPath.Left(strFolderPath.ReverseFind('\\')) + _T("\\image");

	CFileFind file; //디렉토리 탐색 시작
	BOOL bResult = file.FindFile(strFolderPath);
	if (!bResult) {
		// 디렉토리가 없으면 생성
		CreateDirectory(strFolderPath, NULL);
	}

	
	return strFolderPath;
}

void CGlimrepoDlg::moveCircle() {
	int nGray = 160;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int nRadius = Radius;
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0, nWidth * nHeight);
	drawCircle(fm, nSttx, nStty, nRadius, nGray);
	nSttx += Gebx;
	nStty += Geby;
	//drawCircle(fm, nSttx, nStty, nRadius, 0xff);
	//drawCircle(fm, ++nSttx, ++nStty, nRadius, nGray);

	UpdateDisplay();
}

BOOL  CGlimrepoDlg::validImgPos(int x, int y) {
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));

}

void CGlimrepoDlg::drawCircle(unsigned char* fm, double x, double y, int nRadius, int nGray) {
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();

	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius)) {
				fm[j * nPitch + i] = nGray;
			}
		}
	}
	
}

bool CGlimrepoDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius) {
	bool bRet = false;
	double dx = i - nCenterX;
	double dy = j - nCenterY;
	double dDist = dx * dx + dy * dy;
	
	if ((dDist < nRadius * nRadius) && (i >= 0) && (j>=0) && (i < 640) && (j < 480)) {
		bRet = true;
	}
	
	return bRet;
}

void CGlimrepoDlg::DrawXOnImage(int x, int y)
{
	
	HDC hdc = m_image.GetDC();
	if (hdc == nullptr) {
		return;
	}

	CDC* pDC = CDC::FromHandle(hdc);

	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));  
	CPen* pOldPen = pDC->SelectObject(&pen); 
	int geb = 5;
	int x1 = x - geb ;
	int y1 = y - geb;
	int x2 = x + geb;
	int y2 = y + geb;

	pDC->MoveTo(x1, y1); // 시작점 (왼쪽 위)
	pDC->LineTo(x2, y2); // 끝점 (오른쪽 아래)

	pDC->MoveTo(x2, y1); // 시작점 (오른쪽 위)
	pDC->LineTo(x1, y2); // 끝점 (왼쪽 아래)

	CString centerText;
	centerText.Format(_T("(%d, %d)"), x, y);

	pDC->SetTextColor(RGB(0,0, 0));
	pDC->TextOut(x + 10, y + 10, centerText); 

	pDC->SelectObject(pOldPen);

	m_image.ReleaseDC();
}

void CGlimrepoDlg::FindCenter(int& x, int& y) {

	unsigned char* fm = (unsigned char*)m_image.GetBits();

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	int nTh = 100;
	CRect rect(0, 0, nWidth, nHeight);
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	for (int j = rect.top; j < rect.bottom; j++){
		for (int i = rect.left; i < rect.right; i++){
			if (fm[j * nPitch + i] > nTh) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}

	}
	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;

	x = int(dCenterX);
	y = int(dCenterY);
}