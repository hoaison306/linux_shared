	.file	1 "ktmt.c"
	.text
	.align	2
	.globl	isPrime
	.ent	isPrime
isPrime:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-8
	.fmask	0x00000000,0
	addiu	$sp,$sp,-16
	sw	$fp,8($sp)
	move	$fp,$sp
	sw	$4,16($fp)
	lw	$2,16($fp)
	slt	$2,$2,2
	beq	$2,$0,$L2
	sw	$0,4($fp)
	j	$L1
$L2:
	li	$2,2			# 0x2
	sw	$2,0($fp)
$L3:
	lw	$2,0($fp)
	lw	$3,16($fp)
	slt	$2,$2,$3
	beq	$2,$0,$L4
	lw	$3,16($fp)
	lw	$2,0($fp)
	div	$0,$3,$2
	bne	$2,$0,1f
	break	7
1:
	mfhi	$2
	bne	$2,$0,$L5
	sw	$0,4($fp)
	j	$L1
$L5:
	lw	$2,0($fp)
	addiu	$2,$2,1
	sw	$2,0($fp)
	j	$L3
$L4:
	li	$2,1			# 0x1
	sw	$2,4($fp)
$L1:
	lw	$2,4($fp)
	move	$sp,$fp
	lw	$fp,8($sp)
	addiu	$sp,$sp,16
	j	$31
	.end	isPrime
	.align	2
	.globl	FindPrimeMax
	.ent	FindPrimeMax
FindPrimeMax:
	.frame	$fp,40,$31		# vars= 16, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	move	$fp,$sp
	sw	$4,40($fp)
	sw	$5,44($fp)
	sw	$0,16($fp)
	sw	$0,20($fp)
$L8:
	lw	$2,20($fp)
	lw	$3,44($fp)
	slt	$2,$2,$3
	beq	$2,$0,$L9
	lw	$2,20($fp)
	sll	$3,$2,2
	lw	$2,40($fp)
	addu	$2,$3,$2
	lw	$4,0($2)
	jal	isPrime
	move	$3,$2
	li	$2,1			# 0x1
	bne	$3,$2,$L10
	lw	$2,20($fp)
	sll	$3,$2,2
	lw	$2,40($fp)
	addu	$2,$3,$2
	lw	$3,0($2)
	lw	$2,16($fp)
	slt	$2,$2,$3
	beq	$2,$0,$L10
	lw	$2,20($fp)
	sll	$3,$2,2
	lw	$2,40($fp)
	addu	$2,$3,$2
	lw	$2,0($2)
	sw	$2,16($fp)
$L10:
	lw	$2,20($fp)
	addiu	$2,$2,1
	sw	$2,20($fp)
	j	$L8
$L9:
	lw	$2,16($fp)
	beq	$2,$0,$L13
	lw	$2,16($fp)
	sw	$2,24($fp)
	j	$L7
$L13:
	li	$2,-1			# 0xffffffffffffffff
	sw	$2,24($fp)
$L7:
	lw	$2,24($fp)
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	addiu	$sp,$sp,40
	j	$31
	.end	FindPrimeMax
	.rdata
	.align	2
$LC0:
	.word	0
	.word	13
	.word	6
	.word	1
	.word	4
	.word	2
	.align	2
$LC1:
	.ascii	"%d\000"
	.text
	.align	2
	.globl	main
	.ent	main
main:
	.frame	$fp,48,$31		# vars= 24, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$fp,40($sp)
	move	$fp,$sp
	lw	$2,$LC0
	lw	$3,$LC0+4
	lw	$4,$LC0+8
	lw	$5,$LC0+12
	lw	$6,$LC0+16
	lw	$7,$LC0+20
	sw	$2,16($fp)
	sw	$3,20($fp)
	sw	$4,24($fp)
	sw	$5,28($fp)
	sw	$6,32($fp)
	sw	$7,36($fp)
	addiu	$4,$fp,16
	li	$5,6			# 0x6
	jal	FindPrimeMax
	la	$4,$LC1
	move	$5,$2
	jal	printf
	move	$2,$0
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	addiu	$sp,$sp,48
	j	$31
	.end	main
