	.file	"kernel.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"T11 %d\012\015\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {sl, fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #8
	ldr	sl, .L5
.L4:
	add	sl, pc, sl
	str	r0, [fp, #-20]
	str	r1, [fp, #-24]
	mov	r0, #1
	mov	r1, #0
	bl	bwsetfifo(PLT)
	mov	r0, #1
	mov	r1, #255
	bl	setTimer(PLT)
.L2:
	mov	r0, #1
	bl	getTimer(PLT)
	mov	r3, r0
	mov	r0, #1
	ldr	r2, .L5+4
	add	r2, sl, r2
	mov	r1, r2
	mov	r2, r3
	bl	bwprintf(PLT)
	b	.L2
.L6:
	.align	2
.L5:
	.word	_GLOBAL_OFFSET_TABLE_-(.L4+8)
	.word	.LC0(GOTOFF)
	.size	main, .-main
	.ident	"GCC: (GNU) 4.0.2"
