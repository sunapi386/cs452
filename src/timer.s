	.file	"timer.c"
	.text
	.align	2
	.global	setTimer
	.type	setTimer, %function
setTimer:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #24
	str	r0, [fp, #-24]
	str	r1, [fp, #-28]
	ldr	r3, [fp, #-24]
	str	r3, [fp, #-36]
	ldr	r3, [fp, #-36]
	cmp	r3, #2
	beq	.L4
	ldr	r3, [fp, #-36]
	cmp	r3, #3
	beq	.L5
	ldr	r3, [fp, #-36]
	cmp	r3, #1
	beq	.L3
	b	.L2
.L3:
	ldr	r3, .L9
	str	r3, [fp, #-20]
	ldr	r3, .L9+4
	str	r3, [fp, #-16]
	b	.L6
.L4:
	ldr	r3, .L9+8
	str	r3, [fp, #-20]
	ldr	r3, .L9+12
	str	r3, [fp, #-16]
	b	.L6
.L5:
	ldr	r3, .L9+16
	str	r3, [fp, #-20]
	ldr	r3, .L9+20
	str	r3, [fp, #-16]
	b	.L6
.L2:
	mvn	r3, #0
	str	r3, [fp, #-32]
	b	.L7
.L6:
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-28]
	str	r3, [r2, #0]
	ldr	r2, [fp, #-16]
	mov	r3, #128
	str	r3, [r2, #0]
	mov	r3, #0
	str	r3, [fp, #-32]
.L7:
	ldr	r3, [fp, #-32]
	mov	r0, r3
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L10:
	.align	2
.L9:
	.word	-2139029504
	.word	-2139029496
	.word	-2139029472
	.word	-2139029464
	.word	-2139029376
	.word	-2139029368
	.size	setTimer, .-setTimer
	.align	2
	.global	getTimer
	.type	getTimer, %function
getTimer:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #16
	str	r0, [fp, #-20]
	ldr	r3, [fp, #-20]
	str	r3, [fp, #-28]
	ldr	r3, [fp, #-28]
	cmp	r3, #2
	beq	.L14
	ldr	r3, [fp, #-28]
	cmp	r3, #3
	beq	.L15
	ldr	r3, [fp, #-28]
	cmp	r3, #1
	beq	.L13
	b	.L12
.L13:
	ldr	r3, .L19
	str	r3, [fp, #-16]
	b	.L16
.L14:
	ldr	r3, .L19+4
	str	r3, [fp, #-16]
	b	.L16
.L15:
	ldr	r3, .L19+8
	str	r3, [fp, #-16]
	b	.L16
.L12:
	ldr	r3, .L19+12
	str	r3, [fp, #-24]
	b	.L17
.L16:
	ldr	r3, [fp, #-16]
	ldr	r3, [r3, #0]
	str	r3, [fp, #-24]
.L17:
	ldr	r3, [fp, #-24]
	mov	r0, r3
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L20:
	.align	2
.L19:
	.word	-2139029500
	.word	-2139029468
	.word	-2139029372
	.word	1337
	.size	getTimer, .-getTimer
	.ident	"GCC: (GNU) 4.0.2"
