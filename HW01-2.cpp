#include <iostream>
#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\imgcodecs.hpp>
#include<opencv2\imgproc.hpp>

using namespace std;
using namespace cv;
class HistogramIMG {
public:
    Mat showHistogram(Mat src) {
        Mat hist;
        int bins = 256;
        int hist_size[] = { 256 };
        float range[] = { 0, 256 };
        const float* ranges[] = { range };
        calcHist(&src, 1, 0, Mat(), hist, 1, hist_size, ranges);//計算像素分布
        /*
        *calcHist(輸入圖, 幾個圖, 通道*灰階>>0, 輸入陣列, 輸出陣列, 直方圖的通道數, 直方圖要分成段*x軸個數, 像素的灰階範圍*0~256) 
        */
        
        double r_max, r_min;
        minMaxLoc(hist, &r_min, &r_max);//訂出最大 r_min暫時用不到
        int scale = 2;//直方圖寬度
        int hist_height = 256;
        Mat hist_img = Mat::zeros(hist_height, scale * bins, CV_8UC3);//製作一個0矩陣
        for (int i = 0; i < bins; i++)//讀取剛剛統計好的灰階圖中的每個值
        {
            float bin_val = hist.at<float>(i);
            int inten = cvRound(bin_val * hist_height / r_max);//四捨五入取整數
            //繪製直方圖
            rectangle(hist_img, 
                Point(scale * i, hist_height - 1), 
                Point((i + 1) * scale - 1, hist_height - inten),
                CV_RGB(255, 255, 255));
        }
        return hist_img;//完成
    }

    Mat equalization(Mat src) {
        Mat enhance;
        equalizeHist(src, enhance);
        return enhance;
    }
};

int main()
{
    HistogramIMG HT;

    //high-cinstrast
    Mat img_high_contrast = imread("High-contrast.png", 0);
    if (!img_high_contrast.data) {
        cout << "無法開啟圖片" << endl;
        return 0;
    }
    namedWindow("original_high_contrast", WINDOW_AUTOSIZE);
    imshow("original_high_contrast", img_high_contrast);
    Mat img_hist_high_contrast = HT.showHistogram(img_high_contrast);
    imwrite("histogram_high_contrast.png", img_hist_high_contrast);
    imshow("histogram_high_contrast", img_hist_high_contrast);

    Mat img_enhance_high_contrast = HT.equalization(img_high_contrast);
    Mat img_hist_enhance_high_constrat = HT.showHistogram(img_enhance_high_contrast);
    imwrite("histogram_enhance_high_constrat.png", img_hist_enhance_high_constrat);
    imwrite("enhance_high_constrat.png", img_enhance_high_contrast);
    imshow("histogram_enhance_high_constrat", img_hist_enhance_high_constrat);
    imshow("ehance_high_contrast", img_enhance_high_contrast);
    

    //bright
    Mat img_bright = imread("Bright.png", 0);
    if (!img_bright.data)
    {
        cout << "無法開啟圖片" << endl;
        return 0;
    }
    namedWindow("original_bright", WINDOW_AUTOSIZE);
    imshow("original_bright", img_bright);
    Mat img_hist_bright = HT.showHistogram(img_bright);
    imwrite("histogram_bright.png", img_hist_bright);
    imshow("histogram_bright", img_hist_bright);

    Mat img_enhance_bright = HT.equalization(img_bright);
    Mat img_hist_enhance_bright = HT.showHistogram(img_enhance_bright);
    imwrite("histogram_enhance_bright.png", img_hist_enhance_bright);
    imwrite("enhance_bright.png", img_enhance_bright);
    imshow("histogram_enhance_bright", img_hist_enhance_bright);
    imshow("ehance_bright", img_enhance_bright);


    //dark
    Mat img_dark = imread("Dark.png", 0);
    if (!img_dark.data)
    {
        cout << "無法開啟圖片" << endl;
        return 0;
    }
    namedWindow("original_dark", WINDOW_AUTOSIZE);
    imshow("original_dark", img_dark);
    Mat img_hist_dark = HT.showHistogram(img_dark);
    imwrite("histogram_dark.png", img_hist_dark);
    imshow("histogram_dark", img_hist_dark);
    Mat img_enhance_dark = HT.equalization(img_dark);
    Mat img_hist_enhance_dark = HT.showHistogram(img_enhance_dark);
    imwrite("histogram_enhance_dark.png", img_hist_enhance_dark);
    imwrite("enhance_dark.png", img_enhance_dark);
    imshow("img_hist_enhance_dark", img_hist_enhance_dark);
    imshow("enhance_dark", img_enhance_dark);


    //low-constrast
    Mat img_low_contrast = imread("Low-contrast.png", 0);
    if (!img_low_contrast.data)
    {
        cout << "無法開啟圖片" << endl;
        return 0;
    }
    namedWindow("original_low_contrast", WINDOW_AUTOSIZE);
    imshow("original_low_contrast", img_low_contrast);
    Mat img_hist_low_contrast = HT.showHistogram(img_low_contrast);
    imwrite("histogram_low_contrast.png", img_hist_low_contrast);
    imshow("histogram_low_contrast", img_hist_low_contrast);

    Mat img_enhance_low_constrast = HT.equalization(img_low_contrast);
    Mat img_hist_enhance_low_constrast = HT.showHistogram(img_enhance_low_constrast);
    imwrite("histogram_enhance_low_constrast.png", img_hist_enhance_low_constrast);
    imwrite("enhance_low_constrast.png", img_enhance_low_constrast);
    imshow("img_hist_enhance_low_constrast", img_hist_low_contrast);

    waitKey(0);

    return 0;
}