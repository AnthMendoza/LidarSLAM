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
    uint8_t  AreflectChennel0;
    uint16_t AdistChannel1;
    uint8_t  AreflectChennel1;
    uint16_t AdistChannel2;
    uint8_t  AreflectChennel2;
    uint16_t AdistChannel3;
    uint8_t  AreflectChennel3;
    uint16_t AdistChannel4;
    uint8_t  AreflectChennel4;
    uint16_t AdistChannel5;
    uint8_t  AreflectChennel5;
    uint16_t AdistChannel6;
    uint8_t  AreflectChennel6;
    uint16_t AdistChannel7;
    uint8_t  AreflectChennel7;
    uint16_t AdistChannel8;
    uint8_t  AreflectChennel8;
    uint16_t AdistChannel9;
    uint8_t  AreflectChennel9;
    uint16_t AdistChannel10;
    uint8_t  AreflectChennel10;
    uint16_t AdistChannel11;
    uint8_t  AreflectChennel11;
    uint16_t AdistChannel12;
    uint8_t  AreflectChennel12;
    uint16_t AdistChannel13;
    uint8_t  AreflectChennel13;
    uint16_t AdistChannel14;
    uint8_t  AreflectChennel14;
    uint16_t AdistChannel15;
    uint8_t  AreflectChennel15;

    uint16_t BdistChannel0;
    uint8_t  BreflectChennel0;
    uint16_t BdistChannel1;
    uint8_t  BreflectChennel1;
    uint16_t BdistChannel2;
    uint8_t  BreflectChennel2;
    uint16_t BdistChannel3;
    uint8_t  BreflectChennel3;
    uint16_t BdistChannel4;
    uint8_t  BreflectChennel4;
    uint16_t BdistChannel5;
    uint8_t  BreflectChennel5;
    uint16_t BdistChannel6;
    uint8_t  BreflectChennel6;
    uint16_t BdistChannel7;
    uint8_t  BreflectChennel7;
    uint16_t BdistChannel8;
    uint8_t  BreflectChennel8;
    uint16_t BdistChannel9;
    uint8_t  BreflectChennel9;
    uint16_t BdistChannel10;
    uint8_t  BreflectChennel10;
    uint16_t BdistChannel11;
    uint8_t  BreflectChennel11;
    uint16_t BdistChannel12;
    uint8_t  BreflectChennel12;
    uint16_t BdistChannel13;
    uint8_t  BreflectChennel13;
    uint16_t BdistChannel14;
    uint8_t  BreflectChennel14;
    uint16_t BdistChannel15;
    uint8_t  BreflectChennel15;
};

struct Packet{

    std::array<dataBlock, 16> blocks; 

    uint32_t timeStamp;
};

struct Point {
    float x, y, z;
};




void UDP();

void getPoints(std::vector<Point> &returnPoints);


#endif