//
//  main.cpp
//  NoiseReduction
//
//  Created by 양현승 on 2022/06/01.
//

#include <iostream>
#include <array>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;

void ContraHarmonic(Mat src, Mat dst, int kernel, double q){
    Mat temp = src.clone();
    
    for(int row=kernel/2; row<temp.rows-kernel/2-1; row++){
        for(int col=kernel/2; col<temp.cols-kernel/2-1; col++){
            double den=0, num=0;
            for(int i= -(kernel/2); i<=(kernel/2); i++){
                for(int j= -(kernel/2); j<=(kernel/2); j++){
                    den += pow(temp.at<uchar>(row+i, col+j), q);
                    num += pow(temp.at<uchar>(row+i, col+j), q+1);
                }
            }
            dst.at<float>(row, col) = num / den;
        }
    }
    dst.convertTo(dst, CV_8U);
}

int main(int argc, const char * argv[]) {
   
    Mat origin = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/original.png", 0);
    Mat g10 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/Gaussian_0.10.png", 0);
    Mat g15 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/Gaussian_0.15.png", 0);
    Mat g20 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/Gaussian_0.20.png", 0);
    Mat p5 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/pepper_0.05.png", 0);
    Mat p10 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/pepper_0.10.png", 0);
    Mat p15 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/salt_pepper_0.15.png", 0);
    Mat s5 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/salt_0.05.png", 0);
    Mat s10 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/salt_0.10.png", 0);
    Mat s15 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/salt_0.15.png", 0);
    Mat sp5 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/salt_pepper_0.05.png", 0);
    Mat sp10 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/salt_pepper_0.10.png", 0);
    Mat sp15 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/salt_pepper_0.15.png", 0);
    Mat u10 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/uniform_0.10.png", 0);
    Mat u15 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/uniform_0.15.png", 0);
    Mat u20 = imread("/Users/hyunseung/포트폴리오/영상처리/과제/2차과제/NoisyImage/uniform_0.20.png", 0);
    origin.convertTo(origin, CV_32F, 1/255.f);
    g10.convertTo(g10, CV_32F, 1/255.f);
    g15.convertTo(g15, CV_32F, 1/255.f);
    g20.convertTo(g20, CV_32F, 1/255.f);
    p5.convertTo(p5, CV_32F, 1/255.f);
    p10.convertTo(p10, CV_32F, 1/255.f);
    p15.convertTo(p15, CV_32F, 1/255.f);
    s5.convertTo(s5, CV_32F, 1/255.f);
    s10.convertTo(s10, CV_32F, 1/255.f);
    s15.convertTo(s15, CV_32F, 1/255.f);
    sp5.convertTo(sp5, CV_32F, 1/255.f);
    sp10.convertTo(sp10, CV_32F, 1/255.f);
    sp15.convertTo(sp15, CV_32F, 1/255.f);
    u10.convertTo(u10, CV_32F, 1/255.f);
    u15.convertTo(u15, CV_32F, 1/255.f);
    u20.convertTo(u20, CV_32F, 1/255.f);
    
    Mat g10f;
    Mat g15f;
    Mat g20f;
    Mat p5f;
    Mat p10f;
    Mat p15f;
    Mat s5f;
    Mat s10f;
    Mat s15f;
    Mat sp5f;
    Mat sp10f;
    Mat sp15f;
    Mat u10f;
    Mat u15f;
    Mat u20f;
    
    //ContraHarmonic(p15, p15f, 5, 3);
    GaussianBlur(g10, g10f, Size(), 1);
    bilateralFilter(g15, g15f, 3, 0, 2);
    bilateralFilter(g20, g20f, 5, 0, 2);
    medianBlur(p5, p5f, 3);
    medianBlur(p10, p10f, 5);
    medianBlur(p15, p15f, 5);
    medianBlur(s5, s5f, 3);
    medianBlur(s10, s10f, 3);
    medianBlur(s15, s15f, 5);
    medianBlur(sp5, sp5f, 3);
    medianBlur(sp10, sp10f, 3);
    medianBlur(sp15, sp15f, 5);
    GaussianBlur(u10, u10f, Size(), 1);
    bilateralFilter(u15, u15f, 3, 0, 2);
    bilateralFilter(u20, u20f, 5, 0, 2);
     
    imshow("p5f", p5f);
    imshow("p10f", p10f);
    imshow("p15f", p15f);
    imshow("s5f", s5f);
    imshow("s10f", s10f);
    imshow("s15f", s15f);
    imshow("sp5f", sp5f);
    imshow("sp10f", sp10f);
    imshow("sp15f", sp15f);
    imshow("g10f", g10f);
    imshow("g15f", g15f);
    imshow("g20f", g20f);
    imshow("u10f", u10f);
    imshow("u15f", u15f);
    imshow("u20f", u20f);
    
    printf("p5f PSNR: %f\n", PSNR(p5f, origin));
    printf("p10f PSNR: %f\n", PSNR(p10f, origin));
    printf("p15f PSNR: %f\n", PSNR(p15f, origin));
    printf("s5f PSNR: %f\n", PSNR(s5f, origin));
    printf("s10f PSNR: %f\n", PSNR(s10f, origin));
    printf("s15f PSNR: %f\n", PSNR(s15f, origin));
    printf("sp5f PSNR: %f\n", PSNR(sp5f, origin));
    printf("sp10f PSNR: %f\n", PSNR(sp10f, origin));
    printf("sp15f PSNR: %f\n", PSNR(sp15f, origin));
    printf("g10f PSNR: %f\n", PSNR(g10f, origin));
    printf("g15f PSNR: %f\n", PSNR(g15f, origin));
    printf("g20f PSNR: %f\n", PSNR(g20f, origin));
    printf("u10f PSNR: %f\n", PSNR(u10f, origin));
    printf("u15f PSNR: %f\n", PSNR(u15f, origin));
    printf("u20f PSNR: %f\n", PSNR(u20f, origin));
    
    waitKey();
    return 0;
    
    
}
