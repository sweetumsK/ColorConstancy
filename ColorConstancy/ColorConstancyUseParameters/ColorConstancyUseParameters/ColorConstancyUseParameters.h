#pragma once

#include<vector>
#include<opencv2\opencv.hpp>

typedef std::vector<double> ParametersList;

class ColorConstancy {
public:
	static cv::Mat Operate(const cv::Mat inImage, const ParametersList inParametersList);

private:
	ColorConstancy(const cv::Mat inImage, const ParametersList inParametersList);
	~ColorConstancy();
	void UseParameters();
	cv::Mat getDstImage();

	cv::Mat mImage;
	cv::Mat outImage;
	ParametersList mParametersList;
};