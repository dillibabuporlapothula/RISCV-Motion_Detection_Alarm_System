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

```
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


```

## Assembly code

To get the assembly instructions from c code execute below instructions using riscv32-toolchain 

```
/home/dilli/riscv32-toolchain/bin/riscv32-unknown-elf-gcc -c -mabi=ilp32 -march=rv32im -ffreestanding -o motion_detection_alarm motion_detection_alarm.c

/home/dilli/riscv32-toolchain/bin/riscv32-unknown-elf-objdump -d motion_detection_alarm > sample_assembly.txt

```




```



motion_detection_alarm:     file format elf32-littleriscv





Disassembly of section .text:



00000000 <main>:

   0:	ff010113          	add	sp,sp,-16

   4:	00112623          	sw	ra,12(sp)

   8:	00812423          	sw	s0,8(sp)

   c:	01010413          	add	s0,sp,16



00000010 <.L2>:

  10:	00000097          	auipc	ra,0x0

  14:	000080e7          	jalr	ra # 10 <.L2>

  18:	ff9ff06f          	j	10 <.L2>



0000001c <checkForIntrusion>:

  1c:	fd010113          	add	sp,sp,-48

  20:	02112623          	sw	ra,44(sp)

  24:	02812423          	sw	s0,40(sp)

  28:	03010413          	add	s0,sp,48

  2c:	fe042623          	sw	zero,-20(s0)

  30:	fe042423          	sw	zero,-24(s0)

  34:	001f7793          	and	a5,t5,1

  38:	fef42223          	sw	a5,-28(s0)

  3c:	00ff6f33          	or	t5,t5,a5

  40:	fef42023          	sw	a5,-32(s0)

  44:	00ff6f33          	or	t5,t5,a5

  48:	fcf42e23          	sw	a5,-36(s0)



0000004c <.L6>:

  4c:	fe442703          	lw	a4,-28(s0)

  50:	00100793          	li	a5,1

  54:	04f71863          	bne	a4,a5,a4 <.L4>

  58:	00100793          	li	a5,1

  5c:	fef42623          	sw	a5,-20(s0)

  60:	fec42783          	lw	a5,-20(s0)

  64:	00179793          	sll	a5,a5,0x1

  68:	fef42023          	sw	a5,-32(s0)

  6c:	00ff6f33          	or	t5,t5,a5

  70:	fef42023          	sw	a5,-32(s0)

  74:	00100793          	li	a5,1

  78:	fef42423          	sw	a5,-24(s0)

  7c:	fe842783          	lw	a5,-24(s0)

  80:	00179793          	sll	a5,a5,0x1

  84:	fcf42e23          	sw	a5,-36(s0)

  88:	00ff6f33          	or	t5,t5,a5

  8c:	fcf42e23          	sw	a5,-36(s0)

  90:	000027b7          	lui	a5,0x2

  94:	71078513          	add	a0,a5,1808 # 2710 <.L8+0x25e4>

  98:	00000097          	auipc	ra,0x0

  9c:	000080e7          	jalr	ra # 98 <.L6+0x4c>

  a0:	fadff06f          	j	4c <.L6>



000000a4 <.L4>:

  a4:	fe042623          	sw	zero,-20(s0)

  a8:	fec42783          	lw	a5,-20(s0)

  ac:	00179793          	sll	a5,a5,0x1

  b0:	fef42023          	sw	a5,-32(s0)

  b4:	00ff6f33          	or	t5,t5,a5

  b8:	fef42023          	sw	a5,-32(s0)

  bc:	fe042423          	sw	zero,-24(s0)

  c0:	fe842783          	lw	a5,-24(s0)

  c4:	00179793          	sll	a5,a5,0x1

  c8:	fcf42e23          	sw	a5,-36(s0)

  cc:	00ff6f33          	or	t5,t5,a5

  d0:	fcf42e23          	sw	a5,-36(s0)

  d4:	7d000513          	li	a0,2000

  d8:	00000097          	auipc	ra,0x0

  dc:	000080e7          	jalr	ra # d8 <.L4+0x34>

  e0:	f6dff06f          	j	4c <.L6>



000000e4 <delaytime>:

  e4:	fd010113          	add	sp,sp,-48

  e8:	02812623          	sw	s0,44(sp)

  ec:	03010413          	add	s0,sp,48

  f0:	fca42e23          	sw	a0,-36(s0)

  f4:	fe042623          	sw	zero,-20(s0)

  f8:	0340006f          	j	12c <.L8>



000000fc <.L11>:

  fc:	fe042423          	sw	zero,-24(s0)

 100:	0100006f          	j	110 <.L9>



00000104 <.L10>:

 104:	fe842783          	lw	a5,-24(s0)

 108:	00178793          	add	a5,a5,1

 10c:	fef42423          	sw	a5,-24(s0)



00000110 <.L9>:

 110:	fe842703          	lw	a4,-24(s0)

 114:	000f47b7          	lui	a5,0xf4

 118:	23f78793          	add	a5,a5,575 # f423f <.L8+0xf4113>

 11c:	fee7d4e3          	bge	a5,a4,104 <.L10>

 120:	fec42783          	lw	a5,-20(s0)

 124:	00178793          	add	a5,a5,1

 128:	fef42623          	sw	a5,-20(s0)



0000012c <.L8>:

 12c:	fec42703          	lw	a4,-20(s0)

 130:	fdc42783          	lw	a5,-36(s0)

 134:	fcf744e3          	blt	a4,a5,fc <.L11>

 138:	00000013          	nop

 13c:	00000013          	nop

 140:	02c12403          	lw	s0,44(sp)

 144:	03010113          	add	sp,sp,48

 148:	00008067          	ret

```

 
# Unique instructions


To get the unique instructions execute below command which uses python script.

```
python3 instruction_counter.py
```


unique instructions are :

```

Number of different instructions: 16

List of unique instructions:

j

lui

bne

ret

blt

bge

auipc

nop

jalr

and

add

li

or

sw

lw

sll



```









