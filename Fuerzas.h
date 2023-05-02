#include <vector>
#include <math.h>

//#include "Particula.h"


//es para calcular las fuerzas que recibe cada Particula

using namespace std;


vector<double> calcular_fuerzas(vector <Particula> &objetos, int id, vector<int> vecinos, double r_cut_prop, double f_rep, double f_adh, double f_wall, double L, double W, double D){


  vector<double> velocidad_des;

  vector<double> velocidad_por_vec;
  velocidad_por_vec.resize(2);


  double e_x, e_y;


  int N = vecinos.size();
  //cout <<"Hay" << N <<" Vecinos de "<<id<<endl;
  int id_vec;
  double superposicion, d;

  velocidad_des = objetos[id].get_fuerza_migratoria();

  double r_eq;
  double r_cut;

  for (int i = 0; i < N; i++){
    id_vec = vecinos[i];

    r_eq = objetos[id].get_radio() + objetos[id_vec].get_radio();
    r_cut = r_eq + r_eq*r_cut_prop;

    //r_eq=r_eq*10;
    d = sqrt(pow(objetos[id_vec].get_pos_x() - objetos[id].get_pos_x(),2)+pow(objetos[id_vec].get_pos_y() - objetos[id].get_pos_y(),2));

    //superposicion = (objetos[id].get_radio() + objetos[id_vec].get_radio()) - d;

    e_x = (objetos[id_vec].get_pos_x() - objetos[id].get_pos_x())/d;
    e_y = (objetos[id_vec].get_pos_y() - objetos[id].get_pos_y())/d;
    double m;
    double b;
    // -b/m es el punto en que y = 0 de la recta

    if (d <= r_cut){//hay algun efecto

      if (d > r_eq){//atraccion

        //necesito evitar la atraccion a través de paredes
        if (objetos[id_vec].get_pos_y() * objetos[id].get_pos_y() > 0) { //Si ambos estan arriba o abajo, hay atraccion
          velocidad_por_vec[0] = e_x * (f_adh*( (d-r_eq) / (r_cut-r_eq)));
          velocidad_por_vec[1] = e_y * (f_adh*( (d-r_eq) / (r_cut-r_eq)));
        }
        else {
          // Si ambos en x están sobre la abertura, tambien hay interacion
          if (objetos[id_vec].get_pos_x() > (W/2)-(D/2) && objetos[id_vec].get_pos_x() < (W/2)+(D/2) && objetos[id].get_pos_x() > (W/2)-(D/2) && objetos[id].get_pos_x() < (W/2)+(D/2) ){
            velocidad_por_vec[0] = e_x * (f_adh*( (d-r_eq) / (r_cut-r_eq)));
            velocidad_por_vec[1] = e_y * (f_adh*( (d-r_eq) / (r_cut-r_eq)));
          }
          else{
            if (e_y!=0 && e_x!=0){
              m = e_y/e_x;
              b = objetos[id].get_pos_y() - m*objetos[id].get_pos_x();
              if( (-b/m) > (W/2)-(D/2) && (-b/m) < (W/2)+(D/2)){
                velocidad_por_vec[0] = e_x * (f_adh*( (d-r_eq) / (r_cut-r_eq)));
                velocidad_por_vec[1] = e_y * (f_adh*( (d-r_eq) / (r_cut-r_eq)));
              }
              else{
                if (objetos[id].get_id()>1 && objetos[id_vec].get_id()>1){
                  cout<<"Fuerza de atraccion ignorada "<<objetos[id].get_id()<< " y su vecino: " << objetos[id_vec].get_id() <<endl;
                  exit(2) ;
                }

              }
            }
          }
        }
      }//fin atraccion


      else{//repulsion
        velocidad_por_vec[0] = e_x * f_rep*((d-r_eq)/(r_eq));
        velocidad_por_vec[1] = e_y * f_rep*((d-r_eq)/(r_eq));
      }
    }

    velocidad_des[0] += velocidad_por_vec[0];
    velocidad_des[1] += velocidad_por_vec[1];

  }

// TODO ESTO TOCA ARREGLARLO, YA NO TENEMOS FUERZAS ASÍ QUE HAY QUE HACERLO CON VELOCIDADLES
  //base
  double radio = objetos[id].get_radio();

  r_cut = radio + radio*r_cut_prop;

  if ( (objetos[id].get_pos_y() - r_cut < 0)   && (objetos[id].get_pos_x() < (W/2)-(D/2) || objetos[id].get_pos_x() > (W/2)+(D/2) )  && objetos[id].get_pos_y() >= 0  ) {
      d = objetos[id].get_pos_y();

      if (d > radio){//atraccion
        velocidad_des[1] += -f_adh*( (d-radio) / (r_cut-radio));
      }
      else{
        velocidad_des[1] += f_rep*exp((-2*d)/(radio));
      }

}


  //paredes v
  if(objetos[id].get_pos_x()-r_cut < 0){//choca pared vertical izquierda
    d = (objetos[id].get_pos_x());
    if (d > radio){//atraccion
      velocidad_des[0] += -f_adh*( (d-radio) / (r_cut-radio));
    }
    else{
        velocidad_des[0] +=  f_rep*exp((-2*d)/(radio));
    }


  }


  if(objetos[id].get_pos_x()+r_cut > W){//choca pared vertical derecha
    d = abs(W - objetos[id].get_pos_x() );
    if(d > radio){
        velocidad_des[0] += f_adh*( (d-radio) / (r_cut-radio));
    }
    else{
        velocidad_des[0] +=  -f_rep*exp((-2*d)/(r_cut));
    }
  }

  //cout << "Fuerza X =  "<< fuerza[0]<<endl;
//  if (id>1){

      //if (!isfinite(v[0]) || !isfinite(v[1])){

          //if ( (abs(velocidad_des[0]) > 50) || (abs(velocidad_des[1]) > 50) ){
          //cout << id << endl;
          //cout << velocidad_des[0] << " " << velocidad_des[1] << endl;
          //cout << "Posiciones" << objetos[id].get_pos_x() << " " <<objetos[id].get_pos_y()<<endl;
          //cout << "Velocidad: " << objetos[id].get_vel_x() << " " <<objetos[id].get_vel_y()<<endl;
          //cout << objetos[id].get_tar_x() << " " <<objetos[id].get_tar_y()<<endl;
          //cout << objetos[id].get_radio() <<endl;

          //exit(-5);
    //  }

  //}











  return (velocidad_des);
}
