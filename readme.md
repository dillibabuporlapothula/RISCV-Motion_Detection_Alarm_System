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

```

## Assembly code

To get the assembly instructions from c code execute below instructions using riscv32-toolchain 

```bash

riscv32-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o motion_detection_alarm  motion_detection_alarm.c
riscv32-unknown-elf-objdump -d -r motion_detection_alarm > sample_assembly.txt

```




```assembly

motion_detection_alarm:     file format elf32-littleriscv
Disassembly of section .text:
00010054 <main>:
   10054:	ff010113          	addi	sp,sp,-16
   10058:	00112623          	sw	ra,12(sp)
   1005c:	00812423          	sw	s0,8(sp)
   10060:	01010413          	addi	s0,sp,16
   10064:	008000ef          	jal	ra,1006c <checkForIntrusion>
   10068:	ffdff06f          	j	10064 <main+0x10>
0001006c <checkForIntrusion>:
   1006c:	fd010113          	addi	sp,sp,-48
   10070:	02112623          	sw	ra,44(sp)
   10074:	02812423          	sw	s0,40(sp)
   10078:	03010413          	addi	s0,sp,48
   1007c:	001f7793          	andi	a5,t5,1
   10080:	fef42623          	sw	a5,-20(s0)
   10084:	fe042423          	sw	zero,-24(s0)
   10088:	fe042223          	sw	zero,-28(s0)
   1008c:	fe842783          	lw	a5,-24(s0)
   10090:	00179793          	slli	a5,a5,0x1
   10094:	fef42023          	sw	a5,-32(s0)
   10098:	fe442783          	lw	a5,-28(s0)
   1009c:	00279793          	slli	a5,a5,0x2
   100a0:	fcf42e23          	sw	a5,-36(s0)
   100a4:	fe042783          	lw	a5,-32(s0)
   100a8:	fdc42703          	lw	a4,-36(s0)
   100ac:	00ff6f33          	or	t5,t5,a5
   100b0:	00ef6f33          	or	t5,t5,a4
   100b4:	fec42703          	lw	a4,-20(s0)
   100b8:	00100793          	li	a5,1
   100bc:	04f71663          	bne	a4,a5,10108 <checkForIntrusion+0x9c>
   100c0:	00100793          	li	a5,1
   100c4:	fef42423          	sw	a5,-24(s0)
   100c8:	00100793          	li	a5,1
   100cc:	fef42223          	sw	a5,-28(s0)
   100d0:	fe842783          	lw	a5,-24(s0)
   100d4:	00179793          	slli	a5,a5,0x1
   100d8:	fef42023          	sw	a5,-32(s0)
   100dc:	fe442783          	lw	a5,-28(s0)
   100e0:	00279793          	slli	a5,a5,0x2
   100e4:	fcf42e23          	sw	a5,-36(s0)
   100e8:	fe042783          	lw	a5,-32(s0)
   100ec:	fdc42703          	lw	a4,-36(s0)
   100f0:	00ff6f33          	or	t5,t5,a5
   100f4:	00ef6f33          	or	t5,t5,a4
   100f8:	000027b7          	lui	a5,0x2
   100fc:	71078513          	addi	a0,a5,1808 # 2710 <main-0xd944>
   10100:	054000ef          	jal	ra,10154 <delaytime>
   10104:	03c0006f          	j	10140 <checkForIntrusion+0xd4>
   10108:	fe042423          	sw	zero,-24(s0)
   1010c:	fe042223          	sw	zero,-28(s0)
   10110:	fe842783          	lw	a5,-24(s0)
   10114:	00179793          	slli	a5,a5,0x1
   10118:	fef42023          	sw	a5,-32(s0)
   1011c:	fe442783          	lw	a5,-28(s0)
   10120:	00279793          	slli	a5,a5,0x2
   10124:	fcf42e23          	sw	a5,-36(s0)
   10128:	fe042783          	lw	a5,-32(s0)
   1012c:	fdc42703          	lw	a4,-36(s0)
   10130:	00ff6f33          	or	t5,t5,a5
   10134:	00ef6f33          	or	t5,t5,a4
   10138:	3e800513          	li	a0,1000
   1013c:	018000ef          	jal	ra,10154 <delaytime>
   10140:	00000013          	nop
   10144:	02c12083          	lw	ra,44(sp)
   10148:	02812403          	lw	s0,40(sp)
   1014c:	03010113          	addi	sp,sp,48
   10150:	00008067          	ret
00010154 <delaytime>:
   10154:	fd010113          	addi	sp,sp,-48
   10158:	02812623          	sw	s0,44(sp)
   1015c:	03010413          	addi	s0,sp,48
   10160:	fca42e23          	sw	a0,-36(s0)
   10164:	fe042623          	sw	zero,-20(s0)
   10168:	0340006f          	j	1019c <delaytime+0x48>
   1016c:	fe042423          	sw	zero,-24(s0)
   10170:	0100006f          	j	10180 <delaytime+0x2c>
   10174:	fe842783          	lw	a5,-24(s0)
   10178:	00178793          	addi	a5,a5,1
   1017c:	fef42423          	sw	a5,-24(s0)
   10180:	fe842703          	lw	a4,-24(s0)
   10184:	000f47b7          	lui	a5,0xf4
   10188:	23f78793          	addi	a5,a5,575 # f423f <__global_pointer$+0xe2887>
   1018c:	fee7d4e3          	bge	a5,a4,10174 <delaytime+0x20>
   10190:	fec42783          	lw	a5,-20(s0)
   10194:	00178793          	addi	a5,a5,1
   10198:	fef42623          	sw	a5,-20(s0)
   1019c:	fec42703          	lw	a4,-20(s0)
   101a0:	fdc42783          	lw	a5,-36(s0)
   101a4:	fcf744e3          	blt	a4,a5,1016c <delaytime+0x18>
   101a8:	00000013          	nop
   101ac:	02c12403          	lw	s0,44(sp)
   101b0:	03010113          	addi	sp,sp,48
   101b4:	00008067          	ret


```

 
# Unique instructions


To get the unique instructions execute below command which uses python script.

```
python3 instruction_counter.py
```


unique instructions are :

```assembly

Number of different instructions: 15
List of unique instructions:

blt
li
lw
ret
addi
bne
nop
lui
sw
slli
jal
andi
bge
j
or


```









