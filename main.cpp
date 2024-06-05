/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include <cmath>
#include <cstdio>

#define M_PI  3.14159265358979323846


// Definir el objeto Serial para la comunicación por puerto serial
BufferedSerial pc(USBTX, USBRX);

// Definir el objeto PwmOut para generar la señal seno
PwmOut pwmOut(D6);

char men[20];



// Definir la frecuencia y amplitud de la señal seno
float frequency = 100.0; // Frecuencia en Hz
float amplitude = 0.5;    // Amplitud entre 0.0 y 1.0

int main()
{
    // Configurar la frecuencia de la señal seno
    pwmOut.period(1.0 / frequency);

    while (1) {
        // Generar la señal seno y enviarla por el puerto serial
        for (float i = 0.0; i < 2 * M_PI; i += 0.1) {
            float value = amplitude * sin(i);
            int seno_s = int((value*256)+128);
            sprintf(men, "%03u\n", seno_s);
            pc.write(men, 4);
            pwmOut.write(value);
            ThisThread::sleep_for(500ms);
        }
    }
}