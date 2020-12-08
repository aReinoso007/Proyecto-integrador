#include "Operaciones.hpp"

Operaciones::Operaciones(){

}

cv::Mat Operaciones::detectarMov(cv::Mat frame){
    Mat resultado, actual, anterior, resta;
    resultado = frame.clone();
    cvtColor(frame, frame, COLOR_BGR2GRAY);
    actual = frame.clone();
    if(anterior.rows==0 || anterior.cols==0){
        anterior = frame.clone();
    }
    absdiff(actual, anterior, resta);
    anterior = actual.clone();
    threshold(resta, resta, 33, 255, THRESH_BINARY);
    int pixel=0;
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

cv::Mat Operaciones::filtroGassuaian(cv::Mat src, cv::Mat dest, int mascara){
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

cv::Mat Operaciones::filtroMediana(cv::Mat src, cv::Mat dest, int mascara){
    Mat resultado;
    if(mascara%2 == 0){
        medianBlur(src, dest, mascara+1);
        cout << "Valor debe ser impar, Mascara Mediana: " <<mascara << "\n";
        resultado = dest;
    }else{
        medianBlur(src, dest, mascara);
        resultado = dest;
    };
    return resultado = dest;
}

cv::Mat Operaciones::aplicarErosion(cv::Mat frame, cv::Mat dest, cv::Mat tam, int k){
    Mat resultado;
    if(k%2 ==0){
        tam = getStructuringElement(MORPH_CROSS, Size(k+1, k+1));
        erode(frame, dest, tam);
        resultado = dest;
    }else{
        erode(frame, dest, tam);
        resultado = dest;
    };
    return resultado;
}

cv::Mat Operaciones::aplicarBlackHat(cv::Mat frame, cv::Mat dest, cv::Mat tam, int k){
    Mat resultado;
    if(k%2 ==0){
        tam = getStructuringElement(MORPH_CROSS, Size(k+1, k+1));
        morphologyEx(frame, dest, MORPH_BLACKHAT, tam);
        resultado = dest;
    }else{
        morphologyEx(frame, dest, MORPH_BLACKHAT, tam);
        resultado = dest;
    };
    return resultado;
}