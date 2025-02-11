# Projeto de Controle de Servo Motor e LED com PWM na Raspberry Pi Pico

Este projeto foi desenvolvido para controlar um servo motor e um LED utilizando modulação por largura de pulso (PWM) com a Raspberry Pi Pico. O código foi projetado para ser simulado no Wokwi e executado na Raspberry Pi Pico. O servo motor realiza movimentos suaves entre diferentes ângulos, e o LED tem seu brilho controlado via PWM.
## Video
- https://www.youtube.com/watch?v=aQHommlVUlI
## Requisitos

- **Hardware:**
  - Raspberry Pi Pico
  - Servo Motor
  - LED
  - Fios de conexão

- **Software:**
  - VSCode (para edição do código)
  - Wokwi (para simulação)
  - Ambiente de desenvolvimento para Raspberry Pi Pico configurado com a biblioteca `pico/stdlib.h`

## Descrição do Código

### Configuração do PWM

O código configura dois pinos para PWM:
1. **Servo Motor:** O pino 22 (conectado ao servo) é configurado para gerar um sinal PWM. A frequência de 50Hz é utilizada, comum para a maioria dos servo motores.
2. **LED:** O pino 12 (conectado ao LED) também é configurado para PWM, permitindo controlar o brilho do LED.

### Funções de Controle

- **Função `angulo_servo`:** Define a posição do servo motor, ajustando a largura do pulso PWM de acordo com o ângulo desejado.
- **Função `brilho_led`:** Controla o brilho do LED com base na modulação de PWM.

### Movimentos do Servo

- O servo motor é movido entre três posições fixas (500, 1470, 2400) com um intervalo de 5 segundos para cada posição.
- O código também inclui um movimento suave do servo motor, movendo-o de um ângulo para outro de forma gradual, criando uma transição suave.

### Fluxo do Programa

1. Inicializa o PWM para o servo motor e para o LED.
2. Executa um loop infinito onde o servo motor se move entre os ângulos 500, 1470 e 2400, com um controle de brilho do LED ajustado de acordo com a posição do servo.
3. Utiliza uma transição suave entre os ângulos do servo, gerando movimentos suaves.

## Pinagem

- **Pino 12 (PWM_LED):** Controle de brilho do LED via PWM.
- **Pino 22 (SERVO_PIN):** Controle do servo motor via PWM.

## Como Usar

### 1. Compilar o Código
- Compile o código utilizando o ambiente de desenvolvimento da Raspberry Pi Pico. Se estiver usando VSCode, certifique-se de que as bibliotecas necessárias estão configuradas corretamente.

### 2. Conectar o Hardware
- **Servo Motor:** Conecte o pino de controle do servo ao pino 22 da Raspberry Pi Pico.
- **LED:** Conecte o LED ao pino 12.

### 3. Testar o Código
- Se estiver usando o Wokwi, carregue o código e veja a simulação do servo motor movendo-se entre os ângulos e o brilho do LED sendo ajustado.

### 4. Observação
- A frequência do PWM para o servo motor é definida como 50Hz, o que é adequado para o controle de servos.
- O LED será controlado com PWM, e seu brilho será ajustado conforme o movimento do servo.

