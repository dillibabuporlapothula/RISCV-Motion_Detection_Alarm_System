void checkForIntrusion();
void delaytime(int);

int main() {
    while (1) {
        checkForIntrusion();
    }
    return 0;
}

void checkForIntrusion() {
    // Output from PIR sensor
    int PIRSensor_op;
    asm volatile(
    "andi %0, x30, 0x01\n\t"
    : "=r"(PIRSensor_op)
    :
    :);
    int Buzzer = 0, Led = 0;
    int Buzzer_reg = Buzzer * 2, Led_reg = Led * 4;
    asm volatile(
        "or x30, x30, %0\n\t"
        "or x30, x30, %1\n\t"
        :
        : "r"(Buzzer_reg), "r"(Led_reg)
        : "x30" // Specify x30 as a clobber
    );
    if (PIRSensor_op == 1) {
        Buzzer = 1;
        Led = 1;
        Buzzer_reg = Buzzer * 2;
        Led_reg = Led * 4;
        asm volatile(
            "or x30, x30, %0\n\t"
            "or x30, x30, %1\n\t"
            :
            : "r"(Buzzer_reg), "r"(Led_reg)
            : "x30" // Specify x30 as a clobber
        );
        // Keep the buzzer on for a certain time
        delaytime(10000);
    } else {
        Buzzer = 0;
        Led = 0;
        Buzzer_reg = Buzzer * 2;
        Led_reg = Led * 4;
        asm volatile(
            "or x30, x30, %0\n\t"
            "or x30, x30, %1\n\t"
            :
            : "r"(Buzzer_reg), "r"(Led_reg)
            : "x30" // Specify x30 as a clobber
        );
        // Check for every 1000 milliseconds
        delaytime(1000);
    }
}

// Delay function
void delaytime(int seconds) {
    int i, j;
    for (i = 0; i < seconds; i++) {
        for (j = 0; j < 1000000; j++) {
        }
    }
}
