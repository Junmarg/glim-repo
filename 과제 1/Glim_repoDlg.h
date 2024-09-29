
// Glim_repoDlg.h: 헤더 파일
//

#pragma once


// CGlimrepoDlg 대화 상자
class CGlimrepoDlg : public CDialogEx
{
private:
	CImage m_image;
	BOOL validImgPos(int x, int y);
// 생성입니다.
public:
	CGlimrepoDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	int Radius;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIM_REPO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();
	void UpdateDisplay();
	CString FindPath();
	void moveCircle();
	void drawCircle(unsigned char* fm, double x, double y, int nRadius, int nGray);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void DrawXOnImage(int x, int y);
	void FindCenter(int& x, int& y);
	int StartX;
	int StartY;
	double nSttx = 0;
	double nStty = 0;
	double Gebx = 1;
	double Geby = 1;
	int imgtimes;
	int EndX;
	int EndY;
	CStatic resText;
};
