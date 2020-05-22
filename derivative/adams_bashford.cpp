#include <iostream>
#include <fstream>
#include <string>


void adams_bashford(double (*f)(double,double)){
    fstream fin("derivative/rungecutt.txt");
    string line;
    int lines=0;
    while (fin>>line){
        lines++;
    }
    lines/=2;
    fin.clear();
    fin.seekg(0);
    double x[lines];
    double y[lines];
    int i=0;
    while (i<lines){
        fin>>x[i];
        fin>>y[i];
        i++;    
    }
    double step=x[1]-x[0];
    for(int i=3;i<lines;i++){
        y[i+1]=y[i]+step*(
            55*f(x[i],y[i])-
            59*f(x[i-1],y[i-1])+
            37*f(x[i-2],x[i-2])-
            9*f(x[i-3],y[i-3]))/24;
    }
    fin.close();
    fstream fout("derivative/adamsbashford.txt",ios::trunc|ios::out);
    for(int i=0;i<lines;i++){
        fout<<x[i]<<" "<<y[i]<<endl;
    }
    fout.close();
}