/*
	IZP PROJECT 2 - LOGARITHM CALCULATOR
			AUTHOR: Adam Buchta
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

// calculate logarithm "x" via Taylor polynom
double taylor_log(double x, unsigned int n){
    double suma = 0.0;
    double pom = 1.0;
    if(n==1){
        x = 1-x;
        return -x;
    }
	//for x (from 1 to INF)
    if(x>=1.0){ 
        for(int i=1; i<=n; i++){
            pom*=((x-1.0)/x);
            suma += (pom/i);
        }
        return suma;
    }
	//for x (from 0 to 1)
    else{ 
        x = 1.0 - x;
        for(int i=1; i<=n; i++){
            pom*=x;
            suma -= (pom/i);
        }
        return suma;
    }
}

// calculate logarithm "x" via continued fraction method
double cfrac_log(double x, unsigned int n){

    double pom = 1.0;
    double koef = (2*n)-1;
    double suma = koef;

    // calculating from the bottom
    x = (x-1.0)/(x+1.0);
    if(n==1){
        return 2*x;
    }
    for(int i=n; i>1;){
        i--;
        koef = koef-2.0;
        pom = ((i*i)*(x*x))/suma;
        suma = koef-pom;
    }
    return (2.0*x)/suma;

}

double funkce_log(double x, unsigned int n){
    int was;
    if(was == 1){
        return cfrac_log(x, n);
    }
    else{
        was = 1;
        return taylor_log(x, n);
    }
    return 1;
}

double funkce_pow(double x, double y, unsigned int n){
    if(n==1){
        return 1;
    }
    double suma=0.0;
    double pom=1.0;
    double pow_y=1.0;
    double pow_logx=1.0;
    double fakt=1.0;

    for(int i = 1; i<=n; i++){
        fakt*=i;
        pow_y*=y;
        pow_logx*=funkce_log(x, n);
 
        pom= (pow_y*pow_logx)/fakt;
        suma+=pom;
    }
    return suma+1;
}

// function for exceptions
int excep_messages(int argc, char *argv[]){
    double x = atof(argv[2]);
    if(isinf(x)==1){
        fprintf(stderr,"\"x\" is INFINITY.\n");
        return 1;
    }
    if(isnan(x)==1){
        fprintf(stderr,"\"x\" is NaN.\n");
        return 1;
    }
    if(x<=0.0){
        fprintf(stderr, "\"x\" has to be greater than 0.\n");
        return 1;
    }
    if(strcmp(argv[1],"--log")==0){
        if(argc<4 || argc>4){ //wrong usage of arguments for --log
            fprintf(stderr, "Arguments for --log are \"X\" and \"N\"");
            return 1;
        }
        return 0;
    }
    if(strcmp(argv[1],"--pow")==0){
        if(argc<5 || argc>5){ //wrong usage of arguments for --pow
            fprintf(stderr, "Arguments for --pow are \"X\", \"Y\" and \"N\"");
            return 1;
        }
        return 0;
    }
    //wrong usage of arguments for program
    fprintf(stderr, "Run the program with arguments --log or --pow.\n");
    return 1;
}

int main(int argc, char *argv[]){
    int check_excep = excep_messages(argc, argv);
    if (check_excep == 1){
        return 1;
    }

    if(strcmp(argv[1], "--log")==0){
        double x = atof(argv[2]);
        unsigned int n = atof(argv[3]);

        printf("       log(%.4lf) = %.12lf\n", x, log(x));
        printf(" cfrac_log(%.4lf) = %.12lf\n", x, cfrac_log(x, n));
        printf("taylor_log(%.4lf) = %.12lf\n", x, taylor_log(x, n));
        return 0;
    }
    else if(strcmp(argv[1], "--pow")==0){
        double x = atof(argv[2]);
        double y = atof(argv[3]);
        unsigned int n = atof(argv[4]);

        printf("         pow(%.2lf,%.1lf) = %.12lf\n", x, y, pow(x, y));
        printf("  taylor_pow(%.2lf,%.1lf) = %.12lf\n", x, y, funkce_pow(x, y, n));
        printf("taylorcf_pow(%.2lf,%.1lf) = %.12lf\n", x, y, funkce_pow(x, y, n));
        return 0;
    }
}
