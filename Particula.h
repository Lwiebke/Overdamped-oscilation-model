#include <iostream>
#include <list>
#include <math.h>
#include <vector>

using namespace std;
class Particula{
  private:
    int id;
    double pos_x = 0;
    double pos_y = 0;
    double vel_x = 0;
    double vel_y = 0;

    double radio;
    float radio_base;
    float periodo;
    float amplitud_radio;
    float fase;

    double v_deseada;

    double target_x;
    double target_y;

    //double v_deseada_x;
    //double v_deseada_y;


  public:
    Particula(){
      int id;
      double pos_x = 0;
      double pos_y = 0;
      double vel_x = 0;
      double vel_y = 0;

      double radio = 0;
      double masa = 0;

    }
    Particula(const Particula& a_copiar);
    bool operator==(const Particula& a_comparar)const ;

    void set_id(int nuevo_id){id = nuevo_id;}
    void set_radio(double r){radio = r;}

    void set_pos_x(double x) {pos_x = x;}
    void set_pos_y(double y) {pos_y = y;}

    void set_vel_y(double vy) {vel_y = vy;}
    void set_vel_x(double vx) {vel_x = vx;}


    void set_v_deseada(double vd){v_deseada = vd;}

    void set_target_x(double tx){target_x = tx;}
    void set_target_y(double ty){target_y = ty;}



    void set_radio_base(float rb){radio_base=rb;}
    void set_fase(float f) {fase = f;}
    void set_amplitud_radio(float A) {amplitud_radio = A;}
    void set_periodo(float p){periodo=p;}


    int get_id()const {return id;}
    double get_pos_x()const {return pos_x;}
    double get_pos_y()const {return pos_y;}
    double get_vel_y()const {return vel_y;}
    double get_vel_x()const {return vel_x;}


    double get_tar_x()const {return target_x;}
    double get_tar_y()const {return target_y;}
    vector<double> get_fuerza_migratoria(){
      double dist_target = sqrt(pow(target_x-pos_x,2)+pow(target_y-pos_y,2));
      double e_target[] = {(target_x-pos_x)/dist_target,(target_y-pos_y)/dist_target};
      vector<double> fm;
      fm.push_back(v_deseada * e_target[0]);
      fm.push_back(v_deseada * e_target[1]);
      return (fm);


    }



    float get_amplitud(){return amplitud_radio;}
    float get_periodo(){return periodo;}
    float get_fase(){return fase;}
    double get_radio()const {return radio;}
    double get_radio_base()const {return radio_base;}


    float actualizar_radio(double t){
      return (radio_base + amplitud_radio*sin(periodo*t + fase));
    }



};

Particula::Particula (const Particula& a_copiar){
  id = a_copiar.id;
  pos_x = a_copiar.pos_x;
  pos_y = a_copiar.pos_y;
  vel_x = a_copiar.vel_x;
  vel_y = a_copiar.vel_y;


  radio = a_copiar.radio;

  radio_base = a_copiar.radio_base;
  amplitud_radio= a_copiar.amplitud_radio;
  fase = a_copiar.fase;
  periodo = a_copiar.periodo;

  v_deseada = a_copiar.v_deseada;

  //v_deseada_x = a_copiar.v_deseada_x;
  //v_deseada_y = a_copiar.v_deseada_y;

  target_x = a_copiar.target_x;
  target_y = a_copiar.target_y;



}
bool Particula::operator==(const Particula& a_comparar) const{
  if(this->id == a_comparar.id)
   return(1);
  else{return(0);}
}
