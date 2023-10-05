void checkForIntrusion();

void delaytime(int);



int main() {

    while (1) {

        checkForIntrusion();

    }

    return 0;

}


// this function checks for PIR sensor value and activates buzzer

void checkForIntrusion() {

 
    // Replace these variables with actual sensor pins and setup

    // Replace with the actual GPIO pin connected to PIR sensor and buzzer output

    int PIRSensorPin; 

    int BuzzerOutput=0; // initially buzzer will be off

    int LedOutput =0;

    int Led_reg;

    int Buzzer_reg;

    
    //read PIR sensor value

    asm(

	"andi %0, x30, 1\n\t"

	:"=r"(PIRSensorPin));


    asm(

	"or x30, x30, %0\n\t" 

	:"=r"(Buzzer_reg));

	
     asm(

	"or x30, x30, %0\n\t" 

	:"=r"(Led_reg));	


    while (1) {

        if (PIRSensorPin==1) {

	   // Intrusion activate the buzzer and Led
            //digitalWrite(buzzerPin, 1);

            //printf("Buzzer is ON\n");

            BuzzerOutput = 1;

            Buzzer_reg = BuzzerOutput*2;

            
            //writing to buzzer register

            asm(

		"or x30, x30, %0\n\t" 

		:"=r"(Buzzer_reg));


            LedOutput = 1;

            Led_reg = LedOutput*2;

            //writing to Led register

            asm(

		"or x30, x30, %0\n\t" 

		:"=r"(Led_reg));


	    delaytime(10000); // keep the buzzer on for 10000 milliseconds before turning off . can be changed based on need

        } else {

            //No intrusion detected deactivate the buzzer and Led 

            //digitalWrite(buzzerPin, 0);

            //printf("Buzzer is OFF\n");

            BuzzerOutput = 0;

            Buzzer_reg = BuzzerOutput*2;

            asm(

		"or x30, x30, %0\n\t" 

		:"=r"(Buzzer_reg));


            LedOutput = 0;

            Led_reg = LedOutput*2;

            asm(

		"or x30, x30, %0\n\t" 

		:"=r"(Led_reg));


            delaytime(2000); // checking every 2000  milli seconds  



        }

    }

}





//delay function

void delaytime(int seconds) {

    int i, j;

    for (i = 0; i < seconds; i++) {

        for (j = 0; j < 1000000; j++) {

            // Adding a loop inside to approximate seconds

        }

    }

}





