#include "lib/sifalog.h"

IplImage *img, *imgThreshed; 

int main(void)
{
        CvCapture* camera = cvCaptureFromCAM(0);

        SiFaLog log (1212);
	log.start();
        
        while (1) {
                
                string out = log.recieve();
                
                if (strcmp(out.c_str(), "img") == 0) {
                        img = cvQueryFrame(camera);
                        if (img == NULL)
                                continue;
                        
                        log.img(img);
                } else if (strcmp(out.c_str(), "q") == 0) {
                        log.restart();
                }

        }

	return 0;
}

