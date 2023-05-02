#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>

//#include "Particula.h"
using namespace std;



void  escribir_posiciones(string path, string nombre_salida, vector<Particula> particulas,float tiempo_acumulado){
  nombre_salida = path +  nombre_salida;//ruta + ...
  ofstream salida (nombre_salida);
  int N = particulas.size();
  for (int i=2; i<N; i++){
    salida << particulas[i].get_id() << " ";
    salida << particulas[i].get_pos_x() << " ";
    salida << particulas[i].get_pos_y() << " ";
    salida << particulas[i].get_vel_x() << " ";
    salida << particulas[i].get_vel_y() << " ";
    salida << particulas[i].get_radio() << " ";
    salida << "\n";

  }
  salida.close();
}


void anotar_t_salida(ofstream &t_salidas, double t){
  t_salidas << t <<endl;
}
