  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
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

delay:
 jr $ra
 nop

time2string: 
PUSH($s1)
PUSH($ra)
PUSH($s0)

move    $s0, $a0
move    $s1, $a1
#first minute 
srl $s1, $a1, 12
andi  $a0,$s1,0xf
jal hexasc 
nop 
sb $v0,0($s0)


#second minute 
srl $s1, $a1, 8
andi  $a0,$s1,0xf
jal hexasc 
nop 
sb $v0,1($s0)

#second minute 
li $v0,0x3A
sb $v0,2($s0)


#first second 
srl $s1, $a1, 4
andi  $a0,$s1,0xf
jal hexasc 
nop 
sb $v0,3($s0)


#decond second 
addi $s1, $a1, 0
andi  $a0,$s1,0xf
jal hexasc 
nop 
sb $v0,4($s0)

li $v0,0x00
sb $v0,5($s0)


POP($s0)
POP($ra)        
POP($s1)

jr    $ra      
nop
