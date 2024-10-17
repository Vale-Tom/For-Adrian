#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
ATTENZIONE: in ogni funzione viene richiesto il valore del coefficiente di attrito e in caso questo sia diverso da 0 viene eseguita la versione con attrito
*/

void Eulero_cromer(double x, double v, double omega2, double coeff, double energiat, double energia0,double dt)
{
  double delta_energia
  for(int i=1; i<=n; i++)
  {    
    fprintf(fp," %lf %lf %lf %lf %lf\n", x, v, dt*i, energiat, delta_energia);   
    if (coeff==0)
    {

      v= v - omega2*x*dt;
      x= x + v*dt;
    }
    else{

      v= v - (omega2*x+coeff*v)*dt;
      x= x + v*dt;

    }

    energiat=0.5*m*(v*v)+m*g*L*(1-cos(x));
    delta_energia=(energiat-energia0)/energia0;  
  }
}
  
void Verlet(double x, double v, double omega2, double coeff, double energiat, double energia0,double dt)
{
  double delta_energia
  for(int i=1; i<=n; i++)
  {    
    fprintf(fp," %lf %lf %lf %lf %lf\n", x, v, dt*i, energiat, delta_energia);   
    if (coeff==0)
    {
      xv=x;
      x= x + v*dt - 0.5*omega2*x*(dt*dt);
      v= v + 0.5*dt*(-omega2*x-omega2*xv);

    }
    else
    {
      xv=x;
      x= x + v*dt - 0.5*omega2*x*(dt*dt);
      v= (v-0.5*dt*(omega2*(xv+x)+coeff*v))/(1+0.5*dt*coeff);
    }
    energiat=0.5*m*(v*v)+m*g*L*(1-cos(x));
    delta_energia=(energiat-energia0)/energia0;  
  }

}

void Runge_kutta(double x, double v, double omega2, double coeff, double energiat, double energia0,double dt)
{
  double delta_energia

  for(int i=1; i<=n; i++)
  {    

    fprintf(fp," %lf %lf %lf %lf %lf\n", x, v, dt*i, energiat, delta_energia);   

    y1=v*dt;
    y2=(v+(-omega2*(x+y1/2)-coeff*v)*(dt/2))*dt;
    y3=(v+(-omega2*(x+y2/2)-coeff*v)*(dt/2))*dt;
    y4=(v+(-omega2*(x+y3)-coeff*v)*(dt))*dt;
    
    v=v+(-omega2*x-coeff*v)*dt;
    x=x+(1/6)*(y1+2*y2+2*y3+y4);

    energiat=0.5*m*(v*v)+m*g*L*(1-cos(x));
    delta_energia=(energiat-energia0)/energia0;  
  }
}


int main(){
  //Dichiarazioni variabili
  double x0, v0, omega2, x, v, t, dt, k, m, xv, energia0, energiat, delta_energia;
  int  n,scelta;
  FILE *fp;

  //input
  printf("Inserisci k:");
  scanf("%lf", &k);
  
  printf("Inserisci m:");
  scanf("%lf", &m);

  omega2=k/m;
  printf("omega2:%lf\n", omega2);
  
  printf("Inserisci x0:");
  scanf("%lf", &x0);
  
  printf("Inserisci v0:");   
  scanf("%lf", &v0);
    
  printf("Inserisci t:");
  scanf("%lf", &t);
    
  printf("Inserisci dt:");
  scanf("%lf", &dt);
    
  n=(int) t/dt;
  printf("%d\n", n);
  
  x=x0;
  v=v0; 
  
  energia0=0.5*m*(v*v)+m*g*L*(1-cos(x));
  
  energiat=0.5*m*(v*v)+m*g*L*(1-cos(x));
  delta_energia=(energiat-energia0)/energia0;
 

 omega2=g/L;
 
  if((fp = fopen("energiadiscreta.txt", "w"))== NULL)
  {
    printf("Errore nell'apertura del file spazio.txt\n");
    exit(EXIT_FAILURE);
  }

 
  printf("\nTOP! Mo dimme che cazzo devo fa, pls:");
  printf("\n1. Eulero Cromer");
  printf("\n2.Verlet");
  printf("\n3. Runge-kutta (non è un kebabbaro de Rebibbia)");
  scanf("&d",&scelta);

  switch(scelta)
  {
    case(1):
      Eulero_cromer(x, v, omega2, coeff, energiat, energia0, dt);
      break;
    case(2):
      Verlet(x, v, omega2, coeff, energiat, energia0, dt);
      break;
    case(3):
      Runge_kutta(x, v, omega2, coeff, energiat, energia0, dt);

    case (default):
    printf("\nMa sei ncojone");
  }
  
  fclose(fp);


  energiat=0.5*m*(v*v)+m*g*L*(1-cos(x));
  delta_energia=(energiat-energia0)/energia0;

  printf("velocitàf:%lf\n", v);
  printf("posizionef:%lf\n", x);
  printf("energia0:%lf\n", energia0);
  printf("energiat:%lf\n", energiat);
  printf("variazione di energia:%lf\n", delta_energia*100);
 
  return 0;

}
