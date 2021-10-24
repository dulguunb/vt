	.file	"calling_conv.cc"
	.intel_syntax noprefix
# GNU C++17 (GCC) version 11.1.0 (x86_64-pc-linux-gnu)
#	compiled by GNU C version 11.1.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# warning: MPFR header version 4.1.0 differs from library version 4.1.0-p13.
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -masm=intel -mtune=generic -march=x86-64 -O0 -fno-lto -fno-asynchronous-unwind-tables -fno-exceptions -fno-rtti
	.text
	.globl	_Z3fooii
	.type	_Z3fooii, @function
_Z3fooii:
	push	rbp	#
	mov	rbp, rsp	#,
	mov	DWORD PTR -4[rbp], edi	# a, a
	mov	DWORD PTR -8[rbp], esi	# b, b
# calling_conv.cc:3:     return a + b;
	mov	edx, DWORD PTR -4[rbp]	# tmp84, a
	mov	eax, DWORD PTR -8[rbp]	# tmp85, b
	add	eax, edx	# _3, tmp84
# calling_conv.cc:4: }
	pop	rbp	#
	ret	
	.size	_Z3fooii, .-_Z3fooii
	.globl	main
	.type	main, @function
main:
	push	rbp	#
	mov	rbp, rsp	#,
	sub	rsp, 16	#,
# calling_conv.cc:7:     int i = foo(10,20);
	mov	esi, 20	#,
	mov	edi, 10	#,
	call	_Z3fooii	#
	mov	DWORD PTR -4[rbp], eax	# i, tmp84
# calling_conv.cc:8:     return i;
	mov	eax, DWORD PTR -4[rbp]	# _4, i
# calling_conv.cc:9: }
	leave	
	ret	
	.size	main, .-main
	.ident	"GCC: (GNU) 11.1.0"
	.section	.note.GNU-stack,"",@progbits
