	.file	"test.cpp"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.text
	.globl	_Z3sumRiS_
	.type	_Z3sumRiS_, @function
_Z3sumRiS_:
.LFB971:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %edx
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE971:
	.size	_Z3sumRiS_, .-_Z3sumRiS_
	.section	.text._ZN4dataC2Ev,"axG",@progbits,_ZN4dataC5Ev,comdat
	.align 2
	.weak	_ZN4dataC2Ev
	.type	_ZN4dataC2Ev, @function
_ZN4dataC2Ev:
.LFB973:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movl	$20, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE973:
	.size	_ZN4dataC2Ev, .-_ZN4dataC2Ev
	.weak	_ZN4dataC1Ev
	.set	_ZN4dataC1Ev,_ZN4dataC2Ev
	.section	.rodata
.LC0:
	.string	"hahah"
.LC1:
	.string	"ret = %d\n"
.LC2:
	.string	"func:%d\n"
.LC3:
	.string	"linux84 666"
.LC4:
	.string	"0727"
	.text
	.globl	main
	.type	main, @function
main:
.LFB975:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA975
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	leaq	-21(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev
	leaq	-21(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movl	$.LC0, %esi
	movq	%rax, %rdi
.LEHB0:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE0:
	leaq	-21(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4dataC1Ev
	movl	$777, -64(%rbp)
	movl	$888, -60(%rbp)
	leaq	-64(%rbp), %rax
	addq	$8, %rax
	movabsq	$8247343400852088180, %rcx
	movq	%rcx, (%rax)
	movl	$7627637, 8(%rax)
	movl	$10, -68(%rbp)
	movl	$20, -72(%rbp)
	leaq	-72(%rbp), %rdx
	leaq	-68(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_Z3sumRiS_
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
.LEHB1:
	call	printf
	movl	$2, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$8, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC3, %edi
	call	puts
	movl	$.LC4, %edi
	call	puts
.LEHE1:
	movl	$0, %ebx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
.LEHB2:
	call	_ZNSsD1Ev
	movl	%ebx, %eax
	jmp	.L10
.L8:
	movq	%rax, %rbx
	leaq	-21(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume
.LEHE2:
.L9:
	movq	%rax, %rbx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSsD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB3:
	call	_Unwind_Resume
.LEHE3:
.L10:
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE975:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA975:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE975-.LLSDACSB975
.LLSDACSB975:
	.uleb128 .LEHB0-.LFB975
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L8-.LFB975
	.uleb128 0
	.uleb128 .LEHB1-.LFB975
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L9-.LFB975
	.uleb128 0
	.uleb128 .LEHB2-.LFB975
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB3-.LFB975
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSE975:
	.text
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1005:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L11
	cmpl	$65535, -8(%rbp)
	jne	.L11
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	call	__cxa_atexit
.L11:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1005:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__Z3sumRiS_, @function
_GLOBAL__sub_I__Z3sumRiS_:
.LFB1006:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1006:
	.size	_GLOBAL__sub_I__Z3sumRiS_, .-_GLOBAL__sub_I__Z3sumRiS_
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z3sumRiS_
	.section	.rodata
	.align 8
	.type	_ZZL18__gthread_active_pvE20__gthread_active_ptr, @object
	.size	_ZZL18__gthread_active_pvE20__gthread_active_ptr, 8
_ZZL18__gthread_active_pvE20__gthread_active_ptr:
	.quad	_ZL28__gthrw___pthread_key_createPjPFvPvE
	.weakref	_ZL28__gthrw___pthread_key_createPjPFvPvE,__pthread_key_create
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
