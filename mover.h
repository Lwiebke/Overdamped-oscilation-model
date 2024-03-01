


void mover_particulas(vector<Particula> &particulas, vector<vector<int> >& vecinos,double dt,double L,double W,double D, double d_cut, double f_rep, double f_adh, double f_wall, double t){

  vector<double> v;
  vector<double> vel_x;
  vector<double> vel_y;
  for (int i=2;i<particulas.size();i++){
    v = calcular_fuerzas(particulas, i, vecinos[i], d_cut, f_rep, f_adh, f_wall,L, W, D);



    vel_x.push_back(v[0]);
    vel_y.push_back(v[1]);
  }
  for (int i=2;i<particulas.size();i++){
      particulas[i].set_pos_x(  particulas[i].get_pos_x() + vel_x[i-2]*dt);
      particulas[i].set_target_x(particulas[i].get_pos_x());
      particulas[i].set_pos_y(  particulas[i].get_pos_y() + vel_y[i-2]*dt);
      particulas[i].set_vel_x( vel_x[i-2] );
      particulas[i].set_vel_y( vel_y[i-2] );
      particulas[i].set_radio(particulas[i].actualizar_radio(t));
  }
}
