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

// Parametro de velocidade maxima a ser aplicada aos motores
long velocMax;

// Velocidade dos motores 1 e 2, de 0 a 255
long pwmMotor1;
long pwmMotor2;

int pinMotor1 = 11;
int pinMotor2 = 10;

void setup () {
    Serial.begin(9600);

    // Ajusta os pinos de entrada e saida
    for (int i = 0; i < 5; i++) {
        pinMode(trigPin[i], OUTPUT);
        pinMode(echoPin[i], INPUT);
    }

    pinMode(pinMotor1, OUTPUT);
    pinMode(pinMotor2, OUTPUT);
}

void loop () {
    indiceMenorDist = 2;
    menorDist = 500;
    indiceMaiorDist = 2;
    maiorDist = 0;

    // Faz a leitura das distancias dos 5 sensores de ultrassom
    for (int i = 0; i < 5; i++) {
        distCM[i] = distanciaUltraSom(i);

        if (distCM[i] < menorDist) {
            menorDist = distCM[i];
            indiceMenorDist = i;
        }

        if (distCM[i] > maiorDist) {
            maiorDist = distCM[i];
            indiceMaiorDist = i;
        }

        Serial.println(distCM[i]);
    }

    // Caso 1
    // Se qualquer distancia for menor do que 30, diminui a velocidade maxima proporcionalmente. Em 30 = 255, em 0 = 0
    if (menorDist < 25) {
        velocMax = 255 * menorDist / 25L;
    } else {
        velocMax = 255;
    }

    // Se a distancia da frente for menor do que 70, diminui a velocidade maxima proporcionalmente.
    if (distCM[2] < 60) {
        velocMax = 255 * distCM[2] / 55L;
    } else {
        velocMax = 255;
    }

    // Velocidade maxima caso distancia igual a 200
    if (menorDist >= 130) {
        pwmMotor1 = velocMax;
        pwmMotor2 = velocMax;
    } else {
        // Decide curva, se menor distnacia menor que 50
        // Decidir estrategia de procurar espaco livre ou evitar obstaculos
        // Estrategia de busca do espaco livre
        if (menorDist > 40) {
            // Maior espaco esta em frente, segue reto
            if (indiceMaiorDist == 2) {
                pwmMotor1 = velocMax;
                pwmMotor2 = velocMax;
            }

            // Maior espaco esta a direita, curva rapida cortando o motor direito
            if (indiceMaiorDist == 0) {
                pwmMotor1 = 0;
                pwmMotor2 = velocMax;
            }

            // Maior espaco esta na diagonal direita, curva leve cortando o motor direito pela metade
            if (indiceMaiorDist == 1) {
                pwmMotor1 = 0;
                pwmMotor2 = velocMax * 0.4;
            }

            // Maior espaco esta na diagonal esquerda, curva leve cortando o motor esquerdo pela metade
            if (indiceMaiorDist == 3) {
                pwmMotor1 = velocMax * 0.4;
                pwmMotor2 = velocMax;
            }

            // Maior espaco esta a esquerda, curva rapida cortando o motor esquerdo
            if (indiceMaiorDist == 4) {
                pwmMotor1 = velocMax;
                pwmMotor2 = 0;
            }
        } else {
            // Estrategia de evitar obstaculos, pois a menor distancia esta abaixo de 50 cm
            // Menor distancia em frente, vira para a direita
            if (indiceMenorDist == 2 && (indiceMaiorDist == 0 || indiceMaiorDist == 1)) {
                pwmMotor1 = 0;
                pwmMotor2 = velocMax;
            }

            // Menor distancia em frente, vira para a esquerda
            if (indiceMenorDist == 2 && (indiceMaiorDist == 3 || indiceMaiorDist == 4)) {
                pwmMotor1 = velocMax;
                pwmMotor2 = 0;
            }

            // Aproximando da lateral, vira suavemente para a esquerda
            if (indiceMenorDist == 0) {
                pwmMotor1 = velocMax;
                pwmMotor2 = velocMax * 0.4;
            }

            // Aproximando da diagonal, vira rapidamente para a esquerda
            if (indiceMenorDist == 1) {
                pwmMotor1 = velocMax;
                pwmMotor2 = 0;
            }

            // Aproximando da diagonal, vira suavemente para a direita
            if (indiceMenorDist == 3) {
                pwmMotor1 = 0;
                pwmMotor2 = velocMax;
            }

            // Aproximando da lateral, vira suavemente para a direita
            if (indiceMenorDist == 4) {
                pwmMotor1 = velocMax * 0.4;
                pwmMotor2 = velocMax;
            }
        }
    }

    if (pwmMotor1 < 0) {
        pwmMotor1 = 0;
    }

    if (pwmMotor2 < 0) {
        pwmMotor2 = 0;
    }

    analogWrite(pinMotor1, pwmMotor1);
    analogWrite(pinMotor2, pwmMotor2);
}

int distanciaUltraSom (int pino) {
    long duration, distance;
    digitalWrite(trigPin[pino], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin[pino], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin[pino], LOW);
    duration = pulseIn(echoPin[pino], HIGH, 38000);
    distance = (duration) / 58;

    if (distance == 0) {
        distance = 200;
    }

    if (distance > 200) {
        distance = 200;
    }
    return distance;
}