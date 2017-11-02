#include "Histogram.h"

Mat ColorConstancy::MatchColor(const Mat& inFirstImage, const Mat& inSecondImage) {
	ColorConstancy colorConstancy(inFirstImage, inSecondImage);
	colorConstancy.ApplyHistogram();
	return colorConstancy.outImage;
}

ColorConstancy::ColorConstancy(const Mat& inFirstImage, const Mat& inSecondImage) {
	Mat temp;
	cvtColor(inFirstImage, temp, CV_RGB2HSV);
	split(temp, mFirstImage);
	cvtColor(inSecondImage, temp, CV_RGB2HSV);
	split(temp, mSecondImage);
}

ColorConstancy::~ColorConstancy() {}

void ColorConstancy::ApplyHistogram() {
	Mat temp;
	MatND mFirstImageHist, mSecondImageHist;
	for (int colorChannels = 1; colorChannels < 3; ++colorChannels) {
		GetHistogram(mFirstImage[colorChannels], mFirstImageHist);
		GetHistogram(mSecondImage[colorChannels], mSecondImageHist);
		StretchHist(mSecondImage[colorChannels], mFirstImageHist, mSecondImageHist);
	}
	merge(mSecondImage, temp);
	cvtColor(temp, outImage, CV_HSV2RGB);
}

void ColorConstancy::GetHistogram(const Mat& image, MatND& hist) {
	const int nImages = 1;
	const int channels[1] = { 0 };
	const Mat mask = Mat();
	const int dims = 1;
	const int histSize[1] = { 256 };
	const float hRanges[2] = { 0, 255 };
	const float* ranges[1] = { hRanges };
	const bool uniform = true;
	const bool accumulation = false;
	
	calcHist(&image, nImages, channels, mask, hist, dims, histSize, ranges, uniform, accumulation);
}

void ColorConstancy::StretchHist(Mat& image, const MatND& refHist, const MatND& srcHist) {
	Mat lut(1, 256, CV_8U);
	SetLookUpTable(lut, refHist, srcHist);
	LUT(image, lut, image);

	MatND hist;
	GetHistogram(image, hist);
	Mat histImage(hist.rows, hist.rows, CV_8UC3, Scalar(255, 255, 255));
	GetHistImage(refHist, histImage, 0);
	GetHistImage(srcHist, histImage, 1);
	GetHistImage(hist, histImage, 2);
	imshow("test", histImage);
	waitKey(0);
}

void ColorConstancy::SetLookUpTable(Mat& lut, const MatND& refHist, const MatND& srcHist) {
	Mat refCumulatedHist(1, 256, CV_64F), srcCumulatedHist(1, 256, CV_64F);
	GetCumulatedHist(mFirstImage[0].rows * mFirstImage[0].cols, refHist, refCumulatedHist);
	GetCumulatedHist(mSecondImage[0].rows * mSecondImage[0].cols, srcHist, srcCumulatedHist);

	int preRefHead = 0;
	for (int srcHead = 0; srcHead < 256; ++srcHead) {
		double srcMin = 1.0;
		int flag = preRefHead;
		for (int refHead = preRefHead; refHead < 256; ++refHead) {
			double temp = fabs(refCumulatedHist.at<double>(0, refHead) - srcCumulatedHist.at<double>(0, srcHead));
			if (temp < srcMin) {
				srcMin = temp;
				flag = refHead;
			}
		}
		preRefHead = flag;
		lut.at<uchar>(srcHead) = static_cast<uchar> (flag);
	}
}

void ColorConstancy::GetCumulatedHist(const int area, const MatND& hist, Mat& cumulatedHist) {
	double sum = 0.0;
	for (int index = 0; index < 256; ++index) {
		sum = sum + static_cast<double> (hist.at<float>(index));
		cumulatedHist.at<double>(index) = sum / area;
	}
}



void ColorConstancy::GetHistImage(const MatND& hist, Mat& image, const int index) {
	const vector<Scalar> color = { Scalar(0, 0, 255), Scalar(0, 255, 0), Scalar(255, 0, 0) };
	double maxVal = 0;
	double minVal = 0;
	int histSize = hist.rows;
	minMaxLoc(hist, &minVal, &maxVal, 0, 0);
	int hpt = static_cast<int>(0.9*histSize);

	for (int h = 0; h < histSize; h++) {
		float binVal = hist.at<float>(h);
		int intensity = static_cast<int>(binVal*hpt / maxVal);
		line(image, Point(h, histSize), Point(h, histSize - intensity), color[index]);
	}
}
