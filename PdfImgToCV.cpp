#include "PdfImgToCV.h"


using namespace cv;
using namespace PoDoFo;
using namespace std;

/*
using namespace pdfImg;
bool pdfImg::PdfImg::read(PdfObject* obj)
{
	int rows = 0, cols = 0;
	bool isImg = pdfObjectIsImage(obj, rows, cols);
	if (isImg)
	{
		char* ptr;
		pdf_long lLen;
		obj->GetStream()->GetFilteredCopy(&ptr, &lLen);
		data.reset(ptr);
		img = Mat(rows, cols, CV_MAKETYPE(CV_8U, lLen / (rows * cols)), ptr);
	}
	return isImg;
}*/

bool pdfImageToMat(PoDoFo::PdfObject* obj, Mat& dst, cv::ImreadModes mode)
{
	bool isImg = pdfObjectIsImage(obj);
	if (isImg)
	{
		char* ptr;
		pdf_long lLen;
		obj->GetStream()->GetCopy(&ptr, &lLen);
		dst = imdecode(Mat(1, lLen, CV_8S, ptr), mode);
		delete ptr;
	}
	return isImg;
}

bool pdfObjectIsImage(PoDoFo::PdfObject* obj)
{
	bool isImg = false;
	if (obj && obj->IsDictionary())
	{
		PdfObject* filter = obj->GetDictionary().GetKey(PdfName::KeyFilter);
		if (filter)
		{
			if (filter->IsArray() && filter->GetArray().GetSize() == 1 && filter->GetArray()[0].IsName())
			{
				filter = &filter->GetArray()[0];
			}
			PdfObject* width = obj->GetDictionary().GetKey(PdfName("Width"));
			PdfObject* height = obj->GetDictionary().GetKey(PdfName("Height"));
			//int cols = obj->GetDictionary().GetKey(PdfName("Width"))->GetNumber();
			//int rows = obj->GetDictionary().GetKey(PdfName("Height"))->GetNumber();
			if (filter->IsName() && width && height)
			{
				isImg = true;
			}
		}
	}
	return isImg;
}


void pdfPageImage(PoDoFo::PdfMemDocument& doc, int page, std::vector<PoDoFo::PdfObject*>& imgObj)
{
	imgObj.clear();
	if (page < 0 || page >= doc.GetPageCount())
	{
		return;
	}
	PdfDictionary& resource = doc.GetPage(page)->GetResources()->GetDictionary();
	PdfVecObjects& vecObj = doc.GetObjects();
	for (pair<const PdfName, PdfObject*>& i : resource.GetKeys())
	{
		if ((i.first.GetName() == "XObject" || i.first.GetName() == "Image") && i.second->IsDictionary())
		{
			for (pair<const PdfName, PdfObject*>& j : i.second->GetDictionary().GetKeys())
			{
				if (j.second->IsReference())
				{
					PdfObject* obj = vecObj.GetObject(j.second->GetReference());
					if (pdfObjectIsImage(obj))
					{
						imgObj.push_back(obj);
					}
				}
			}
		}
	}
}
