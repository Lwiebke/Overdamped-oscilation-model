#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <time.h>


#include "Particula.h"
#include "Archivo.h"
#include "set_particulas.h"
#include "Cell_index.h"

#include "Fuerzas.h"
#include "mover.h"
//#include "vecinos.h"



using namespace std;

int main(int argc, char *argv[]){

  vector<Particula> particulas;

  //Estos se pueden modificar manualmente

    double L = 80;
    double W = 20;
    double D = 3;

    double max_time = 200;
    double dt = 0.005;
    double dt_escritura = 0.05;

    int N_deseado = 200;
    double v_deseada = 1;

    double radio_base = 1;
    double amplitud_radio = 0.15;
    double frecuencia = 0;

    //double d_eq = 15;
    double d_cut_prop = 0.17;//tambien como papper (usa 6/5 de r_eq)
    //double f_rep = 30;//como papper
    double f_rep = 50;//como papper pero * 3.3 (por la velocidad velocidad deseada)
    //double f_adh = 2.5;//como papper pero * 3.3 (por la velocidad velocidad deseada)
    double f_adh = 10;//como papper pero * 3.3 (por la velocidad velocidad deseada)
    double f_wall = 50;//como papper



    int seed = 44;
    string path = "./Comparisons/Stop/";


  if (argc == 18){

    L = atof(argv[1]);
    W = atof(argv[2]);
    D = atof(argv[3]);

    N_deseado = atoi(argv[4]);
    v_deseada = atof(argv[5]);

    max_time = atof(argv[6]);
    dt = atof(argv[7]);
    dt_escritura = atof(argv[8]);

    radio_base = atof(argv[9]);
    amplitud_radio = atof(argv[10]);
    frecuencia = atof(argv[11]);


    //d_eq = atof(argv[12]);
    d_cut_prop = atof(argv[12]);
    f_rep = atof(argv[13]);
    f_adh = atof(argv[14]);
    f_wall = atof(argv[15]);


    seed = atoi(argv[16]);
    path = argv[17];

  }


  srand(seed);

  string nombre_salida = "Room_";
  int num_escrito = 0;
  ofstream t_salidas(path+"Tiempos_salida.txt", ofstream::app);

  //double max_radio = 0.2;

  int N;

  particulas = ubicar_particulas(W, L, D,N_deseado, radio_base, amplitud_radio,frecuencia,v_deseada);//tengo las particulas en sus posiciones iniciales
  N = particulas.size();

  vector <bool> ya_salidas;
  ya_salidas.resize(N);
  for (int p=0; p < N; p++){
    ya_salidas[p] = 0;
  }

  cout << N <<"\n";
  vector<vector<int> > vecinos;
  escribir_posiciones(path,nombre_salida+"_0.txt",particulas,0);
  vector<double> fuerzas;


  double t = 0;
  int cont_escritura = 0;
  int max_pasos = int(max_time/dt);
  //cout << int(dt_escritura/dt)<<endl;
  string tiempo_formated;
  clock_t timer;
  timer = clock();
  for (int i = 0; i < max_pasos; i++){ //for de pasos temporales
    //cout << i<<endl;
    vecinos = calcular_vecinos(particulas,W,L,d_cut_prop);
    //cout << vecinos[1][0] <<endl;
    mover_particulas(particulas,vecinos,dt, L, W, D,d_cut_prop,f_rep,f_adh,f_wall,t);
    //break;
    t += dt;
    cont_escritura++;



//Anotar tiempo de las particulas que salieron:
  for (int p = 0; p < particulas.size();p++){
    if (particulas[p].get_pos_y() + particulas[p].get_radio() < 0 && !ya_salidas[p]){
      anotar_t_salida(t_salidas,t);
      ya_salidas[p] = 1;
    }
  }
//Reingresar partículas luego de que ya salieron
    for (int p = 0; p < particulas.size();p++){
      if (particulas[p].get_pos_y() + particulas[p].get_radio() < -L/10){
        reubicar_particula(particulas,p,W,L);
        ya_salidas[p]=0;
        //particulas[p].set_target_y(0);

      }
    }

    if (cont_escritura == int(dt_escritura/dt) ){
      num_escrito++;
      cout<< nombre_salida + "_" + to_string(num_escrito) <<".txt" << " escrito." <<endl;
      escribir_posiciones(path,nombre_salida +"_"+ to_string(num_escrito) +".txt",particulas,t);
      cont_escritura = 0;

    }
  }
  t_salidas.close();
  cout << "Fin" << endl;

  timer = clock() - timer;
  printf ("%f seconds).\n",((float)timer)/CLOCKS_PER_SEC);
  return 0;
}
