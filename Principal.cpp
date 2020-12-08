#include "Header.hpp"

Mat frame, actual, anterior, resta, frame2, gaus, mediana, erosion, apertura, cierre, blackhat, dilatar;
int mascaraMediana = 0;
int mascaraGausiana = 0;
int kernel=3;

void eventoTrack(int v, void *p){
    cout << "Valor: " << v << endl;
}
void Erosionar(){

}

void Dilatar(){

}

Mat aplicarMediana(Mat src, Mat dest, int mascara){
    if(mascara%2 == 0){
        medianBlur(src, dest, mascara+1);
        cout << "Valor debe ser impar, Mascara Mediana: " <<mascara << "\n";
        return dest;
    }else{
        medianBlur(src, dest, mascara);
        return dest;
    };
    return dest;
}

Mat aplicarGaussiana(Mat src, Mat dest, int mascara){
    Mat resultado;
    if(mascara%2 == 0){
        GaussianBlur(src, dest, Size(),mascara+1);
        cout << "Valor debe ser impar, Mascara Gausiana: " <<mascara << "\n";
        resultado = dest;
    }else{
        GaussianBlur(src, dest, Size(),mascara);
        resultado =  dest;
    };

    return dest;
}

int main(int argc, char *argv[]){

    VideoCapture video("resources/vid2.webm");
    //VideoCapture video(0);

    namedWindow("Video", WINDOW_AUTOSIZE);
    if(video.isOpened()){
      
        createTrackbar("Mascara Filtro Mediana", "Video", &mascaraMediana, 11, eventoTrack, NULL);
        createTrackbar("Filtro Gausiano", "Video", &mascaraGausiana, 11, eventoTrack, NULL);
        createTrackbar("Kernel", "Video", &kernel, 39, eventoTrack, NULL);
        Mat tamanio = getStructuringElement(MORPH_CROSS, Size(kernel, kernel));
        while(true){
            video >> frame;
            video >> erosion;
            video >> blackhat;
            video >> dilatar;
            video >> gaus;
            video >> mediana;
            
            if(frame.rows==0 || frame.cols==0)
                break;
            resize(frame, frame, Size(), 0.5,0.5);
            frame2 = frame;

            gaus = aplicarGaussiana(frame, gaus, mascaraGausiana);
            mediana = aplicarMediana(frame, mediana, mascaraMediana);

            if(kernel%2 ==0){
                tamanio = getStructuringElement(MORPH_CROSS, Size(kernel+1, kernel+1));
                erode(frame, erosion, tamanio);
                dilate(frame, dilatar, tamanio);
                morphologyEx(frame, blackhat, MORPH_BLACKHAT, tamanio);
            }else
            {
                erode(frame, erosion, tamanio);
                dilate(frame, dilatar, tamanio);
                morphologyEx(frame, blackhat, MORPH_BLACKHAT, tamanio);
            };
            
            /*Esta parte para el detector de movimiento */
            cvtColor(frame, frame, COLOR_BGR2GRAY);
            actual = frame.clone();
            if(anterior.rows==0 || anterior.cols==0){
                anterior = frame.clone();
            }
            absdiff(actual, anterior, resta);
            anterior = actual.clone();
            threshold(resta, resta, 33, 255, THRESH_BINARY);

            int pixel= 0;
            for(int i=0;i<frame2.rows;i++){
                for(int j=0;j<frame2.cols;j++){
            
                    pixel = (int) resta.at<uchar>(i,j);
                    if (pixel != 0){
                    break;
                    }
                    frame2.at<Vec3b>(i,j) = resta.at<Vec3b>(); 
                }
                for(int j=resta.cols-1;j>=0;j--){
                    pixel = (int) resta.at<uchar>(i,j);
                    if (pixel != 0)
                        break;
                    frame2.at<Vec3b>(i,j) = resta.at<Vec3b>(); 
                }
            }

            //cvtColor(frame, frame, COLOR_GRAY2BGR);
            imshow("Video", frame);
            imshow("Gausiano", gaus);
            imshow("Mediana", mediana);
            imshow("Dilatar", dilatar);
            imshow("Erosion", erosion);
            imshow("Blackhat", blackhat);
            imshow("Movimiento", frame2);

            
            if(waitKey(23)==27)
                break;
        }      
    }

    destroyAllWindows();

    return 0;
}