#include "Header.hpp"


void eventoTrack(int v, void *p){
    cout << "Valor: " << v << endl;
}


int main(int argc, char *argv[]){

    /* 
    Video en .mp4
    tamaños de mascaras (kernels)
    dilatacion
    erosion
    apertura
    cierre
    blackhat
     o top hat
    
    Deterctor de movimiento -> eliminar zona sin movimiento, no usar background subtractor
    */
    VideoCapture video(0);
    int mascaraMediana = 0;
    int mascaraGausiana = 0;
    Mat tamanio = getStructuringElement(MORPH_CROSS, Size(37, 37));

    namedWindow("Video", WINDOW_AUTOSIZE);
    if(video.isOpened()){
        Mat frame, actual, anterior, resta, frame2;
        Mat gaus;
        Mat mediana;
        Mat erosion, apertura, cierre, blackhat, dilatar;
        
        
        createTrackbar("Mascara Filtro Mediana", "Video", &mascaraMediana, 11, eventoTrack, NULL);
        createTrackbar("Filtro Gausiano", "Video", &mascaraGausiana, 11, eventoTrack, NULL);
        
        while(3==3){
            video >> frame;
            video >> gaus;
            video >> mediana;
            video >> erosion;
            video >> apertura;
            video >> cierre;
            video >> blackhat;
            video >> dilatar;
            video >> frame2;

            erode(frame, erosion, tamanio);
            dilate(frame, dilatar, tamanio);
            morphologyEx(frame, blackhat, MORPH_BLACKHAT, tamanio);

            /*Esta parte para el detector de movimiento */
            cvtColor(frame, frame2, COLOR_BGR2GRAY);
            /*se clona la imagen*/
            actual = frame.clone();
            if(anterior.rows ==0 || anterior.cols ==0){
                anterior = frame.clone();
            }
            resta = cv::abs(actual-anterior);
            anterior = actual.clone();
            threshold(resta, resta, 33, 255, THRESH_BINARY);
            /*
            if(mascaraMediana%2 == 0){
                medianBlur(frame, mediana, mascaraMediana+1);
                cout << "Valor debe ser impar, Mascara Mediana: " <<mascaraMediana << "\n";
            }else{
                medianBlur(frame, mediana, mascaraMediana);
            };
            
            if(mascaraGausiana%2 == 0){
                GaussianBlur(frame, gaus, Size(),mascaraGausiana+1);
                cout << "Valor debe ser impar, Mascara Gausiana: " <<mascaraGausiana << "\n";
            }else{
                GaussianBlur(frame, gaus, Size(),mascaraGausiana);
            };*/


            
            
            imshow("Video", frame);
            /*
            imshow("Gausiano", gaus);
            imshow("Mediana", mediana);
            imshow("Dilatar", dilatar);
            imshow("Erosion", erosion);
            imshow("Blackhat", blackhat);
            */
            imshow("Movimiento", resta);

            
            if(waitKey(23)==27)
                break;
        }      
    }

    destroyAllWindows();

    return 0;
}