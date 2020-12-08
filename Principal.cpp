#include "Header.hpp"


void eventoTrack(int v, void *p){
    cout << "Valor: " << v << endl;
}

int main(int argc, char *argv[]){

    VideoCapture video("resources/vid2.webm");

    Mat frame, actual, anterior, resta, frame2, gaus, mediana, erosion, apertura, cierre, blackhat, dilatar;

    
    int mascaraMediana = 0;
    int mascaraGausiana = 0;
    Mat tamanio = getStructuringElement(MORPH_CROSS, Size(37, 37));

    namedWindow("Video", WINDOW_AUTOSIZE);
    if(video.isOpened()){
      
        //createTrackbar("Mascara Filtro Mediana", "Video", &mascaraMediana, 11, eventoTrack, NULL);
        //createTrackbar("Filtro Gausiano", "Video", &mascaraGausiana, 11, eventoTrack, NULL);
 
        while(true){
            video >> frame;
            //video >> gaus;
            //video >> mediana;
            //video >> erosion;
            //video >> apertura;
            //video >> cierre;
            //video >> blackhat;
            //video >> dilatar;
            
            
            if(frame.rows==0 || frame.cols==0)
                break;
            resize(frame, frame, Size(), 0.5,0.5);
            frame2 = frame;

            //erode(frame, erosion, tamanio);
            //dilate(frame, dilatar, tamanio);
            //morphologyEx(frame, blackhat, MORPH_BLACKHAT, tamanio);

            /*Esta parte para el detector de movimiento */
            


            //cvtColor(frame, frame2, COLOR_BGR2GRAY);
            cvtColor(frame, frame, COLOR_BGR2GRAY);
            
            // Método para clonar imágenes
            actual = frame.clone();
            
            if(anterior.rows==0 || anterior.cols==0){
                anterior = frame.clone();
            }
            
            absdiff(actual, anterior, resta);
            anterior = actual.clone();
            
            // Threshold propio de OpenCV
            threshold(resta, resta, 33, 255, THRESH_BINARY);

            int pixel= 0;
            for(int i=0;i<frame2.rows;i++){
                //filas
                for(int j=0;j<frame2.cols;j++){
            
                    pixel = (int) resta.at<uchar>(i,j);
                    //COmprobamos si el pixel es = 0
                    //ya que la resta de las imagenes nos da 0 y en la parte que se esta sumando mas 1
                    if (pixel != 0){
                    break;
                    }
                    frame2.at<Vec3b>(i,j) = resta.at<Vec3b>(); 
                }
                 //barrido de izquierda a derecha
                for(int j=resta.cols-1;j>=0;j--){
                    pixel = (int) resta.at<uchar>(i,j);
                    if (pixel != 0)
                        break;
                    frame2.at<Vec3b>(i,j) = resta.at<Vec3b>(); 
                }
            }

            
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
            imshow("Movimiento", frame2);

            
            if(waitKey(1)==27)
                break;
        }      
    }

    destroyAllWindows();

    return 0;
}