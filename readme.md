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


```

## Assembly code

To get the assembly instructions from c code execute below instructions using riscv32-toolchain 

```bash

riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o motion_detection_alarm  motion_detection_alarm.c
riscv64-unknown-elf-objdump -d -r motion_detection_alarm > sample_assembly.txt

```




```assembly

motion_detection_alarm:     file format elf32-littleriscv
Disassembly of section .text:
00010054 <main>:
   10054:	fd010113          	addi	sp,sp,-48
   10058:	02812623          	sw	s0,44(sp)
   1005c:	03010413          	addi	s0,sp,48
   10060:	fe042623          	sw	zero,-20(s0)
   10064:	fe042423          	sw	zero,-24(s0)
   10068:	ff300793          	li	a5,-13
   1006c:	fef42223          	sw	a5,-28(s0)
   10070:	fec42783          	lw	a5,-20(s0)
   10074:	00279793          	slli	a5,a5,0x2
   10078:	fef42023          	sw	a5,-32(s0)
   1007c:	fe842783          	lw	a5,-24(s0)
   10080:	00379793          	slli	a5,a5,0x3
   10084:	fcf42e23          	sw	a5,-36(s0)
   10088:	fe042783          	lw	a5,-32(s0)
   1008c:	fdc42703          	lw	a4,-36(s0)
   10090:	fe442683          	lw	a3,-28(s0)
   10094:	00df7f33          	and	t5,t5,a3
   10098:	00ff6f33          	or	t5,t5,a5
   1009c:	00ef6f33          	or	t5,t5,a4
   100a0:	002f7793          	andi	a5,t5,2
   100a4:	fcf42c23          	sw	a5,-40(s0)
   100a8:	fd842783          	lw	a5,-40(s0)
   100ac:	00078c63          	beqz	a5,100c4 <main+0x70>
   100b0:	00100793          	li	a5,1
   100b4:	fef42623          	sw	a5,-20(s0)
   100b8:	00100793          	li	a5,1
   100bc:	fef42423          	sw	a5,-24(s0)
   100c0:	00c0006f          	j	100cc <main+0x78>
   100c4:	fe042623          	sw	zero,-20(s0)
   100c8:	fe042423          	sw	zero,-24(s0)
   100cc:	fec42783          	lw	a5,-20(s0)
   100d0:	00279793          	slli	a5,a5,0x2
   100d4:	fef42023          	sw	a5,-32(s0)
   100d8:	fe842783          	lw	a5,-24(s0)
   100dc:	00379793          	slli	a5,a5,0x3
   100e0:	fcf42e23          	sw	a5,-36(s0)
   100e4:	fe042783          	lw	a5,-32(s0)
   100e8:	fdc42703          	lw	a4,-36(s0)
   100ec:	fe442683          	lw	a3,-28(s0)
   100f0:	00df7f33          	and	t5,t5,a3
   100f4:	00ff6f33          	or	t5,t5,a5
   100f8:	00ef6f33          	or	t5,t5,a4
   100fc:	fa5ff06f          	j	100a0 <main+0x4c>




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
lw
sw
slli
addi
li
beqz
andi
and
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


- If input is zero there is no motion and buzzer,LED will be off and output will be 00. When ever PIR sensor detects motion and input is high the output buzzer and LED will turn on and we can see output going to 11 state from below waveforms.

   ![Screenshot (268)](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/6e30db77-ea85-4eac-8a3e-54a23bf715d4)


- For ```input 0``` case


   ![Screenshot (276)](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/a1a18f9c-6d3d-44c0-9f9e-410a14d54c85)


- For ```input 1``` case
  
  ![Screenshot (275)](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/587e1074-ec43-4993-b1fc-bb5efa6cb349)


  we can see that output is changing from 00 -> 01 -> staying at 11 -> 10 -> back to 00 . the small glitches 01 and 10 are because of masking being performed.





### Instruction verification



![Screenshot (277)](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/fbeccf39-1a71-4149-b089-590c43acb912)





![Screenshot (278)](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/2f26ff6c-5f26-4a47-8989-78644c65b5b6)






