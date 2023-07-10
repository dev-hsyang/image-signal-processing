//
//  main.cpp
//  ImageSignalProccessing
//
//  Created by 양현승 on 2022/04/17.
//

#include <iostream>
#include "opencv2/core.hpp"
#include <array>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

void Gauss1(InputArray input, OutputArray& output, float sigma) {
    const Mat& img = input.getMat();
    output.create(img.size(), img.type());
    Mat dst = output.getMat();
    Mat tmp(img.size(), img.type());
    int windowSize = int(ceil(sigma * 2) + 1);
    
    for(int y=0; y<img.rows; y++)
        for(int x=0; x<img.cols; x++){
            float wSum = 0;
            float vSum = 0;
            for(int t=-windowSize; t<=windowSize; t++){
                    float g = exp( -(t * t) / (sigma * sigma) );
                    wSum+= g;
                    vSum+= g * img.at<float>(min(img.rows-1, max(0, y+t)), x);
                }
            tmp.at<float>(y,x) = vSum / wSum;
        }
    
    // x, y seperable 하게 operation 하여 시간복잡도 개선
    
    for(int y=0; y<img.rows; y++)
        for(int x=0; x<img.cols; x++){
            float wSum = 0;
            float vSum = 0;
            for(int s=-windowSize; s<=windowSize; s++){
                    float g = exp( -(s * s) / (sigma * sigma) );
                    wSum+= g;
                    vSum+= g * tmp.at<float>(y, min(img.cols-1, max(0, x+s)));
                }
            dst.at<float>(y,x) = vSum / wSum;
        }
    
    /*
    for( int y=0; y<img.rows; y++)
        for( int x=0; x<img.cols; x++){
            float wSum = 0;
            float vSum = 0;
            for( int t=-windowSize; t<=windowSize; t++)
                for( int s=-windowSize; s<windowSize; s++){
                    float g = exp(-(s*s+t*t)/(sigma*sigma));
                    wSum += g;
                    vSum += g * img.at<float>(min(img.rows-1, max(0, y+t)), min(img.cols-1, max(0, x+s)));
                }
            dst.at<float>(y,x) = vSum / wSum;
        }
     */
}

void myMedianFilter(InputArray input, OutputArray& output, int windowSize) {
    int filter = ceil((windowSize-1)/2);
    const Mat& image = input.getMat();
    output.create(image.size(), image.type());
    Mat dst = output.getMat();
    
    int xSum;
    int ySum;
    for(int y=0; y<image.rows; y++)
        for(int x=0; x<image.cols; x++){
            
            vector<uchar> neighbors;
            
            for(int i=-filter; i<=filter; i++)
                for(int j=-filter; j<=filter; j++){
                    
                    xSum = y + i;
                    ySum = x + j;
                    //padding
                    if(xSum<0)
                        xSum = 0;
                    if(xSum>=image.cols)
                        xSum = image.cols - 1;
                    if(ySum<0)
                        ySum = 0;
                    if(ySum>=image.rows)
                        ySum = image.rows - 1;
                    neighbors.push_back(image.at<uchar>(xSum, ySum));
                    //neighbors.push_back(image.at<uchar>(min(image.rows-1, max(0, y+i)), min(image.cols-1, max(0, x+j))));
                }
            sort(neighbors.begin(), neighbors.end());
            dst.at<uchar>(y, x) = neighbors[(int)(neighbors.size() / 2)];
            neighbors.clear();
        }
}

int main(int argc, const char * argv[]) {
    
    Mat image = imread("/Users/hyunseung/포트폴리오/영상처리/과제/1차과제/레드벨벳-슬기-패션.jpg.webp", 0);
    Mat image2 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/1차과제/MedianFilterInput.png", 0);
    Mat MedianFilterInput = imread("/Users/hyunseung/포트폴리오/영상처리/과제/1차과제/MedianFilterInput.png", 0);
    image.convertTo(image, CV_32F,1/255.f); // image의 intensity를 0~255인 정수인 것을 0~1인 실수로 바꾼다.
    image2.convertTo(image2, CV_32F, 1/255.f);
    Mat a = image / 128; // image matrix를 나누어도 실수값이 나온다. 기존 intensity대로 0~255였으면 행렬의 각 원소는 0, 1, 2 세가지 값만 나오게 되고 이후에 128을 다시 곱해도 세가지 값만 나오게 되어 복구가 불가능해진다.
    Mat b = a * 128; // 실수값에 128을 곱하면 실수값이 나온다. 복구가 가능해지는 것
    
    Mat power;
    pow(image, 0.2, power); // gamma transformation
    
    Mat out1;
    Gauss1(image2, out1, 5);
    
    Mat out2;
    GaussianBlur(image2, out2, Size(), 5);
    
    Mat medianFiltered1;
    myMedianFilter(MedianFilterInput, medianFiltered1, 5);
    
    Mat median2;
    myMedianFilter(MedianFilterInput, median2, 3);
    
    Mat medianFiltered2;
    medianBlur(MedianFilterInput, medianFiltered2, 5);
    

    //printf("image size is: %d x %d\n", image.cols, image.rows);
    //imshow("Seulgi", image);
    //imshow("intensity operated(multiply)", b);
    //imshow("gamma transformed", power);
    //imshow("image 2", image2);
    //imshow("Gaussian F", out1);
    imshow("source", MedianFilterInput);
    imshow("myMedianFilter", medianFiltered1);
    imshow("median", median2);
    imshow("medianBlur", medianFiltered2);
    waitKey();
}
