// **************************************
// * ROBOZONA                           *
// * 2015 Estrategia & Inovacao Arizona *
// * Robo com 5 sensores de ultrassom   *
// * 2 sensores de IR                   *
// * 2 motores CC                       *
// **************************************

//Pinos dos transistores dos motores CC
int trigPin[5] = {12, 13, 2, 3, 4};
int echoPin[5] = {5, 6, 7, 8, 9};
long distCM[5] = {400, 400, 400, 400, 400};
long menorDist;
int indiceMenorDist;
long maiorDist;
int indiceMaiorDist;

long velocMax; //parametro de velocidade maxima a ser aplicada aos motores 

float pesoLaterais = 1; //peso a ser dado para a proximidade das laterais do robo no calculo
float pesoDiagonais = 2; //peso a ser dado para a proximidade das laterais do robo no calculo

long pwmMotor1; //velocidade do motor 1, de 0 a 255
long pwmMotor2; //velocidade do motor 2, de 0 a 255 

float gravidadeDireita;
float gravidadeEsquerda;

int pinMotor1 = 11;
int pinMotor2 = 10;
int pinIR1 = 0;
int valorIR1;
int pinIR2 = 1;
int valorIR2;

boolean turnLeft;

long dist;
long novaDist;

void setup() {
  Serial.begin (9600);
  
  //Ajusta os pinos de entrada e saida 
  for (int i=0; i < 5; i++){
    pinMode(trigPin[i], OUTPUT);
    pinMode(echoPin[i], INPUT);
  }
  
  pinMode(pinMotor1, OUTPUT);
  pinMode(pinMotor2, OUTPUT);
}



void loop() {

  //Faz a leitura das distancias dos 5 sensores de ultrassom
  
  indiceMenorDist = 2;
  menorDist = 500;
  indiceMaiorDist = 2;
  maiorDist = 0;
 
  for (int i=0; i < 5; i++){
    distCM[i] = distanciaUltraSom(i);
    
    if (distCM[i] < menorDist)
    {
      menorDist = distCM[i];
      indiceMenorDist = i;
    }
    
    if (distCM[i] > maiorDist)
    {
      maiorDist = distCM[i];
      indiceMaiorDist = i;
    }
    
    Serial.println(distCM[i]);
  }
  
  //Serial.println("AAA");

  
  // Caso 1
  // Se qualquer distancia for menor do que 30, diminui a velocidade maxima proporcionalmente. Em 30 = 255, em 0 = 0
  if (menorDist < 30)
    {
      velocMax = 255 * menorDist / 30L;
    }
  else
    {
      velocMax = 255;
    }
    //Serial.println(velocMax);

  if (distCM[2] < 70)
  {
    velocMax = 255 * distCM[2] / 70L;
  }
  

  // Caso 2
  if (menorDist == 200)
    {
    pwmMotor1 = velocMax;
    pwmMotor2 = velocMax;
    }  
  else // Decidir estrategia de procurar espaco livre ou evitar obstaculos
  {
    if (menorDist > 50) // Estrategia de busca do espaco livre
    {
      if (indiceMaiorDist == 2) // Maior espaco esta em frente, segue reto
      {
       pwmMotor1 = velocMax;
       pwmMotor2 = velocMax;
      }
      
      if (indiceMaiorDist ==0) // Maior espaco esta a direita, curva rapida cortando o motor direito
      {
        pwmMotor1 = 0;
        pwmMotor2 = velocMax;
      }

      if (indiceMaiorDist ==1) // Maior espaco esta na diagonal direita, curva leve cortando o motor direito pela metade
      {
        pwmMotor1 = 0;
        pwmMotor2 = velocMax / 2L;
      }
      
      if (indiceMaiorDist == 3) // Maior espaco esta na diagonal esquerda, curva leve cortando o motor esquerdo pela metade
      {
        pwmMotor1 = velocMax / 2L;
        pwmMotor2 = velocMax;
      }

      if (indiceMaiorDist ==4) // Maior espaco esta a esquerda, curva rapida cortando o motor esquerdo
      {
        pwmMotor1 = velocMax;
        pwmMotor2 = 0;
      }

     
    }
    else // Estrategia de evitar obstaculos, pois a menor distancia esta abaixo de 50 cm
    {
      if (indiceMenorDist == 2 && (indiceMaiorDist == 0 || indiceMaiorDist == 1)) // Menor distancia em frente, vira para a direita
      {
        pwmMotor1 = 0;
        pwmMotor2 = velocMax;
      }
      
      if (indiceMenorDist == 2 && (indiceMaiorDist == 3 || indiceMaiorDist == 4)) // Menor distancia em frente, vira para a esquerda
      {
        pwmMotor1 = velocMax;
        pwmMotor2 = 0;
      }
     
     if (indiceMenorDist == 0) // Aproximando da lateral, vira suavemente para a esquerda
     {
        pwmMotor1 = velocMax;
        pwmMotor2 = velocMax / 2L;
     }
     
          if (indiceMenorDist == 1) // Aproximando da diagonal, vira rapidamente para a esquerda
     {
        pwmMotor1 = velocMax;
        pwmMotor2 = 0;
     }
     
          if (indiceMenorDist == 3) // Aproximando da diagonal, vira suavemente para a direita
     {
        pwmMotor1 = 0;
        pwmMotor2 = velocMax;
     }
     
          if (indiceMenorDist == 4) // Aproximando da lateral, vira suavemente para a direita
     {
        pwmMotor1 = velocMax / 2L;
        pwmMotor2 = velocMax;
     }
     
    }
  }
  
  
 // Serial.println(menorDist);
  
  
  
  if (pwmMotor1 < 0)
  {
    pwmMotor1 = 0;
  }
          
  if (pwmMotor2 < 0)
  {
    pwmMotor2 = 0;
  }
  
  
  analogWrite(pinMotor1, pwmMotor1);
  analogWrite(pinMotor2, pwmMotor2);
  
}



int distanciaUltraSom(int pino)
{
  long duration, distance;
  digitalWrite(trigPin[pino], LOW);  
  delayMicroseconds(2);
  digitalWrite(trigPin[pino], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin[pino], LOW);
  duration = pulseIn(echoPin[pino], HIGH, 38000);
  distance = (duration) / 58;
    if (distance == 0) {
       //distance = 431; atençao: troquei para 200 (2 metros, para melhorar os algoritmos)
       distance = 200;
     }
     
     if (distance > 200) {
       distance = 200;
     }
  return distance;
}




