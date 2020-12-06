

all:
	g++ Principal.cpp -I//usr/local/include/opencv4/ -L/usr/local/include/opencv4/opencv2/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_video -lopencv_videoio -o alexChevere.bin
	
run:
	./alexChevere.bin
