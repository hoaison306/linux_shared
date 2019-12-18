	.file	1 "de1.c"
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
	.align	2
	.globl	CheckMaxNguyenTo
	.ent	CheckMaxNguyenTo
CheckMaxNguyenTo:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	sw	$4,32($fp)
	sw	$5,36($fp)
	li	$2,-1			# 0xffffffffffffffff
	sw	$2,16($fp)
	sw	$0,20($fp)
	sw	$0,20($fp)
$L9:
	lw	$2,20($fp)
	lw	$3,36($fp)
	slt	$2,$2,$3
	beq	$2,$0,$L10
	lw	$2,20($fp)
	sll	$3,$2,2
	lw	$2,32($fp)
	addu	$2,$3,$2
	lw	$4,0($2)
	jal	soNguyenTo
	move	$4,$2
	lw	$2,20($fp)
	sll	$3,$2,2
	lw	$2,32($fp)
	addu	$2,$3,$2
	lw	$2,0($2)
	bne	$4,$2,$L11
	lw	$2,20($fp)
	sll	$3,$2,2
	lw	$2,32($fp)
	addu	$2,$3,$2
	lw	$3,0($2)
	lw	$2,16($fp)
	slt	$2,$2,$3
	beq	$2,$0,$L11
	lw	$2,20($fp)
	sll	$3,$2,2
	lw	$2,32($fp)
	addu	$2,$3,$2
	lw	$2,0($2)
	sw	$2,16($fp)
$L11:
	lw	$2,20($fp)
	addiu	$2,$2,1
	sw	$2,20($fp)
	j	$L9
$L10:
	lw	$2,16($fp)
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	j	$31
	.end	CheckMaxNguyenTo
	.rdata
	.align	2
$LC0:
	.word	49
	.word	14
	.word	42
	.word	68
	.word	31
	.word	17
	.word	62
	.word	47
	.word	89
	.word	12
	.word	26
	.word	27
	.word	79
	.word	3
	.word	18
	.word	37
	.word	83
	.word	99
	.word	13
	.word	48
	.word	96
	.word	83
	.word	87
	.word	99
	.word	54
	.word	56
	.word	37
	.word	98
	.word	53
	.word	98
	.word	38
	.word	90
	.word	67
	.word	4
	.word	89
	.word	64
	.word	20
	.word	80
	.word	33
	.word	80
	.word	7
	.word	43
	.word	39
	.word	36
	.word	64
	.word	93
	.word	32
	.word	60
	.word	30
	.word	15
	.word	84
	.word	14
	.word	16
	.word	44
	.word	8
	.word	66
	.word	77
	.word	77
	.word	35
	.word	47
	.word	13
	.word	38
	.word	61
	.word	10
	.word	64
	.word	18
	.word	59
	.word	44
	.word	66
	.word	45
	.word	48
	.word	57
	.word	99
	.word	83
	.word	54
	.word	9
	.word	67
	.word	5
	.word	71
	.word	79
	.word	8
	.word	16
	.word	3
	.word	12
	.word	17
	.word	53
	.word	27
	.word	34
	.word	46
	.word	61
	.word	13
	.word	91
	.word	24
	.word	29
	.word	56
	.word	79
	.word	77
	.word	99
	.word	32
	.word	41
	.word	14
	.word	85
	.word	34
	.word	48
	.word	98
	.word	86
	.word	16
	.word	84
	.word	88
	.word	99
	.word	40
	.word	51
	.word	60
	.word	31
	.word	70
	.word	91
	.word	44
	.word	84
	.word	83
	.word	86
	.word	61
	.word	27
	.word	78
	.word	49
	.word	44
	.word	3
	.word	61
	.word	41
	.word	43
	.word	56
	.word	62
	.word	75
	.word	15
	.word	54
	.word	93
	.word	44
	.word	0
	.word	90
	.word	85
	.word	0
	.word	95
	.word	88
	.word	1
	.word	23
	.word	27
	.word	21
	.word	85
	.word	21
	.word	27
	.word	13
	.word	94
	.word	81
	.word	98
	.word	59
	.word	12
	.word	39
	.word	0
	.word	37
	.word	35
	.word	16
	.word	45
	.word	67
	.word	84
	.word	55
	.word	99
	.word	31
	.word	63
	.word	65
	.word	22
	.word	24
	.word	17
	.word	51
	.word	3
	.word	85
	.word	26
	.word	60
	.word	16
	.word	18
	.word	37
	.word	82
	.word	43
	.word	44
	.word	99
	.word	18
	.word	92
	.word	68
	.word	46
	.word	35
	.word	34
	.word	67
	.word	77
	.word	65
	.word	6
	.word	95
	.word	47
	.word	64
	.word	18
	.word	91
	.word	67
	.word	86
	.word	55
	.word	31
	.word	63
	.word	18
	.word	94
	.word	21
	.word	16
	.word	31
	.word	17
	.word	35
	.word	55
	.word	48
	.word	69
	.word	44
	.word	98
	.word	86
	.word	85
	.word	86
	.word	82
	.word	84
	.word	41
	.word	10
	.word	81
	.word	28
	.word	90
	.word	79
	.word	14
	.word	51
	.word	74
	.word	85
	.word	20
	.word	1
	.word	25
	.word	84
	.word	37
	.word	76
	.word	17
	.word	87
	.word	48
	.word	67
	.word	87
	.word	33
	.word	55
	.word	30
	.word	19
	.word	35
	.word	44
	.word	65
	.word	35
	.word	34
	.word	86
	.word	2
	.word	92
	.word	55
	.word	7
	.word	35
	.word	42
	.word	23
	.word	62
	.word	27
	.word	83
	.word	36
	.word	64
	.word	59
	.word	0
	.word	18
	.word	62
	.word	18
	.word	53
	.word	52
	.word	26
	.word	75
	.word	25
	.word	10
	.word	8
	.word	10
	.word	58
	.word	82
	.word	73
	.word	26
	.word	38
	.word	65
	.word	56
	.word	84
	.word	38
	.word	29
	.word	26
	.word	16
	.word	30
	.word	27
	.word	41
	.word	59
	.word	16
	.word	57
	.word	57
	.word	18
	.word	17
	.word	48
	.word	50
	.word	44
	.word	16
	.word	48
	.word	1
	.word	38
	.word	91
	.word	51
	.word	38
	.word	83
	.word	80
	.word	35
	.word	87
	.word	91
	.word	64
	.word	73
	.word	71
	.word	43
	.word	79
	.word	20
	.word	35
	.word	49
	.word	67
	.word	44
	.word	63
	.word	13
	.word	6
	.word	66
	.word	85
	.word	97
	.word	99
	.word	58
	.word	26
	.word	22
	.word	18
	.word	9
	.word	27
	.word	66
	.word	15
	.word	82
	.word	10
	.word	23
	.word	40
	.word	13
	.word	68
	.word	17
	.word	8
	.word	33
	.word	63
	.word	89
	.word	99
	.word	22
	.word	58
	.word	76
	.word	56
	.word	72
	.word	14
	.word	14
	.word	27
	.word	50
	.word	34
	.word	34
	.word	60
	.word	80
	.word	43
	.word	74
	.word	25
	.word	72
	.word	29
	.word	34
	.word	18
	.word	87
	.word	62
	.word	39
	.word	52
	.word	4
	.word	1
	.word	67
	.word	62
	.word	76
	.word	82
	.word	91
	.word	91
	.word	34
	.word	27
	.word	58
	.word	90
	.word	20
	.word	8
	.word	25
	.word	25
	.word	28
	.word	64
	.word	76
	.word	72
	.word	8
	.word	69
	.word	83
	.word	62
	.word	28
	.word	96
	.word	82
	.word	18
	.word	53
	.word	81
	.word	31
	.word	28
	.word	70
	.word	29
	.word	82
	.word	21
	.word	99
	.word	28
	.word	16
	.word	78
	.word	77
	.word	90
	.word	12
	.word	70
	.word	57
	.word	31
	.word	59
	.word	68
	.word	17
	.word	85
	.word	44
	.word	68
	.word	80
	.word	57
	.word	13
	.word	69
	.word	70
	.word	81
	.word	93
	.word	81
	.word	42
	.word	1
	.word	43
	.word	34
	.word	4
	.word	58
	.word	87
	.word	45
	.word	95
	.word	83
	.word	68
	.word	35
	.word	90
	.word	52
	.word	38
	.word	57
	.word	88
	.word	74
	.word	33
	.word	38
	.word	93
	.word	45
	.word	85
	.word	60
	.word	95
	.word	72
	.word	97
	.word	51
	.word	76
	.word	53
	.word	95
	.word	81
	.word	26
	.word	50
	.word	60
	.word	18
	.word	14
	.word	47
	.word	8
	.word	20
	.word	9
	.word	70
	.word	90
	.word	86
	.word	90
	.word	92
	.word	94
	.word	84
	.word	4
	.word	27
	.word	29
	.word	87
	.word	14
	.word	39
	.word	6
	.word	77
	.word	1
	.word	20
	.word	25
	.word	88
	.word	19
	.word	75
	.word	95
	.word	41
	.word	84
	.word	28
	.word	38
	.word	71
	.word	63
	.word	65
	.word	3
	.word	11
	.word	41
	.word	52
	.word	40
	.word	22
	.word	67
	.word	22
	.word	17
	.word	39
	.word	58
	.word	78
	.word	24
	.word	52
	.word	43
	.word	85
	.word	15
	.word	3
	.word	14
	.word	32
	.word	20
	.word	20
	.word	39
	.word	49
	.word	1
	.word	62
	.word	37
	.word	64
	.word	73
	.word	93
	.word	68
	.word	84
	.word	24
	.word	5
	.word	75
	.word	85
	.word	22
	.word	79
	.word	24
	.word	7
	.word	76
	.word	89
	.word	97
	.word	85
	.word	38
	.word	48
	.word	67
	.word	97
	.word	40
	.word	11
	.word	79
	.word	39
	.word	31
	.word	15
	.word	54
	.word	9
	.word	95
	.word	14
	.word	77
	.word	13
	.word	95
	.word	65
	.word	96
	.word	36
	.word	99
	.word	90
	.word	92
	.word	54
	.word	81
	.word	23
	.word	68
	.word	91
	.word	65
	.word	9
	.word	10
	.word	16
	.word	97
	.word	27
	.word	81
	.word	70
	.word	10
	.word	88
	.word	59
	.word	16
	.word	87
	.word	42
	.word	71
	.word	58
	.word	52
	.word	82
	.word	43
	.word	20
	.word	35
	.word	21
	.word	62
	.word	55
	.word	63
	.word	47
	.word	50
	.word	39
	.word	78
	.word	27
	.word	83
	.word	22
	.word	39
	.word	11
	.word	44
	.word	38
	.word	53
	.word	57
	.word	99
	.word	13
	.word	58
	.word	58
	.word	2
	.word	88
	.word	19
	.word	74
	.word	40
	.word	77
	.word	37
	.word	35
	.word	62
	.word	58
	.word	70
	.word	52
	.word	45
	.word	43
	.word	52
	.word	76
	.word	65
	.word	89
	.word	16
	.word	21
	.word	66
	.word	48
	.word	58
	.word	17
	.word	61
	.word	6
	.word	58
	.word	35
	.word	5
	.word	21
	.word	32
	.word	84
	.word	11
	.word	31
	.word	60
	.word	35
	.word	73
	.word	47
	.word	4
	.word	40
	.word	85
	.word	36
	.word	31
	.word	95
	.word	97
	.word	45
	.word	24
	.word	59
	.word	82
	.word	4
	.word	72
	.word	29
	.word	38
	.word	4
	.word	19
	.word	91
	.word	59
	.word	11
	.word	80
	.word	76
	.word	51
	.word	71
	.word	85
	.word	80
	.word	21
	.word	68
	.word	29
	.word	48
	.word	0
	.word	23
	.word	3
	.word	21
	.word	48
	.word	30
	.word	37
	.word	30
	.word	35
	.word	30
	.word	43
	.word	15
	.word	95
	.word	29
	.word	79
	.word	65
	.word	7
	.word	2
	.word	62
	.word	65
	.word	31
	.word	64
	.word	14
	.word	46
	.word	66
	.word	37
	.word	80
	.word	90
	.word	71
	.word	17
	.word	21
	.word	40
	.word	15
	.word	47
	.word	11
	.word	44
	.word	60
	.word	98
	.word	61
	.word	57
	.word	50
	.word	23
	.word	27
	.word	63
	.word	80
	.word	59
	.word	82
	.word	71
	.word	83
	.word	16
	.word	95
	.word	36
	.word	40
	.word	7
	.word	14
	.word	29
	.word	3
	.word	13
	.word	9
	.word	79
	.word	54
	.word	67
	.word	68
	.word	39
	.word	4
	.word	0
	.word	90
	.word	23
	.word	21
	.word	24
	.word	48
	.word	53
	.word	93
	.word	85
	.word	51
	.word	98
	.word	55
	.word	2
	.word	94
	.word	41
	.word	57
	.word	30
	.word	25
	.word	29
	.word	11
	.word	18
	.word	23
	.word	7
	.word	44
	.word	48
	.word	76
	.word	60
	.word	62
	.word	27
	.word	92
	.word	11
	.word	94
	.word	59
	.word	31
	.word	5
	.word	11
	.word	81
	.word	40
	.word	15
	.word	19
	.word	57
	.word	38
	.word	3
	.word	59
	.word	6
	.word	1
	.word	46
	.word	29
	.word	30
	.word	3
	.word	28
	.word	79
	.word	55
	.word	40
	.word	87
	.word	71
	.word	97
	.word	95
	.word	12
	.word	2
	.word	58
	.word	46
	.word	11
	.word	8
	.word	25
	.word	81
	.word	43
	.word	68
	.word	28
	.word	44
	.word	47
	.word	79
	.word	91
	.word	59
	.word	67
	.word	60
	.word	67
	.word	14
	.word	18
	.word	26
	.word	48
	.word	38
	.word	2
	.word	42
	.word	13
	.word	35
	.word	87
	.word	50
	.word	91
	.word	49
	.word	31
	.word	42
	.word	36
	.word	42
	.word	78
	.word	22
	.word	16
	.word	74
	.word	31
	.word	90
	.word	40
	.word	27
	.word	60
	.word	40
	.word	6
	.word	65
	.word	15
	.word	21
	.word	14
	.word	20
	.word	20
	.word	99
	.word	38
	.word	56
	.word	12
	.word	34
	.word	36
	.word	11
	.word	46
	.word	77
	.word	25
	.word	50
	.word	63
	.word	31
	.word	1
	.word	56
	.word	95
	.word	13
	.word	5
	.word	54
	.word	71
	.word	30
	.word	46
	.word	40
	.word	96
	.word	83
	.word	18
	.word	35
	.word	47
	.word	71
	.word	58
	.word	47
	.word	72
	.word	3
	.word	68
	.word	24
	.word	88
	.word	78
	.word	13
	.word	97
	.word	33
	.word	25
	.word	71
	.word	56
	.word	4
	.word	8
	.word	48
	.word	47
	.word	13
	.word	83
	.word	36
	.word	19
	.word	75
	.word	73
	.word	1
	.word	12
	.word	84
	.word	41
	.word	4
	.word	51
	.word	95
	.word	82
	.word	76
	.word	25
	.word	0
	.word	72
	.word	3
	.word	38
	.word	1
	.word	13
	.word	50
	.word	20
	.word	6
	.word	42
	.word	45
	.word	95
	.word	19
	.word	34
	.word	71
	.word	56
	.word	26
	.word	91
	.word	31
	.word	81
	.word	8
	.word	13
	.word	75
	.word	56
	.word	35
	.word	66
	.word	62
	.word	3
	.word	12
	.word	29
	.word	8
	.word	70
	.word	42
	.word	86
	.word	61
	.word	40
	.word	17
	.word	77
	.word	82
	.word	20
	.word	43
	.word	55
	.word	51
	.word	33
	.word	31
	.word	64
	.word	14
	.word	82
	.word	58
	.word	51
	.word	13
	.word	76
	.word	87
	.word	97
	.word	96
	.word	82
	.word	4
	.word	56
	.word	58
	.word	92
	.word	89
	.word	90
	.word	44
	.word	15
	.word	10
	.word	63
	.word	28
	.word	33
	.word	98
	.word	96
	.word	76
	.word	53
	.word	16
	.word	54
	.word	50
	.word	13
	.text
	.align	2
	.globl	main
	.ent	main
main:
	.frame	$fp,4032,$31		# vars= 4008, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-4032
	sw	$31,4028($sp)
	sw	$fp,4024($sp)
	move	$fp,$sp
	addiu	$2,$fp,16
	la	$3,$LC0
	li	$6,4000			# 0xfa0
	move	$4,$2
	move	$5,$3
	jal	memcpy
	li	$2,1000			# 0x3e8
	sw	$2,4016($fp)
	addiu	$4,$fp,16
	lw	$5,4016($fp)
	jal	CheckMaxNguyenTo
	sw	$2,4020($fp)
	move	$2,$0
	move	$sp,$fp
	lw	$31,4028($sp)
	lw	$fp,4024($sp)
	addiu	$sp,$sp,4032
	j	$31
	.end	main