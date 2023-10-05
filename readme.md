## AIM

In this project, we are going to make a __motion detection security alarm__. It can detect the motion of an intruder with help of a PIR Sensor.The main objective is that it focuses on detection of motion 
without any external touch. The passive infrared sensor detects the IR radiations emitted from humans within its range and it sends the signal to processor then the led glows amd then it triggers buzzer ,hence motion is detected.

## Working

Our project is based on the idea that every body generates heat energy in the form of infrared rays which are not visible to human naked eye,but can be detected using PIR Sensor.The electronic motion sensor detects the motion within its range that is around five metres of an unusual motion. The PIR sensor detects the motion of an intruder whenever an motion is within its range. As it detects the infrared rays emitted by a body,then it sends the signal to RISC V processor which triggers the buzzer until it is powered off. One need to activate the system before they go to sleep or going outside.
So activate signal need to be given by user.

# Image representation

![Screenshot (221)](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/3063ea9d-28da-4f43-bb28-6604c16d0793)


## Block Diagram


![Untitled Diagram drawio (3)](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/4df6bcca-b413-42e0-907f-fc4a6d24dae7)

# C Program

## Tested with sample values

executed below commands

```
gcc .c
./a.out
```

- For sensor output '0'.

  ![VirtualBox_ubuntu-VLSI_05_10_2023_17_44_06](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/40ef93af-a663-4d4c-a751-21d0dd31298d)
  

- For sensor output '1'.

  
  ![VirtualBox_ubuntu-VLSI_05_10_2023_17_44_32](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/2eca9d64-f332-4610-be92-339394146770)


# C code 

```

void checkForIntrusion();
void delaytime(int);


int main() {

    while (1) {
        checkForIntrusion();
    }

    return 0;

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


// this function checks for PIR sensor value and activates buzzer

void checkForIntrusion() {

    // Replace these variables with actual sensor pins and setup

    // Replace with the actual GPIO pin connected to PIR sensor and buzzer output

    int PIRSensorPin; 

    int BuzzerOutput=0; // initially buzzer will be off

    int LedOutput =0;

    int Led_reg;

    int Buzzer_reg;

    Buzzer_reg = BuzzerOutput*2;


    asm(

	"or x30, x30, %0\n\t" 

	:"=r"(Buzzer_reg));


     asm(

	"or x30, x30, %0\n\t" 

	:"=r"(Led_reg));	


    asm(

	"andi %0, x30, 1\n\t"

	:"=r"(PIRSensorPin));

    
    while (1) {

        if (PIRSensorPin) {

	   // Intrusion activate the buzzer and Led

            //digitalWrite(buzzerPin, 1);

            //printf("Buzzer is ON\n");

            BuzzerOutput = 1;

            Buzzer_reg = BuzzerOutput*2;

            asm(

		"or x30, x30, %0\n\t" 

		:"=r"(Buzzer_reg));


            LedOutput = 1;

            Led_reg = LedOutput*2;

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

```


  







