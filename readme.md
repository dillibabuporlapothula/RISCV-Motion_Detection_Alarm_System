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

//#include <stdio.h>
int main()
{
	int PIRSensor_op;
	int Buzzer;
	int Led;
	int mask=0xFFFFFFFE;
	//int i,j;
	
	
	//for(i=0;i<2;i++)
	 while(1)	
	{
          
		asm volatile(
	    	"addi x10, x30, 0\n\t"
		"and %0, x10, 1\n\t"
		:"=r"(PIRSensor_op)
	    	:
	    	:"x30"
	    	);

          asm volatile(
		"addi x10, x30, 0\n\t"
		"and %0, x10, 1\n\t"
		:"=r"(PIRSensor_op) 
		:
                :"x10");
                 
        	
        	//printf("PIRSensor_op is %d\n",PIRSensor_op);
		asm volatile(
			"addi x10, x30, 0\n\t"
			"and %0, x10, 1\n\t"
			:"=r"(PIRSensor_op)
			:
			:"x10"
			);
		  PIRSensor_op=1;
		//printf("PIRSensor_op_objectdetected = %d\n",PIRSensor_op);
				
		
		if(PIRSensor_op)
		{
		 //printf("PIRSensor_op is '1' hence motion detected\n");
		  Led = 1;
		  mask=0xFFFFFFF2;
		  asm volatile(
		      "and x30, x30, %1\n\t"
		      "or x30, x30, %0\n\t"
                      :
		      :"r"(Led),"r"(mask)
		      :"x30"
		      );
		  //printf("Led = %d\n",Led);
		  
		                       
                        Buzzer = 1;
			mask=0xFFFFFFF4;
			asm volatile(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:
			:"r"(Buzzer),"r"(mask)
			:"x30"
			);
	        	//	  printf("Buzzer = %d\n",Buzzer);
		}
		else
		{
		 //printf("PIRSensor_op is '0' hence motion un detected\n");
		  Led = 0;
		   mask=0xFFFFFFF4;
		  asm volatile(
		      "and x30, x30, %1\n\t"
		      "or x30, x30, %0\n\t"
                      :
		      :"r"(Led),"r"(mask)
		      :"x30"
		      );
		      
                  //printf("Led = %d\n",Led); 
                  
                                       
                        Buzzer = 0;
			mask=0xFFFFFFF4;
			asm volatile(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:
			:"r"(Buzzer),"r"(mask)
			:"x30"
			); 
			
	       //printf("Buzzer sounds=%d\n",Buzzer);
		}
	                                                          
			
			}
			
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
   10054:	fe010113          	addi	sp,sp,-32
   10058:	00812e23          	sw	s0,28(sp)
   1005c:	02010413          	addi	s0,sp,32
   10060:	ffe00793          	li	a5,-2
   10064:	fef42623          	sw	a5,-20(s0)
   10068:	000f0513          	mv	a0,t5
   1006c:	00157793          	andi	a5,a0,1
   10070:	fef42423          	sw(a5,-24(s0)
   10074:	000f0513          	mv	a0,t5
   10078:	00157793          	andi	a5,a0,1
   1007c:	fef42423          	sw(a5,-24(s0)
   10080:	000f0513          	mv(a0,t5)
   10084:	00157793          	andi(a5,a0,1)
   10088:	fef42423          	sw(a5,-24(s0)
   1008c:	00100793          	li(a5,1)
   10090:	fef42423          	sw(a5,-24(s0)
   10094:	fe842783          	lw(a5,-24(s0)
   10098:	04078463          	beqz(a5,100e0 <main+0x8c>
   1009c:	00100793          	li(a5,1)
   100a0:	fef42223          	sw(a5,-28(s0)
   100a4:	ff200793          	li(a5,-14)
   100a8:	fef42623          	sw(a5,-20(s0)
   100ac:	fe442783          	lw(a5,-28(s0)
   100b0:	fec42703          	lw(a4,-20(s0)
   100b4:	00ef7f33          	and(t5,t5,a4)
   100b8:	00ff6f33          	or(t5,t5,a5)
   100bc:	00100793          	li(a5,1)
   100c0:	fef42023          	sw(a5,-32(s0)
   100c4:	ff400793          	li(a5,-12)
   100c8:	fef42623          	sw(a5,-20(s0)
   100cc:	fe042783          	lw(a5,-32(s0)
   100d0:	fec42703          	lw(a4,-20(s0)
   100d4:	00ef7f33          	and(t5,t5,a4)
   100d8:	00ff6f33          	or(t5,t5,a5)
   100dc:	f8dff06f          	j(10068 <main+0x14>
   100e0:	fe042223          	sw(zero,-28(s0)
   100e4:	ff400793          	li(a5,-12)
   100e8:	fef42623          	sw(a5,-20(s0)
   100ec:	fe442783          	lw(a5,-28(s0)
   100f0:	fec42703          	lw(a4,-20(s0)
   100f4:	00ef7f33          	and(t5,t5,a4)
   100f8:	00ff6f33          	or(t5,t5,a5)
   100fc:	fe042023          	sw(zero,-32(s0)
   10100:	ff400793          	li(a5,-12)
   10104:	fef42623          	sw(a5,-20(s0)
   10108:	fe042783          	lw(a5,-32(s0)
   1010c:	fec42703          	lw(a4,-20(s0)
   10110:	00ef7f33          	and(t5,t5,a4)
   10114:	00ff6f33          	or(t5,t5,a5)
   10118:	f51ff06f          	j(10068 <main+0x14>


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

li
lw
sw
j
andi
addi
and
beqz
or
mv

```

## Spike simulation

Here i modified the values to force the inputs for various test cases and observe the spice simulations.









