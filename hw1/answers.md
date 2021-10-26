#
# What is an ISA? What parts belong to an ISA specification?
 
 > ISA stands for Instruction Set Architecture. The reason having ISA is that it standardizes the instruction sets regardless of the physical implmentation. For instance the X86 ISA is implemented by AMD and Intel. Their instruction sets are identical however their physical implementation of the instruction sets are different.
 
 [Wiki page for different X86 ISA supported machines](https://en.wikipedia.org/wiki/X86_instruction_listings)

 > ISA generally can be classified as RISC and CISC. RISC stands for reduced instruction set computer. CISC stands for complex instruction set computer.

 > ISA includes addressing mode, register specifications (general purpose, index registers, base registers, instruction pointer registers).

 > Addressing mode specifies how to calculate effective memory addresses of an operand by using the information held in registers and/or constants contained within a machine instruction somewhere else
 For instance: 

 ```nasm 
 jump <address> 
 ```

 the adderss is effective PC address

[Intel's ISA x86-64 implementation](https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-instruction-set-reference-manual-325383.pdf)

[AMD's x86-64 implementation](https://www.amd.com/system/files/TechDocs/24592.pdf)

[x86-asm manual](http://ref.x86asm.net/)

#
# What is a calling convention? What does the x86_64/Linux calling convention specify?  Where do you find this information?

> Operating system specifies also how to access the syscalls through instruction sets by maniuplating the general registers. These information is instructed on the compilers (GCC,G++,clang, etc).

> In general it describes how you can pass parameters to the functions and how you can get the result. Usually the EDX,EAX registers are used for the return values. Usually also you only need to push the parameters to the stack in a reverse order or right to left.


```bash
gcc -S -fverbose-asm -masm=intel -fno-asynchronous-unwind-tables -O0 calling_conv.cc
```

> I disassembled calling_conv.c to calling_conv.s. I noticed that it doesn't push the arguments to the stack rather it uses esi and edi registers. I think it's a result of some optimazation. However the usage of stack is still valid: 

The relevant part of the code is below I explained the 

```nasm
_Z3fooii:
	push	rbp	#    # set the base pointer to this function's context
	mov	rbp, rsp	#,  ; <Saves the stack pointer to base pointer
	mov	DWORD PTR -4[rbp], edi	# a, a < Pops the edi to the same location where "a" is - I am not really sure why?
	mov	DWORD PTR -8[rbp], esi	# b, b < Pops the edi to the same location where "b" is - I am not really sure why?
# calling_conv.cc:3:     return a + b;
	mov	edx, DWORD PTR -4[rbp]	# tmp84, a < Stores the a and b to the temporary variables
	mov	eax, DWORD PTR -8[rbp]	# tmp85, b
	add	eax, edx	# _3, tmp84
	# calling_conv.cc:4: }
	pop	rbp	# < store the base pointer back to the main function
	ret	
```


(Calling convention wiki)[https://wiki.osdev.org/Calling_Conventions]
(Function prologue and epilogue)[https://en.wikipedia.org/wiki/Function_prologue_and_epilogue]
(Some info about function calling convention)[https://aaronbloomfield.github.io/pdr/book/x86-32bit-ccc-chapter.pdf]
(Function epilogue/prologue)[https://www.cs.utexas.edu/~novak/codegen.pdf]

#
# What are the generic parts of the encoding of an x86 instruction? Where do you find this information? 

> x86(32 bit) Instruction can be encoded with at most 15bytes there are following components

1. Legacy prefixes (1-4 bytes, optional)
2. Opcode with prefixes (1-4 bytes, required)
3. ModR/M (1 byte, if required)
4. SIB (1 byte, if required)
5. Diplacement (1, 2, 4 or 8 bytes, if required)
6. Immediate (1, 2, 4 or 8 bytes, if required) 


(x86 Instruction Encoding)[https://wiki.osdev.org/X86-64_Instruction_Encoding]

## 2. Prefix opcode byte (4bytes)
	Prefix opcode allowes multiple opcodes to be available and it also allows you to have non-supported opcodes.	
	They're usually the first 1 bytes of the encoded instruction.
	-----------------
	|1|1|1|1|1|1|1|1| .....
	-----------------
	this part of the encoding affects the operation of the instruction. For instance: 00000000 means it's register to register addition.
	the last two bits of the bytes are named d and s
	-----------------
	|1|1|1|1|1|1|d|s| .....
	-----------------
	d = 0 (if adding register to memory)
	d = 1 (if adding memory to register)
	s = 0 (if adding 8bit operand)
	s = 1 (if adding 16 bit or 32 bit operand)

## 3. ModR/M (1 byte)
	It controls the addressing mode and instruction operand size.
	7 6 5 4 3 2 1 0
	---------------
	| | | | | | | |
	---------------
	^_^ ^___^ ^___^
	MOD  REG   R/M

	MOD:
		00 -> register indirect addressing mode
		01 -> one byte signed displacement (follows addressing mode bytes)
		10 -> (four byte signed displacement)
		11 -> (register addressing mode)
	REG: 4-32bit registers
		000 - al,ax,eax
		001 - cl,dx,edx
		010 - dl,dx,edx
		011 - bl,bx,ebx
		100 - ah,sp,esp
		101 - ch,bp,ebp
		110 - dh,ci,esi
		111 - bh,di,edi
	R/M: (in more details)[https://www.plantation-productions.com/Webster/www.artofasm.com/Windows/HTML/ISA.html]


## 4. SIB (Scale,Index,Base)

	Why do we need this?! you might ask. Well you need this part of the encoding due to instruction form such as this: [ebx + edx * 4]

	7 6 5 4 3 2 1 0
	-----------------
	| | | | | | | | |
	-----------------
	^_^ ^___^ ^____^
	scale index base
	|
	Scale: 
		00 index*1  000
		01 index*2
		10 index*3
		11 index*4
	Index:
		000 eax
		001 ecx
		010 edx
		011 ebx
		100 illegal
		101 ebp
		110 esi
		111 edi
	Base:
		-|- everything is the same as Index except from
		100 esp
		101 displacement only if MOD=00 EBP if MOD=01 or MOD=10
		110 esi
		111 edi

## 5. Displacement
	You just put the displacement value at the end of these previous bytes :-)

## 6. Immediate
	When you implement ADD(or any other operations) using immediate value instead of register there are three differences
	1. The opcode H.O will be 1 instead of 0 (check the #2 Header!) however this does not tell CPU it should execute ADD operation!
	2. There is no direction (d) bit in the because well obviously it's an immediate value!
	3. There is no REG field in Mod-Reg-R/M section. It should have "000" in corresponding fields


Example:
	
	ADD(AL,CL)
	In hex:
	0x0  0x0 0xc 0x01
	In Binary
	0000|0000|1100|0001

		^ ^^^ ^_^   ^_^
		d s|MOD  al register  cl register

I wrote this assemby code to demonstrate the encoding

``` nasm
global _start
section .text
_start:
    add al, cl  
```

After assembling with nasm: nasm -f elf32 encoding1.s

and disassembling it with: objdump -d encoding1.o  

I get this result:

```
encoding1.o:     file format elf32-i386


Disassembly of section .text:

00000000 <_start>:
   0:   00 c8                   add    %cl,%al
        ^___^
        Here you can see the encoded assembly in hex. Not sure why 0x01 is dropped though?!

```

Reference: https://www.plantation-productions.com/Webster/www.artofasm.com/Windows/HTML/ISA.html#1028108


# What is the benefit of a pipeline in CPU core design? What are pipeline conflicts?

Pipelining is the process of accumulating instruction from the processor through pipeline. It allows storing and executing instructions in an orderly process.

Pipeline allows you to execute multiple instructions simultanously. However it comes with some issues.
Advnatages:
1. The cycle time of the processesor is reduced
2. It increases the throughput of the system
3. It makes the system reliable

Conflicts:
1. Timing Variations: All stages cannot take same amount of time. This problem generally occurs in instruction processing where different instructions have different operand requirements and thus different processing time.
2. Data Hazards: When several instructions are in partial execution, and if they reference same data then the problem arises. We must ensure that next instruction does not attempt to access data before the current instruction because this will lead to incorrect results.
3. Branching: In order to fetch and execute the next instruction, we must know what that instruction is. If the present instruction is conditional branch, and its result will lead us to the next instruction, then the next instruction may not be known until the current one is processed
4. Interrupts: Interrupts set unwanted instruction into the instruction stream. Interrupts effect the execution of instruction.
5. Data dependency: It arises when an instruction depends upon the result of a previous instruction but this result is not yet available.

# When are jumps/calls slow? What does “slow” mean? 


1. Calls command can be slow because if it tries to access syscalls it needs to do context switching. Therefore it needs to save the ESP,EBP and all of the registers and start the new process in a different context and fetch back the result and continue the previous process.
2. It also takes 20 CPU cycles to evaluate jump/calls. Because the pipeline executes multiple instructions simultanously therefore if there is an occurance of jump/call it needs to branch out to a different instruction sets. There is however a something called branch predictor unit in modern CPU. The modern CPU tries to predict the future and figure out the branch target before branch is actually fully executed. This happens before the decoder part of the pipeline.

https://blog.cloudflare.com/branch-predictor/
https://xania.org/201602/bpu-part-three
http://www.ece.uah.edu/~milenka/docs/VladimirUzelac.thesis.pdf


# What belongs to the state of a Linux process? Examples? How to access it?

Linux processes have 5 states
1. Running&Runnable
2. Interruptable_sleep
3. uninterruptable_sleep
4. stopped
5. zombie

Depending on what signal you sent to the process it can go from Running to different states. For instance if you send SIGSTOP (ctrl+x) it will put the process into stopped. To start the process again you need to send SIGCONT. If the program calls exit() then it will go to zombie state. With top command you can check the state of the process

* R – RUNNING/RUNNABLE
* S – INTERRRUPTABLE_SLEEP
* D – UNINTERRUPTABLE_SLEEP
* T – STOPPED
* Z – ZOMBIE

For example: ``` 3032 dulguun   20   0 5498548 799664 249936 S   6.3   4.9 137:01.28 firefox ``` This process is on uniterruptable_sleep mode