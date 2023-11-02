
// #include<stdio.h>
// #include<stdlib.h>


int main() {
    int PIRSensor_op;
    int Buzzer = 0;
    int Buzzer_reg;
    int Led = 0  ;
    int Led_reg; // Register for the Led
    int mask1 = 0xFFFFFFF3;
    Buzzer_reg = Buzzer * 4;
    Led_reg = Led * 8;

    asm volatile(
        "and x30, x30, %2\n\t"
        "or x30, x30, %0\n\t"
        "or x30, x30, %1\n\t"
        :
        : "r"(Buzzer_reg), "r"(Led_reg),"r"(mask1)
        : "x30"
    );


        // printf("Initial values are:\n");
        // printf("PIRSensor_op = %d,Buzzer_reg = %d,  Led_reg=%d\n",PIRSensor_op,Buzzer_reg,Led_reg);

//     	int z;
// for(z=0;z<1;z++)

    while (1) 
    {	

            // Simulate activating the buzzer and Led (replace with actual control)
            asm volatile(
                "andi %0, x30, 2\n\t"
                : "=r"(PIRSensor_op)
                :
                :
            );


        // PIRSensor_op=0; // setting the sensor value for spike simulation

        //printf("setting PIRSensor_op value to %d\n",PIRSensor_op);

        if (PIRSensor_op) {
                // Simulate activating the buzzer and Led (replace with actual control)
                // digital_write(Buzzer, 1);
                // digital_write(Led, 0);
                // printf("Buzzer ON and Led are Off\n");
                Buzzer = 1;
                Led = 1;
        

        //printf("intrusion detected since sensor value is 1 \n");

            } else {
                // Simulate deactivating the buzzer and Led (replace with actual control)
                // digital_write(Buzzer, 0);
                // digital_write(Led, 1);
                // printf("Buzzer OFF and Led are ON\n");
                Buzzer = 0;
                Led = 0;

        //printf("intrusion not detected since sensor value is 0 \n");
            }

            // Update the corresponding registers for the buzzer and Led
            Buzzer_reg = Buzzer * 4;
            Led_reg = Led * 8;

            asm volatile(
                "and x30, x30, %2\n\t"
                "or x30, x30, %0\n\t"
                "or x30, x30, %1\n\t"
                :
                : "r"(Buzzer_reg), "r"(Led_reg),"r"(mask1)
                : "x30"
            );
         
    //printf("PIRSensor_op = %d,Buzzer_reg = %d,  Led_reg=%d\n",PIRSensor_op,Buzzer_reg,Led_reg);
    

    }

    return 0;
}

