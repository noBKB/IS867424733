  # hexmain.S
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
	# Declare hexasc global too so it can be called from another file
	# (e.g. timetemplate.S, or the auto-grader's test harness).
	.globl hex2asc, hexasc

hex2asc:
	li	a0, 4		# test number (from 0 to 15)
	
	addi    sp,sp,-4
	sw      ra,0(sp)
	
	jal	hexasc		# call hexasc
	
	li	a7, 11	# write a0 to stdout
	ecall

	lw      ra,0(sp)
	addi    sp,sp,4
	jr      ra	

  # You can write your own code for hexasc here
  #
hexasc:
	andi	a0, a0, 0xf	# only the low nibble is significant
	li	t0, 10
	bltu	a0, t0, digit
	addi	a0, a0, 0x37	# 10 becomes 'A'
	jr	ra

digit:
	addi	a0, a0, 0x30	# 0 becomes '0'
	jr	ra
