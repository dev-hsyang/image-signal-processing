//
//  main.cpp
//  Boundary Extraction and Filtering
//
//  Created by 양현승 on 2022/06/28.
//

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;
Mat boundary;
Mat image;
Mat eroded;


void mouseEvent(int event, int x, int y, int flags, void* userdata){
    
    if(event==EVENT_LBUTTONDOWN){
        cout<<"LEFT BUTTON CLICKED"<<endl;
//        cout<<"COORDINATE: " << x << ", " << y << endl;
        
        Mat X(boundary.size(), CV_32FC1);
        X.at<float>(y, x) = 1;
        
        Mat Xn;
        
        int thres = 170;
        for(int i=0; i<thres; i++){
            dilate(X, X, Mat(), Point(-1, -1), 2);
            X = X - boundary;
            Xn = X;

            imshow("REGION FILTERING", X);
            waitKey(50);
        }
//        Mat MAX = image - boundary;
//        while(true){
//            dilate(X, X, Mat(), Point(-1, -1), 2);
//            X = X - boundary;
//            Xn = X;
//            imshow("X", X);
//
//            if(sum(X != eroded) == Scalar(0, 0, 0, 0))
//                break;
//
//            waitKey(50);
//        }
        
        imshow("REGION FILTERED: RECT", X + boundary);
    }
    
    if(event==EVENT_RBUTTONDOWN){
        cout << "RIGHT BUTTON CLICKED" << endl;
        
        Mat X(boundary.size(), CV_32FC1);
        X.at<float>(y,x) = 1;
        
        int thres = 220;
        for(int i=0; i<thres; i++){
            Mat filter = getStructuringElement(MORPH_CROSS, Size(3,3), Point(3/2, 3/2));
            dilate(X, X, filter, Point(-1, -1), 2);
            X = X - boundary;
            
            imshow("REGION FILTERING", X);
            waitKey(30);
        }
        imshow("REGION FILTERED: CROSS", X + boundary);
    }
}

int main(int argc, const char * argv[]) {
    
    image = imread("/Users/hyunseung/포트폴리오/영상처리/과제/3차과제/Profile.png", 0);
    image.convertTo(image, CV_32F, 1/255.f);
    erode(image, eroded, Mat(), Point(-1,-1), 2);
    boundary = image - eroded;
    
//    imshow("image", image);
//    imshow("eroded", eroded);
    imshow("BOUNDARY", boundary);
    cout << "LEFT BUTTON: RECT STRUCTURE ELEMENT" << endl;
    cout << "RIGHT BUTTON: CROSS STRUCTURE ELMENT" << endl;
    setMouseCallback("BOUNDARY", mouseEvent);

    waitKey();
}

