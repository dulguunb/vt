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
	mov	DWORD PTR -8[rbp], esi	# b, b < Pops the edi to the same location where "a" is - I am not really sure why?
# calling_conv.cc:3:     return a + b;
	mov	edx, DWORD PTR -4[rbp]	# tmp84, a < Stores the a and b to the temporary variables
	mov	eax, DWORD PTR -8[rbp]	# tmp85, b
	add	eax, edx	# _3, tmp84
    # calling_conv.cc:4: }
	pop	rbp	# < store the base pointer back to the main function
	ret	
```


(Calling convention wiki)[https://wiki.osdev.org/Calling_Conventions]


