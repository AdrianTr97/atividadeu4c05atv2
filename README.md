Simulando Sequência de LEDs com Raspberry Pi Pico W no Wokwi

🏗️ Visão Geral

Este projeto demonstra a ativação sequencial de três LEDs utilizando o Raspberry Pi Pico W, com controle via um botão de entrada. O sistema gerencia a ativação e desativação dos LEDs em intervalos de 3 segundos, garantindo que a sequência seja concluída antes de permitir uma nova ativação.

A simulação foi realizada na plataforma Wokwi, proporcionando um ambiente prático para testes de sistemas embarcados.

🔹 Características Principais

Acionamento dos LEDs progressivamente ao pressionar o botão.

Uso da função add_alarm_in_ms() para controlar o tempo de transição entre os estados.

Prevenção de múltiplas ativações simultâneas durante a execução da sequência.

Implementação de debounce por software para garantir leituras corretas do botão.

🔧 Configuração de Hardware

Componentes Utilizados

Microcontrolador: Raspberry Pi Pico W

LEDs: Vermelho, Azul e Verde

Resistores: 330Ω para cada LED

Botão: Aciona a sequência dos LEDs

Ligação dos LEDs ao Pico W

LEDs:

GPIO 11: Vermelho

GPIO 12:Amarelo

GPIO 13:Verde

Botao: GPIO 05

📝 Estrutura do Código

O funcionamento da sequência de LEDs está definido no arquivo atividade2_leds.c, que utiliza a biblioteca Pico SDK para configurar os GPIOs e administrar os temporizadores.

🚀 Como Rodar a Simulação no Wokwi

Acesse o Wokwi e crie um novo projeto com o Raspberry Pi Pico W.

Carregue os arquivos do projeto (atividade2_leds.c, CMakeLists.txt e diagram.json).

Edite o diagram.json para definir os LEDs e suas respectivas conexões.

Compile e inicie a simulação.

Pressione o botão para ativar a sequência e acompanhe a transição dos LEDs.

📂 Estrutura do Projeto

├── atividade2_leds.c   # Código principal em C
├── CMakeLists.txt      # Arquivo de configuração do CMake
├── diagram.json        # Definição dos componentes no Wokwi
├── README.md           # Documentação do projeto

⚠️ Observações

A implementação utiliza um temporizador para garantir a execução da sequência antes de permitir nova ativação.

👤 Autor

Adrian Trajano de A. da S.
