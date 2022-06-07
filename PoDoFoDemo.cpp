// PoDoFoDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <podofo.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include"PdfImgToCV.h"

using namespace std;
using namespace PoDoFo;
using namespace cv;

int main()
{
	PdfMemDocument document("test.pdf");
	vector<PdfObject*> imgObj;
	pdfPageImage(document, 1, imgObj);
	Mat img;
	for (int i = 0; i < imgObj.size(); ++i)
	{
		pdfImageToMat(imgObj[i], img, IMREAD_COLOR);
		imshow("test", img);
		waitKey();
	}

}
