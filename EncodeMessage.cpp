#include "EncodeMessage.h"
#include <cmath>
#include <iostream>



// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {
    
}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions) {

    std::string manipulated_message;

    std::string encodeBinary = ""; //0100001010111101010001010110101010110101010101001101010110110


    int index = 0;
    for (char c : message) {
        int asciiValue = static_cast<int>(c);
        if(isPrime(index)){
            asciiValue += fibonacci(index);
            if(asciiValue<33){
                asciiValue+=33;
            }else if(asciiValue>126){
                asciiValue=126;
            }
        }

        manipulated_message+=static_cast<char>(asciiValue);
        index++;
    }

    int msg_length = manipulated_message.length();
    int shift = msg_length/2;

    std::string shiftedStr;
    shiftedStr = manipulated_message.substr(msg_length - shift) + manipulated_message.substr(0, msg_length - shift);


    for (char c : shiftedStr) {
        int asciiValue = static_cast<int>(c);
        std::string binaryValue = intToBinary(asciiValue);
        encodeBinary += binaryValue;
    }

    if(encodeBinary.length()%7 != 0){
        for(int i = 0; i < encodeBinary.length() % 7; ++i){
            encodeBinary.insert(0, "0");
        }
    }

    index = 0;
    for(const auto& position : positions){
        int cX = position.first;
        int cY = position.second;

        int value = img.get_data(cX,cY);

        if (encodeBinary.length()>index){
            if ((value % 2) != encodeBinary[index]) {
                value ^= 1;
                img.set_data(cX, cY, value);
            } else {
                img.set_data(cX, cY, value);
            }
        }
        index++;
    }
    return img;
}


std::string EncodeMessage::intToBinary(int n){
    std::string binary;
    while (n > 0) {
        binary.insert(binary.begin(), '0' + (n & 1));
        n >>= 1;
    }
    return binary;
}

bool EncodeMessage::isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}


int EncodeMessage::fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

