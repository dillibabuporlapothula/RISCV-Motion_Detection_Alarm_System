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

## Assembly code

To get the assembly instructions from c code execute below instructions using riscv32-toolchain 

```
/home/dilli/riscv32-toolchain/bin/riscv32-unknown-elf-gcc -o motion_detection_alarm motion_detection_alarm.c

/home/dilli/riscv32-toolchain/bin/riscv32-unknown-elf-objdump -d motion_detection_alarm > sample_assembly.txt

```




```


motion_detection_alarm:     file format elf32-littleriscv





Disassembly of section .text:



00010094 <exit>:

   10094:	ff010113          	add	sp,sp,-16

   10098:	00000593          	li	a1,0

   1009c:	00812423          	sw	s0,8(sp)

   100a0:	00112623          	sw	ra,12(sp)

   100a4:	00050413          	mv	s0,a0

   100a8:	3a4000ef          	jal	1044c <__call_exitprocs>

   100ac:	c281a503          	lw	a0,-984(gp) # 11ae8 <_global_impure_ptr>

   100b0:	03c52783          	lw	a5,60(a0)

   100b4:	00078463          	beqz	a5,100bc <exit+0x28>

   100b8:	000780e7          	jalr	a5

   100bc:	00040513          	mv	a0,s0

   100c0:	5b4000ef          	jal	10674 <_exit>



000100c4 <register_fini>:

   100c4:	00000793          	li	a5,0

   100c8:	00078863          	beqz	a5,100d8 <register_fini+0x14>

   100cc:	00010537          	lui	a0,0x10

   100d0:	56c50513          	add	a0,a0,1388 # 1056c <__libc_fini_array>

   100d4:	4f40006f          	j	105c8 <atexit>

   100d8:	00008067          	ret



000100dc <_start>:

   100dc:	00002197          	auipc	gp,0x2

   100e0:	de418193          	add	gp,gp,-540 # 11ec0 <__global_pointer$>

   100e4:	c3418513          	add	a0,gp,-972 # 11af4 <completed.1>

   100e8:	c5018613          	add	a2,gp,-944 # 11b10 <__BSS_END__>

   100ec:	40a60633          	sub	a2,a2,a0

   100f0:	00000593          	li	a1,0

   100f4:	27c000ef          	jal	10370 <memset>

   100f8:	00000517          	auipc	a0,0x0

   100fc:	4d050513          	add	a0,a0,1232 # 105c8 <atexit>

   10100:	00050863          	beqz	a0,10110 <_start+0x34>

   10104:	00000517          	auipc	a0,0x0

   10108:	46850513          	add	a0,a0,1128 # 1056c <__libc_fini_array>

   1010c:	4bc000ef          	jal	105c8 <atexit>

   10110:	1c4000ef          	jal	102d4 <__libc_init_array>

   10114:	00012503          	lw	a0,0(sp)

   10118:	00410593          	add	a1,sp,4

   1011c:	00000613          	li	a2,0

   10120:	06c000ef          	jal	1018c <main>

   10124:	f71ff06f          	j	10094 <exit>



00010128 <__do_global_dtors_aux>:

   10128:	ff010113          	add	sp,sp,-16

   1012c:	00812423          	sw	s0,8(sp)

   10130:	c341c783          	lbu	a5,-972(gp) # 11af4 <completed.1>

   10134:	00112623          	sw	ra,12(sp)

   10138:	02079263          	bnez	a5,1015c <__do_global_dtors_aux+0x34>

   1013c:	00000793          	li	a5,0

   10140:	00078a63          	beqz	a5,10154 <__do_global_dtors_aux+0x2c>

   10144:	00011537          	lui	a0,0x11

   10148:	6ac50513          	add	a0,a0,1708 # 116ac <__EH_FRAME_BEGIN__>

   1014c:	00000097          	auipc	ra,0x0

   10150:	000000e7          	jalr	zero # 0 <exit-0x10094>

   10154:	00100793          	li	a5,1

   10158:	c2f18a23          	sb	a5,-972(gp) # 11af4 <completed.1>

   1015c:	00c12083          	lw	ra,12(sp)

   10160:	00812403          	lw	s0,8(sp)

   10164:	01010113          	add	sp,sp,16

   10168:	00008067          	ret



0001016c <frame_dummy>:

   1016c:	00000793          	li	a5,0

   10170:	00078c63          	beqz	a5,10188 <frame_dummy+0x1c>

   10174:	00011537          	lui	a0,0x11

   10178:	c3818593          	add	a1,gp,-968 # 11af8 <object.0>

   1017c:	6ac50513          	add	a0,a0,1708 # 116ac <__EH_FRAME_BEGIN__>

   10180:	00000317          	auipc	t1,0x0

   10184:	00000067          	jr	zero # 0 <exit-0x10094>

   10188:	00008067          	ret



0001018c <main>:

   1018c:	ff010113          	add	sp,sp,-16

   10190:	00112623          	sw	ra,12(sp)

   10194:	00812423          	sw	s0,8(sp)

   10198:	01010413          	add	s0,sp,16

   1019c:	070000ef          	jal	1020c <checkForIntrusion>

   101a0:	ffdff06f          	j	1019c <main+0x10>



000101a4 <delaytime>:

   101a4:	fd010113          	add	sp,sp,-48

   101a8:	02812623          	sw	s0,44(sp)

   101ac:	03010413          	add	s0,sp,48

   101b0:	fca42e23          	sw	a0,-36(s0)

   101b4:	fe042623          	sw	zero,-20(s0)

   101b8:	0340006f          	j	101ec <delaytime+0x48>

   101bc:	fe042423          	sw	zero,-24(s0)

   101c0:	0100006f          	j	101d0 <delaytime+0x2c>

   101c4:	fe842783          	lw	a5,-24(s0)

   101c8:	00178793          	add	a5,a5,1

   101cc:	fef42423          	sw	a5,-24(s0)

   101d0:	fe842703          	lw	a4,-24(s0)

   101d4:	000f47b7          	lui	a5,0xf4

   101d8:	23f78793          	add	a5,a5,575 # f423f <__global_pointer$+0xe237f>

   101dc:	fee7d4e3          	bge	a5,a4,101c4 <delaytime+0x20>

   101e0:	fec42783          	lw	a5,-20(s0)

   101e4:	00178793          	add	a5,a5,1

   101e8:	fef42623          	sw	a5,-20(s0)

   101ec:	fec42703          	lw	a4,-20(s0)

   101f0:	fdc42783          	lw	a5,-36(s0)

   101f4:	fcf744e3          	blt	a4,a5,101bc <delaytime+0x18>

   101f8:	00000013          	nop

   101fc:	00000013          	nop

   10200:	02c12403          	lw	s0,44(sp)

   10204:	03010113          	add	sp,sp,48

   10208:	00008067          	ret



0001020c <checkForIntrusion>:

   1020c:	fd010113          	add	sp,sp,-48

   10210:	02112623          	sw	ra,44(sp)

   10214:	02812423          	sw	s0,40(sp)

   10218:	03010413          	add	s0,sp,48

   1021c:	fe042623          	sw	zero,-20(s0)

   10220:	fe042423          	sw	zero,-24(s0)

   10224:	fec42783          	lw	a5,-20(s0)

   10228:	00179793          	sll	a5,a5,0x1

   1022c:	fef42223          	sw	a5,-28(s0)

   10230:	00ff6f33          	or	t5,t5,a5

   10234:	fef42223          	sw	a5,-28(s0)

   10238:	00ff6f33          	or	t5,t5,a5

   1023c:	fef42023          	sw	a5,-32(s0)

   10240:	001f7793          	and	a5,t5,1

   10244:	fcf42e23          	sw	a5,-36(s0)

   10248:	fdc42783          	lw	a5,-36(s0)

   1024c:	04078663          	beqz	a5,10298 <checkForIntrusion+0x8c>

   10250:	00100793          	li	a5,1

   10254:	fef42623          	sw	a5,-20(s0)

   10258:	fec42783          	lw	a5,-20(s0)

   1025c:	00179793          	sll	a5,a5,0x1

   10260:	fef42223          	sw	a5,-28(s0)

   10264:	00ff6f33          	or	t5,t5,a5

   10268:	fef42223          	sw	a5,-28(s0)

   1026c:	00100793          	li	a5,1

   10270:	fef42423          	sw	a5,-24(s0)

   10274:	fe842783          	lw	a5,-24(s0)

   10278:	00179793          	sll	a5,a5,0x1

   1027c:	fef42023          	sw	a5,-32(s0)

   10280:	00ff6f33          	or	t5,t5,a5

   10284:	fef42023          	sw	a5,-32(s0)

   10288:	000027b7          	lui	a5,0x2

   1028c:	71078513          	add	a0,a5,1808 # 2710 <exit-0xd984>

   10290:	f15ff0ef          	jal	101a4 <delaytime>

   10294:	fb5ff06f          	j	10248 <checkForIntrusion+0x3c>

   10298:	fe042623          	sw	zero,-20(s0)

   1029c:	fec42783          	lw	a5,-20(s0)

   102a0:	00179793          	sll	a5,a5,0x1

   102a4:	fef42223          	sw	a5,-28(s0)

   102a8:	00ff6f33          	or	t5,t5,a5

   102ac:	fef42223          	sw	a5,-28(s0)

   102b0:	fe042423          	sw	zero,-24(s0)

   102b4:	fe842783          	lw	a5,-24(s0)

   102b8:	00179793          	sll	a5,a5,0x1

   102bc:	fef42023          	sw	a5,-32(s0)

   102c0:	00ff6f33          	or	t5,t5,a5

   102c4:	fef42023          	sw	a5,-32(s0)

   102c8:	7d000513          	li	a0,2000

   102cc:	ed9ff0ef          	jal	101a4 <delaytime>

   102d0:	f79ff06f          	j	10248 <checkForIntrusion+0x3c>



000102d4 <__libc_init_array>:

   102d4:	ff010113          	add	sp,sp,-16

   102d8:	00812423          	sw	s0,8(sp)

   102dc:	000117b7          	lui	a5,0x11

   102e0:	00011437          	lui	s0,0x11

   102e4:	01212023          	sw	s2,0(sp)

   102e8:	6b078793          	add	a5,a5,1712 # 116b0 <__init_array_start>

   102ec:	6b040713          	add	a4,s0,1712 # 116b0 <__init_array_start>

   102f0:	00112623          	sw	ra,12(sp)

   102f4:	00912223          	sw	s1,4(sp)

   102f8:	40e78933          	sub	s2,a5,a4

   102fc:	02e78263          	beq	a5,a4,10320 <__libc_init_array+0x4c>

   10300:	40295913          	sra	s2,s2,0x2

   10304:	6b040413          	add	s0,s0,1712

   10308:	00000493          	li	s1,0

   1030c:	00042783          	lw	a5,0(s0)

   10310:	00148493          	add	s1,s1,1

   10314:	00440413          	add	s0,s0,4

   10318:	000780e7          	jalr	a5

   1031c:	ff24e8e3          	bltu	s1,s2,1030c <__libc_init_array+0x38>

   10320:	00011437          	lui	s0,0x11

   10324:	000117b7          	lui	a5,0x11

   10328:	6b878793          	add	a5,a5,1720 # 116b8 <__do_global_dtors_aux_fini_array_entry>

   1032c:	6b040713          	add	a4,s0,1712 # 116b0 <__init_array_start>

   10330:	40e78933          	sub	s2,a5,a4

   10334:	40295913          	sra	s2,s2,0x2

   10338:	02e78063          	beq	a5,a4,10358 <__libc_init_array+0x84>

   1033c:	6b040413          	add	s0,s0,1712

   10340:	00000493          	li	s1,0

   10344:	00042783          	lw	a5,0(s0)

   10348:	00148493          	add	s1,s1,1

   1034c:	00440413          	add	s0,s0,4

   10350:	000780e7          	jalr	a5

   10354:	ff24e8e3          	bltu	s1,s2,10344 <__libc_init_array+0x70>

   10358:	00c12083          	lw	ra,12(sp)

   1035c:	00812403          	lw	s0,8(sp)

   10360:	00412483          	lw	s1,4(sp)

   10364:	00012903          	lw	s2,0(sp)

   10368:	01010113          	add	sp,sp,16

   1036c:	00008067          	ret



00010370 <memset>:

   10370:	00f00313          	li	t1,15

   10374:	00050713          	mv	a4,a0

   10378:	02c37e63          	bgeu	t1,a2,103b4 <memset+0x44>

   1037c:	00f77793          	and	a5,a4,15

   10380:	0a079063          	bnez	a5,10420 <memset+0xb0>

   10384:	08059263          	bnez	a1,10408 <memset+0x98>

   10388:	ff067693          	and	a3,a2,-16

   1038c:	00f67613          	and	a2,a2,15

   10390:	00e686b3          	add	a3,a3,a4

   10394:	00b72023          	sw	a1,0(a4)

   10398:	00b72223          	sw	a1,4(a4)

   1039c:	00b72423          	sw	a1,8(a4)

   103a0:	00b72623          	sw	a1,12(a4)

   103a4:	01070713          	add	a4,a4,16

   103a8:	fed766e3          	bltu	a4,a3,10394 <memset+0x24>

   103ac:	00061463          	bnez	a2,103b4 <memset+0x44>

   103b0:	00008067          	ret

   103b4:	40c306b3          	sub	a3,t1,a2

   103b8:	00269693          	sll	a3,a3,0x2

   103bc:	00000297          	auipc	t0,0x0

   103c0:	005686b3          	add	a3,a3,t0

   103c4:	00c68067          	jr	12(a3)

   103c8:	00b70723          	sb	a1,14(a4)

   103cc:	00b706a3          	sb	a1,13(a4)

   103d0:	00b70623          	sb	a1,12(a4)

   103d4:	00b705a3          	sb	a1,11(a4)

   103d8:	00b70523          	sb	a1,10(a4)

   103dc:	00b704a3          	sb	a1,9(a4)

   103e0:	00b70423          	sb	a1,8(a4)

   103e4:	00b703a3          	sb	a1,7(a4)

   103e8:	00b70323          	sb	a1,6(a4)

   103ec:	00b702a3          	sb	a1,5(a4)

   103f0:	00b70223          	sb	a1,4(a4)

   103f4:	00b701a3          	sb	a1,3(a4)

   103f8:	00b70123          	sb	a1,2(a4)

   103fc:	00b700a3          	sb	a1,1(a4)

   10400:	00b70023          	sb	a1,0(a4)

   10404:	00008067          	ret

   10408:	0ff5f593          	zext.b	a1,a1

   1040c:	00859693          	sll	a3,a1,0x8

   10410:	00d5e5b3          	or	a1,a1,a3

   10414:	01059693          	sll	a3,a1,0x10

   10418:	00d5e5b3          	or	a1,a1,a3

   1041c:	f6dff06f          	j	10388 <memset+0x18>

   10420:	00279693          	sll	a3,a5,0x2

   10424:	00000297          	auipc	t0,0x0

   10428:	005686b3          	add	a3,a3,t0

   1042c:	00008293          	mv	t0,ra

   10430:	fa0680e7          	jalr	-96(a3)

   10434:	00028093          	mv	ra,t0

   10438:	ff078793          	add	a5,a5,-16

   1043c:	40f70733          	sub	a4,a4,a5

   10440:	00f60633          	add	a2,a2,a5

   10444:	f6c378e3          	bgeu	t1,a2,103b4 <memset+0x44>

   10448:	f3dff06f          	j	10384 <memset+0x14>



0001044c <__call_exitprocs>:

   1044c:	fd010113          	add	sp,sp,-48

   10450:	01412c23          	sw	s4,24(sp)

   10454:	c281aa03          	lw	s4,-984(gp) # 11ae8 <_global_impure_ptr>

   10458:	03212023          	sw	s2,32(sp)

   1045c:	02112623          	sw	ra,44(sp)

   10460:	148a2903          	lw	s2,328(s4)

   10464:	02812423          	sw	s0,40(sp)

   10468:	02912223          	sw	s1,36(sp)

   1046c:	01312e23          	sw	s3,28(sp)

   10470:	01512a23          	sw	s5,20(sp)

   10474:	01612823          	sw	s6,16(sp)

   10478:	01712623          	sw	s7,12(sp)

   1047c:	01812423          	sw	s8,8(sp)

   10480:	04090063          	beqz	s2,104c0 <__call_exitprocs+0x74>

   10484:	00050b13          	mv	s6,a0

   10488:	00058b93          	mv	s7,a1

   1048c:	00100a93          	li	s5,1

   10490:	fff00993          	li	s3,-1

   10494:	00492483          	lw	s1,4(s2)

   10498:	fff48413          	add	s0,s1,-1

   1049c:	02044263          	bltz	s0,104c0 <__call_exitprocs+0x74>

   104a0:	00249493          	sll	s1,s1,0x2

   104a4:	009904b3          	add	s1,s2,s1

   104a8:	040b8463          	beqz	s7,104f0 <__call_exitprocs+0xa4>

   104ac:	1044a783          	lw	a5,260(s1)

   104b0:	05778063          	beq	a5,s7,104f0 <__call_exitprocs+0xa4>

   104b4:	fff40413          	add	s0,s0,-1

   104b8:	ffc48493          	add	s1,s1,-4

   104bc:	ff3416e3          	bne	s0,s3,104a8 <__call_exitprocs+0x5c>

   104c0:	02c12083          	lw	ra,44(sp)

   104c4:	02812403          	lw	s0,40(sp)

   104c8:	02412483          	lw	s1,36(sp)

   104cc:	02012903          	lw	s2,32(sp)

   104d0:	01c12983          	lw	s3,28(sp)

   104d4:	01812a03          	lw	s4,24(sp)

   104d8:	01412a83          	lw	s5,20(sp)

   104dc:	01012b03          	lw	s6,16(sp)

   104e0:	00c12b83          	lw	s7,12(sp)

   104e4:	00812c03          	lw	s8,8(sp)

   104e8:	03010113          	add	sp,sp,48

   104ec:	00008067          	ret

   104f0:	00492783          	lw	a5,4(s2)

   104f4:	0044a683          	lw	a3,4(s1)

   104f8:	fff78793          	add	a5,a5,-1

   104fc:	04878e63          	beq	a5,s0,10558 <__call_exitprocs+0x10c>

   10500:	0004a223          	sw	zero,4(s1)

   10504:	fa0688e3          	beqz	a3,104b4 <__call_exitprocs+0x68>

   10508:	18892783          	lw	a5,392(s2)

   1050c:	008a9733          	sll	a4,s5,s0

   10510:	00492c03          	lw	s8,4(s2)

   10514:	00f777b3          	and	a5,a4,a5

   10518:	02079263          	bnez	a5,1053c <__call_exitprocs+0xf0>

   1051c:	000680e7          	jalr	a3

   10520:	00492703          	lw	a4,4(s2)

   10524:	148a2783          	lw	a5,328(s4)

   10528:	01871463          	bne	a4,s8,10530 <__call_exitprocs+0xe4>

   1052c:	f92784e3          	beq	a5,s2,104b4 <__call_exitprocs+0x68>

   10530:	f80788e3          	beqz	a5,104c0 <__call_exitprocs+0x74>

   10534:	00078913          	mv	s2,a5

   10538:	f5dff06f          	j	10494 <__call_exitprocs+0x48>

   1053c:	18c92783          	lw	a5,396(s2)

   10540:	0844a583          	lw	a1,132(s1)

   10544:	00f77733          	and	a4,a4,a5

   10548:	00071c63          	bnez	a4,10560 <__call_exitprocs+0x114>

   1054c:	000b0513          	mv	a0,s6

   10550:	000680e7          	jalr	a3

   10554:	fcdff06f          	j	10520 <__call_exitprocs+0xd4>

   10558:	00892223          	sw	s0,4(s2)

   1055c:	fa9ff06f          	j	10504 <__call_exitprocs+0xb8>

   10560:	00058513          	mv	a0,a1

   10564:	000680e7          	jalr	a3

   10568:	fb9ff06f          	j	10520 <__call_exitprocs+0xd4>



0001056c <__libc_fini_array>:

   1056c:	ff010113          	add	sp,sp,-16

   10570:	00812423          	sw	s0,8(sp)

   10574:	000117b7          	lui	a5,0x11

   10578:	00011437          	lui	s0,0x11

   1057c:	6b878793          	add	a5,a5,1720 # 116b8 <__do_global_dtors_aux_fini_array_entry>

   10580:	6bc40413          	add	s0,s0,1724 # 116bc <__fini_array_end>

   10584:	40f40433          	sub	s0,s0,a5

   10588:	00912223          	sw	s1,4(sp)

   1058c:	00112623          	sw	ra,12(sp)

   10590:	40245493          	sra	s1,s0,0x2

   10594:	02048063          	beqz	s1,105b4 <__libc_fini_array+0x48>

   10598:	ffc40413          	add	s0,s0,-4

   1059c:	00f40433          	add	s0,s0,a5

   105a0:	00042783          	lw	a5,0(s0)

   105a4:	fff48493          	add	s1,s1,-1

   105a8:	ffc40413          	add	s0,s0,-4

   105ac:	000780e7          	jalr	a5

   105b0:	fe0498e3          	bnez	s1,105a0 <__libc_fini_array+0x34>

   105b4:	00c12083          	lw	ra,12(sp)

   105b8:	00812403          	lw	s0,8(sp)

   105bc:	00412483          	lw	s1,4(sp)

   105c0:	01010113          	add	sp,sp,16

   105c4:	00008067          	ret



000105c8 <atexit>:

   105c8:	00050593          	mv	a1,a0

   105cc:	00000693          	li	a3,0

   105d0:	00000613          	li	a2,0

   105d4:	00000513          	li	a0,0

   105d8:	0040006f          	j	105dc <__register_exitproc>



000105dc <__register_exitproc>:

   105dc:	c281a703          	lw	a4,-984(gp) # 11ae8 <_global_impure_ptr>

   105e0:	14872783          	lw	a5,328(a4)

   105e4:	04078c63          	beqz	a5,1063c <__register_exitproc+0x60>

   105e8:	0047a703          	lw	a4,4(a5)

   105ec:	01f00813          	li	a6,31

   105f0:	06e84e63          	blt	a6,a4,1066c <__register_exitproc+0x90>

   105f4:	00271813          	sll	a6,a4,0x2

   105f8:	02050663          	beqz	a0,10624 <__register_exitproc+0x48>

   105fc:	01078333          	add	t1,a5,a6

   10600:	08c32423          	sw	a2,136(t1) # 10208 <delaytime+0x64>

   10604:	1887a883          	lw	a7,392(a5)

   10608:	00100613          	li	a2,1

   1060c:	00e61633          	sll	a2,a2,a4

   10610:	00c8e8b3          	or	a7,a7,a2

   10614:	1917a423          	sw	a7,392(a5)

   10618:	10d32423          	sw	a3,264(t1)

   1061c:	00200693          	li	a3,2

   10620:	02d50463          	beq	a0,a3,10648 <__register_exitproc+0x6c>

   10624:	00170713          	add	a4,a4,1

   10628:	00e7a223          	sw	a4,4(a5)

   1062c:	010787b3          	add	a5,a5,a6

   10630:	00b7a423          	sw	a1,8(a5)

   10634:	00000513          	li	a0,0

   10638:	00008067          	ret

   1063c:	14c70793          	add	a5,a4,332

   10640:	14f72423          	sw	a5,328(a4)

   10644:	fa5ff06f          	j	105e8 <__register_exitproc+0xc>

   10648:	18c7a683          	lw	a3,396(a5)

   1064c:	00170713          	add	a4,a4,1

   10650:	00e7a223          	sw	a4,4(a5)

   10654:	00c6e6b3          	or	a3,a3,a2

   10658:	18d7a623          	sw	a3,396(a5)

   1065c:	010787b3          	add	a5,a5,a6

   10660:	00b7a423          	sw	a1,8(a5)

   10664:	00000513          	li	a0,0

   10668:	00008067          	ret

   1066c:	fff00513          	li	a0,-1

   10670:	00008067          	ret



00010674 <_exit>:

   10674:	05d00893          	li	a7,93

   10678:	00000073          	ecall

   1067c:	00054463          	bltz	a0,10684 <_exit+0x10>

   10680:	0000006f          	j	10680 <_exit+0xc>

   10684:	ff010113          	add	sp,sp,-16

   10688:	00812423          	sw	s0,8(sp)

   1068c:	00050413          	mv	s0,a0

   10690:	00112623          	sw	ra,12(sp)

   10694:	40800433          	neg	s0,s0

   10698:	00c000ef          	jal	106a4 <__errno>

   1069c:	00852023          	sw	s0,0(a0)

   106a0:	0000006f          	j	106a0 <_exit+0x2c>



000106a4 <__errno>:

   106a4:	c301a503          	lw	a0,-976(gp) # 11af0 <_impure_ptr>

   106a8:	00008067          	ret

```

 
# Unique instructions


To get the unique instructions execute below command which uses python script.

```
python3 instruction_counter.py
```


unique instructions are :

```

Number of different instructions: 32

List of unique instructions:

sub

or

neg

zext.b

lui

auipc

sb

ecall

beqz

mv

lbu

li

bge

bne

jr

sw

j

bltz

bnez

ret

beq

add

bgeu

bltu

sra

jalr

sll

nop

jal

blt

lw

and

```









