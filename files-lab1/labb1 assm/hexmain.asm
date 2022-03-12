  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,0xf	# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #
hexasc:
	andi $t0, $a0, 0xf	#get the 4 least significant bits 
	addi $t1,$t1,10		# declera reg t1 with value 10
	slt $t2, $t0, $t1	#if t0 < t1 (10) set t2 to 1
	beq $t2,$0,func		# when t0 > 10 go to func
	addi $v0,$t0,0x30	#start at char 0 to 9, note: 0x30 =0 and t0 is btn 0 and 9
	j end	
	
	
func:
addi $v0,$t0,0x37	

end:
jr $ra

#17 = 0x11 we check just the least bits and its 1
#t1 with value 10

