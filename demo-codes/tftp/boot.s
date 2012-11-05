	AREA	SelfBoot, CODE, READONLY

	ENTRY
	IMPORT	main
reset
	ldr	a1, =0xc0a8a865
	bl	main
	b	.
	
	END	
	
	