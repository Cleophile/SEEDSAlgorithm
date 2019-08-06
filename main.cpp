//
//  main.cpp
//  test_seeds
//
//  Created by 王天民 on 2019/8/5.
//  Copyright © 2019 AokiW. All rights reserved.
//

#include <iostream>
#include "seed.hpp"
// #include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, const char * argv[])
{
    int bins=5;
    float confidence = 0.100000001;
    int prior = 1;
    int means = 1;
    int iterations = 2;
    int color_space = 1; // 0: RGB 1: LaB
    int levels = 3; // number of time doubles to reach the final goal
    
    Mat img = imread("/Users/wangtianmin/Downloads/bear.jpeg");
    
    std::cout << img.cols << ' ' << img.rows << ' ' << img.channels() << std::endl;
    SEEDS seeds(img.cols, img.rows, img.channels(), bins, 0,confidence, prior, means, color_space);
    
    seeds.initialize(img,10,10, levels); // SET the size of super pixels, and how many times does the number doubles
    seeds.iterate(iterations);
    
    // int result[img.rows][img.cols] = {};
    cv::Mat labels(img.rows, img.cols, CV_32SC1, cv::Scalar(0));
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            labels.at<int>(i, j) = seeds.labels[levels - 1][j + img.cols*i];
        }
    }
    cv::Mat aftermath = img.clone();
    for (int i=1; i<img.rows-1; i++)
    {
        for (int j=1; j<img.cols-1; j++)
        {
            if(labels.at<int>(i,j)!= labels.at<int>(i+1,j) || labels.at<int>(i,j)!= labels.at<int>(i-1,j) || labels.at<int>(i,j+1)!=labels.at<int>(i,j)  || labels.at<int>(i,j-1)!=labels.at<int>(i,j))
            {
                // is boundry
                aftermath.at<Vec3b>(i,j)[0] = 255;
                aftermath.at<Vec3b>(i,j)[1] = 255;
                aftermath.at<Vec3b>(i,j)[2] = 255;
            }
        }
    }
    
    cv::imwrite("/Users/wangtianmin/Downloads/result.jpg",aftermath);
    // namedWindow("MyWindow", WINDOW_AUTOSIZE);
    // cv::imshow("MyWindow",img);
    
    // int unconnected_components = SuperpixelTools::relabelConnectedSuperpixels(labels);
    
    return 0;
}
