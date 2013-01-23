#ifndef FEATUREBASEDMATCHER_H_
#define FEATUREBASEDMATCHER_H_

#include "opencv2/features2d/features2d.hpp"

class FeatureBasedMatcher {

public:
	static cv::Mat getFlannMatches(cv::Mat image1,
			std::vector<cv::KeyPoint> keyPoints1, cv::Mat descriptors1,
			cv::Mat image2, std::vector<cv::KeyPoint> keyPoints2,
			cv::Mat descriptors2);

private:
	static std::vector<cv::KeyPoint> getSiftFeatures(cv::Mat image);
	static cv::Mat getSiftFeaturesDescriptions(cv::Mat image,
			std::vector<cv::KeyPoint> keyPoints);
	static std::vector<cv::KeyPoint> getSurfFeatures(cv::Mat image,
			int hessianThreshold = 400);
	static cv::Mat getSurfFeaturesDescriptions(cv::Mat image,
			std::vector<cv::KeyPoint> keyPoints);

};

#endif /* FEATUREBASEDMATCHER_H_ */
