#include "FeatureBasedMatcher.h"

std::vector<cv::KeyPoint> FeatureBasedMatcher::getSiftFeatures(cv::Mat image) {
	cv::SiftFeatureDetector siftDetector;
	std::vector<cv::KeyPoint> keyPoints;
	siftDetector.detect(image, keyPoints);
	return keyPoints;
}

cv::Mat FeatureBasedMatcher::getSiftFeaturesDescriptions(cv::Mat image,
		std::vector<cv::KeyPoint> keyPoints) {
	cv::SiftDescriptorExtractor siftExtractor;
	cv::Mat descriptors;
	siftExtractor.compute(image, keyPoints, descriptors);
	return descriptors;
}

std::vector<cv::KeyPoint> FeatureBasedMatcher::getSurfFeatures(cv::Mat image,
		int hessianThreshold) {
	cv::SurfFeatureDetector surfDetector(hessianThreshold);
	std::vector<cv::KeyPoint> keyPoints;
	surfDetector.detect(image, keyPoints);
	return keyPoints;
}

cv::Mat FeatureBasedMatcher::getSurfFeaturesDescriptions(cv::Mat image,
		std::vector<cv::KeyPoint> keyPoints) {
	cv::SurfDescriptorExtractor surfExtractor;
	cv::Mat descriptors;
	surfExtractor.compute(image, keyPoints, descriptors);
	return descriptors;
}

cv::Mat FeatureBasedMatcher::getFlannMatches(cv::Mat image1,
		std::vector<cv::KeyPoint> keyPoints1, cv::Mat descriptors1,
		cv::Mat image2, std::vector<cv::KeyPoint> keyPoints2,
		cv::Mat descriptors2) {

	/* Perform Flann matching */
	cv::FlannBasedMatcher flannMatcher;
	std::vector<cv::DMatch> matches;
	flannMatcher.match(descriptors1, descriptors2, matches);

    /* Compute min and max distance between keypoints */
    double maxDistance = 0, minDistance = 1000, distance;
    for (int i(0); i < descriptors1.rows; i++) {
        distance = matches[i].distance;
        if (distance < minDistance) {
            minDistance = distance;
        }
        if (distance > maxDistance) {
            maxDistance = distance;
        }
    }
    /* Then keep only good matches */
    std::vector<cv::DMatch> goodMatches;
    for (int i(0); i < descriptors1.rows; i++) {
        if (matches[i].distance < 2 * minDistance) {
            goodMatches.push_back(matches[i]);
        }
    }

    /* Draw and return only good matches */
	cv::Mat outputImage;
	cv::drawMatches(image1, keyPoints1, image2, keyPoints2, goodMatches,
			outputImage, cv::Scalar::all(-1), cv::Scalar::all(-1),
			std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	return outputImage;

}
