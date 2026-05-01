package aed;

import java.util.Scanner;
import java.io.PrintStream;

class Archivos {
    float[] leerVector(Scanner entrada, int largo) {
        float[] vector = new float[largo];
        float valor;

        for(int i = 0;i < largo ;i++){
            valor = entrada.nextFloat();
            vector[i] = valor;
        }
        return vector;
    }

    float[][] leerMatriz(Scanner entrada, int filas, int columnas) {
        float[][] matriz = new float[filas][columnas];
        float valor;
        for(int i = 0; i < filas ;i++){
            for(int j = 0; j < columnas ;j++){
                valor = entrada.nextFloat();
                matriz[i][j] = valor;    
            }
        }            
        return matriz;
    }

    void imprimirPiramide(PrintStream salida, int alto){
        for(int i = 1;i <= alto;i++){ //piso
            String linea= "";
            for(int j = 1;j <= alto - i;j++){
                linea += " ";     
            }
            for(int k = 1;k<= 2*i -1;k++ ){
                linea += "*";
            }
            for(int j = 1;j <= alto - i;j++){
                linea += " ";
            }         
            salida.println(linea);
        }
        salida.close();
    }
}
