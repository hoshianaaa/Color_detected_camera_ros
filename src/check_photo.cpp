#include <ros/ros.h>
#include <ros/package.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <std_msgs/String.h>

int main(int argc, char** argv)
{
    std::string file_path = ros::package::getPath("opencv_practice") + "/img/";

    cv::Mat img = cv::imread(file_path + "field.png", cv::IMREAD_COLOR);
    cv::resize(img, img, cv::Size(), 0.2, 0.2);
    cv::imshow("source_image", img);

    //input_image -> hsv
    cv::Mat hsv_image;
    cv::cvtColor(img ,hsv_image, CV_BGR2HSV);
    imshow("HSV_image", hsv_image);

    //hsv_image -> red,yellow,blue
    int width = hsv_image.cols;
    int height = hsv_image.rows;
    int hue, sat, val;
    cv::Mat red_image = cv::Mat(cv::Size(width, height), CV_8UC1);
    cv::Mat yellow_image = cv::Mat(cv::Size(width, height), CV_8UC1);
    cv::Mat blue_image = cv::Mat(cv::Size(width, height), CV_8UC1);

    for (int y=0;y<height;y++){
        for(int x=0;x<width;x++){
             hue = hsv_image.at<cv::Vec3b>(y, x)[0];
             sat = hsv_image.at<cv::Vec3b>(y, x)[1];
             val = hsv_image.at<cv::Vec3b>(y, x)[2];
             if((hue<8||hue>168) && sat > 100)
                  red_image.at<unsigned char>(y, x) = 0;
             else
                  red_image.at<unsigned char>(y, x) = 255;
             if((hue>20&&hue<40) && sat>100 && val>100)
                  yellow_image.at<unsigned char>(y, x) = 0;
             else
                  yellow_image.at<unsigned char>(y, x) = 255;
             if((hue>97&&hue<117) && sat>100 && val>100)
                  blue_image.at<unsigned char>(y, x) = 0;
             else
                  blue_image.at<unsigned char>(y, x) = 255;
        }
    }
   
    //red_image,yellow_image,blue_imageの黒いピクセルの個数をカウント
    imshow("red_image",red_image);
    imshow("yellow_image",yellow_image);
    imshow("blue_image",blue_image);

    long int red_image_count=0;
    long int yellow_image_count=0;
    long int blue_image_count=0;
    for (int y=0;y<height;y++){
        for (int x=0;x<width;x++){
            if (red_image.at<unsigned char>(y, x) == 0)red_image_count++;
            if (yellow_image.at<unsigned char>(y, x) == 0)yellow_image_count++;
            if (blue_image.at<unsigned char>(y, x) == 0)blue_image_count++;
        }
    }

    std_msgs::String msg_info;
    std::stringstream sss;
    sss << "red_image_count: " << red_image_count;
    sss << " yellow_image_count: " << yellow_image_count;
    sss << " blue_image_count: " << blue_image_count;

    msg_info.data = sss.str();
    ROS_INFO("%s", msg_info.data.c_str());


    cv::waitKey();

    return 0;
}
