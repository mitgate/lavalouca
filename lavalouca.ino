#include "Ticker.h"

int BOMBA=2;
int ENTRAR_AGUA=3;
int SABAO=4;
int ESGOTO=5;
int AQUECIMENTO=6;


int Porta = A1;
int Cheio = A2;
int Vazio = A3;
int Botao = A5;

long TEMPO=0;
long TEMPO_PAUSA=0;
long TEMPO_PRELAVAGEM=100000;
long TEMPO_LAVAGEM=2100000;
long TEMPO_ENXAGUE=500000;
long TEMPO_ESGOTO=48000;
long TEMPO_AGUA=40000;
long TEMPO_SABAO=5000;


int STATE_BOMBA=0;
int STATE_BOTAO=0;
int STATE_LIGADO=0;
int STATE_RUNNING=0;


void IniciaPreLavagem();
void IniciaLavagem();
void IniciaEnxague1();
void IniciaEnxague2();
void Fim();

void AtivaEntradaAgua();
void PararEntradaAgua();
//void AtivaAquecimento();
//void PararAquecimento();
void LigarBomba();
void PararBomba();
void AtivaEsgoto();
void PararEsgoto();
void AtivaSabao();
void PararSabao();


void MonitorarPorta();
void MonitorarAgua();
void MonitorarBotao();

//inicio
Ticker timer_prelavagem(IniciaPreLavagem,   0,1);
Ticker timer_lavagem(IniciaLavagem,         0,1);
Ticker timer_enxague1(IniciaEnxague1,       0,1);
Ticker timer_enxague2(IniciaEnxague2,       0,1);
Ticker timer_fim(Fim,       0,1);



//prelavagem
Ticker timer_prelavagem_inicia_agua(AtivaEntradaAgua,  0, 1);
Ticker timer_prelavagem_parar_agua(PararEntradaAgua,  0, 1);
//Ticker timer_prelavagem_inicia_aquecimento(AtivaAquecimento,  0, 1);
//Ticker timer_prelavagem_parar_aquecimento(PararAquecimento,  0, 1);
Ticker timer_prelavagem_inicia_bomba(LigarBomba,        0, 1);
Ticker timer_prelavagem_parar_bomba(PararBomba,        0, 1);
Ticker timer_prelavagem_inicia_esgoto(AtivaEsgoto,       0,1);
Ticker timer_prelavagem_parar_esgoto(PararEsgoto,       0,1);
Ticker timer_prelavagem_inicia_preesgoto(AtivaEsgoto,       0,1);
Ticker timer_prelavagem_parar_preesgoto(PararEsgoto,       0,1);


//lavagem
Ticker timer_lavagem_inicia_sabao(AtivaSabao,       0,1);
Ticker timer_lavagem_parar_sabao(PararSabao,       0,1);
Ticker timer_lavagem_inicia_agua(AtivaEntradaAgua,  0, 1);
Ticker timer_lavagem_parar_agua(PararEntradaAgua,  0, 1);
//Ticker timer_lavagem_inicia_aquecimento(AtivaAquecimento,  0, 1);
//Ticker timer_lavagem_parar_aquecimento(PararAquecimento,  0, 1);
Ticker timer_lavagem_inicia_bomba(LigarBomba,        0, 1);
Ticker timer_lavagem_parar_bomba(PararBomba,        0, 1);
Ticker timer_lavagem_inicia_esgoto(AtivaEsgoto,       0,1);
Ticker timer_lavagem_parar_esgoto(PararEsgoto,       0,1);

//enxague1
Ticker timer_enxague1_inicia_agua(AtivaEntradaAgua,  0, 1);
Ticker timer_enxague1_parar_agua(PararEntradaAgua, 0, 1);
//Ticker timer_enxague1_inicia_aquecimento(AtivaAquecimento,  0, 1);
//Ticker timer_enxague1_parar_aquecimento(PararAquecimento,  0, 1);
Ticker timer_enxague1_inicia_bomba(LigarBomba,       0, 1);
Ticker timer_enxague1_parar_bomba(PararBomba,       0, 1);
Ticker timer_enxague1_inicia_esgoto(AtivaEsgoto,     0, 1);
Ticker timer_enxague1_parar_esgoto(PararEsgoto,     0, 1);

//enxague2
Ticker timer_enxague2_inicia_agua(AtivaEntradaAgua,  0, 1);
Ticker timer_enxague2_parar_agua(PararEntradaAgua, 0, 1);
//Ticker timer_enxague2_inicia_aquecimento(AtivaAquecimento,  0, 1);
//Ticker timer_enxague2_parar_aquecimento(PararAquecimento,  0, 1);
Ticker timer_enxague2_inicia_bomba(LigarBomba,       0, 1);
Ticker timer_enxague2_parar_bomba(PararBomba,       0, 1);
Ticker timer_enxague2_inicia_esgoto(AtivaEsgoto,     0, 1);
Ticker timer_enxague2_parar_esgoto(PararEsgoto,     0, 1);

//Monitores
Ticker timer_monitorar_porta(MonitorarPorta, 300);
Ticker timer_monitorar_agua(MonitorarAgua, 1500);
Ticker timer_monitorar_botao(MonitorarBotao, 500);



void setup() {
   pinMode(BOMBA, OUTPUT);
   pinMode(ENTRAR_AGUA, OUTPUT);    
   pinMode(SABAO, OUTPUT);    
   pinMode(ESGOTO, OUTPUT);    
   pinMode(AQUECIMENTO, OUTPUT);    
   pinMode(7, OUTPUT);    
   pinMode(8, OUTPUT);    
   pinMode(9, OUTPUT);    

   digitalWrite(BOMBA, HIGH); 
   digitalWrite(ENTRAR_AGUA, HIGH); 
   digitalWrite(SABAO, HIGH); 
   digitalWrite(ESGOTO, HIGH); 
   digitalWrite(AQUECIMENTO, HIGH); 
   digitalWrite(7, HIGH); 
   digitalWrite(8, HIGH); 
   digitalWrite(9, HIGH); 


  
  Serial.begin(9600);
  delay(2000);

  TEMPO=1;

  //pre-lavagem

  timer_prelavagem.interval(TEMPO);
  
  timer_prelavagem_inicia_preesgoto.interval(TEMPO);
  timer_prelavagem_parar_preesgoto.interval(TEMPO+TEMPO_ESGOTO);

  TEMPO=TEMPO+TEMPO_ESGOTO;

  timer_prelavagem_inicia_agua.interval(TEMPO);
  timer_prelavagem_parar_agua.interval(TEMPO+TEMPO_AGUA);

  //timer_prelavagem_inicia_aquecimento.interval(TEMPO);
  //timer_prelavagem_parar_aquecimento.interval(TEMPO+TEMPO_AGUA+TEMPO_PRELAVAGEM);


  timer_prelavagem_inicia_bomba.interval(TEMPO+TEMPO_AGUA);
  timer_prelavagem_parar_bomba.interval(TEMPO+TEMPO_AGUA+TEMPO_PRELAVAGEM);

  
  timer_prelavagem_inicia_esgoto.interval(TEMPO+TEMPO_AGUA+TEMPO_PRELAVAGEM);
  timer_prelavagem_parar_esgoto.interval(TEMPO+TEMPO_AGUA+TEMPO_PRELAVAGEM+TEMPO_ESGOTO);


  //Lavagem Quente
  
  TEMPO=TEMPO+TEMPO_AGUA+TEMPO_PRELAVAGEM+TEMPO_ESGOTO;
  timer_lavagem.interval(TEMPO);


  timer_lavagem_inicia_sabao.interval(TEMPO);
  timer_lavagem_parar_sabao.interval(TEMPO+TEMPO_SABAO);
  
  timer_lavagem_inicia_agua.interval(TEMPO);
  timer_lavagem_parar_agua.interval(TEMPO+TEMPO_AGUA);

  //timer_lavagem_inicia_aquecimento.interval(TEMPO+TEMPO_AGUA);

  //prolonga aquecimento
  //TEMPO=TEMPO+500000;

  
  //timer_lavagem_parar_aquecimento.interval(TEMPO+TEMPO_AGUA+TEMPO_LAVAGEM);


  timer_lavagem_inicia_bomba.interval(TEMPO+TEMPO_AGUA);
  timer_lavagem_parar_bomba.interval(TEMPO+TEMPO_AGUA+TEMPO_LAVAGEM);

  
  timer_lavagem_inicia_esgoto.interval(TEMPO+TEMPO_AGUA+TEMPO_LAVAGEM);
  timer_lavagem_parar_esgoto.interval(TEMPO+TEMPO_AGUA+TEMPO_LAVAGEM+TEMPO_ESGOTO);

 
  
  //enxague 1
  
  TEMPO=TEMPO+TEMPO_AGUA+TEMPO_LAVAGEM+TEMPO_ESGOTO;
  timer_enxague1.interval(TEMPO);
  
  timer_enxague1_inicia_agua.interval(TEMPO);
  timer_enxague1_parar_agua.interval(TEMPO+TEMPO_AGUA);

  //timer_enxague1_inicia_aquecimento.interval(TEMPO+TEMPO_AGUA);
  //timer_enxague1_parar_aquecimento.interval(TEMPO+10000);

  timer_enxague1_inicia_bomba.interval(TEMPO+TEMPO_AGUA);
  timer_enxague1_parar_bomba.interval(TEMPO+TEMPO_AGUA+TEMPO_ENXAGUE);

 
  timer_enxague1_inicia_esgoto.interval(TEMPO+TEMPO_AGUA+TEMPO_ENXAGUE);
  timer_enxague1_parar_esgoto.interval(TEMPO+TEMPO_AGUA+TEMPO_ENXAGUE+TEMPO_ESGOTO);


  //enxague 2
  TEMPO=TEMPO+TEMPO_AGUA+TEMPO_ENXAGUE+TEMPO_ESGOTO;
  timer_enxague2.interval(TEMPO);

  timer_enxague2_inicia_agua.interval(TEMPO);
  timer_enxague2_parar_agua.interval(TEMPO+TEMPO_AGUA);

  //timer_enxague2_inicia_aquecimento.interval(TEMPO+TEMPO_AGUA);
  //prolonga aquecimento
  //TEMPO=TEMPO+120000;

  //timer_enxague2_parar_aquecimento.interval(TEMPO+TEMPO_AGUA+TEMPO_ENXAGUE);

  timer_enxague2_inicia_bomba.interval(TEMPO+TEMPO_AGUA);
  timer_enxague2_parar_bomba.interval(TEMPO+TEMPO_AGUA+TEMPO_ENXAGUE);

 
  timer_enxague2_inicia_esgoto.interval(TEMPO+TEMPO_AGUA+TEMPO_ENXAGUE);
  timer_enxague2_parar_esgoto.interval(TEMPO+TEMPO_AGUA+TEMPO_ENXAGUE+TEMPO_ESGOTO);


  //FIM
  TEMPO=TEMPO+TEMPO_AGUA+TEMPO_ENXAGUE+TEMPO_ESGOTO;
    
  timer_fim.interval(TEMPO);


  
  timer_monitorar_porta.start();
  timer_monitorar_agua.start();
  timer_monitorar_botao.start();
  
  }

void loop() {

  timer_monitorar_porta.update();
  timer_monitorar_agua.update();
  timer_monitorar_botao.update();
  
  
  timer_prelavagem.update();
  timer_lavagem.update();
  timer_enxague1.update();
  timer_enxague2.update();
  timer_fim.update();



  timer_prelavagem_inicia_agua.update();
  timer_prelavagem_parar_agua.update();
  //timer_prelavagem_inicia_aquecimento.update();
  //timer_prelavagem_parar_aquecimento.update();
  timer_prelavagem_inicia_bomba.update();
  timer_prelavagem_parar_bomba.update();
  timer_prelavagem_inicia_esgoto.update();
  timer_prelavagem_parar_esgoto.update();
  timer_prelavagem_inicia_preesgoto.update();
  timer_prelavagem_parar_preesgoto.update();
  
  
  timer_lavagem_inicia_sabao.update();
  timer_lavagem_parar_sabao.update();
  timer_lavagem_inicia_agua.update();
  timer_lavagem_parar_agua.update();
  //timer_lavagem_inicia_aquecimento.update();
  //timer_lavagem_parar_aquecimento.update();
  timer_lavagem_inicia_bomba.update();
  timer_lavagem_parar_bomba.update();
  timer_lavagem_inicia_esgoto.update();
  timer_lavagem_parar_esgoto.update();
  
  timer_enxague1_inicia_agua.update();
  timer_enxague1_parar_agua.update();
  //timer_enxague1_inicia_aquecimento.update();
  //timer_enxague1_parar_aquecimento.update();
  timer_enxague1_inicia_bomba.update();
  timer_enxague1_parar_bomba.update();
  timer_enxague1_inicia_esgoto.update();
  timer_enxague1_parar_esgoto.update();
  
  timer_enxague2_inicia_agua.update();
  timer_enxague2_parar_agua.update();
  //timer_enxague2_inicia_aquecimento.update();
  //timer_enxague2_parar_aquecimento.update();
  timer_enxague2_inicia_bomba.update();
  timer_enxague2_parar_bomba.update();
  timer_enxague2_inicia_esgoto.update();
  timer_enxague2_parar_esgoto.update();
  
  

  if ( STATE_LIGADO == 1){
      if (STATE_RUNNING==0){
          
          STATE_RUNNING=1;

          timer_prelavagem.start();
          timer_prelavagem_inicia_agua.start();
          timer_prelavagem_parar_agua.start();    
          //timer_prelavagem_inicia_aquecimento.start();
          //timer_prelavagem_parar_aquecimento.start();      
          timer_prelavagem_inicia_bomba.start();
          timer_prelavagem_parar_bomba.start();      
          timer_prelavagem_inicia_esgoto.start();
          timer_prelavagem_parar_esgoto.start();

          timer_prelavagem_inicia_preesgoto.start();
          timer_prelavagem_parar_preesgoto.start();

          timer_lavagem.start();
          timer_lavagem_parar_sabao.start();
          timer_lavagem_inicia_sabao.start();  
          timer_lavagem_inicia_agua.start();
          timer_lavagem_parar_agua.start();    
          //timer_lavagem_inicia_aquecimento.start();
          //timer_lavagem_parar_aquecimento.start();      
          timer_lavagem_inicia_bomba.start();
          timer_lavagem_parar_bomba.start();      
          timer_lavagem_inicia_esgoto.start();
          timer_lavagem_parar_esgoto.start();
      
          timer_enxague1.start();
          timer_enxague1_inicia_agua.start();
          timer_enxague1_parar_agua.start();    
          //timer_enxague1_inicia_aquecimento.start();
          //timer_enxague1_parar_aquecimento.start();
          timer_enxague1_inicia_bomba.start();
          timer_enxague1_parar_bomba.start();      
          timer_enxague1_inicia_esgoto.start();
          timer_enxague1_parar_esgoto.start();    


          timer_enxague2.start();
          timer_enxague2_inicia_agua.start();
          timer_enxague2_parar_agua.start();
          //timer_enxague2_inicia_aquecimento.start();
          //timer_enxague2_parar_aquecimento.start();      
          timer_enxague2_inicia_bomba.start();
          timer_enxague2_parar_bomba.start();      
          timer_enxague2_inicia_esgoto.start();
          timer_enxague2_parar_esgoto.start();

          timer_fim.start();
  
      }
  }
  else {
          
          timer_prelavagem_inicia_agua.stop();
          timer_prelavagem_parar_agua.stop();
          //timer_prelavagem_inicia_aquecimento.stop();
          //timer_prelavagem_parar_aquecimento.stop();
          timer_prelavagem_inicia_bomba.stop();
          timer_prelavagem_parar_bomba.stop();

          timer_lavagem_parar_sabao.stop();
          timer_lavagem_inicia_sabao.stop();
          timer_lavagem_inicia_agua.stop();
          timer_lavagem_parar_agua.stop();
          //timer_lavagem_inicia_aquecimento.stop();
          //timer_lavagem_parar_aquecimento.stop();
          timer_lavagem_inicia_bomba.stop();
          timer_lavagem_parar_bomba.stop();
            
          timer_enxague1_inicia_agua.stop();
          timer_enxague1_parar_agua.stop();
          //timer_enxague1_inicia_aquecimento.stop();
          //timer_enxague1_parar_aquecimento.stop();
          timer_enxague1_inicia_bomba.stop();
          timer_enxague1_parar_bomba.stop();
          
          timer_enxague2_inicia_agua.stop();
          timer_enxague2_parar_agua.stop();
          //timer_enxague2_inicia_aquecimento.stop();
          //timer_enxague2_parar_aquecimento.stop();
          timer_enxague2_inicia_bomba.stop();
          timer_enxague2_parar_bomba.stop();
      
  }


  
}


void AtivaEntradaAgua(){
    Serial.println("Ativando Agua");
    Serial.println( analogRead(Cheio) );
    Serial.println( analogRead(Vazio) );
    
    if (analogRead(Cheio) == 0){ 
        digitalWrite(ENTRAR_AGUA, LOW); 
    }
    
}
void PararEntradaAgua(){
    Serial.println("Parando Agua");
    digitalWrite(ENTRAR_AGUA, HIGH); 
}
void AtivaAquecimento(){
    Serial.println("Ativando Aquecimento");
    //digitalWrite(AQUECIMENTO, LOW); 
}
void PararAquecimento(){
    Serial.println("Parando Aquecimento");
    //digitalWrite(AQUECIMENTO, HIGH); 
}

void LigarBomba(){
    Serial.println("Ativando Bomba");
    STATE_BOMBA=1;
    digitalWrite(BOMBA, LOW); 
}
void PararBomba(){
    Serial.println("Parando Bomba");
    STATE_BOMBA=0;
    digitalWrite(BOMBA, HIGH); 
}
void AtivaEsgoto(){
    Serial.println("Ativando Esgoto");
    PararEntradaAgua();
    //PararAquecimento();
    PararBomba();            
    digitalWrite(ESGOTO, LOW); 
  
}
void PararEsgoto(){
    Serial.println("Parando Esgoto");
    digitalWrite(ESGOTO, HIGH); 
}
void AtivaSabao(){
    Serial.println("Ativando Sabao");
    digitalWrite(SABAO, LOW); 
  
}
void PararSabao(){
    Serial.println("Parando Sabao");
    digitalWrite(SABAO, HIGH); 
}

void IniciaPreLavagem(){
    Serial.println("_________________________");
    Serial.println("     Pre Lavagem         ");
}
void IniciaLavagem(){
    Serial.println("_________________________");
    Serial.println("        Lavagem         ");
}
void IniciaEnxague1(){
    Serial.println("_________________________");
    Serial.println("       Enxague1         ");
}
void IniciaEnxague2(){
    Serial.println("_________________________");
    Serial.println("       Enxague2         ");
}
void Fim(){
    Serial.println("_________________________");
    Serial.println("           FIM          ");
    STATE_LIGADO=0;
    STATE_RUNNING=0;
    PararEntradaAgua();
    //PararAquecimento();
    PararBomba();            
    PararSabao();
    
}




void MonitorarPorta(){
    
    if (analogRead(Porta) == 0){        
        Serial.println("Porta Aberta");     
        //Serial.println(PORTD);     
    
        if (TEMPO_PAUSA == 0){
            TEMPO_PAUSA = TEMPO;
        }

        //Parar Bomba
        digitalWrite(BOMBA, HIGH); 
        
    }
    else{
        if (STATE_BOMBA == 1){
            digitalWrite(BOMBA, LOW); 
        }       
    }
  
}

void MonitorarAgua(){
  //Serial.println(analogRead(Cheio));
  //Serial.println(analogRead(Vazio));
    if (analogRead(Cheio) > 400){
        Serial.println("Esta cheio.");
        PararEntradaAgua();
    } 
    if (analogRead(Vazio) > 400){
        Serial.println("Esta Vazio.");
        //PararAquecimento();
        PararBomba();
        
    } 

}

void MonitorarBotao(){
    //Serial.println(analogRead(Botao) );
    if (analogRead(Botao) == 0){
        STATE_BOTAO=STATE_BOTAO+1;
    } 
    if (STATE_BOTAO >= 5){
        Serial.println("Botao");

        STATE_BOTAO=0;

        if (STATE_LIGADO == 0){
            STATE_LIGADO=1;
        }
        else{
            Serial.println("Desligando...");
            STATE_LIGADO=0;
            STATE_RUNNING==0;
            PararEntradaAgua();
            //PararAquecimento();
            PararBomba();            
            PararSabao();
            timer_lavagem_inicia_esgoto.interval(1);
            timer_lavagem_parar_esgoto.interval(TEMPO_ESGOTO);
            timer_lavagem_inicia_esgoto.start();
            timer_lavagem_parar_esgoto.start();            
            

        }
        
    }
    
}
