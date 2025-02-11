#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define MOTOR 22

int main()
{
    // define a GPIO MOTOR para a função PWM
    gpio_set_function(MOTOR, GPIO_FUNC_PWM);
    // cata o slice da GPIO 22, que no caso é o slice 3
    uint slice = pwm_gpio_to_slice_num(MOTOR);
    // divide o clock de sistema por 150 para ficarmos com 1 microssegundo para cada incremento do wrap
    pwm_set_clkdiv(slice, 125.0);
    // define o wrap para 20000 o que nos deixa com 20 milissegundos de período, ou 50 Hz
    pwm_set_wrap(slice, 20000);
    // ativa o PWM
    pwm_set_enabled(slice, true);     

    // usamos essa função para não nos preocuparmos com o canal do slice, que nesse caso é o A
    pwm_set_gpio_level(MOTOR, 2400); // 180 graus
    sleep_ms(5000);
    pwm_set_gpio_level(MOTOR, 1470); // 90 graus
    sleep_ms(5000);
    pwm_set_gpio_level(MOTOR, 500); // 0 graus
    sleep_ms(5000);

    // variável que controlará o variação do motor de 0 até 180 graus, começando de onde parou   
    uint16_t fade = 500;

    while (true) {

        // esse while controla a descida do braço do motor
        while(fade != 2400)
        {
            pwm_set_gpio_level(MOTOR, fade);
            fade += 5;
            sleep_ms(10);
        }
        
        // já esse controla a subida
        while(fade != 500)
        {
            pwm_set_gpio_level(MOTOR, fade);
            fade -= 5;
            sleep_ms(10);
        }

    }
}
