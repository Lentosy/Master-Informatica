	.text
	.file	"overflow"
	.p2align	4, 0x90         # -- Begin function echo
	.type	echo,@function
echo:                                   # @echo
.Lfunc_begin0:
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	%edi, %ecx
	leaq	.Lformat(%rip), %rdi
	xorl	%eax, %eax
	movl	%ecx, %esi
	callq	printf@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	echo, .Lfunc_end0-echo
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90         # -- Begin function read
	.type	read,@function
read:                                   # @read
.Lfunc_begin1:
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	leaq	.Lformat.1(%rip), %rdi
	leaq	4(%rsp), %rsi
	xorl	%eax, %eax
	callq	scanf@PLT
	movl	4(%rsp), %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	read, .Lfunc_end1-read
	.cfi_endproc
                                        # -- End function
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
.Lfunc_begin2:
	.file	1 "test/overflow.c"
	.loc	1 1 0                   # overflow.c:1:0
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$56, %rsp
	.cfi_def_cfa_offset 64
.Ltmp0:
	.loc	1 2 1 prologue_end      # overflow.c:2:1
	movl	$9, 12(%rsp)
	xorl	%eax, %eax
	.loc	1 3 5                   # overflow.c:3:5
	testb	%al, %al
	jne	.LBB2_3
# %bb.1:                                # %cont
	.loc	1 0 5 is_stmt 0         # overflow.c:0:5
	movl	$9, %eax
	.loc	1 3 5                   # overflow.c:3:5
	movl	%eax, %eax
	.loc	1 3 1                   # overflow.c:3:1
	movl	$5, 16(%rsp,%rax,4)
	.loc	1 4 5 is_stmt 1         # overflow.c:4:5
	movl	12(%rsp), %eax
	incl	%eax
	cmpl	$9, %eax
	jg	.LBB2_4
# %bb.2:                                # %cont1
	cltq
	.loc	1 4 1 is_stmt 0         # overflow.c:4:1
	movl	$5, 16(%rsp,%rax,4)
	xorl	%eax, %eax
	addq	$56, %rsp
	.cfi_def_cfa_offset 8
	retq
.Ltmp1:
.LBB2_3:                                # %trap
	.cfi_def_cfa_offset 64
	.loc	1 0 1                   # overflow.c:0:1
	leaq	.L__unnamed_1(%rip), %rdi
	leaq	.L__unnamed_2(%rip), %rsi
	movl	$3, %edx
	xorl	%eax, %eax
	callq	__assert@PLT
.LBB2_4:                                # %trap2
	leaq	.L__unnamed_3(%rip), %rdi
	leaq	.L__unnamed_4(%rip), %rsi
	movl	$4, %edx
	xorl	%eax, %eax
	callq	__assert@PLT
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc
                                        # -- End function
	.type	.Lformat,@object        # @format
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lformat:
	.asciz	"%d\n"
	.size	.Lformat, 4

	.type	.Lformat.1,@object      # @format.1
.Lformat.1:
	.asciz	"%d"
	.size	.Lformat.1, 3

	.type	.L__unnamed_1,@object   # @0
	.section	.rodata.str1.16,"aMS",@progbits,1
	.p2align	4
.L__unnamed_1:
	.asciz	"out-of-bounds array access"
	.size	.L__unnamed_1, 27

	.type	.L__unnamed_2,@object   # @1
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_2:
	.asciz	"overflow.c"
	.size	.L__unnamed_2, 11

	.type	.L__unnamed_3,@object   # @2
	.section	.rodata.str1.16,"aMS",@progbits,1
	.p2align	4
.L__unnamed_3:
	.asciz	"out-of-bounds array access"
	.size	.L__unnamed_3, 27

	.type	.L__unnamed_4,@object   # @3
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_4:
	.asciz	"overflow.c"
	.size	.L__unnamed_4, 11

	.section	.debug_str,"MS",@progbits,1
.Linfo_string0:
	.asciz	"Cheetah Compiler"      # string offset=0
.Linfo_string1:
	.asciz	"overflow.c"            # string offset=17
.Linfo_string2:
	.asciz	"test"                  # string offset=28
.Linfo_string3:
	.asciz	"main"                  # string offset=33
.Linfo_string4:
	.asciz	"int"                   # string offset=38
	.section	.debug_abbrev,"",@progbits
	.byte	1                       # Abbreviation Code
	.byte	17                      # DW_TAG_compile_unit
	.byte	1                       # DW_CHILDREN_yes
	.byte	37                      # DW_AT_producer
	.byte	14                      # DW_FORM_strp
	.byte	19                      # DW_AT_language
	.byte	5                       # DW_FORM_data2
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	16                      # DW_AT_stmt_list
	.byte	23                      # DW_FORM_sec_offset
	.byte	27                      # DW_AT_comp_dir
	.byte	14                      # DW_FORM_strp
	.ascii	"\264B"                 # DW_AT_GNU_pubnames
	.byte	25                      # DW_FORM_flag_present
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	6                       # DW_FORM_data4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	2                       # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	0                       # DW_CHILDREN_no
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	6                       # DW_FORM_data4
	.byte	64                      # DW_AT_frame_base
	.byte	24                      # DW_FORM_exprloc
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	3                       # Abbreviation Code
	.byte	36                      # DW_TAG_base_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	62                      # DW_AT_encoding
	.byte	11                      # DW_FORM_data1
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	0                       # EOM(3)
	.section	.debug_info,"",@progbits
.Lcu_begin0:
	.long	71                      # Length of Unit
	.short	4                       # DWARF version number
	.long	.debug_abbrev           # Offset Into Abbrev. Section
	.byte	8                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x40 DW_TAG_compile_unit
	.long	.Linfo_string0          # DW_AT_producer
	.short	2                       # DW_AT_language
	.long	.Linfo_string1          # DW_AT_name
	.long	.Lline_table_start0     # DW_AT_stmt_list
	.long	.Linfo_string2          # DW_AT_comp_dir
                                        # DW_AT_GNU_pubnames
	.quad	.Lfunc_begin2           # DW_AT_low_pc
	.long	.Lfunc_end2-.Lfunc_begin2 # DW_AT_high_pc
	.byte	2                       # Abbrev [2] 0x2a:0x19 DW_TAG_subprogram
	.quad	.Lfunc_begin2           # DW_AT_low_pc
	.long	.Lfunc_end2-.Lfunc_begin2 # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	87
	.long	.Linfo_string3          # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	1                       # DW_AT_decl_line
	.long	67                      # DW_AT_type
                                        # DW_AT_external
	.byte	3                       # Abbrev [3] 0x43:0x7 DW_TAG_base_type
	.long	.Linfo_string4          # DW_AT_name
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	0                       # End Of Children Mark
	.section	.debug_macinfo,"",@progbits
	.byte	0                       # End Of Macro List Mark
	.section	.debug_pubnames,"",@progbits
	.long	.LpubNames_end0-.LpubNames_begin0 # Length of Public Names Info
.LpubNames_begin0:
	.short	2                       # DWARF Version
	.long	.Lcu_begin0             # Offset of Compilation Unit Info
	.long	75                      # Compilation Unit Length
	.long	42                      # DIE offset
	.asciz	"main"                  # External Name
	.long	0                       # End Mark
.LpubNames_end0:
	.section	.debug_pubtypes,"",@progbits
	.long	.LpubTypes_end0-.LpubTypes_begin0 # Length of Public Types Info
.LpubTypes_begin0:
	.short	2                       # DWARF Version
	.long	.Lcu_begin0             # Offset of Compilation Unit Info
	.long	75                      # Compilation Unit Length
	.long	67                      # DIE offset
	.asciz	"int"                   # External Name
	.long	0                       # End Mark
.LpubTypes_end0:

	.section	".note.GNU-stack","",@progbits
	.section	.debug_line,"",@progbits
.Lline_table_start0:
