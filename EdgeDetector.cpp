// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <iostream>

// Default constructor
EdgeDetector::EdgeDetector() {

    const double* kernel1[3] = {
            new double[3]{1.0, 0.0, -1.0},
            new double[3]{2.0, 0.0, -2.0},
            new double[3]{1.0, 0.0, -1.0}
    };

    ImageMatrix imageMatrix1 = ImageMatrix(kernel1,3,3);

    xKernel = new double*[3];
    for (int i = 0; i < 3; ++i) {
        xKernel[i] = new double[3];
        for (int j = 0; j < 3; ++j) {
            xKernel[i][j] = imageMatrix1.get_data()[i][j];
        }
    }

    const double* kernel2[3] = {
            new double[3]{1.0, 2.0, 1.0},
            new double[3]{0.0, 0.0, 0.0},
            new double[3]{-1.0, -2.0, -1.0}
    };

    ImageMatrix imageMatrix2 = ImageMatrix(kernel2,3,3);

    yKernel = new double*[3];
    for (int i = 0; i < 3; ++i) {
        yKernel[i] = new double[3];
        for (int j = 0; j < 3; ++j) {
            yKernel[i][j] = imageMatrix2.get_data()[i][j];
        }
    }
}

// Destructor
EdgeDetector::~EdgeDetector() {
    if(xKernel != nullptr){
        for (int i = 0; i < 3; i++) {
            delete[] xKernel[i];
        }
        delete[] xKernel;
    }

    if(yKernel != nullptr){
        for (int i = 0; i < 3; i++) {
            delete[] yKernel[i];
        }
        delete[] yKernel;
    }
}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {

    std::vector<std::pair<int, int>> edgePixels;

    ImageMatrix input_image2 = ImageMatrix(input_image);
    ImageMatrix input_image3 = ImageMatrix(input_image);

    Convolution xMyConv(xKernel,3,3,1, true);
    Convolution yMyConv(yKernel,3,3,1, true);


    ImageMatrix xConvolvedImage = xMyConv.convolve(input_image3);
    ImageMatrix yConvolvedImage = yMyConv.convolve(input_image2);

    ImageMatrix gradientImage(xConvolvedImage.get_height(),xConvolvedImage.get_width());


    int resultHeight = gradientImage.get_height();
    int resultWidth = gradientImage.get_width();

    double sum = 0;
    for (int i = 0; i < resultHeight; i++) {
        for (int j = 0; j < resultWidth; j++) {
            double gradient_value = sqrt(pow(xConvolvedImage.get_data(i,j),2) + pow(yConvolvedImage.get_data(i,j),2));
            gradientImage.set_data(i,j,gradient_value);
            sum+=gradient_value;
        }
    }

    threshold = sum/(resultWidth*resultHeight);
    for (int i = 0; i < resultHeight; i++) {
        for (int j = 0; j < resultWidth; j++) {
            if(gradientImage.get_data(i,j)>threshold){
                edgePixels.push_back(std::make_pair(i,j));
            }
        }
    }

    return edgePixels;
}

