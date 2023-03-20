# Medical_Image_Processing_HW01-2
醫療影像處理-Histogram Equalization

## 顯示直方圖

```
int main(){
  HistogramIMG HT;
  Mat img_high_contrast = imread("High-contrast.png", 0);
  Mat img_hist_high_contrast = HT.showHistogram(img_high_contrast);
  imshow("histogram_high_contrast", img_hist_high_contrast);
}
```

## Equalization

```
int main(){
  HistogramIMG HT;
  Mat img_high_contrast = imread("High-contrast.png", 0);
  Mat img_enhance_high_contrast = HT.equalization(img_high_contrast);
  imshow("ehance_high_contrast", img_enhance_high_contrast);
}
```

## 處理用的class

```
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
```
