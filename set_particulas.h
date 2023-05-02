//Sub rutina diseñada para ubicar N particulas con radios < 0 en espacio cuadrado de lado L sin superposición con
//otras partículas ni con las paredes.

#include <vector>
#include <cmath>
#include <ctime>
#include <string>
#include <fstream>

//#include "Particula.h"

using namespace std;


vector <Particula> ubicar_particulas(double W, double L, double D,int N_deseado,float radio_base, float amplitud, float periodo,double v_deseada){
  //srand(time(NULL));
  int tolerancia_col = 10000;

  double posx, posy;
  double distancia;
  int i = 2;
  int j;
  vector <Particula> particulas;

  Particula izq;
  izq.set_id(0);
  izq.set_radio(0);
  izq.set_vel_x(0);
  izq.set_vel_y(0);
  izq.set_pos_y(0);
  izq.set_pos_x((W/2)-(D/2));

  Particula der;
  der.set_id(1);
  der.set_radio(0);
  der.set_vel_x(0);
  der.set_vel_y(0);
  der.set_pos_y(0);
  der.set_pos_x((W/2)+(D/2));


  particulas.push_back(izq);
  particulas.push_back(der);



  Particula aux;
  float fase;

  aux.set_radio_base(radio_base);

  aux.set_amplitud_radio(amplitud);
  aux.set_periodo(periodo);
  aux.set_v_deseada(v_deseada);
  aux.set_target_y(-L);
  //aux.set_target_x( ((W/2)-(D/2)) + (double)(rand()/(RAND_MAX/D)) );


  int colisiones = 0;




  double nuevo_radio;
  while (colisiones < tolerancia_col && i-2 < N_deseado){

    //generar_radio
    fase = (double)(rand())/(RAND_MAX/(2*M_PI) );
    aux.set_fase(fase);
    //cout<<"La fase es: "<<fase<<endl;
    nuevo_radio = aux.actualizar_radio(0);
    //radios.push_back(nuevo_radio);


    //para evitar colisiones con las paredes:
    posx = nuevo_radio + (double)(rand()) / ((double)(RAND_MAX/((W - 2*nuevo_radio))  ));
    posy = nuevo_radio + (double)(rand()) / ((double)(RAND_MAX/((L - 2*nuevo_radio))  ));

    for (j=0; j<i; j++){//ver si no se superpone con otra particula ya puesta.
      distancia = sqrt( pow((particulas[j].get_pos_x() - posx),2) + pow(particulas[j].get_pos_y() - posy,2) );
      if (distancia < (nuevo_radio+particulas[j].get_radio()) ){//hay superposicion, buscar nueva posicion
        colisiones++;

        break;

      }
    }
    if (j == i){ //si recorrí todas las particulas previamente ubicadas sin colisiones, paso a la siguente
      aux.set_id(i);
      aux.set_pos_x(posx);
      aux.set_pos_y(posy);
      aux.set_vel_x(0);
      aux.set_vel_y(0);
      aux.set_radio(nuevo_radio);
      aux.set_target_x( posx );
      particulas.push_back(aux);
      i++;

      }

  }
  return particulas;

}


void reubicar_particula(vector<Particula> &particulas, int id, double W, double L){

  double nuevo_radio = particulas[id].get_radio();
  double posx, posy, distancia;
  bool done = 0;
//encontrar nueva posicion
  while (!done) {


    posx = nuevo_radio + (double)(rand()) / ((double)(RAND_MAX/(W - 2*nuevo_radio)  ));
    posy = L*0.7 + (double)(rand()) / ((double)(RAND_MAX/((L - nuevo_radio)-L*0.7)  ));
    int j;
    for (j=0; j<particulas.size(); j++){//ver si no se superpone con otra particula ya puesta.
      distancia = sqrt( pow((particulas[j].get_pos_x() - posx),2) + pow(particulas[j].get_pos_y() - posy,2) );
      if (distancia < (nuevo_radio+particulas[j].get_radio()) ){//hay superposicion, buscar nueva posicion
        break;
      }
    }
    if (j == particulas.size()){ //si recorrí todas las particulas previamente ubicadas sin colisiones, paso a la siguente

      particulas[id].set_pos_x(posx);
      particulas[id].set_pos_y(posy);
      particulas[id].set_vel_x(0);
      particulas[id].set_vel_y(0);
      particulas[id].set_target_x( posx );
      done = 1;
    }
  }
}

/*
vector<Particula>  cargar_particulas(archivo_carga, &t, &i,dt){
  ifstream ultima_pos;
  string aux;
  ultima_pos.open(archivo_carga);
  ultima_pos >> aux;
  t = stod(aux)
  while(ultima_pos >> aux){

  }

}
*/
