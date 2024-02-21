#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    DecodeMessage decoder;
    EdgeDetector edgeDetector;
    ImageSharpening sharpener;
    ImageMatrix sharpenImage;
    std::vector<std::pair<int, int>> edge_pixels;
    sharpenImage = sharpener.sharpen(img,2);
    edge_pixels = edgeDetector.detectEdges(sharpenImage);
    std::string secretCode = decoder.decodeFromImage(sharpenImage,edge_pixels);
    return secretCode;
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    EncodeMessage encoder;
    EdgeDetector edgeDetector;
    std::vector<std::pair<int, int>> edge_pixels;
    edge_pixels = edgeDetector.detectEdges(img);
    ImageMatrix encodedImage(img.get_height(),img.get_width());
    encodedImage = encoder.encodeMessageToImage(img,message,edge_pixels);
    return encodedImage;
}
