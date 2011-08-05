#include "sifalog.h"

SiFaLog::SiFaLog(unsigned int p)
{
        port = p;
 
        struct sockaddr_in server;	
        

        if ((serversock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {             
                printf("Error with socket() \n");
                exit(ERROR_SOCKET);
        }    	

        /* set up the PORT */
        memset(&server, 0, sizeof(server));                                     
        server.sin_family = AF_INET;                                            
        server.sin_port = htons(port);
        server.sin_addr.s_addr = INADDR_ANY;                                    
                       

        if (bind(serversock, (struct sockaddr *)&server, sizeof(server))== -1) {     
                printf("Error with bind() \n");
                exit(ERROR_BIND);
        }     
        

        /* wait for connection */                                               
        if (listen(serversock, 10) == -1) {                                     
                printf("Error with listen() \n");
                exit(ERROR_LISTEN);
        }     
        
}

int SiFaLog::start()
{
        printf("Waiting for connection on port %d\n", port);

        /* accept the client */                                                   
        if ((clientsock = accept(serversock, NULL, NULL)) == -1) {
                printf("Error with accept() \n");
                exit(ERROR_ACCEPT);
                return ERROR_ACCEPT;
        }

        return 0;
}

void SiFaLog::img(IplImage *img)
{
        vector<uchar> buff;

        vector<int> param = vector<int>(2);
        param[0] = CV_IMWRITE_JPEG_QUALITY;
        param[1] = 95;

        imencode(".jpg", img, buff, param);		

        char len[10];
        sprintf(len, "%.8d", buff.size());
        
        /* send length */
        send(clientsock, len, strlen(len), 0);
        
        /* send the image */
        send(clientsock, &buff[0], buff.size(), 0);
        buff.clear();

}

int SiFaLog::restart()
{
        printf("Restarting connection\n");
        close(clientsock);

        /* accept the client */                                                   
        if ((clientsock = accept(serversock, NULL, NULL)) == -1) {
                printf("Error with accept() \n");
                exit(ERROR_ACCEPT);
                return ERROR_ACCEPT;
        }

        return 0;
}

string SiFaLog::recieve()
{
        char data[128];
        int bytes = recv(clientsock, data, 128, 0);
	
        if (bytes == 0) {
                restart();
        }
        string out = data;

        return out;
}

