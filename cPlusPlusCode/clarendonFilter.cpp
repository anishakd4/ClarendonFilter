#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;


//interpolation
void interpolation(uchar* lut, float* curve, float* originalValue){
    for(int i=0; i<256; i++){
        int j=0;
        float a = i;
        while (a>originalValue[j]){
            j++;
        }
        if(a == originalValue[j]){
            lut[i] = curve[j];
            continue;
        }
        float slope = ((float)(curve[j] - curve[j-1]))/((float)(originalValue[j] - originalValue[j-1]));
        float constant = curve[j] - slope * originalValue[j];
        lut[i] = slope * a + constant;
    }
}

int main(){

    //Read input image
    Mat image = imread("../assets/anish.jpg");

    //check if image exists
    if(image.empty()){
        cout<<"Can not find image"<<endl;
        return 0;
    }

    //Define variable to store final result
    Mat clarendon;

    //Interpolation values
    float originValues[]={0, 28, 56, 85, 113, 141, 170, 198, 227, 255};
    float blueValues[]=  {0, 38, 66, 104, 139, 175, 206, 226, 245 , 255};
    float redValues[]=   {0, 16, 35, 64, 117, 163, 200, 222, 237, 249};
    float greenValues[]= {0, 24, 49, 98, 141, 174, 201, 223, 239, 255};

    //create a clone of input image to work on
    clarendon = image.clone();

    //split the channels
    vector<Mat> channels;
    split(clarendon, channels);

    //create a lookup table
    Mat lookupTable(1, 256, CV_8U);
    uchar* lut = lookupTable.ptr();

    //Apply interpolation and create lookup table
    interpolation(lut, blueValues, originValues);
    //Apply mapping for Blue Channel
    LUT(channels[0], lookupTable, channels[0]);

    //Apply interpolation and create lookup table
    interpolation(lut, greenValues, originValues);
    //Apply mapping for green Channel
    LUT(channels[1], lookupTable, channels[1]);

    //Apply interpolation and create lookup table
    interpolation(lut, redValues, originValues);
    //Apply mapping for Red Channel
    LUT(channels[2], lookupTable, channels[2]);

    //merge back the channels
    merge(channels, clarendon);

    //Create windows to display images
    namedWindow("image", WINDOW_AUTOSIZE);
    namedWindow("clarendon", WINDOW_AUTOSIZE);

    //display images
    imshow("image", image);
    imshow("clarendon", clarendon);

    //Press esc to exit the program
    waitKey(0);

    //close all the opened windows
    destroyAllWindows();

    return 0;
}