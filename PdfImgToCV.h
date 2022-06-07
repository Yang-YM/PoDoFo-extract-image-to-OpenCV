#ifndef PDFIMGTOCV
#define PDFIMGTOCV

//#include <memory>
#include <podofo.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include<vector>

bool pdfImageToMat(PoDoFo::PdfObject* obj, cv::Mat& dst, cv::ImreadModes mode);
bool pdfObjectIsImage(PoDoFo::PdfObject* obj);
void pdfPageImage(PoDoFo::PdfMemDocument& doc, int page, std::vector<PoDoFo::PdfObject*>& imgObj);


/*
namespace pdfImg
{
	/*
	class PdfImg
	{
	public:
		cv::Mat img;
		bool read(PoDoFo::PdfObject* obj);
	private:
		std::unique_ptr<char> data;
	};

}*/


#endif // !PDFIMGTOCV
