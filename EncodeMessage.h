#ifndef ENCODE_MESSAGE_H
#define ENCODE_MESSAGE_H

#include <string>
#include <vector>
#include "ImageMatrix.h"

class EncodeMessage {
public:
    EncodeMessage();
    ~EncodeMessage();

    ImageMatrix encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions);

    std::string intToBinary(int n);
    bool isPrime(int n);
    int fibonacci(int n);

private:
    // Any private helper functions or variables if necessary

    
};

#endif // ENCODE_MESSAGE_H
