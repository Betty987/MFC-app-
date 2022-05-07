
// DIPDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "DIP.h"
#include "DIPDlg.h"
#include "afxdialogex.h"
#include <math.h>
#include "opencv2/tracking.hpp"
#include <opencv2/core/ocl.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
using namespace cv;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CDIPDlg dialog



CDIPDlg::CDIPDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIP_DIALOG, pParent)
	, m_w(0)
	, m_h(0)
	, m_shear_ratio(0)
	, m_angle(0)
	, m_a(0)
	, m_b(0)
	, m_ga(0)
	, m_gb(0)
	, m_c(0)
	, m_sharpen_type(0)
	, m_thre(0)
	, m_blocksize(0)
	, m_C(0)
	
	
	, m_seedx(0)
	, m_seedy(0)
	, m_region(0)
	

	
	, m_SE_size(3)
	, m_SE_shape(0)
	, m_color_mode(0)
	, m__filter__type(0)
	, m__filter__size(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDIPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_w);
	DDX_Text(pDX, IDC_EDIT2, m_h);
	DDX_Text(pDX, IDC_EDIT4, m_shear_ratio);
	DDX_Text(pDX, IDC_EDIT3, m_angle);
	DDX_Text(pDX, IDC_EDIT5, m_a);
	DDX_Text(pDX, IDC_EDIT6, m_b);
	DDX_Text(pDX, IDC_EDIT7, m_ga);
	DDX_Text(pDX, IDC_EDIT8, m_gb);




	DDX_Text(pDX, IDC_EDIT9, m_c);
	DDX_Radio(pDX, IDC_RADIO1, m_sharpen_type);
	DDX_Text(pDX, IDC_EDIT11, m_thre);
	DDX_Text(pDX, IDC_EDIT12, m_blocksize);
	DDX_Text(pDX, IDC_EDIT13, m_C);

	DDX_Text(pDX, IDC_EDIT14, m_seedx);
	DDX_Text(pDX, IDC_EDIT15, m_seedy);
	DDX_Text(pDX, IDC_EDIT16, m_region);



	DDX_Text(pDX, IDC_EDIT17, m_SE_size);
	DDX_Radio(pDX, IDC_RADIO7, m_SE_shape);
	DDX_Radio(pDX, IDC_RADIO10, m_color_mode);
	DDX_Radio(pDX, IDC_RADIO13, m__filter__type);
	DDX_Text(pDX, IDC_EDIT18, m__filter__size);
}

BEGIN_MESSAGE_MAP(CDIPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &CDIPDlg::OnBnClickedOpen)
//	ON_BN_CLICKED(IDC_BUTTON1, &CDIPDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_Resize, &CDIPDlg::OnBnClickedResize)
ON_BN_CLICKED(IDC_HSHEAR, &CDIPDlg::OnBnClickedHshear)
ON_BN_CLICKED(IDC_ROTATE, &CDIPDlg::OnBnClickedRotate)
ON_BN_CLICKED(IDC_VSHEAR, &CDIPDlg::OnBnClickedVshear)
ON_BN_CLICKED(IDC_HISTEQ, &CDIPDlg::OnBnClickedHisteq)
ON_BN_CLICKED(IDC_LCB, &CDIPDlg::OnBnClickedLcb)
ON_BN_CLICKED(IDC_DRA, &CDIPDlg::OnBnClickedDra)
ON_BN_CLICKED(IDC_SMOOTH, &CDIPDlg::OnBnClickedSmooth)
ON_BN_CLICKED(IDC_VIDEO, &CDIPDlg::OnBnClickedVideo)
ON_BN_CLICKED(IDC_SHARPEN, &CDIPDlg::OnBnClickedSharpen)
ON_BN_CLICKED(IDC_TH, &CDIPDlg::OnBnClickedTh)
ON_BN_CLICKED(IDC_ADTH, &CDIPDlg::OnBnClickedAdth)
ON_BN_CLICKED(IDC_REGION, &CDIPDlg::OnBnClickedRegion)
ON_BN_CLICKED(IDC_ERODE, &CDIPDlg::OnBnClickedErode)
ON_BN_CLICKED(IDC_DILATE, &CDIPDlg::OnBnClickedDilate)
ON_BN_CLICKED(IDC_MORPHOPEN, &CDIPDlg::OnBnClickedMorphopen)
ON_BN_CLICKED(IDC_MORPHCLOSE, &CDIPDlg::OnBnClickedMorphclose)
ON_BN_CLICKED(IDC_CONVERTCOLOR, &CDIPDlg::OnBnClickedConvertcolor)
ON_BN_CLICKED(IDC_INTSLICING, &CDIPDlg::OnBnClickedIntslicing)
ON_BN_CLICKED(IDC_INTTRANSFER, &CDIPDlg::OnBnClickedInttransfer)
ON_BN_CLICKED(IDC_FACEDETECT, &CDIPDlg::OnBnClickedFacedetect)
ON_BN_CLICKED(IDC_TRACKING, &CDIPDlg::OnBnClickedTracking)
END_MESSAGE_MAP()


// CDIPDlg message handlers

BOOL CDIPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	namedWindow("view");

	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);

	::SetParent(hWnd, GetDlgItem(IDC_PIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);





	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDIPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDIPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDIPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDIPDlg::OnBnClickedOpen()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, _T("*.jpg"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		_T("Image files(*.bmp,*.jpg)|*.bmp;*.jpg|All files(*.*)|*.*|"), NULL);

	dlg.m_ofn.lpstrTitle = _T("Open Images");

	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	CString filePath = dlg.GetPathName();

	string sFileName = (LPCTSTR)filePath;

	src = imread(sFileName);

	if (src.empty())
	{
		AfxMessageBox(_T("Reading image error!"));
		return;
	}
	CRect rect;

	GetDlgItem(IDC_PIC)->GetClientRect(&rect);

	Mat img;

	resize(src, img, Size(rect.Width(), rect.Height()));

	imshow("view", img);
	
}





void CDIPDlg::OnBnClickedResize()
{
	// TODO: Add your control notification handler code here

	if (src.empty())
	{
		AfxMessageBox(_T("Please open an image!"));
		return;
	}
	UpdateData(TRUE);
	Mat dst;
	resize(src, dst, Size(m_w, m_h));

	imshow("Resize", dst);
	
}


void CDIPDlg::OnBnClickedHshear()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open image!"));
		return;
	}

	UpdateData(TRUE);

	Mat dst;

	Mat hShear_mat(2, 3, CV_32FC1);//H shear matrix
	Point2f srcPoints[3];//3 points from the original image
	Point2f dstPoints[3];//3 points from the result image

	//3 points from the original image
	srcPoints[0] = Point2f(0, 0);//topleft
	srcPoints[1] = Point2f(0, src.rows);//bottomleft
	srcPoints[2] = Point2f(src.cols, 0);//topright

	//3 points from the result image
	if (m_shear_ratio >= 0)
	{
		dstPoints[0] = Point2f(src.rows*m_shear_ratio, 0);//topleft
		dstPoints[1] = Point2f(0, src.rows);//bottomleft
		dstPoints[2] = Point2f(src.cols + src.rows*m_shear_ratio, 0);//topright
	}
	else
	{
		dstPoints[0] = Point2f(0, 0);//topleft
		dstPoints[1] = Point2f(src.rows*(-m_shear_ratio), src.rows);//bottomleft
		dstPoints[2] = Point2f(src.cols, 0);//topright
	}


	hShear_mat = getAffineTransform(srcPoints, dstPoints);//caculate the transfer matrix

	//calculate canvas
	int dst_width = src.cols + src.rows*fabs(m_shear_ratio);
	int dst_height = src.rows;

	warpAffine(src, dst, hShear_mat, Size(dst_width, dst_height));

	imshow("hshear", dst);


}


void CDIPDlg::OnBnClickedRotate()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open image!"));
		return;
	}

	UpdateData(TRUE);
	Mat dst;

	Mat rot_mat(2, 3, CV_32FC1);//Rotation matrix

	//caculate canvas
	double sin_value = sin(m_angle*CV_PI / 180);
	double cos_value = cos(m_angle*CV_PI / 180);

	int width = src.cols;
	int height = src.rows;

	int rotate_width = (int)(height*fabs(sin_value) + width * fabs(cos_value));
	int rotate_height = (int)(width*fabs(sin_value) + height * fabs(cos_value));

	//caculate rotation matrix
	Point center = Point(src.cols / 2, src.rows / 2);
	double angle = m_angle;
	double scale = 1;

	rot_mat = getRotationMatrix2D(center, angle, scale);

	//calculate translation
	rot_mat.at<double>(0, 2) += (rotate_width - width) / 2;
	rot_mat.at<double>(1, 2) += (rotate_height - height) / 2;

	//Rotation
	warpAffine(src, dst, rot_mat, Size(rotate_width, rotate_height));
	imshow("rotate", dst);
}


void CDIPDlg::OnBnClickedVshear()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open image!"));
		return;
	}

	UpdateData(TRUE);

	Mat dst;

	Mat hShear_mat(2, 3, CV_32FC1);//V shear matrix
	Point2f srcPoints[3];//3 points from the original image
	Point2f dstPoints[3];//3 points from the result image

	//3 points from the original image
	srcPoints[0] = Point2f(0, 0);//topleft
	srcPoints[1] = Point2f(0, src.rows);//bottomleft
	srcPoints[2] = Point2f(src.cols, 0);//topright

	//3 points from the result image
	if (m_shear_ratio >= 0)
	{
		dstPoints[0] = Point2f(0, 0);//topleft
		dstPoints[1] = Point2f(0, src.rows);//bottomleft
		dstPoints[2] = Point2f(src.cols, src.cols*m_shear_ratio);//topright
	}
	else
	{
		dstPoints[0] = Point2f(0, src.cols*(-m_shear_ratio));//topleft
		dstPoints[1] = Point2f(0, src.rows+src.cols*(-m_shear_ratio));//bottomleft
		dstPoints[2] = Point2f(src.cols,0);//topright
	}


	hShear_mat = getAffineTransform(srcPoints, dstPoints);//calculate the transfer matrix

	//calculate canvas
	int dst_width = src.cols;
	int dst_height = src.rows+ src.cols*fabs(m_shear_ratio);

	warpAffine(src, dst, hShear_mat, Size(dst_width, dst_height));

	imshow("vshear", dst);

}


void CDIPDlg::OnBnClickedHisteq()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open an image!"));
		return;
	}

	
	Mat dst;
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	equalizeHist(gray, dst);
	imshow("Hist", dst);


}


void CDIPDlg::OnBnClickedLcb()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open image!"));
		return;
	}

	UpdateData(TRUE);
	Mat dst;
	Mat gray_img;
	cvtColor(src, gray_img, CV_BGR2GRAY);
	dst = gray_img.clone();
	for (int i = 0; i < gray_img.rows;i++) {
		for (int j = 0; j < gray_img.cols; j++) {
			int temp = gray_img.at<uchar>(i, j);
			if (temp < m_a) {
				dst.at<uchar>(i, j) = temp * m_ga / m_a;
			}
			else if (temp <= m_b) {
				dst.at<uchar>(i, j) = (temp-m_a) *(m_gb-m_ga)/(m_b-m_a)+ m_ga;
			}
			else {
				dst.at<uchar>(i, j) = (temp - m_b) *(255 - m_gb) / (255 - m_b) + m_gb;
			}
		}
	}
	imshow("LCB", dst);
}


void CDIPDlg::OnBnClickedDra()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open image!"));
		return;
	}

	UpdateData(TRUE);
	Mat dst;
	Mat gray_img;
	cvtColor(src, gray_img, CV_BGR2GRAY);
	dst = gray_img.clone();
	for (int i = 0; i < gray_img.rows; i++) {
		for (int j = 0; j < gray_img.cols; j++) {
			int temp = gray_img.at<uchar>(i, j);
			dst.at<uchar>(i, j) = m_c*log10((float)(1+temp));
		}
	}
	imshow("DRA", dst);

}


void CDIPDlg::OnBnClickedSmooth()
{
	// TODO: Add your control notification handler code here
		if (src.empty())
		{
		AfxMessageBox(_T("Please open an image!"));
		return;
		}
	

		UpdateData(TRUE);
		Mat dst;
		Mat gray_img;
		cvtColor(src, gray_img, CV_BGR2GRAY);
		if (m__filter__size <= 0)
		{
			AfxMessageBox(_T("Enter a correct template size!"));
			return;
		}
		switch (m__filter__type) {
		case 0://mean filter
			blur(gray_img, dst, Size(m__filter__size, m__filter__size));
			imshow("mean filter", dst);
			break;
		case 1://median filter
			medianBlur(gray_img,dst,m__filter__size);
			imshow("median filter", dst);
			break;
		case 2://gaussian filter
			GaussianBlur(gray_img, dst, Size(m__filter__size, m__filter__size),0);
			imshow("gaussian filter", dst);
		}

}


void CDIPDlg::OnBnClickedVideo()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, _T("*.jpg"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		_T("Image files(*.bmp,*.jpg)|*.bmp;*.jpg|All files(*.*)|*.*|"), NULL);

	dlg.m_ofn.lpstrTitle = _T("Open Images");

	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	CString filePath = dlg.GetPathName();

	string sFileName = (LPCTSTR)filePath;

	src = imread(sFileName);

	VideoCapture capture;
	capture.open(sFileName);
	

	CRect rect;
	GetDlgItem(IDC_PIC)->GetClientRect(&rect);

	Mat img;
	while (1) {
		Mat frame;
		capture >> frame;
		if (frame.empty()) {
			break;
		}
		else {
			resize(frame, img, Size(rect.Width(), rect.Height()));
			imshow("view", img);
			waitKey(30);
		}
	}

	

}


void CDIPDlg::OnBnClickedSharpen()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open an image!"));
		return;
	}


	UpdateData(TRUE);
	Mat dst;
	Mat gray_img;
	cvtColor(src, gray_img, CV_BGR2GRAY);
	Mat grad_x, grad_y,grad_x_abs, grad_y_abs;
	Mat tmp;
	Mat dsth4;
	switch (m_sharpen_type) {
	case 0://sobel
		Sobel(gray_img, grad_x, CV_16S, 1, 0, 3, 1, 1);
		convertScaleAbs(grad_x, grad_x_abs);
		imshow("grad_x", grad_x_abs);

		Sobel(gray_img, grad_y, CV_16S, 0, 1, 3, 1, 1);
		convertScaleAbs(grad_y, grad_y_abs);
		imshow("grad_y", grad_y_abs);

		addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5,0, dst);
		imshow("sobel", dst);
		break;
	case 1://laplacian
		Laplacian(gray_img, tmp, CV_16S, 3, 1);
		convertScaleAbs(tmp, dst);
		imshow("laplacian", dst);

		break;
	case 2://laplacian h4
		Laplacian(gray_img, tmp, CV_16S, 3, 1);
		convertScaleAbs(tmp, dst);
		addWeighted(gray_img, 0.5, dst, 0.5, 0, dsth4);
		imshow("laplacian-h4",dsth4);
		break;
	}
}


void CDIPDlg::OnBnClickedTh()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open an image!"));
		return;
	}


	UpdateData(TRUE);
	Mat dst;
	Mat gray_img;
	cvtColor(src, gray_img, CV_BGR2GRAY);

	if (m_thre < 0 || m_thre>255)
	{
		AfxMessageBox(_T("Threshold value is out of range!"));
		return;
	}
	

	threshold(gray_img, dst, m_thre, 255, THRESH_BINARY);
	imshow("threshold", dst);
}


void CDIPDlg::OnBnClickedAdth()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open an image!"));
		return;
	}


	UpdateData(TRUE);
	Mat dst;
	Mat gray_img;
	cvtColor(src, gray_img, CV_BGR2GRAY);


	
	adaptiveThreshold(gray_img, dst, 255, ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY, m_blocksize, m_C);
	imshow("Adaptive threshold", dst);

}


void CDIPDlg::OnBnClickedRegion()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open image！"));
		return;
	}

	Mat g_src, dst;

	cvtColor(src, g_src, CV_BGR2GRAY);

	dst = Mat::zeros(g_src.size(), CV_8UC1);

	UpdateData(TRUE);

	if (m_seedx<0 || m_seedx>(src.rows - 1) || m_seedy<0 || m_seedy>(src.cols - 1))
	{
		AfxMessageBox("The position of seed is out of range!");
		return;
	}

	Point2i pt(m_seedy, m_seedx);//seed coordinate

	int th = m_region;

	Point2i ptGrowing; // pixel being checked
	int nGrowLabel = 0;   //flag to record the result 
	int nSrcValue = 0;  //gray value of original pixel
	int nCurValue = 0; //gray value of ptGrowing

	int DIR[8][2] = { {-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1} };//8-neighbours


	std::vector<Point2i> vcGrowPt; //growing pixel stack

	vcGrowPt.push_back(pt);//push the seed into the stack

	dst.at<uchar>(pt.y, pt.x) = 255;

	nSrcValue = g_src.at<uchar>(pt.y, pt.x);//record the gray value of seed

	while (!vcGrowPt.empty())
	{
		pt = vcGrowPt.back();//get pixels in stack
		vcGrowPt.pop_back();

		//judge the 8-neigbours
		for (int i = 0; i < 8; i++)
		{
			ptGrowing.x = pt.x + DIR[i][0];
			ptGrowing.y = pt.y + DIR[i][1];

			//check the edge points
			if (ptGrowing.x<0 || ptGrowing.x>(src.cols - 1) || ptGrowing.y<0 || ptGrowing.y>(src.rows - 1))
			{
				continue;
			}

			nGrowLabel = dst.at<uchar>(ptGrowing.y, ptGrowing.x); //get the grow flag of the current pixel

			if (nGrowLabel == 0)
			{
				nCurValue = g_src.at<uchar>(ptGrowing.y, ptGrowing.x);//get the gray value of current pixel
				if (abs(nCurValue - nSrcValue) < th)
				{
					dst.at<uchar>(ptGrowing.y, ptGrowing.x) = 255; //grow it, set it to 255
					vcGrowPt.push_back(ptGrowing);//push it into the stack
				}

			}

		}
	}
	imshow("region", dst);



}


void CDIPDlg::OnBnClickedErode()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open image！"));
		return;
	}

	Mat g_src, dst,src_bin;

	cvtColor(src, g_src, CV_BGR2GRAY);
	threshold(g_src, src_bin, 120, 255, THRESH_BINARY);
	UpdateData(TRUE);
	Mat SE = getStructuringElement(m_SE_shape,Size(m_SE_size,m_SE_size));
	erode(src_bin, dst, SE);
	imshow("Erode", dst);
}


void CDIPDlg::OnBnClickedDilate()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open image！"));
		return;
	}

	Mat g_src, dst, src_bin;

	cvtColor(src, g_src, CV_BGR2GRAY);
	threshold(g_src, src_bin, 120, 255, THRESH_BINARY);
	UpdateData(TRUE);
	Mat SE = getStructuringElement(m_SE_shape, Size(m_SE_size, m_SE_size));
	dilate(src_bin, dst, SE);
	imshow("Dilate", dst);
}


void CDIPDlg::OnBnClickedMorphopen()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open image！"));
		return;
	}

	Mat g_src, dst, src_bin;

	cvtColor(src, g_src, CV_BGR2GRAY);
	threshold(g_src, src_bin, 120, 255, THRESH_BINARY);
	UpdateData(TRUE);
	Mat SE = getStructuringElement(m_SE_shape, Size(m_SE_size, m_SE_size));
	morphologyEx(src_bin, dst,MORPH_OPEN, SE);
	imshow("Opening", dst);

}


void CDIPDlg::OnBnClickedMorphclose()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open image！"));
		return;
	}

	Mat g_src, dst, src_bin;

	cvtColor(src, g_src, CV_BGR2GRAY);
	threshold(g_src, src_bin, 120, 255, THRESH_BINARY);
	UpdateData(TRUE);
	Mat SE = getStructuringElement(m_SE_shape, Size(m_SE_size, m_SE_size));
	morphologyEx(src_bin, dst, MORPH_CLOSE, SE);
	imshow("Closing", dst);
}


void CDIPDlg::OnBnClickedConvertcolor()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open image！"));
		return;
	}
	if (src.channels()!=3)
	{
		AfxMessageBox(_T("Please open a color image！"));
		return;
	}
	Mat dst;
	UpdateData(TRUE);

	switch (m_color_mode) {
	case 0:
		cvtColor(src, dst, CV_BGR2HSV);
		imshow("HSV", dst);
		break;
	case 1:
		cvtColor(src, dst, CV_BGR2XYZ);
		imshow("XYZ", dst);
		break;
	case 2:
		cvtColor(src, dst, CV_BGR2YUV);
		imshow("YUV", dst);
		break;
	}
	
}


void CDIPDlg::OnBnClickedIntslicing()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open image！"));
		return;
	}
	Mat g_src;
	if (src.channels() != 1)
	{
		cvtColor(src, g_src, CV_BGR2GRAY);
	}

	
	Mat dst(g_src.size(),CV_8UC3);
	for (int i = 0; i < g_src.rows; i++) {
		for (int j = 0; j < g_src.cols; j++) {
			int temp = g_src.at<uchar>(i, j);
			if (temp < 84) {
				dst.at<Vec3b>(i, j)[0] = 150;
				dst.at<Vec3b>(i, j)[1] = 100;
				dst.at<Vec3b>(i, j)[2] = 222;

			}
			else if (temp < 168) {
				dst.at<Vec3b>(i, j)[0] = 0;
				dst.at<Vec3b>(i, j)[1] = 255;
				dst.at<Vec3b>(i, j)[2] = 0;

			}
			else {
				dst.at<Vec3b>(i, j)[0] = 0;
				dst.at<Vec3b>(i, j)[1] = 128;
				dst.at<Vec3b>(i, j)[2] = 255;

			}

		}
	}
	imshow("color", dst);

}


void CDIPDlg::OnBnClickedInttransfer()
{
	// TODO: Add your control notification handler code here
	if (src.empty())
	{
		AfxMessageBox(_T("Please open image！"));
		return;
	}
	Mat g_src;
	if (src.channels() != 1)
	{
		cvtColor(src, g_src, CV_BGR2GRAY);
	}


	Mat dst(g_src.size(), CV_8UC3);
	for (int i = 0; i < g_src.rows; i++) {
		for (int j = 0; j < g_src.cols; j++) {
			int temp = g_src.at<uchar>(i, j);
			if (temp < 64) {
				dst.at<Vec3b>(i, j)[0] = 255;
				dst.at<Vec3b>(i, j)[1] = 4*temp;
				dst.at<Vec3b>(i, j)[2] = 0;

			}
			else if (temp < 128) {
				dst.at<Vec3b>(i, j)[0] = 4*(127-temp);
				dst.at<Vec3b>(i, j)[1] = 255;
				dst.at<Vec3b>(i, j)[2] = 0;

			}
			else if (temp < 192) {
				dst.at<Vec3b>(i, j)[0] = 0;
				dst.at<Vec3b>(i, j)[1] = 255;
				dst.at<Vec3b>(i, j)[2] = 4 * (temp-127);

			}
			else {
				dst.at<Vec3b>(i, j)[0] = 0;
				dst.at<Vec3b>(i, j)[1] = 4 * (255 - temp);
				dst.at<Vec3b>(i, j)[2] = 255;

			}

		}
	}
	imshow("color", dst);
}


void CDIPDlg::OnBnClickedFacedetect()
{
	// TODO: Add your control notification handler code here
	  // TODO: Add your control notification handler code here
  VideoCapture cap(0); // open the default camera



	if (!cap.isOpened())  // check if we succeeded
	{
		MessageBox(_T("Can not open camera!"));//
		return;
	}

	CascadeClassifier face_cascade;
	string face_cascade_name = "D:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt2.xml";//load feature file


	CascadeClassifier eye_cascader;
	String eyefile = "D:\\opencv\\sources\\data\\haarcascades\\haarcascade_eye.xml";


	if (!face_cascade.load(face_cascade_name))
	{
		MessageBox(_T("could not load face feature data...\n！"));
		return;
	}

	if (!eye_cascader.load(eyefile))
	{//Load features
		MessageBox(_T("could not load eye feature data...\n！"));
		return;
	}


	vector<Rect> faces;
	vector<Rect> eyes;
	Mat frame, frame_gray;

	while (1)
	{
		cap >> frame; // get a new frame from camera
		if (frame.data != NULL)
		{
			cvtColor(frame, frame_gray, CV_BGR2GRAY);
			equalizeHist(frame_gray, frame_gray);

			face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(100, 100), Size(500, 500));

			for (int i = 0; i < faces.size(); i++)
			{
				
				  Rect roi;
				  roi.x = faces[static_cast<int>(i)].x;
				  roi.y = faces[static_cast<int>(i)].y;
				  roi.width = faces[static_cast<int>(i)].width;
				  roi.height = faces[static_cast<int>(i)].height / 2;
				  Mat faceROI = frame(roi);
				  eye_cascader.detectMultiScale(faceROI, eyes, 1.2, 3, 0, Size(20, 20));
				  for (size_t k = 0; k < eyes.size(); k++) {
				    Rect rect;
				    rect.x = faces[static_cast<int>(i)].x + eyes[k].x;
				    rect.y = faces[static_cast<int>(i)].y + eyes[k].y;
				    rect.width = eyes[k].width;
				    rect.height = eyes[k].height;
				    //recognize the eye
				    rectangle(frame, rect, Scalar(0, 255, 0), 2, 8, 0);
				    Point center;
				    center.x = rect.x + rect.width / 2;
				    center.y = rect.y + rect.height / 2;
				    //recognize iris
				    circle(frame, center, 5, Scalar(0, 255, 255), -1, 8);
				  }

				  Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
				  ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
			
				rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height),
					Scalar(0, 0, 255), 4, 8, 0);
			}

			imshow("Face detection", frame);
		}

		if (waitKey(30) >= 0)
		{
			cap.release();
			break;
		}
	}
}
Mat firstFrame;
Point previousPoint, currentPoint;
Rect2d bbox;
	void draw_rectangle(int event, int x, int y, int flags, void*)
	{
		if (event == EVENT_LBUTTONDOWN)
		{
			previousPoint = Point(x, y);
		}
		else if (event == EVENT_MOUSEMOVE && (flags&EVENT_FLAG_LBUTTON))
		{
			Mat tmp;
			firstFrame.copyTo(tmp);
			currentPoint = Point(x, y);
			rectangle(tmp, previousPoint, currentPoint, Scalar(0, 255, 0, 0), 1, 8, 0);
			imshow("output", tmp);
		}
		else if (event == EVENT_LBUTTONUP)
		{
			bbox.x = previousPoint.x;
			bbox.y = previousPoint.y;
			bbox.width = abs(previousPoint.x - currentPoint.x);
			bbox.height = abs(previousPoint.y - currentPoint.y);
		}
		else if (event == EVENT_RBUTTONUP)
		{
			destroyWindow("output");
		}

	}




void CDIPDlg::OnBnClickedTracking()
{
	// TODO: Add your control notification handler code here
	VideoCapture cap(0); // open the default camera



	if (!cap.isOpened())  // check if we succeeded
	{
		MessageBox(_T("Can not open camera!"));//
		return;
	}
	Mat frame;
	cap.read(firstFrame);
	if (!firstFrame.empty())
	{
		namedWindow("output", WINDOW_AUTOSIZE);
		imshow("output", firstFrame);
		setMouseCallback("output", draw_rectangle, 0);
		waitKey();

	}

	
	Ptr<TrackerTLD> tracker = TrackerTLD::create();
	cap.read(frame);
	tracker->init(frame, bbox);
	namedWindow("output", WINDOW_AUTOSIZE);
	while (cap.read(frame))
	{
		tracker->update(frame, bbox);
		rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
		imshow("output", frame);
		if (waitKey(20) == 'q')
			return;
	}
	cap.release();
	destroyWindow("output");
	return;


	
}
