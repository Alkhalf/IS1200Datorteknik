  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
.data
.globl hexasc
.globl delay
.globl while4
.globl for4
.globl loop4
.globl done4
.globl time2string
.align 2
.text




hexasc:
	andi $t0, $a0, 0xf	#get the 4 least significant bits 
	addi $t1,$t1,10		# declera reg t1 with value 10
	slt $t2, $t0, $t1	#if t0 < t1 (10) set t2 to 1
	beq $t2,$0,func	
	nop 	                # when t0 > 10 go to func
	addi $v0,$t0,0x30	#start at char 0 to 9, note: 0x30 =0 and t0 is btn 0 and 9
	j end	
	nop
	
	
func:
addi $v0,$t0,0x37	

end:
jr $ra
nop




delay: 
PUSH $s0
PUSH $ra
PUSH $t6
move $t7,$a0
while4:
ble  $t7, $0, done4
nop 
addi $t7,$t7,-1

   
for4: 
addi $s0,$0 , 0 
addi $t6, $0, 3750

loop4: 
slt  $t1, $s0, $t6 
beq  $t1, $0, while4
nop
addi  $s0 ,$s0, 1 
j loop4  
nop

done4: 
POP $t6
POP $ra
POP $s0
jr $ra 
nop

time2string: 
PUSH $s1
PUSH $ra
PUSH $s0

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

j enddd





#decond second 
addi $s1, $a1, 0
andi  $a0,$s1,0xf
jal hexasc 
nop 
sb $v0,4($s0)


li $v0,0x58
sb $v0,5($s0)

li $v0,0x00
sb $v0,6($s0)
enddd:


POP $s0
POP $ra        
POP $s1

jr    $ra      
nop