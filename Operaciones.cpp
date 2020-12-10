#include "Operaciones.hpp"

Operaciones::Operaciones(){

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

cv::Mat Operaciones::aplicarErosion(cv::Mat frame, cv::Mat dest, int k){
    Mat resultado, tam;
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

cv::Mat Operaciones::aplicarBlackHat(cv::Mat frame, cv::Mat dest, int k){
    Mat resultado, tam;
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

cv::Mat Operaciones::aplicarDilatar(cv::Mat frame, cv::Mat dest, int k){

    Mat resultado, tam;
    if(k%2 ==0){
        tam = getStructuringElement(MORPH_CROSS, Size(k+1, k+1));
        dilate(frame, dest, tam);
        resultado = dest;
    }else{
        dilate(frame, dest, tam);
        resultado = dest;
    };
    return resultado;

}

cv::Mat Operaciones::aplicarApertura(cv::Mat frame, cv::Mat dest, int k){
    Mat resultado, tam;
    if(k%2 ==0){
        tam = getStructuringElement(MORPH_CROSS, Size(k+1, k+1));
        morphologyEx(frame, dest, MORPH_OPEN, tam);
        resultado = dest;
    }else{
        morphologyEx(frame, dest, MORPH_OPEN, tam);
        resultado = dest;
    };
    return resultado;
}

cv::Mat Operaciones::aplicarCierre(cv::Mat frame, cv::Mat dest, int k){
    Mat resultado, tam;
    if(k%2 ==0){
        tam = getStructuringElement(MORPH_CROSS, Size(k+1, k+1));
        morphologyEx(frame, dest, MORPH_CLOSE, tam);
        resultado = dest;
    }else{
        morphologyEx(frame, dest, MORPH_CLOSE, tam);
        resultado = dest;
    };
    return resultado;
}

int Operaciones::logistics(int r, int kContrast, int mContrast){
    double rd = (double) r;
    double dK = ((double)kContrast)/100.0;
    double res = 1.0/(1.0+exp(-dK*(rd-((double)mContrast))));
    res*=255.0;
    return ((int) res);
}

cv::Mat Operaciones::aplicarContrast(Mat frame, int m, int k){
    Mat resultado, gris;
    bool bandera = true;
    int pixel = 0;
    cvtColor(frame, gris, COLOR_BGR2GRAY);
    if(bandera){
        resultado = Mat::zeros(Size(frame.cols, frame.rows), CV_8UC1), Scalar(0,0,0);
        bandera = false;
    }
    for(int i=0; i<gris.rows;i++){
        for(int j=0;j<gris.cols;j++){
            pixel = gris.at<uchar>(i,j);
            resultado.at<uchar>(i,j) = logistics(pixel, k, m);
        }
    }
    return resultado;
}

cv::Mat Operaciones::aplicarThreshold(Mat frame, int mThreshold){
    Mat resultado, gris;
    bool bandera = true;
    int pixel = 0;
    cvtColor(frame, gris, COLOR_BGR2GRAY);
    if(bandera){
        resultado = Mat::zeros(Size(frame.cols, frame.rows), CV_8UC1), Scalar(0,0,0);
        bandera = false;
    }
    for(int i=0; i<gris.rows;i++){
        for(int j=0;j<gris.cols;j++){
            pixel = gris.at<uchar>(i,j);
            if(pixel > mThreshold)
                pixel = 255;
            else
                pixel =0;
            resultado.at<uchar>(i,j) = pixel;
        }
    }
    return resultado;
}

