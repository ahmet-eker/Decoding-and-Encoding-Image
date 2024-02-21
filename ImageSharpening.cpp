#include "ImageSharpening.h"
#include <iostream>

// Default constructor
ImageSharpening::ImageSharpening() {
    const double* kernel[3] = {
            new double[3]{1.0, 1.0, 1.0},
            new double[3]{1.0, 1.0, 1.0},
            new double[3]{1.0, 1.0, 1.0}
    };

    ImageMatrix imageMatrix = ImageMatrix(kernel,3,3);
    ImageMatrix blurred_matrix = imageMatrix*(1.0/9);

    blurring_kernel = new double*[3];
    for (int i = 0; i < 3; ++i) {
        blurring_kernel[i] = new double[3];
        for (int j = 0; j < 3; ++j) {
            blurring_kernel[i][j] = blurred_matrix.get_data()[i][j];
        }
    }

}

ImageSharpening::~ImageSharpening(){
    if(blurring_kernel != nullptr){
        for (int i = 0; i < 3; i++) {
            delete[] blurring_kernel[i];
        }
        delete[] blurring_kernel;
    }
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {

    Convolution myConv(blurring_kernel,3,3,1, true);

    ImageMatrix blurredImage = myConv.convolve(input_image);

    ImageMatrix sharpenedImage = input_image + ((input_image - blurredImage) * k);

    for(int i = 0; i<sharpenedImage.get_height();++i){
        for(int j = 0; j<sharpenedImage.get_width(); ++j){
            if(sharpenedImage.get_data(i,j)<0){
                sharpenedImage.set_data(i,j,0);
            } else if(sharpenedImage.get_data(i,j)>255){
                sharpenedImage.set_data(i,j,255);
            }
        }
    }
    return sharpenedImage;
}
