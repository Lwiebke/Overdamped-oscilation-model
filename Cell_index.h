#include <iostream>
#include <math.h>
#include <list>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>



void asignar_particulas_celdas(vector<vector<list<int> > > &grilla, vector<Particula> &particulas,float altura, float ancho){

  int N = particulas.size();
  int M1 = grilla.size();
  int M2 = grilla[0].size();
  float L = altura;
  float W = ancho;

  float cell_len =  float(L)/M1;

  for (int id = 0; id < N; id++){//para cada particula
    int pertenencia_celda_x = M2-1;//si recorre todo el ciclo y nunca entra a los if, es porque se encuentra en la última celda posible, A.K.A. "M-1".
    int pertenencia_celda_y = M1-1;
    for (int i = 0; i < M1; i++){//recorrer la grilla para encontrar su posicion
      if ( (particulas[id].get_pos_y() < cell_len*i) ){
        pertenencia_celda_y = i-1;
        if (pertenencia_celda_y < 0){
          pertenencia_celda_y = 0;
        }
        break;
      }
    }
    for (int i = 0; i < M2; i++){//recorrer la grilla para encontrar su posicion
      if ( (particulas[id].get_pos_x() < cell_len*i)){
        pertenencia_celda_x = i-1;
        if (pertenencia_celda_x < 0){
          pertenencia_celda_x = 0;
        }
        break;

      }
    }

    grilla[pertenencia_celda_y][pertenencia_celda_x].push_back(id);//y añadir a la celda correspondiente el id de la particula
  }
}

bool son_vecinas(Particula *A, Particula *B,double r_cut_prop){
  bool vecindad = false;
  float distancia;

  distancia = sqrt(powf(A->get_pos_x() - B->get_pos_x() ,2.0) + powf(A->get_pos_y() - B->get_pos_y() ,2.0));
  //distancia = distancia - (A->get_radio() + B->get_radio());
  if (distancia <= (A->get_radio()*(1+r_cut_prop)+B->get_radio()*(1+r_cut_prop) ))
    vecindad = true;

  return vecindad;
}


vector<vector<int> > calcular_vecinos(vector<Particula> &particulas, float W, float L, double r_cut_prop){

  //inicializacíon
      float minima_distancia = 0;
      vector<vector<int> > vecinos;
      int M, M1, M2;
      int N = particulas.size();
      vector< vector< list<int> > > grilla;
      float r_max = particulas[2].get_radio_base() + particulas[2].get_amplitud();


      vecinos.resize(N);

      float cell_len;

      if (W==L){
        M = floor(L/(2*r_max));
        grilla.resize(M);
        for (int i=0; i<M; i++){
          grilla[i].resize(M);
        }
      }
      else{
          if(W<L){
            M2 = floor(W/(2*r_max));
            cell_len = float(W)/M2;
            M1 = ceil(L/cell_len);

          }
          else{
            M1 = floor(L/(2*r_max));
            cell_len = float(L)/M1;
            M2 = ceil(W/cell_len);
          }

        grilla.resize(M1);
        for (int i=0; i<M1; i++){
          grilla[i].resize(M2);
        }
      }
      asignar_particulas_celdas(grilla, particulas, L, W);

      //recorro todas las celdas...
      int id1, id2;
      float distancia;
      for (int i=0;i<M1;i++){
        for (int j=0; j<M2;j++){

  //y para cada una cada par de particulas (intra_celda).
          for (auto primera = grilla[i][j].begin(); primera!=grilla[i][j].end(); ++primera){
            id1 = *primera;

            for (auto segunda =  grilla[i][j].begin(); segunda!=grilla[i][j].end(); ++segunda){
              if (id1 < *segunda){ //misma celda
                id2 = *segunda;
                if(son_vecinas(&particulas[id1], &particulas[id2],r_cut_prop)){

                  vecinos[id1].push_back(id2);
                  vecinos[id2].push_back(id1);
                }
              }
            }

            if(j+1 < M2 && i+1 < M1){//si estoy lejos de los bordes, me muevo adelane, arriba y diagonal adelante-arriba
              for (auto segunda =  grilla[i+1][j+1].begin(); segunda!=grilla[i+1][j+1].end(); ++segunda){ //diagonal arriba-derecha
                id2 = *segunda;
                if(son_vecinas(&particulas[id1], &particulas[id2],r_cut_prop)){
                  vecinos[id1].push_back(id2);
                  vecinos[id2].push_back(id1);
                }
              }
            }
            if  (i+1 < M1){ //arriba
              for (auto segunda =  grilla[i+1][j].begin(); segunda!=grilla[i+1][j].end(); ++segunda){
                id2 = *segunda;
                if(son_vecinas(&particulas[id1], &particulas[id2],r_cut_prop) ){
                  vecinos[id1].push_back(id2);
                  vecinos[id2].push_back(id1);
                }
              }
            }

            if  (j+1 < M2){ //derecha
              for (auto segunda =  grilla[i][j+1].begin(); segunda!=grilla[i][j+1].end(); ++segunda){//arriba
                id2 = *segunda;
                if (son_vecinas(&particulas[id1], &particulas[id2],r_cut_prop)){
                  vecinos[id1].push_back(id2);
                  vecinos[id2].push_back(id1);
                }
              }
            }

            //abajo a la derecha
            if (i > 0 && (j+1) < M2){//normal
              for (auto segunda =  grilla[i-1][j+1].begin(); segunda!=grilla[i-1][j+1].end(); ++segunda){
                id2 = *segunda;
                if (son_vecinas(&particulas[id1], &particulas[id2],r_cut_prop)){
                  vecinos[id1].push_back(id2);
                  vecinos[id2].push_back(id1);
                }
              }
            }

      }
    }
  }

  for(int i=0; i<vecinos.size();i++){
    sort(vecinos[i].begin(),vecinos[i].end());
    vecinos[i].erase(unique(vecinos[i].begin(),vecinos[i].end()),vecinos[i].end());
  }
  return vecinos;

  }
