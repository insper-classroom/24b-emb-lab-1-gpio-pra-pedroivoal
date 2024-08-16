#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int LED_PIN = 2;
const int CLOCKWISE_BTN_PIN = 3; // RED
const int COUNTERCLOCKWISE_BTN_PIN = 4; // GREEN

const int MOTOR_PIN_1 = 13;
const int MOTOR_PIN_2 = 12;
const int MOTOR_PIN_3 = 11;
const int MOTOR_PIN_4 = 10;

const int clockwise_step_sequence[4][4] = {
    {0, 0, 0, 1},
    {0, 0, 1, 0},
    {0, 1, 0, 0},
    {1, 0, 0, 0},
};

const int counterclockwise_step_sequence[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1},
};

void motor_28BYJ_48(int step, const int step_sequence[4][4]);
void my_init();

int main()
{
    stdio_init_all();
    my_init();

    while (true)
    {
        if (!gpio_get(CLOCKWISE_BTN_PIN))
        {
            while (!gpio_get(CLOCKWISE_BTN_PIN)){}
            gpio_put(LED_PIN, 1);
            motor_28BYJ_48(2048, clockwise_step_sequence);
            gpio_put(LED_PIN, 0);
        }

        if (!gpio_get(COUNTERCLOCKWISE_BTN_PIN))
        {
            while (!gpio_get(COUNTERCLOCKWISE_BTN_PIN)){}
            gpio_put(LED_PIN, 1);
            motor_28BYJ_48(2048, counterclockwise_step_sequence);
            gpio_put(LED_PIN, 0);
        }
    }
}

void motor_28BYJ_48(int steps_number, const int step_sequence[4][4])
{
    for (int i = 0; i < steps_number; i++)
    {

        if (!gpio_get(COUNTERCLOCKWISE_BTN_PIN))
        {
            if (step_sequence[0][0] == 1)
            {
                while (!gpio_get(COUNTERCLOCKWISE_BTN_PIN)){}
                break;
            }
        } 
        else if (!gpio_get(CLOCKWISE_BTN_PIN))
        {
            if (step_sequence[0][0] == 0)
            {
                while (!gpio_get(CLOCKWISE_BTN_PIN)){}
                break;
            }
        }

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

    gpio_init(CLOCKWISE_BTN_PIN);
    gpio_set_dir(CLOCKWISE_BTN_PIN, GPIO_IN);
    gpio_pull_up(CLOCKWISE_BTN_PIN);

    gpio_init(COUNTERCLOCKWISE_BTN_PIN);
    gpio_set_dir(COUNTERCLOCKWISE_BTN_PIN, GPIO_IN);
    gpio_pull_up(COUNTERCLOCKWISE_BTN_PIN);
}
