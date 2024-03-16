#include <iostream>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdint>

// Create a structure for the packet, see specification at labitat wiki
struct px_data {
    uint8_t fmt;
    uint8_t version;
    uint16_t x;
    uint16_t y;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

int main(int argc, char* argv[]) {
    int sockfd;
    struct sockaddr_in serverAddr;

    // Open a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket error");
        exit(EXIT_FAILURE);
    }

    // Set server information
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("100.65.0.2");
    serverAddr.sin_port = htons(5005);

    // Create and fill the header and data structures
    px_data pp;
    pp.fmt = 0;     // Set the format
    pp.version = 1; // Set the version

    std.cout << "press Ctrl-C to stop" << "\n";
    // Create a 10 x 10 grid of red
    while (true) {
        int c = 0;
        int i = 1;
        while (i < 10) {
            int k = 1;
            while (k < 10) {
                // Set x,y and red, green, blue of the packet
                pp.x = i;
                pp.y = k;
                pp.r = 255;
                pp.g = 0;
                pp.b = 0;
                std::cout << "packet: " << c << " x: " << i << " y: " << k << "\n";
                k++;
                c++;
                // Send each packet
                if (sendto(sockfd, &pp, sizeof(pp), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
                    perror("Send error");
                }
            }
            i++;
        }
    }
    
    close(sockfd);
    
    return 0;
}
