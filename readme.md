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

```

/home/dilli/riscv32-toolchain/bin/riscv32-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o motion_detection_alarm  motion_detection_alarm.c
/home/dilli/riscv32-toolchain/bin/riscv32-unknown-elf-objdump -d -r motion_detection_alarm > sample_assembly.txt

```




```assembly
motion_detection_alarm:     file format elf32-littleriscv
Disassembly of section .text:

00010074 <main>:
   10074:	ff010113          	add	sp,sp,-16
   10078:	00112623          	sw	ra,12(sp)
   1007c:	00812423          	sw	s0,8(sp)
   10080:	01010413          	add	s0,sp,16
   10084:	008000ef          	jal	1008c <checkForIntrusion>
   10088:	ffdff06f          	j	10084 <main+0x10>

0001008c <checkForIntrusion>:
   1008c:	fd010113          	add	sp,sp,-48
   10090:	02112623          	sw	ra,44(sp)
   10094:	02812423          	sw	s0,40(sp)
   10098:	03010413          	add	s0,sp,48
   1009c:	001f7793          	and	a5,t5,1
   100a0:	fef42623          	sw	a5,-20(s0)
   100a4:	fe042423          	sw	zero,-24(s0)
   100a8:	fe042223          	sw	zero,-28(s0)
   100ac:	fe842783          	lw	a5,-24(s0)
   100b0:	00179793          	sll	a5,a5,0x1
   100b4:	fef42023          	sw	a5,-32(s0)
   100b8:	fe442783          	lw	a5,-28(s0)
   100bc:	00279793          	sll	a5,a5,0x2
   100c0:	fcf42e23          	sw	a5,-36(s0)
   100c4:	fe042783          	lw	a5,-32(s0)
   100c8:	fdc42703          	lw	a4,-36(s0)
   100cc:	00ff6f33          	or	t5,t5,a5
   100d0:	00ef6f33          	or	t5,t5,a4
   100d4:	fec42703          	lw	a4,-20(s0)
   100d8:	00100793          	li	a5,1
   100dc:	04f71663          	bne	a4,a5,10128 <checkForIntrusion+0x9c>
   100e0:	00100793          	li	a5,1
   100e4:	fef42423          	sw	a5,-24(s0)
   100e8:	00100793          	li	a5,1
   100ec:	fef42223          	sw	a5,-28(s0)
   100f0:	fe842783          	lw	a5,-24(s0)
   100f4:	00179793          	sll	a5,a5,0x1
   100f8:	fef42023          	sw	a5,-32(s0)
   100fc:	fe442783          	lw	a5,-28(s0)
   10100:	00279793          	sll	a5,a5,0x2
   10104:	fcf42e23          	sw	a5,-36(s0)
   10108:	fe042783          	lw	a5,-32(s0)
   1010c:	fdc42703          	lw	a4,-36(s0)
   10110:	00ff6f33          	or	t5,t5,a5
   10114:	00ef6f33          	or	t5,t5,a4
   10118:	000027b7          	lui	a5,0x2
   1011c:	71078513          	add	a0,a5,1808 # 2710 <main-0xd964>
   10120:	054000ef          	jal	10174 <delaytime>
   10124:	03c0006f          	j	10160 <checkForIntrusion+0xd4>
   10128:	fe042423          	sw	zero,-24(s0)
   1012c:	fe042223          	sw	zero,-28(s0)
   10130:	fe842783          	lw	a5,-24(s0)
   10134:	00179793          	sll	a5,a5,0x1
   10138:	fef42023          	sw	a5,-32(s0)
   1013c:	fe442783          	lw	a5,-28(s0)
   10140:	00279793          	sll	a5,a5,0x2
   10144:	fcf42e23          	sw	a5,-36(s0)
   10148:	fe042783          	lw	a5,-32(s0)
   1014c:	fdc42703          	lw	a4,-36(s0)
   10150:	00ff6f33          	or	t5,t5,a5
   10154:	00ef6f33          	or	t5,t5,a4
   10158:	3e800513          	li	a0,1000
   1015c:	018000ef          	jal	10174 <delaytime>
   10160:	00000013          	nop
   10164:	02c12083          	lw	ra,44(sp)
   10168:	02812403          	lw	s0,40(sp)
   1016c:	03010113          	add	sp,sp,48
   10170:	00008067          	ret

00010174 <delaytime>:
   10174:	fd010113          	add	sp,sp,-48
   10178:	02812623          	sw	s0,44(sp)
   1017c:	03010413          	add	s0,sp,48
   10180:	fca42e23          	sw	a0,-36(s0)
   10184:	fe042623          	sw	zero,-20(s0)
   10188:	0340006f          	j	101bc <delaytime+0x48>
   1018c:	fe042423          	sw	zero,-24(s0)
   10190:	0100006f          	j	101a0 <delaytime+0x2c>
   10194:	fe842783          	lw	a5,-24(s0)
   10198:	00178793          	add	a5,a5,1
   1019c:	fef42423          	sw	a5,-24(s0)
   101a0:	fe842703          	lw	a4,-24(s0)
   101a4:	000f47b7          	lui	a5,0xf4
   101a8:	23f78793          	add	a5,a5,575 # f423f <__global_pointer$+0xe2863>
   101ac:	fee7d4e3          	bge	a5,a4,10194 <delaytime+0x20>
   101b0:	fec42783          	lw	a5,-20(s0)
   101b4:	00178793          	add	a5,a5,1
   101b8:	fef42623          	sw	a5,-20(s0)
   101bc:	fec42703          	lw	a4,-20(s0)
   101c0:	fdc42783          	lw	a5,-36(s0)
   101c4:	fcf744e3          	blt	a4,a5,1018c <delaytime+0x18>
   101c8:	00000013          	nop
   101cc:	00000013          	nop
   101d0:	02c12403          	lw	s0,44(sp)
   101d4:	03010113          	add	sp,sp,48
   101d8:	00008067          	ret


```

 
# Unique instructions


To get the unique instructions execute below command which uses python script.

```
python3 instruction_counter.py
```


unique instructions are :

```

Number of different instructions: 15
List of unique instructions:

nop
lui
ret
or
li
bge
lw
sll
and
jal
bne
blt
sw
add
j

```









