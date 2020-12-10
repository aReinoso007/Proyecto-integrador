#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sstream>
#include <fstream>

#include <dirent.h>

#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/video/video.hpp>
#include <opencv4/opencv2/videoio/videoio.hpp>
#include <opencv4/opencv2/imgcodecs/imgcodecs.hpp>

#include <math.h>

using namespace std;
using namespace cv;

class Operaciones{

    public:
        Operaciones();
            cv::Mat filtroMediana(cv::Mat, cv::Mat, int);
            cv::Mat filtroGassuaian(cv::Mat, cv::Mat, int);
            cv::Mat aplicarErosion(cv::Mat, cv::Mat, int);
            cv::Mat aplicarBlackHat(cv::Mat, cv::Mat, int);
            cv::Mat aplicarDilatar(cv::Mat, cv::Mat, int);
};