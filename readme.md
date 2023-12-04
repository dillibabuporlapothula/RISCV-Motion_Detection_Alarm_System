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



![Screenshot (279)](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/a74cabfd-0521-40cc-9c13-34f45476dee2)

**002f7793** :  ```   andi   a5,t5,2   ``` 

 The instruction is performing a bitwise AND operation between the value in register t5 and the immediate value 2, effectively performing a bit masking operation to extract specific bits or check for a particular bit pattern in the t5 register.

 

 **fcf42c23**:  ```  sw   a5,-40(s0)  ```

  The instruction stores the content of register a5 into memory and we can see the 11 as output and 00000011 being stored in registor x30 .

 


 




![Screenshot (278)](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/2f26ff6c-5f26-4a47-8989-78644c65b5b6)


  **fdc42703**:  ```  lw	a4,-36(s0) ```

  This instruction loads a word from the memory address calculated by adding the immediate value -36 to the content of register s0 and stores it in register a4. the output value in x30 register is 00. 


# Gate Level Simulation


- GLS, initiated by running a test bench using the netlist file derived from synthesis, serves as the Design Under Test (DUT), ensuring logical consistency akin to RTL code.
- The netlist, a logical match to RTL, facilitates using the same test bench, affirming the logical correctness of the design post-synthesis.
- Gate Level Simulation conducted on the Yosys-synthesized netlist involves mapping standard cells from the sky130 library, confirming the integrity of the design's logic.
- The process to convert the processor code to a netlist involves several sequential steps. The commands used are :

```

read_liberty -lib sky130_fd_sc_hd__tt_025C_1v80_256.lib 
read_verilog processor.v
synth -top wrapper
dfflibmap -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib 
abc -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib
write_verilog syntheised__processor_test.v

```


![VirtualBox_ubuntu-VLSI_03_11_2023_01_46_19](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/d931c1f0-0994-4284-bd92-36668a918106)


- Next the commands to run GLS simulation is as follows

```

iverilog -o test synth_processor_test.v testbench.v sky130_sram_1kbyte_1rw1r_32x256_8.v sky130_fd_sc_hd.v primitives.v
./test
gtkwave waverform.vcd

```

**Input 0** - For the sensor input changing from one to zero the output changing from 11 to 01 for short period because of masking and finally settling to 00.  

![op_00](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/b09559f7-8860-4868-9c67-04cd2d11560a)





**Input 1** - For the sensor input one the output is 01 initially because of masking and finally 11.


![op_11](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/38219923-72ba-431f-adac-dbfcdb5eb7a6)





**overall**

![overall](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/9b7815ba-7b03-47ba-a4f6-b157fba45978)






###  Synthesized netlised (wrapper module) with 2 SRAM cells highlighted in red



![VirtualBox_ubuntu-VLSI_03_11_2023_02_37_20](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/9758f0bb-2430-4bfd-a7f0-b6cc32565ced)



# Openlane

OpenLane is an automated RTL to GDSII flow based on several components including OpenROAD, Yosys, Magic, Netgen, CVC, SPEF-Extractor, KLayout and a number of custom scripts for design exploration and optimization. The flow performs all ASIC implementation steps from RTL all the way down to GDSII.

commands to run openlane

```

make mount
%./flow.tcl -interactive
% package require openlane 0.9
% prep -design project

```


![VirtualBox_ubuntu-VLSI_16_11_2023_22_43_57](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/60c4dda7-e2f7-4da3-8d60-1da78c4577b7)

### Synthesis

- The logic synthesis process progresses from mapping the high-level HDL description to generic gates for optimization and subsequently mapping the optimized netlist to standard cells to align with the chosen technology for the final implementation of the logic. This intricate process ensures the efficient translation of high-level design specifications into a hardware description that is optimized for the targeted technology platform.
command to run synthesis

```
run_synthesis

```



![VirtualBox_ubuntu-VLSI_16_11_2023_22_43_57](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/479b70d6-e73c-42d4-bcc7-8085f7d0bd40)



synthesis results are below showing SRAM.


![VirtualBox_ubuntu-VLSI_16_11_2023_22_46_58](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/98a635b4-0318-4849-9f5a-58af136f3db9)


### Floorplan  


- The goal is to efficiently allocate silicon area and establish a robust power distribution network (PDN) for synthesized netlist components. Macro placement and blockages are defined to ensure a legalized GDS file during chip placement.
  
- Power planning involves creating a peripheral ring connected to pads and employing power straps for central power distribution, mitigating issues like IR drop. Key floorplan environment variables include core utilization, aspect ratio, core margin, and pin configurations. Vertical and horizontal metal layers are specified, with values typically one more than file specifications. This meticulous floorplanning optimizes silicon area, ensuring a reliable PDN and compliance with design constraints for successful chip implementation.



command to run floorplan is 

```
run_floorplan

```


![VirtualBox_ubuntu-VLSI_17_11_2023_00_13_36](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/bbab1ec9-88cb-4aff-8be5-8c0128ed8976)



Following the completion of the floorplan run, a .def file will be generated in the results/floorplan directory. The floorplan files can be examined by consulting the floorplan.tcl. To visualize the floorplan, execute the Magic tool after navigating to the results/floorplan directory, using the following command:


```
magic -T /home/dilli/Desktop/sky130A.tech lef read /home/dilli/OpenLane/designs/alarm/runs/RUN_2023.11.22_10.02.23/tmp/merged.nom.lef def read wrapper.def &

```





 ![floorplan](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/29f6acc0-1bcc-4b75-ade1-18abb413f27d)

 



#### Core area




![VirtualBox_ubuntu-VLSI_17_11_2023_00_45_20](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/55350234-36ea-4950-bc66-44355b254716)




#### Die area 





![VirtualBox_ubuntu-VLSI_17_11_2023_00_45_30](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/69c0385e-f394-4c69-91aa-913ed5153d3e)









### Placement


- In the OpenLANE ASIC flow, the placement of standard cells on floorplan rows is a crucial step aligned with technology LEF file-defined sites. This process unfolds in two stages: Global Placement, aiming for optimal but potentially overlapping positions, and Detailed Placement, refining positions to adhere to legal constraints.


- The synthesized netlist undergoes placement, with the initial step optimizing for wire length reduction. The subsequent detailed placement fine-tunes cell positions for legality. Execution of a specific command initiates the placement process, streamlining the positioning of cells on the floorplan for optimal chip implementation.
  



command to run placement

```
run_placement

```





![VirtualBox_ubuntu-VLSI_17_11_2023_00_47_12](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/a6a94ad6-413a-4660-a377-13028b2fd3c5)




- To veiw on magic run below command in /results/placement path


```
magic -T /home/dilli/Desktop/sky130A.tech lef read /home/dilli/OpenLane/designs/alarm/runs/RUN_2023.11.22_10.02.23/tmp/merged.nom.lef def read wrapper.def &

```





![-placement-magic](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/022a4410-39ca-4f53-9e38-a1d18efff5f4)







### CTS



- Clock tree synthesis is vital for creating a network that distributes the clock signal to all sequential elements, with the key goal of minimizing skew across the chip. The widely used H-trees serve as an effective network topology in achieving this objective.

-  The primary purpose of constructing a clock tree is to ensure the clock input reaches every element, maintaining zero clock skew. This process is essential for synchronized clock distribution across the integrated circuit, and the H-tree methodology is commonly employed in Clock Tree Synthesis (CTS).

  
command to run placement

```
run_cts

```




![VirtualBox_ubuntu-VLSI_17_11_2023_00_49_13](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/27243d99-babe-4513-a7d4-1ff8a6d0b9f0)





### Routing


It establishes the interconnect system between standard cells by utilizing the remaining metal layers post Clock Tree Synthesis (CTS) and Power Distribution Network (PDN) generation. Routing is conducted on specific grids to minimize Design Rule Checking (DRC) errors.

OpenLANE employs the TritonRoute tool for routing, executed in two stages:

- *Global Routing*  : The routing region is partitioned into rectangular grids, represented as coarse 3D routes using the Fastroute tool.
- *Detailed Routing* : Finer grids and routing guides are utilized for precise physical wiring, facilitated by the TritonRoute tool.
  
Key features of TritonRoute include adhering to pre-processed route guides, assuming each net satisfies inter-guide connectivity, and employing a Mixed-Integer Linear Programming (MILP) based panel routing scheme. It operates within an intra-layer parallel and inter-layer sequential routing framework.

command to run placement

```
run_routing

```




![VirtualBox_ubuntu-VLSI_22_11_2023_01_11_17](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/e0d0979f-02a1-4d97-aaed-33e0a7fdd522)





To view in magic go to /results/routing folder path and execute below magic command

```
magic -T /home/dilli/Desktop/sky130A.tech lef read /home/dilli/OpenLane/designs/alarm/runs/RUN_2023.11.22_10.02.23/tmp/merged.nom.lef def read wrapper.def &

```




![routing-magic](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/2a212562-214b-4943-9960-41eb533f8d97)






![routing-magic-zoom](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/553ecf64-c7b2-428c-a523-58dce0d3fab4)





- For viewing the Area:




  ![routing-area](https://github.com/dillibabuporlapothula/RISCV-Motion_Detection_Alarm_System/assets/141803312/77594111-4de4-44a8-88e0-80f735747c82)




