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

