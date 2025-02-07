#include <stdio.h>               // Biblioteca padrão para entrada e saída
#include "pico/stdlib.h"         // Biblioteca padrão da Raspberry Pi Pico
#include "hardware/pwm.h"        // Biblioteca para controle de PWM (Pulse Width Modulation)

// Definição dos pinos utilizados
#define PWM_LED 12               // Pino do LED (não está sendo utilizado no código)
#define SERVO_PIN 22             // Pino ao qual o servo motor está conectado
#define PWM_FREQ 50              // Frequência do PWM (50Hz, comum para servos)
#define PWM_WRAP 20000           // Valor máximo do contador do PWM (período do sinal)

// Função para definir o ângulo do servo motor
void angulo_servo(uint pin, uint16_t pulse_width) {
    pwm_set_gpio_level(pin, pulse_width);  // Define o nível PWM para ajustar o ângulo do servo
}

// Função para controlar o brilho do LED via PWM
void brilho_led() {
    gpio_put(PWM_LED, 1);
    sleep_ms(500);
    gpio_put(PWM_LED, 0);
    sleep_ms(500);
}

int main()
{
    stdio_init_all();  // Inicializa a entrada/saída padrão (não essencial para este código)
    
    // Configura os pinos para a função PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    gpio_set_function(PWM_LED, GPIO_FUNC_PWM);  // Configuração desnecessária, pois o LED não está sendo controlado
    
    // Obtém o número do slice PWM associado ao pino do servo
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    uint led_slice = pwm_gpio_to_slice_num(PWM_LED);
    
    // Configuração do PWM
    pwm_set_wrap(slice_num, PWM_WRAP);   // Define o valor máximo do contador PWM
    pwm_set_clkdiv(slice_num, 125.0f);   // Define o divisor do clock para ajustar a frequência
    pwm_set_enabled(slice_num, true);    // Habilita o PWM no slice configurado


     // Configuração do PWM para o LED (usa um valor menor de wrap para suavizar o controle)
     pwm_set_wrap(led_slice, 100);      // Define um range menor para melhor controle do brilho
     pwm_set_clkdiv(led_slice, 4.0f);    // Ajusta o divisor do clock para um PWM visível
     pwm_set_enabled(led_slice, true);
 

    gpio_init(PWM_LED);
    gpio_set_dir(PWM_LED, GPIO_OUT);
    
    while (1) {
        // Define diferentes posições do servo motor
        angulo_servo(SERVO_PIN, 2400);  
        brilho_led(PWM_LED, 1000);  
        sleep_ms(5000);                
        
        angulo_servo(SERVO_PIN, 1470);  
        brilho_led(PWM_LED, 1000);  
        sleep_ms(5000);
        
        angulo_servo(SERVO_PIN, 500);   
        brilho_led(PWM_LED, 1000);  
        sleep_ms(5000);
        


// Move o servo do menor para o ângulo de 1470 e ajusta o brilho
for (uint16_t pos = 500; pos <= 1470; pos += 5) {
    angulo_servo(SERVO_PIN, pos);
    brilho_led(PWM_LED, pos);
    sleep_ms(10);  // Pequeno atraso para suavizar o movimento
}

// Move o servo do ângulo de 1470 para o maior ângulo de 2400 e ajusta o brilho
for (uint16_t pos = 1470; pos <= 2400; pos += 5) {
    angulo_servo(SERVO_PIN, pos);
    brilho_led(PWM_LED, pos);
    sleep_ms(10);  // Pequeno atraso para suavizar o movimento
}

// Move o servo de volta para 1470 e ajusta o brilho
for (uint16_t pos = 2400; pos >= 1470; pos -= 5) {
    angulo_servo(SERVO_PIN, pos);
    brilho_led(PWM_LED, pos);
    sleep_ms(10);
}

// Move o servo de volta para o ângulo de 500 e ajusta o brilho
for (uint16_t pos = 1470; pos >= 500; pos -= 5) {
    angulo_servo(SERVO_PIN, pos);
    brilho_led(PWM_LED, pos);
    sleep_ms(10);
}
    }
}
