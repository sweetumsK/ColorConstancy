#pragma once
#include <vector>
#include <opencv2\opencv.hpp>

typedef std::vector<double> ParametersList;

class ColorConstancyParameters {
public:
	static ParametersList Operate(const cv::Mat inRefImage,const cv::Mat inSrcImage);

private:
	ColorConstancyParameters(const cv::Mat inRefImage, const cv::Mat inSrcImage);
	~ColorConstancyParameters();
	void CalculateParameters();
	ParametersList GetParametersList();

	cv::Mat mRefImage;
	cv::Mat mSrcImage;
	ParametersList parametersList;
};