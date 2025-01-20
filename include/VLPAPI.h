#ifndef VLPAPI_H
#define VLPAPI_H

#include <cstdint>
#include <vector>
#include <array>

struct dataBlock{

    uint8_t flagFF;
    uint8_t flagEE;

    uint16_t azimuth;

    uint16_t AdistChannel0;
    uint8_t  Areflectchannel0;
    uint16_t AdistChannel1;
    uint8_t  Areflectchannel1;
    uint16_t AdistChannel2;
    uint8_t  Areflectchannel2;
    uint16_t AdistChannel3;
    uint8_t  Areflectchannel3;
    uint16_t AdistChannel4;
    uint8_t  Areflectchannel4;
    uint16_t AdistChannel5;
    uint8_t  Areflectchannel5;
    uint16_t AdistChannel6;
    uint8_t  Areflectchannel6;
    uint16_t AdistChannel7;
    uint8_t  Areflectchannel7;
    uint16_t AdistChannel8;
    uint8_t  Areflectchannel8;
    uint16_t AdistChannel9;
    uint8_t  Areflectchannel9;
    uint16_t AdistChannel10;
    uint8_t  Areflectchannel10;
    uint16_t AdistChannel11;
    uint8_t  Areflectchannel11;
    uint16_t AdistChannel12;
    uint8_t  Areflectchannel12;
    uint16_t AdistChannel13;
    uint8_t  Areflectchannel13;
    uint16_t AdistChannel14;
    uint8_t  Areflectchannel14;
    uint16_t AdistChannel15;
    uint8_t  Areflectchannel15;

    uint16_t BdistChannel0;
    uint8_t  Breflectchannel0;
    uint16_t BdistChannel1;
    uint8_t  Breflectchannel1;
    uint16_t BdistChannel2;
    uint8_t  Breflectchannel2;
    uint16_t BdistChannel3;
    uint8_t  Breflectchannel3;
    uint16_t BdistChannel4;
    uint8_t  Breflectchannel4;
    uint16_t BdistChannel5;
    uint8_t  Breflectchannel5;
    uint16_t BdistChannel6;
    uint8_t  Breflectchannel6;
    uint16_t BdistChannel7;
    uint8_t  Breflectchannel7;
    uint16_t BdistChannel8;
    uint8_t  Breflectchannel8;
    uint16_t BdistChannel9;
    uint8_t  Breflectchannel9;
    uint16_t BdistChannel10;
    uint8_t  Breflectchannel10;
    uint16_t BdistChannel11;
    uint8_t  Breflectchannel11;
    uint16_t BdistChannel12;
    uint8_t  Breflectchannel12;
    uint16_t BdistChannel13;
    uint8_t  Breflectchannel13;
    uint16_t BdistChannel14;
    uint8_t  Breflectchannel14;
    uint16_t BdistChannel15;
    uint8_t  Breflectchannel15;
};

struct Packet{

    std::array<dataBlock, 16> blocks; 

    uint32_t timeStamp;
};

struct Point {
    float x, y, z;
    uint8_t reflectivity;
};




void UDP();

void getPoints(std::vector<Point> &returnPoints);


#endif