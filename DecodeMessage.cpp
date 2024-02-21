// DecodeMessage.cpp

#include "DecodeMessage.h"
#include <iostream>

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}


std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {

    std::cout<<"\n\n\n\n\n" << edgePixels.size() << "\n\n\n\n\n" <<std::endl;


    std::string decodedString = "";
    std::string lsbString = "";

    for (const auto& pair : edgePixels) {
        int decimal_value = (int) image.get_data(pair.first,pair.second);
        int lsb = decimal_value % 2;
        std::string charLsb = std::to_string(lsb);
        lsbString += charLsb;
    }

    if(lsbString.length()%7 != 0){
        for(int i = 0; i < lsbString.length() % 7; ++i){
            lsbString.insert(0, "0");
        }
    }

    for(int i = 0 ; i < lsbString.length()/7; ++i){
        std::string subStr = lsbString.substr(i*7, 7);
        int decimalValue = std::stoi(subStr, 0, 2);
        if(decimalValue<33){
            decimalValue += 33;
        }else if(decimalValue>126){
            decimalValue=126;
        }
        char characterValue = static_cast<char>(decimalValue);
        decodedString += characterValue;
    }

    return decodedString;
}

