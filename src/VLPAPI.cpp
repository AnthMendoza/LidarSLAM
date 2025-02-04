#include <iostream>
#include <iomanip>       // For std::hex and std::setw
#include <cstring>       // For memset
#include <cstdlib>       // For exit
#include <stdio.h>
#include <sys/socket.h>  // For socket functions
#include <netinet/in.h>  // For sockaddr_in
#include <unistd.h>      // For close()
#include <bitset>
#include <mutex>
#include <vector>
#include <array>
#include "../include/VLPAPI.h"
#include <cmath>



uint8_t threasholdLower = 10;
uint8_t threasholdUpper = 100;
float maxDistance = 70;

Packet packet;

std::mutex readAndWrite;


std::array<Point,pointSize> setOfPoints = {};
uint32_t count = 0;

void readPacket(Packet &packet ,std::array<float , 16> &verticalAngle){
    std::lock_guard<std::mutex> lock(readAndWrite);



    for( int i = 0 ; i <  12 ; i++){

        uint16_t* distChannels[] = {
            &packet.blocks[i].AdistChannel0, &packet.blocks[i].AdistChannel1,  &packet.blocks[i].AdistChannel2,
            &packet.blocks[i].AdistChannel3, &packet.blocks[i].AdistChannel4,  &packet.blocks[i].AdistChannel5,
            &packet.blocks[i].AdistChannel6, &packet.blocks[i].AdistChannel7,  &packet.blocks[i].AdistChannel8,
            &packet.blocks[i].AdistChannel9, &packet.blocks[i].AdistChannel10, &packet.blocks[i].AdistChannel11,
            &packet.blocks[i].AdistChannel12,&packet.blocks[i].AdistChannel13, &packet.blocks[i].AdistChannel14,
            &packet.blocks[i].AdistChannel15,
            &packet.blocks[i].BdistChannel0, &packet.blocks[i].BdistChannel1,  &packet.blocks[i].BdistChannel2,
            &packet.blocks[i].BdistChannel3, &packet.blocks[i].BdistChannel4,  &packet.blocks[i].BdistChannel5,
            &packet.blocks[i].BdistChannel6, &packet.blocks[i].BdistChannel7,  &packet.blocks[i].BdistChannel8,
            &packet.blocks[i].BdistChannel9, &packet.blocks[i].BdistChannel10, &packet.blocks[i].BdistChannel11,
            &packet.blocks[i].BdistChannel12,&packet.blocks[i].BdistChannel13, &packet.blocks[i].BdistChannel14,
            &packet.blocks[i].BdistChannel15
        };

        uint8_t* reflectivity[] = {
            &packet.blocks[i].Areflectchannel0, &packet.blocks[i].Areflectchannel1,  &packet.blocks[i].Areflectchannel2,
            &packet.blocks[i].Areflectchannel3, &packet.blocks[i].Areflectchannel4,  &packet.blocks[i].Areflectchannel5,
            &packet.blocks[i].Areflectchannel6, &packet.blocks[i].Areflectchannel7,  &packet.blocks[i].Areflectchannel8,
            &packet.blocks[i].Areflectchannel9, &packet.blocks[i].Areflectchannel10, &packet.blocks[i].Areflectchannel11,
            &packet.blocks[i].Areflectchannel12,&packet.blocks[i].Areflectchannel13, &packet.blocks[i].Areflectchannel14,
            &packet.blocks[i].Areflectchannel15,
            &packet.blocks[i].Breflectchannel0, &packet.blocks[i].Breflectchannel1,  &packet.blocks[i].Breflectchannel2,
            &packet.blocks[i].Breflectchannel3, &packet.blocks[i].Breflectchannel4,  &packet.blocks[i].Breflectchannel5,
            &packet.blocks[i].Breflectchannel6, &packet.blocks[i].Breflectchannel7,  &packet.blocks[i].Breflectchannel8,
            &packet.blocks[i].Breflectchannel9, &packet.blocks[i].Breflectchannel10, &packet.blocks[i].Breflectchannel11,
            &packet.blocks[i].Breflectchannel12,&packet.blocks[i].Breflectchannel13, &packet.blocks[i].Breflectchannel14,
            &packet.blocks[i].Breflectchannel15
        };


        for(int j = 0 ; j<32 ; j++){
            Point point;
            point.x = static_cast<float>(*distChannels[j]) * .002f * cosf(verticalAngle[i]) * sinf((static_cast<float>(packet.blocks[i].azimuth)/100)* 0.01745329252f);
            point.y = static_cast<float>(*distChannels[j]) * .002f * cosf(verticalAngle[i]) * cosf((static_cast<float>(packet.blocks[i].azimuth)/100)* 0.01745329252f);
            point.z = static_cast<float>(*distChannels[j]) * .002f * sinf(verticalAngle[i]);
            point.reflectivity = *reflectivity[j];
            if( *reflectivity[j] >= threasholdLower && *reflectivity[j] <= threasholdUpper && static_cast<float>(*distChannels[j]) < maxDistance){
                setOfPoints[count%pointSize] = point;
                count++;
            }
        }
        
    }

}


void getPoints(std::array<Point,pointSize> &returnPoints){
    std::lock_guard<std::mutex> lock(readAndWrite);
    returnPoints = setOfPoints;

}




void UDP() { 
    
    const int PORT = 2368;
    const int BUFFER_SIZE = 1206;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "Error creating socket.\n";
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cerr << "Error binding socket.\n";
        close(sock);
    }

    std::cout << "Listening for UDP packets on port " << PORT << "...\n";

    char buffer[BUFFER_SIZE];
    sockaddr_in clientAddr{};
    socklen_t clientAddrLen = sizeof(clientAddr);

    std::array<float , 16> verticalAngles = {-15,1,-13,-3,-11,5,-9,7,-7,9,-5,11,-3,13,-1,15}; //degrees

    for(int i = 0 ; i < 16 ; i++){
        verticalAngles[i] = verticalAngles[i] * 0.01745329252f; // degrees to radians
    }

    while (true) {
        memset(buffer, 0, sizeof(buffer)); // Zero-initialize the buffer

        ssize_t bytesReceived = recvfrom(sock, buffer, BUFFER_SIZE, 0,
                                         reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);

        if (bytesReceived < 0) {
            std::cerr << "Error receiving data.\n";
            break;
        }

       //std::cout << "Received " << bytesReceived << " bytes as hex:\n";
        if(bytesReceived == BUFFER_SIZE){
            for(int i = 0 ; i < 12 ; i++){
                memcpy(&packet.blocks[i] , buffer + i * 100 , 100);
            }
            memcpy(&packet.timeStamp , buffer + 1200, 4);
            readPacket(packet ,verticalAngles);
        }else{
            std::cout<<"Packet Failed expected size " << BUFFER_SIZE << "bytes : recieved "<< bytesReceived << " bytes";
        }
    }
    close(sock);
}
