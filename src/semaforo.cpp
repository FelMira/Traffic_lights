#include "semaforo.hpp"
DigitalOut semaforo[]={(PD_12),(PD_13),(PD_14)};
InterruptIn botao(PA_0);
int tempo,estado=1,i;
float times[]={20.0,4.0,10.0};
bool alerta,desligado;
Timer contador;
Ticker alarme;
Timeout timeout;

void desligar_semaforo(){
    for(i=0;i<=2;i++){
            semaforo[i]=0;
        }
}

void mudar_led(){
    desligar_semaforo();
    if(estado>=2){
        estado=0;
        }
    else{
        estado++;
    }
    semaforo[estado]=1;
    timeout.attach(&mudar_led, times[estado]);
}

void piscar(){
    semaforo[1]= !semaforo[1];
}

void ativar_timer(){
    contador.start();
}

void desativar_timer(){
    contador.stop();
    tempo = contador.read();
    if(tempo<=3&&semaforo[0]==1){
        mudar_led();
        }
    else if(tempo>3&&tempo<=10){
        if(desligado==0){    
            if(alerta==0){
                timeout.detach();
                desligar_semaforo();
                alarme.attach(&piscar, 0.5);
                alerta=1;
                }
            else{
                desligar_semaforo();
                semaforo[estado]=1;
                timeout.attach(&mudar_led, times[estado]);
                alarme.detach();
                alerta=0;
                }
            }
        }
    else if(tempo>10){
            if(desligado==0){
                timeout.detach();
                alarme.detach();
                desligar_semaforo();
                desligado=1;
                alerta=0;
                }
            else{
                estado=2;
                semaforo[estado]=1;
                timeout.attach(&mudar_led, times[estado]);               
                desligado=0;
                }
        }
    contador.reset();
}