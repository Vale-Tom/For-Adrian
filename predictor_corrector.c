#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int main(){
  //Dichiarazioni variabili
  double x0, v0, omega2, x, v, t, dt, k, m, xv, energia0, energiat, delta_energia;
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
  fprintf(fv,"%f\n%f\n%f\n%f\n%f\n%f\n", t, dt,  k, m, x0, v0);

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

 fprintf(fp,"%f\n",x0);
 fprintf(fq,"%f\n",v0);
 
 energiat=0.5*m*(v*v)+0.5*k*(x*x);
 delta_energia=(energiat-energia0)/energia0;
 fprintf(fu,"%f\n",energiat);
 fprintf(fr,"%f\n",delta_energia);

    
 v0=v;//velocità in n-esimo t
 x_neg1=x-v0*dt;
 //passo precedente a quello iniziale per iniziare il ciclo
 
 for(int i=1; i<=n; i++)
  {
    x_pre=x_neg1+2*v0*dt;//x prevista
    //v=v0;//v_n della formula
    v= v0 + 0.5*dt*(-omega2*x-omega2*x_pre);
    
    //v calcolata usando l'accelerazione in x_pre
    x_neg1=x //conservo il valore di x_n-1 per la successiva iterazione
    x= x + (v+v0)*0.5*dt;//x corretta
    
    v0=v;
    
    energiat=0.5*m*(v*v)+0.5*k*(x*x);
    delta_energia=(energiat-energia0)/energia0;
    
    fprintf(fp,"%f\n",x);
    fprintf(fq,"%f\n",v);  
    fprintf(fu,"%f\n",energiat);
    fprintf(fr,"%f\n",delta_energia);
    
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
