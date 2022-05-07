
// DIPDlg.h : header file
//

#pragma once
#include "opencv.hpp"

using namespace std;
using namespace cv;

// CDIPDlg dialog
class CDIPDlg : public CDialogEx
{
// Construction
public:
	CDIPDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();


	Mat src;//the original image 
//	afx_msg void OnBnClickedButton1();
	int m_w;
	int m_h;
	afx_msg void OnBnClickedResize();
	afx_msg void OnBnClickedHshear();
	double m_shear_ratio;
	double m_angle;
	afx_msg void OnBnClickedRotate();
	afx_msg void OnBnClickedVshear();
	afx_msg void OnBnClickedHisteq();
	int m_a;
	int m_b;
	int m_ga;
	int m_gb;
	afx_msg void OnBnClickedLcb();
	afx_msg void OnBnClickedDra();

	afx_msg void OnBnClickedSmooth();
//	int m_filter_type;
	int m_filter_size;
	
	int m_filter_type;
	int m_c;
	afx_msg void OnBnClickedVideo();
	int m_sharpen_type;
	afx_msg void OnBnClickedSharpen();
	int m_thre;
	afx_msg void OnBnClickedTh();
	afx_msg void OnBnClickedAdth();
	int m_blocksize;
	int m_C;
	int m_seedx;
	int m_seedy;
	int m_region;
	afx_msg void OnBnClickedRegion();
	
	
	afx_msg void OnBnClickedErode();
	int m_SE_size;
	int m_SE_shape;
	afx_msg void OnBnClickedDilate();
	afx_msg void OnBnClickedMorphopen();
	afx_msg void OnBnClickedMorphclose();
	int m_color_mode;
	afx_msg void OnBnClickedConvertcolor();
	afx_msg void OnBnClickedIntslicing();
	afx_msg void OnBnClickedInttransfer();
	int m__filter__type;
	int m__filter__size;
	afx_msg void OnBnClickedFacedetect();
	afx_msg void OnBnClickedTracking();
};
