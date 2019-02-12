#include <opencv2/highgui/highgui.hpp>

int main(int argc, char * argv[]) {
	const std::string file_name(argv[1]);
	cv::Mat image = cv::imread(file_name);
}