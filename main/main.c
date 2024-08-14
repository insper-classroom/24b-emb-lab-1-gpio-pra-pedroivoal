#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int LED_PIN = 2;
const int BTN_PIN = 3;

const int MOTOR_PIN_1 = 13;
const int MOTOR_PIN_2 = 12;
const int MOTOR_PIN_3 = 11;
const int MOTOR_PIN_4 = 10;

const int step_sequence[8][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1},
};

void motor_28BYJ_48(int step);
void my_init();

int main()
{
    stdio_init_all();
    my_init();

    while (true)
    {
        if (!gpio_get(BTN_PIN))
        {
            gpio_put(LED_PIN, 1);
            double graus = 360;
            motor_28BYJ_48(graus/360 * 2048);
            gpio_put(LED_PIN, 0);
        }
        while (gpio_get(BTN_PIN)){}
    }
}

void motor_28BYJ_48(int step)
{
    for (int i = 0; i < step; i++)
    {
        gpio_put(MOTOR_PIN_1, step_sequence[i%4][0]);
        gpio_put(MOTOR_PIN_2, step_sequence[i%4][1]);
        gpio_put(MOTOR_PIN_3, step_sequence[i%4][2]);
        gpio_put(MOTOR_PIN_4, step_sequence[i%4][3]);
        sleep_ms(10);
    }
}

void my_init()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(MOTOR_PIN_1);
    gpio_set_dir(MOTOR_PIN_1, GPIO_OUT);
    gpio_init(MOTOR_PIN_2);
    gpio_set_dir(MOTOR_PIN_2, GPIO_OUT);
    gpio_init(MOTOR_PIN_3);
    gpio_set_dir(MOTOR_PIN_3, GPIO_OUT);
    gpio_init(MOTOR_PIN_4);
    gpio_set_dir(MOTOR_PIN_4, GPIO_OUT);

    gpio_init(BTN_PIN);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_pull_up(BTN_PIN);
}
