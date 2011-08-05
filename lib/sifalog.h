#ifndef _SIFALOG_H
#define _SIFALOG_H

#include <cv.h>   
#include <highgui.h>                                       
#include <cxcore.h>

#include <netinet/in.h>                                                         
#include <sys/socket.h>                                                         
#include <arpa/inet.h>  


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>

using namespace std;
using namespace cv;

#define ERROR_SOCKET 1
#define ERROR_BIND 2
#define ERROR_LISTEN 4
#define ERROR_ACCEPT 8

class SiFaLog {
        int serversock;
        int clientsock;
        unsigned int port;

public:
        SiFaLog(unsigned int p);
        int start();
        void img(IplImage *img);
        int restart();
        string recieve();
};




#endif

