#include "stdafx.h"
#include "common.h"
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>
#include <algorithm>

wchar_t* projectPath;

int minimum(int a, int b) {
	int res = (a < b) ? a : b;
	return res;
}

Mat ShiTomasiImplemented(Mat src) {
	Mat gradX, gradY;
	Sobel(src, gradX, CV_32F, 1, 0, 3);
	Sobel(src, gradY, CV_32F, 0, 1, 3);

	Mat Ixx = gradX.mul(gradX);
	Mat Iyy = gradY.mul(gradY);
	Mat Ixy = gradX.mul(gradY);

	double thr = 5;
	int w = 3;

	Mat corners = Mat::zeros(src.size(), CV_32FC1);
	int n = src.rows;
	int m = src.cols;
	int wlen = w / 2;

	for (int y = wlen; y < n - wlen; ++y) {
		for (int x = wlen; x < m - wlen; ++x) {
			Mat H = Mat::zeros(2, 2, CV_32FC1);
			float Sxx = sum(Ixx(Rect(x - wlen, y - wlen, w, w)))[0];
			float Syy = sum(Iyy(Rect(x - wlen, y - wlen, w, w)))[0];
			float Sxy = sum(Ixy(Rect(x - wlen, y - wlen, w, w)))[0];
			H.at<float>(0, 0) = Sxx;
			H.at<float>(0, 1) = Sxy;
			H.at<float>(1, 0) = Sxy;
			H.at<float>(1, 1) = Syy;
			Mat eigenvalues, eigenvectors;
			eigen(H, eigenvalues, eigenvectors);
			float min_eigen_value = minimum(eigenvalues.at<float>(0), eigenvalues.at<float>(1));
			if (min_eigen_value > thr) {
				corners.at<float>(y, x) = min_eigen_value;
			}
		}
	}

	double maxVal;
	minMaxLoc(corners, nullptr, &maxVal);

	double threshold = 0.01 * maxVal;

	std::vector<Point2f> detectedCorners;
	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (corners.at<float>(y, x) > threshold) {
				detectedCorners.push_back(Point2f(x, y));
			}
		}
	}

	std::vector<Point2f> filteredCorners;
	double minDistance = 10;
	for (const auto& pt : detectedCorners) {
		bool keep = true;
		for (const auto& existingPt : filteredCorners) {
			if (norm(pt - existingPt) < minDistance) {
				keep = false;
				break;
			}
		}
		if (keep)
			filteredCorners.push_back(pt);
	}

	Mat img_color2;
	cvtColor(src, img_color2, COLOR_GRAY2BGR);
	for (const auto& corner : filteredCorners) {
		circle(img_color2, corner, 5, Scalar(0, 0, 255), -1);
	}

	return img_color2;
}

Mat ShiTomasiOriginal(Mat src) {
	int maxCorners = 100;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;

	std::vector<Point2f> corners;
	goodFeaturesToTrack(src, corners, maxCorners, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);

	Mat img_color1;
	cvtColor(src, img_color1, COLOR_GRAY2BGR);
	for (const auto& corner : corners) {
		circle(img_color1, corner, 5, Scalar(0, 0, 255), -1);
	}

	return img_color1;
}

int main() 
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_FATAL);
    projectPath = _wgetcwd(0, 0);

	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		if (src.empty()) {
			std::cerr << "Error: Could not read the image." << std::endl;
			continue;
		}

		Mat img_color1 = ShiTomasiOriginal(src);
		Mat img_color2 = ShiTomasiImplemented(src);

		imshow("Original Image", src);
		imshow("Shi-Tomasi Corner Detection", img_color1);
		imwrite("og.jpg", img_color1);
		imshow("My Implementation", img_color2);
		imwrite("mine.jpg", img_color2);
		waitKey();
	}

	return 0;
}