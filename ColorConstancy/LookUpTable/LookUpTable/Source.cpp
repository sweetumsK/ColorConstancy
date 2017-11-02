#include"ColorMap.h"
#include<cstring>

using namespace std;

int main() {
	Mat image = imread("1.jpg");
	for (int i = 0; i < 13; i++) {
		Mat result = ColorMap::GetColorMap(image, i);
		imwrite("1_"+to_string(i)+".jpg", result);
	}
}