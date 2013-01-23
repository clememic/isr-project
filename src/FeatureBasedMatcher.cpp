#include "FeatureBasedMatcher.h"

std::vector<cv::KeyPoint> getSiftFeatures(cv::Mat image) {
	cv::SiftFeatureDetector siftDetector;
	std::vector<cv::KeyPoint> keyPoints;
	siftDetector.detect(image, keyPoints);
	return keyPoints;
}

cv::Mat getSiftFeaturesDescriptions(cv::Mat image,
		std::vector<cv::KeyPoint> keyPoints) {
	cv::SiftDescriptorExtractor siftExtractor;
	cv::Mat descriptors;
	siftExtractor.compute(image, keyPoints, descriptors);
	return descriptors;
}

std::vector<cv::KeyPoint> getSurfFeatures(cv::Mat image, int hessianThreshold =
		400) {
	cv::SurfFeatureDetector surfDetector(hessianThreshold);
	std::vector<cv::KeyPoint> keyPoints;
	surfDetector.detect(image, keyPoints);
	return keyPoints;
}

cv::Mat getSurfFeaturesDescriptions(cv::Mat image,
		std::vector<cv::KeyPoint> keyPoints) {
	cv::SurfDescriptorExtractor surfExtractor;
	cv::Mat descriptors;
	surfExtractor.compute(image, keyPoints, descriptors);
	return descriptors;
}

cv::Mat getFlannMatches(cv::Mat image1, std::vector<cv::KeyPoint> keyPoints1,
		cv::Mat descriptors1, cv::Mat image2,
		std::vector<cv::KeyPoint> keyPoints2, cv::Mat descriptors2) {
	cv::FlannBasedMatcher flannMatcher;
	std::vector<cv::DMatch> matches;
	flannMatcher.match(descriptors1, descriptors2, matches);
	// TODO Draw only "good" matches
	cv::Mat outputImage;
	cv::drawMatches(image1, keyPoints1, image2, keyPoints2, matches,
			outputImage, cv::Scalar::all(-1), cv::Scalar::all(-1),
			std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	return outputImage;
}
