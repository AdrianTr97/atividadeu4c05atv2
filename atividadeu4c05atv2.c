#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos dos LEDs e do botão
#define LED_PIN_BLUE 11   // Pino do LED Azul
#define LED_PIN_RED 12    // Pino do LED Vermelho
#define LED_PIN_GREEN 13  // Pino do LED Verde
#define BUTTON_PIN 5      // Pino do Botão

// Variáveis globais para controle do ciclo
bool cycle_active = false; // Indica se o ciclo está em execução
int led_state = 0;         // Controla qual LED está sendo desligado

// Callback do temporizador para desligar os LEDs sequencialmente
int64_t led_callback(alarm_id_t id, void *user_data) {
    switch (led_state) {
        case 0:
            gpio_put(LED_PIN_BLUE, 0); // Desliga o LED Azul
            printf("LED Azul desligado\n");
            break;
        case 1:
            gpio_put(LED_PIN_RED, 0); // Desliga o LED Vermelho
            printf("LED Vermelho desligado\n");
            break;
        case 2:
            gpio_put(LED_PIN_GREEN, 0); // Desliga o LED Verde
            printf("LED Verde desligado\n");
            cycle_active = false; // Desativa o ciclo, aguardando nova ativação
            printf("Todos os LEDs desligados. Pressione bot\xc3\xa3o para reiniciar.\n");
            return 0; // Finaliza a sequência
    }
 
    led_state++; // Avança para o próximo estado
    add_alarm_in_ms(3000, led_callback, NULL, false); // Programa o próximo desligamento em 3s
    return 0;
}

// Função para iniciar o ciclo de LEDs
void start_led_one_shot() {
    printf("Iniciando disparo (0ne shot)!\n");
    gpio_put(LED_PIN_BLUE, 1);  // Liga o LED Azul
    gpio_put(LED_PIN_RED, 1);   // Liga o LED Vermelho
    gpio_put(LED_PIN_GREEN, 1); // Liga o LED Verde
    led_state = 0;
    cycle_active = true;
    
    // Inicia o primeiro desligamento após 3 segundos
    add_alarm_in_ms(3000, led_callback, NULL, false);
}

// Configuração dos GPIOs
void config_gpio() {
    // Configura LEDs como saída
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    // Configura botão como entrada com pull-up interno ativado
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
}

int main() {
    stdio_init_all();
    sleep_ms(500); // Pequeno atraso para estabilização
    printf("System init!\n");

    config_gpio(); // Inicializa os GPIOs
    
    // Loop principal
    while (true) {
        if (gpio_get(BUTTON_PIN) == 0 && !cycle_active) { // Verifica se o botão foi pressionado e o ciclo não está ativo
            sleep_ms(50); // Debounce para evitar leituras falsas
            if (gpio_get(BUTTON_PIN) == 0) { // Confirma a pressão do botão após debounce
                start_led_one_shot(); // Inicia um novo ciclo quando o botão for pressionado
            }
        }
        sleep_ms(10); // Pequeno atraso para reduzir consumo de CPU
    }
}
