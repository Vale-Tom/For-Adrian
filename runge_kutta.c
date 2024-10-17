#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int main(){
  //Dichiarazioni variabili
  double x0, v0, omega2, x, v, t, dt, k, m, xv, energia0, energiat, delta_energia,x_plus,v_plus;
  int  n;
  FILE *fp;
  FILE *fq;
  FILE *fr;   
  FILE *fu;
  FILE *fv;
  
  
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
  

  if((fv = fopen("dati.txt", "w"))== NULL)
    { printf("Errore nell'apertura del file dati.txt\n");
      exit(EXIT_FAILURE);
  }
  fprintf(fv,"%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n", t, dt,  k, m, x0, v0);

   fclose(fv);


  n=(int) t/dt;
  printf("%d\n", n);
  
  x=x0;
  v=v0;

  energia0=0.5*m*(v*v)+0.5*k*(x*x);

  if((fp = fopen("spazio.txt", "w"))== NULL)
    { printf("Errore nell'apertura del file spazio.txt\n");
      exit(EXIT_FAILURE);
  }
    if((fq = fopen("velocita.txt", "w"))== NULL)
    { printf("Errore nell'apertura del file velicita.txt\n");
      exit(EXIT_FAILURE);
  }
      if((fr = fopen("deltaenergia.txt", "w"))== NULL)
    { printf("Errore nell'apertura del file deltaenergia.txt\n");
      exit(EXIT_FAILURE);
    }      
      if((fu = fopen("energiadiscreta.txt", "w"))== NULL)
	  { printf("Errore nell'apertura del file energiadiscreta.txt\n");
      exit(EXIT_FAILURE);
  }

 fprintf(fp,"%lf\n",x0);
 fprintf(fq,"%lf\n",v0);
 
 energiat=0.5*m*(v*v)+0.5*k*(x*x);
 delta_energia=(energiat-energia0)/energia0;
 
 fprintf(fu,"%lf\n",energiat);
 fprintf(fr,"%lf\n",delta_energia);
    
  
 for(int i=1; i<=n; i++)
  {
    //xv=x;
    //x= x + v*dt;
    //v= v - omega2*xv*dt;
    x_plus=v*dt;
    v_plus=-omega2*x*dt;

    v= v + -omega2*(x+0.5*x_plus)*dt;
    x= x + (v+0.5*v_plus)*dt;

    /**/
    
    energiat=0.5*m*(v*v)+0.5*k*(x*x);
    delta_energia=(energiat-energia0)/energia0;
    
    fprintf(fp,"%lf\n",x);
    fprintf(fq,"%lf\n",v);  
    fprintf(fu,"%lf\n",energiat);
    fprintf(fr,"%lf\n",delta_energia);
    
    /*
    delta_energia=energiat-energia0;    
    /printf("x: %lf\n", x);*/
  }
 
 fclose(fp);
 fclose(fq);
 fclose(fr);
 fclose(fu);
 

 energiat=0.5*m*(v*v)+0.5*k*(x*x);
 delta_energia=(energiat-energia0)/energia0;

 printf("velocitàf:%lf\n", v);
 printf("posizionef:%lf\n", x);
 printf("energia0:%lf\n", energia0);
 printf("energiat:%lf\n", energiat);
 printf("variazione di energia:%lf\n", delta_energia*100);
 
 return 0;

}
