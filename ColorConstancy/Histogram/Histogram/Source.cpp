#include "Histogram.h"

int main() {
	Mat firstImage, secondImage, result;
	firstImage = imread("test2.jpg");
	secondImage = imread("test1.jpg");
	result = ColorConstancy::MatchColor(firstImage, secondImage);
	imwrite("test2-1-SV-result.jpg", result);
}