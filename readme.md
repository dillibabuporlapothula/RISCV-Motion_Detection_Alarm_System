## AIM

In this project, we are going to make a __motion detection security alarm__. It can detect the motion of an intruder with help of a PIR Sensor.The main objective is that it focuses on detection of motion 
without any external touch. The passive infrared sensor detects the IR radiations emitted from humans within its range and it sends the signal to processor then the led glows amd then it triggers buzzer ,hence motion is detected.

## Working

Our project is based on the idea that every body generates heat energy in the form of infrared rays which are not visible to human naked eye,but can be detected using PIR Sensor.The electronic motion sensor detects the motion within its range that is around five metres of an unusual motion. The PIR sensor detects the motion of an intruder whenever an motion is within its range. As it detects the infrared rays emitted by a body,then it sends the signal to RISC V processor which triggers the buzzer until it is powered off. One need to activate the system before they go to sleep or going outside.
So activate signal need to be given by user.

# Image representation

![Screenshot (221)](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/3063ea9d-28da-4f43-bb28-6604c16d0793)


## Block Diagram

![Screenshot (222)](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/2aaf20a5-8298-4318-9a00-a74fb759baef)


# C Program

## Tested with sample sensor values

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

```c

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


        PIRSensor_op=0; // setting the sensor value for spike simulation

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


```

## Assembly code

To get the assembly instructions from c code execute below instructions using riscv32-toolchain 

```bash

riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o motion_detection_alarm  motion_detection_alarm.c
riscv64-unknown-elf-objdump -d -r motion_detection_alarm > sample_assembly.txt

```




```assembly

motion_detection_alarm: file format elf32-littleriscv
Disassembly of section .text:

00010054 <main>:
   10054:	fd010113           addi sp,sp,-48
   10058:	02812623           sw s0,44(sp)
   1005c:	03010413           addi s0,sp,48
   10060:	fe042623           sw zero,-20(s0)
   10064:	fe042423           sw zero,-24(s0)
   10068:	ff300793           li a5,-13
   1006c:	fef42223           sw a5,-28(s0)
   10070:	fec42783           lw a5,-20(s0)
   10074:	00279793           slli a5,a5,0x2
   10078:	fef42023           sw a5,-32(s0)
   1007c:	fe842783           lw a5,-24(s0)
   10080:	00379793           slli a5,a5,0x3
   10084:	fcf42e23           sw a5,-36(s0)
   10088:	fe042783           lw a5,-32(s0)
   1008c:	fdc42703           lw a4,-36(s0)
   10090:	fe442683           lw a3,-28(s0)
   10094:	00df7f33           and t5,t5,a3
   10098:	00ff6f33           or t5,t5,a5
   1009c:	00ef6f33           or t5,t5,a4
   100a0:	002f7793           andi a5,t5,2
   100a4:	fcf42c23           sw a5,-40(s0)
   100a8:	fc042c23           sw zero,-40(s0)
   100ac:	fd842783           lw a5,-40(s0)
   100b0:	00078c63           beqz a5,100c8 <main+0x74>
   100b4:	00100793           li a5,1
   100b8:	fef42623           sw a5,-20(s0)
   100bc:	00100793           li a5,1
   100c0:	fef42423           sw a5,-24(s0)
   100c4:	00c0006f           j 100d0 <main+0x7c>
   100c8:	fe042623           sw zero,-20(s0)
   100cc:	fe042423           sw zero,-24(s0)
   100d0:	fec42783           lw a5,-20(s0)
   100d4:	00279793           slli a5,a5,0x2
   100d8:	fef42023           sw a5,-32(s0)
   100dc:	fe842783           lw a5,-24(s0)
   100e0:	00379793           slli a5,a5,0x3
   100e4:	fcf42e23           sw a5,-36(s0)
   100e8:	fe042783           lw a5,-32(s0)
   100ec:	fdc42703           lw a4,-36(s0)
   100f0:	fe442683           lw a3,-28(s0)
   100f4:	00df7f33           and t5,t5,a3
   100f8:	00ff6f33           or t5,t5,a5
   100fc:	00ef6f33           or t5,t5,a4
   10100:	fa1ff06f           j 100a0 <main+0x4c>



```

 
# Unique instructions


To get the unique instructions execute below command which uses python script.

```
python3 instruction_counter.py
```


unique instructions are :

```assembly


Number of different instructions: 10

List of unique instructions:

or
beqz
addi
sw
lw
slli
andi
and
li
j


```

## Spike simulation

Here i modified the values to force the inputs for various test cases and observe the spice simulations.

### C code for Spike simulation 

```c

#include<stdio.h>
#include<stdlib.h>


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


        printf("Initial values are:\n");
        printf("PIRSensor_op = %d,Buzzer_reg = %d,  Led_reg=%d\n",PIRSensor_op,Buzzer_reg,Led_reg);

    	int z;
for(z=0;z<1;z++)
    //while (1) 
    {	

            // Simulate activating the buzzer and Led (replace with actual control)
            asm volatile(
                "andi %0, x30, 2\n\t"
                : "=r"(PIRSensor_op)
                :
                :
            );


        PIRSensor_op=0; // setting the sensor value for spike simulation

        printf("setting PIRSensor_op value to %d\n",PIRSensor_op);

        if (PIRSensor_op) {
                // Simulate activating the buzzer and Led (replace with actual control)
                // digital_write(Buzzer, 1);
                // digital_write(Led, 0);
                // printf("Buzzer ON and Led are Off\n");
                Buzzer = 1;
                Led = 1;
        

        printf("intrusion detected since sensor value is 1 \n");

            } else {
                // Simulate deactivating the buzzer and Led (replace with actual control)
                // digital_write(Buzzer, 0);
                // digital_write(Led, 1);
                // printf("Buzzer OFF and Led are ON\n");
                Buzzer = 0;
                Led = 0;

        printf("intrusion not detected since sensor value is 0 \n");
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
         
    printf("PIRSensor_op = %d,Buzzer_reg = %d,  Led_reg=%d\n",PIRSensor_op,Buzzer_reg,Led_reg);
    

    }

    return 0;
}



```


## Spike output 

commands used to execute spike are as below 

```linux

riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-linux-ubuntu14/bin/riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o out Home-alarm.c

riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-linux-ubuntu14/bin/spike pk out

```

- Initially all the register values will be zero and If i give PIR sensor value is 0 that means no intrusion is detected and buzzer and LED will be zero and they will be turned off. 


	![sensor0](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/75ee0448-3679-466e-affc-c3e0b7abaa51)



- Similarly If i give PIR sensor value is 1 that means intrusion is detected and buzzer and LED will be 1, buzzer_reg will be 4 and Led_reg will be 8 and they will turned on. 
		       

	![sensor1](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/8a0307e0-b9fb-47ab-ad11-2428d0100e1e)




## Functional Verification



![VirtualBox_ubuntu-VLSI_31_10_2023_00_34_57](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/bfa23822-606e-4df8-93b9-8fb49ebf06eb)







![VirtualBox_ubuntu-VLSI_31_10_2023_00_37_41](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/e6888090-f38f-4871-9d4a-cb7642ad36b5)



