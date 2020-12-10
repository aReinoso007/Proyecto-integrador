#include "Operaciones.hpp"

Mat frame, actual, anterior, resta, frame2, gaus, mediana, erosion, apertura, cierre, blackhat, dilatar, camara, frame3, actual2, anterior2, resta2;
int mascaraMediana = 0;
int mascaraGausiana = 0;
int kernel=3;
int pixel= 0;
int pixel2= 0;
Operaciones operaciones;

void eventoTrack(int v, void *p){
    cout << "Valor: " << v << endl;
}

Mat detectarMovimiento(Mat frame){
    Mat resultado;
    resultado = frame.clone();
    cvtColor(frame, frame, COLOR_BGR2GRAY);
    actual = frame.clone();
    if(anterior.rows==0 || anterior.cols==0){
        anterior = frame.clone();
    }
    absdiff(actual, anterior, resta);
    anterior = actual.clone();
    threshold(resta, resta, 33, 255, THRESH_BINARY);
    
    for(int i=0;i<resultado.rows;i++){
        for(int j=0;j<resultado.cols;j++){
            pixel = (int) resta.at<uchar>(i,j);
            if (pixel != 0){
            break;
            }
            resultado.at<Vec3b>(i,j) = resta.at<Vec3b>(); 
        }
        for(int j=resta.cols-1;j>=0;j--){
            pixel = (int) resta.at<uchar>(i,j);
            if (pixel != 0)
                break;
            resultado.at<Vec3b>(i,j) = resta.at<Vec3b>(); 
        }
    }

    return resultado;
}

Mat detectarMovimiento2(Mat frame){
    Mat resultado;
    resultado = frame.clone();
    cvtColor(frame, frame, COLOR_BGR2GRAY);
    actual2 = frame.clone();
    if(anterior2.rows==0 || anterior2.cols==0){
        anterior2 = frame.clone();
    }
    absdiff(actual2, anterior2, resta2);
    anterior2 = actual2.clone();
    threshold(resta2, resta2, 33, 255, THRESH_BINARY);
    
    for(int i=0;i<resultado.rows;i++){
        for(int j=0;j<resultado.cols;j++){
            pixel2 = (int) resta2.at<uchar>(i,j);
            if (pixel2 != 0){
            break;
            }
            resultado.at<Vec3b>(i,j) = resta2.at<Vec3b>(); 
        }
        for(int j=resta2.cols-1;j>=0;j--){
            pixel2 = (int) resta2.at<uchar>(i,j);
            if (pixel2 != 0)
                break;
            resultado.at<Vec3b>(i,j) = resta2.at<Vec3b>(); 
        }
    }

    return resultado;
}

int main(int argc, char *argv[]){

    VideoCapture video("resources/vid2.webm");
    VideoCapture video2(0);

    namedWindow("Video", WINDOW_AUTOSIZE);
    while(video.isOpened() & video2.isOpened()){
      
        createTrackbar("Mascara Filtro Mediana", "Video", &mascaraMediana, 11, eventoTrack, NULL);
        createTrackbar("Filtro Gausiano", "Video", &mascaraGausiana, 11, eventoTrack, NULL);
        createTrackbar("Kernel", "Video", &kernel, 39, eventoTrack, NULL);

        while(true){
            video >> frame;
            video >> erosion;
            video >> blackhat;
            video >> dilatar;
            video >> gaus;
            video >> mediana;
            video >> apertura;
            video >> cierre;    
            video2 >> frame3;
            video2 >> camara;

            if(frame.rows==0 || frame.cols==0)
                break;
            if(frame3.rows==0 || frame3.cols==0)
                break;
            
            resize(frame, frame, Size(), 0.3,0.3);

            resize(frame3, frame3, Size(frame.cols, frame.rows));
            resize(camara, camara, Size(frame3.cols, frame3.rows));
            resize(gaus, gaus, Size(), 0.3,0.3);
            resize(mediana, mediana, Size(), 0.3,0.3);
            resize(erosion, erosion, Size(), 0.3,0.3);
            resize(dilatar, dilatar, Size(), 0.3,0.3);
            resize(blackhat, blackhat, Size(), 0.3,0.3);
            resize(apertura, apertura, Size(), 0.3,0.3);
            resize(cierre, cierre, Size(), 0.3,0.3);

            frame2 = frame;
            camara = frame3;

            gaus = operaciones.filtroGassuaian(frame, gaus, mascaraGausiana);
            mediana = operaciones.filtroMediana(frame, mediana, mascaraMediana);
            frame2 = detectarMovimiento(frame);
            
            erosion = operaciones.aplicarDilatar(frame, erosion, kernel);
            dilatar = operaciones.aplicarDilatar(frame, dilatar, kernel);
            blackhat = operaciones.aplicarBlackHat(frame, blackhat, kernel);
            apertura = operaciones.aplicarApertura(frame, apertura, kernel);
            cierre = operaciones.aplicarCierre(frame, cierre, kernel);

            camara = detectarMovimiento2(frame3);

            imshow("Video", frame);
            imshow("Gausiano", gaus);
            imshow("Mediana", mediana);
            imshow("Dilatar", dilatar);
            imshow("Erosion", erosion);
            imshow("Blackhat", blackhat);
            imshow("Apertura", apertura);
            imshow("Cierre", cierre);
            imshow("Movimiento", frame2);
            imshow("Webcam", camara);

            
            if(waitKey(1)==27)
                break;
        }      
    }
    video.release();
    destroyAllWindows();

    return 0;
}