#include <iostream>
#include <math.h>
#include <list>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

//#include "Archivo.h"

using namespace std;




vector<vector<int> > calcular_vecinos(vector<Particula> &particulas, float W, float L, double r_cut_prop){
  double d;
    vector<vector<int> > vecinos;
    int N = particulas.size();
    vecinos.resize(N);
    for (int i=0;i<N;i++){
      for (int j=0;j<N;j++){

        if(i!=j){
          d = sqrt(powf(particulas[i].get_pos_x() - particulas[j].get_pos_x() ,2.0) + powf(particulas[i].get_pos_y() - particulas[j].get_pos_y() ,2.0));
          if (d <= (particulas[i].get_radio()*1.5+particulas[j].get_radio()*1.5 )) {
            vecinos[i].push_back(j);
            vecinos[j].push_back(i);
          }
        }
      }
    }
return vecinos;
}
