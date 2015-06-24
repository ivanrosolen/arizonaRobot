# Arizona Robot

![Arizona](http://ivanrosolen.com/arizonaRobot/arizona.png "Arizona")

### O quê?

Criado com o intuito de aprender um pouco sobre arduino, mas e depois o que mais fazer?!?!?!?

Que tal um campeonato interno para ver quem faz a melhor lógica para um robo chegar ao final de um labirinto?

Surge então o **#1º TechnoPalooza Arizona**

### Por quê?

Aprender, trocar conhecimento, estudar novas tecnologias e claro, nos divertir muito no processo.

### Desafio?

O Robozona foi construído com um controlador Arduino Uno, utilizando dois motores de corrente contínua, cinco
sensores de distância por ultrassom e dois sensores de proximidade por infravermelho. É movido por bateria de NiCd de
9.6V e 700 mAh de capacidade.

Toda a estrutura do robô, incluindo as rodas, foi projetada em CAD (projeto abaixo) e impressa em 3D com plástico
PLA (foto na sequência).

Os cinco sensores de ultrassom têm cobertura individual de 22.5º para cada lado e estão posicionados da seguinte
forma:

À frente, no eixo longitudinal do robô;
À direita e esquerda, em ângulos de 35º
À direita e esquerda, em ângulos de 70º

![Arizona Robot 3D](http://ivanrosolen.com/arizonaRobot/3D.png "Arizona Robot 3D")

![Arizona Robot 3D](http://ivanrosolen.com/arizonaRobot/Real.png "Arizona Robot 3D")


A ligação dos pinos no Arduino é mostrada abaixo, sendo usados para os sensores de ultrassom os pinos 5, 6, 7, 8 e 9, e para os
sensores de IR os pinos analógicos 0 e 1. O funcionamento dos sensores de ultrassom e IR é descrito nos documento contidos nos
apêndices.

![Arizona Robot 3D](http://ivanrosolen.com/arizonaRobot/Circuito.png "Arizona Robot 3D")

A razão de vida do robô é se movimentar o mais rapidamente possível, sem colidir com obstáculos. Para isso ele utiliza seus 7 sensores e algoritmos que acionam os motores em função do que detecta à sua frente. A princípio, se não houver nenhum obstáculo, ele segue em frente.

O programa C do folder **Exemplo** é um algoritmo básico para movimentação, longe de estar otimizado.

A partir do programa fornecido ou começando do zero, o desafio é fazer o robô sair de um labirinto relativamente simples, no menor tempo possível. Lembrando que os motores só funcionam para a frente e têm inércia, ou seja, não param imediatamente.

### Aonde? Quando?

Será realizado na Arizona dia 04/07/2015 | 10h às 15h


### Referências

Ambiente de programação <https://www.arduino.cc/en/Main/Software>

Download e tutoriais de arduino: <http://arduino.cc/en/Tutorial/HomePage/>

123Design: <http://www.123dapp.com/design-alt>

Exemplos arduino no folder **Exemplo**

Modelo 3D para impressão no folder **3DPrint**

Schematics do robô no folder **Schematics**

PDFs explicando componentes Arduinos utilizados no folder **Referências**


![Arizona](http://ivanrosolen.com/arizonaRobot/logo.png "Arizona")