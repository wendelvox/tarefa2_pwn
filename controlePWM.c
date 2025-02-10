#include <stdio.h>               // Biblioteca padrão para entrada e saída
#include "pico/stdlib.h"         // Biblioteca padrão da Raspberry Pi Pico
#include "hardware/pwm.h"        // Biblioteca para controle de PWM (Pulse Width Modulation)

// Definição dos pinos utilizados
#define LED_GPIO  12               // Pino do LED (não está sendo utilizado no código)
#define SERVO_PIN 22             // Pino ao qual o servo motor está conectado
#define PWM_FREQ 50              // Frequência do PWM (50Hz, comum para servos)
#define PWM_WRAP 20000           // Valor máximo do contador do PWM (período do sinal)


//Setup PWM
void pwm_setup(uint gpio, uint16_t pulse_width) {
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    uint wrap_value = PWM_WRAP; // Definindo manualmente para 50Hz, 20ms de período
    uint16_t level = (pulse_width * wrap_value) / 20000; // Convertendo para escala de 20ms
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), level);
}

// Função para definir o ângulo do servo motor
void angulo_servo(uint pin, uint16_t pulse_width) {
    pwm_set_gpio_level(pin, pulse_width);  // Define o nível PWM para ajustar o ângulo do servo
}

// Função para controlar o brilho do LED via PWM
void brilho_led(uint16_t pulse_width) {
    uint slice_num = pwm_gpio_to_slice_num(LED_GPIO );
    uint wrap_value = PWM_WRAP;
    uint16_t level = (pulse_width * wrap_value) / 20000; // Normalizando brilho baseado no servo
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(LED_GPIO ), level);
}

int main()
{
    stdio_init_all();  // Inicializa a entrada/saída padrão (não essencial para este código)
    
    // Configura os pinos para a função PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    gpio_set_function(LED_GPIO , GPIO_FUNC_PWM);  // Configuração desnecessária, pois o LED não está sendo controlado
    
    // Obtém o número do slice PWM associado ao pino do servo
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    uint led_slice = pwm_gpio_to_slice_num(LED_GPIO );
    
    // Configuração do PWM
    pwm_set_wrap(slice_num, PWM_WRAP);   // Define o valor máximo do contador PWM
    pwm_set_clkdiv(slice_num, 125.0f);   // Define o divisor do clock para ajustar a frequência
    pwm_set_enabled(slice_num, true);    // Habilita o PWM no slice configurado


     // Configuração do PWM para o LED (usa um valor menor de wrap para suavizar o controle)
     pwm_set_wrap(led_slice, PWM_WRAP);      // Define um range menor para melhor controle do brilho
     pwm_set_clkdiv(led_slice, 125.0f);    // Ajusta o divisor do clock para um PWM visível
     pwm_set_enabled(led_slice, true);
 

    
    while (1) {
      
     
        // Posição 180 graus
        pwm_setup(SERVO_PIN, 2400);
        brilho_led(2400);
        sleep_ms(5000);
        
       
        // Posição 90 graus
        pwm_setup(SERVO_PIN, 1470);
        brilho_led(1470);
        sleep_ms(5000);
        
        // Posição 0 graus
        pwm_setup(SERVO_PIN, 500);
        brilho_led(500);
        sleep_ms(5000);
        
    
        // Movimento suave entre 0 e 180 graus
        for (uint16_t pos = 500; pos <= 2400; pos += 5) {
            pwm_setup(SERVO_PIN, pos);
            brilho_led(pos);
            sleep_ms(10);
        }
        for (uint16_t pos = 2400; pos >= 500; pos -= 5) {
            pwm_setup(SERVO_PIN, pos);
            brilho_led(pos);
            sleep_ms(10);
        }
    }
}
