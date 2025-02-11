#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define LED_R 13
#define LED_G 11
#define LED_B 12


int main()
{
    // define a GPIO LED para a função PWM
    gpio_set_function(LED_R, GPIO_FUNC_PWM);
    gpio_set_function(LED_G, GPIO_FUNC_PWM);
    gpio_set_function(LED_B, GPIO_FUNC_PWM);
    
    // cata o slice da GPIO 11, 12 e 13, que no caso é o slice 5 e 6
    uint slice_r = pwm_gpio_to_slice_num(LED_R);
    uint slice_g = pwm_gpio_to_slice_num(LED_G);

    // divide o clock de sistema por 125 para ficarmos com 1 microssegundo para cada incremento do wrap
    pwm_set_clkdiv(slice_r, 125.0);
    pwm_set_clkdiv(slice_g, 125.0);

    // define o wrap para 20000 o que nos deixa com 5 milissegundos de período, ou 200 Hz
    pwm_set_wrap(slice_r, 1000);
    pwm_set_wrap(slice_g, 1000);

    pwm_set_gpio_level(LED_R, 0);
    pwm_set_gpio_level(LED_G, 0);
    pwm_set_gpio_level(LED_B, 0);

    // ativa o PWM
    pwm_set_enabled(slice_r, true);
    pwm_set_enabled(slice_g, true);

    uint16_t fade = 0;

    while (true)
    {   
        while(fade<1000)
        {
            pwm_set_gpio_level(LED_R, fade);
            fade += 5;
            sleep_ms(10);
        }

        while(fade>0)
        {
            pwm_set_gpio_level(LED_R, fade);
            fade -= 5;
            sleep_ms(10);
        }

        while(fade<1000)
        {
            pwm_set_gpio_level(LED_G, fade);
            fade += 5;
            sleep_ms(10);
        }

        while(fade>0)
        {
            pwm_set_gpio_level(LED_G, fade);
            fade -= 5;
            sleep_ms(10);
        }

        while(fade<1000)
        {
            pwm_set_gpio_level(LED_B, fade);
            fade += 5;
            sleep_ms(10);
        }

        while(fade>0)
        {
            pwm_set_gpio_level(LED_B, fade);
            fade -= 5;
            sleep_ms(10);
        }

    }
}
