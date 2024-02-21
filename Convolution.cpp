#include <iostream>

#include "Convolution.h"

// Default constructor 
Convolution::Convolution() {

}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** kernel, int kernelHeight, int kernelWidth, int stride, bool padding){

    this->kernelHeight=kernelHeight;
    this->kernelWidth=kernelWidth;
    this->stride=stride;
    this->padding=padding;

    customKernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        customKernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            customKernel[i][j] = kernel[i][j];
        }
    }
}

// Destructor
Convolution::~Convolution() {
    if(customKernel != nullptr){
        for (int i = 0; i < kernelHeight; i++) {
            delete[] customKernel[i];
        }
        delete[] customKernel;
    }
}

// Copy constructor
Convolution::Convolution(const Convolution &other){
    this->kernelHeight = other.kernelHeight;
    this->kernelWidth = other.kernelWidth;
    this->stride = other.stride;
    this->padding = other.padding;
    this->outputHeight = other.outputHeight;
    this->outputWidth = other.outputWidth;

    customKernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        customKernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            customKernel[i][j] = other.customKernel[i][j];
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if(this == &other){
        return *this;
    }

    // Deallocate old memory
    if (customKernel != nullptr) {
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] customKernel[i];
        }
        delete[] customKernel;
    }

    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;
    stride = other.stride;
    padding = other.padding;
    outputHeight = other.outputHeight;
    outputWidth = other.outputWidth;

    customKernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        customKernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            customKernel[i][j] = other.customKernel[i][j];
        }
    }
    return *this;
}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {

    int imageWidth = input_image.get_width();
    int imageHeight = input_image.get_height();

    int resultHeight = calculateOutputHeight(imageHeight,kernelHeight,padding, stride);
    int resultWidth = calculateOutputWidth(imageWidth,kernelWidth,padding, stride);

    ImageMatrix padding_input_image(input_image.get_height()+2,input_image.get_width()+2);
    padding_input_image = pad(input_image);

    double** kernel = customKernel;
    double** image = (padding) ? padding_input_image.get_data() : input_image.get_data();



    ImageMatrix resultImageMatrix(resultHeight,resultWidth);

    for (int i = 0; i < resultHeight; i++) {
        for (int j = 0; j < resultWidth; j++) {
            double sum = 0.0;
            for (int m = 0; m < kernelHeight; m++) {
                for (int n = 0; n < kernelWidth; n++) {
                    int x = i * stride + m;
                    int y = j * stride + n;
                    sum += image[x][y] * kernel[m][n];
                }
            }
                resultImageMatrix.set_data(i,j,sum);
        }
    }
    return resultImageMatrix;
}

ImageMatrix Convolution::pad(const ImageMatrix& input_image) const {
    int image_width = input_image.get_width();
    int image_height = input_image.get_height();

    int result_height = image_height+2;
    int result_width = image_width+2;

    double** image = input_image.get_data();

    ImageMatrix padImageMatrix(result_height,result_width);

    for (int i = 0; i < result_height; i++) {
        for (int j = 0; j < result_width; j++) {
            if (i < 1 || i >= image_height + 1 || j < 1 || j >= image_width + 1) {
                padImageMatrix.set_data(i,j,0.0); // Fill with zeros for padding.
            } else {
                padImageMatrix.set_data(i,j,image[i - 1][j - 1]);
            }
        }
    }

    return padImageMatrix;
}

int Convolution::calculateOutputHeight(int image_height, int kernel_height, bool isPadding, int stride) const {
    int intPadding = (padding) ? 1 : 0;

    double result = (((image_height-kernel_height)+(2*intPadding))/stride)+1;
    int result_height = int (result);
    return int (result_height);
}

int Convolution::calculateOutputWidth(int image_width, int kernel_width, bool isPadding, int stride) const {
    int intPadding = (padding) ? 1 : 0;

    double result = (((image_width-kernel_width)+(2*intPadding))/stride)+1;
    int result_width = int (result);
    return int (result_width);
}

int Convolution::getKernelHeight() const {
    return kernelHeight;
}

int Convolution::getKernelWidth() const {
    return kernelWidth;
}

int Convolution::getStride() const {
    return stride;
}

bool Convolution::getPadding() const {
    return padding;
}

int Convolution::getOutputHeight() const {
    return outputHeight;
}

int Convolution::getOutputWidth() const {
    return outputWidth;
}

double** Convolution::getCustomKernel() const {
    return customKernel;
}
