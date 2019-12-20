	.file	1 "de1_final.c"
	.text
	.align	2
	.globl	soNguyenTo
	.ent	soNguyenTo
soNguyenTo:
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
	li	$2,-1			# 0xffffffffffffffff
	sw	$2,4($fp)
	j	$L1
$L2:
	sw	$0,0($fp)
	li	$2,2			# 0x2
	sw	$2,0($fp)
$L4:
	lw	$3,16($fp)
	sra	$2,$3,31
	srl	$2,$2,31
	addu	$2,$3,$2
	sra	$3,$2,1
	lw	$2,0($fp)
	slt	$2,$3,$2
	bne	$2,$0,$L3
	lw	$3,16($fp)
	lw	$2,0($fp)
	div	$0,$3,$2
	bne	$2,$0,1f
	break	7
1:
	mfhi	$2
	bne	$2,$0,$L6
	li	$2,-1			# 0xffffffffffffffff
	sw	$2,4($fp)
	j	$L1
$L6:
	lw	$2,0($fp)
	addiu	$2,$2,1
	sw	$2,0($fp)
	j	$L4
$L3:
	lw	$2,16($fp)
	sw	$2,4($fp)
$L1:
	lw	$2,4($fp)
	move	$sp,$fp
	lw	$fp,8($sp)
	addiu	$sp,$sp,16
	j	$31
	.end	soNguyenTo
