addi $a0, $0, 8
addi $a1, $a0,0  
addi $a2, $0, 1
addi $a3, $0, 0   
addi $v0, $v0,1  

beq $a0, $0,end


loop: 
beq  $a2,$a0 ,end 
addi  $v0, $0, 0 
beq $0,$0,loop1
   
   
loop1: 
beq $a3,$a2, svt
add $v0 , $v0, $a1
addi $a3, $a3, 1  
beq $0,$0,loop1

svt:
addi $a2, $a2, 1 
add $a1, $0, $v0  
addi $a3, $0, 0  
beq $0, $0, loop

  
end: 	
beq $0, $0, end	
    	
