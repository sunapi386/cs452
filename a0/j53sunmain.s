	.file	"j53sunmain.c"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	mov	r3, #0
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
	.size	main, .-main
	.ident	"GCC: (GNU) 4.0.2"
