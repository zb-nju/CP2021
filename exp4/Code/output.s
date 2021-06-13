.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text

read:
li $v0, 4
la $a0, _prompt
syscall
li $v0, 5
syscall
jr $ra

write:
li $v0, 1
syscall
li $v0, 4
la $a0, _ret
syscall
move $v0, $0
jr $ra

process:
addi $sp, $sp, -8
sw $fp, 0($sp)
sw $ra, 4($sp)
move $fp, $sp
addi $sp, $sp, -128
li $t0, 4
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $t0, -8($fp)
lw $t1, 8($fp)
li $t2, 12
add $t0, $t1, $t2
sw $t0, -8($fp)
lw $t0, -8($fp)
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
lw $t0, -16($fp)
lw $t1, 8($fp)
li $t2, 12
add $t0, $t1, $t2
sw $t0, -16($fp)
lw $t0, -16($fp)
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
lw $t0, -4($fp)
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $t0, -20($fp)
lw $t1, -4($fp)
li $t2, 0
add $t0, $t1, $t2
sw $t0, -20($fp)
lw $t0, -24($fp)
lw $t1, -20($fp)
li $t2, 0
sub $t0, $t1, $t2
sw $t0, -24($fp)
lw $t0, -24($fp)
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $t0, -28($fp)
lw $t1, -4($fp)
li $t2, 1
mul $t0, $t1, $t2
sw $t0, -28($fp)
lw $t0, -32($fp)
lw $t1, -28($fp)
li $t2, 1
div $t0, $t1, $t2
sw $t0, -32($fp)
lw $t0, -32($fp)
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $t0, -36($fp)
lw $t1, -4($fp)
li $t2, 32
add $t0, $t1, $t2
sw $t0, -36($fp)
<<<<<<< HEAD
lw $t0, -40($fp)
lw $t1, -36($fp)
li $t2, 2
sub $t0, $t1, $t2
sw $t0, -40($fp)
lw $t0, -40($fp)
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $t0, -44($fp)
lw $t1, 8($fp)
lw $t2, -4($fp)
mul $t0, $t1, $t2
sw $t0, -44($fp)
lw $t0, -48($fp)
lw $t1, 8($fp)
lw $t2, -4($fp)
mul $t0, $t1, $t2
sw $t0, -48($fp)
lw $t0, -52($fp)
lw $t1, -44($fp)
lw $t2, -48($fp)
add $t0, $t1, $t2
sw $t0, -52($fp)
lw $t0, -56($fp)
lw $t1, -4($fp)
lw $t2, 8($fp)
mul $t0, $t1, $t2
sw $t0, -56($fp)
lw $t0, -60($fp)
lw $t1, -52($fp)
lw $t2, -56($fp)
sub $t0, $t1, $t2
sw $t0, -60($fp)
lw $t0, -64($fp)
lw $t1, -60($fp)
lw $t2, 8($fp)
sub $t0, $t1, $t2
sw $t0, -64($fp)
lw $t0, -68($fp)
lw $t1, -4($fp)
lw $t2, 8($fp)
mul $t0, $t1, $t2
sw $t0, -68($fp)
lw $t0, -72($fp)
lw $t1, -64($fp)
lw $t2, -68($fp)
add $t0, $t1, $t2
sw $t0, -72($fp)
lw $t0, -76($fp)
lw $t1, -4($fp)
lw $t2, -4($fp)
mul $t0, $t1, $t2
sw $t0, -76($fp)
lw $t0, -80($fp)
lw $t1, -72($fp)
lw $t2, -76($fp)
add $t0, $t1, $t2
sw $t0, -80($fp)
lw $t0, -84($fp)
lw $t1, 8($fp)
lw $t2, 8($fp)
div $t0, $t1, $t2
sw $t0, -84($fp)
lw $t0, -88($fp)
lw $t1, -80($fp)
lw $t2, -84($fp)
add $t0, $t1, $t2
sw $t0, -88($fp)
lw $t0, -92($fp)
lw $t1, -88($fp)
li $t2, 12
sub $t0, $t1, $t2
sw $t0, -92($fp)
lw $t0, -96($fp)
lw $t1, -92($fp)
li $t2, 29
add $t0, $t1, $t2
sw $t0, -96($fp)
lw $t0, -96($fp)
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $t0, -100($fp)
lw $t1, -4($fp)
li $t2, 3
mul $t0, $t1, $t2
sw $t0, -100($fp)
lw $t0, -104($fp)
lw $t1, -100($fp)
li $t2, 336
add $t0, $t1, $t2
sw $t0, -104($fp)
lw $t0, -108($fp)
lw $t1, 8($fp)
li $t2, 12
mul $t0, $t1, $t2
sw $t0, -108($fp)
lw $t0, -112($fp)
lw $t1, -108($fp)
li $t2, 4
div $t0, $t1, $t2
sw $t0, -112($fp)
lw $t0, -116($fp)
lw $t1, -104($fp)
lw $t2, -112($fp)
sub $t0, $t1, $t2
sw $t0, -116($fp)
lw $t0, -120($fp)
lw $t1, -116($fp)
li $t2, 20
add $t0, $t1, $t2
sw $t0, -120($fp)
lw $t0, -124($fp)
lw $t1, -120($fp)
li $t2, 20
sub $t0, $t1, $t2
sw $t0, -124($fp)
lw $t0, -128($fp)
lw $t1, -124($fp)
li $t2, 0
sub $t0, $t1, $t2
sw $t0, -128($fp)
lw $t0, -128($fp)
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $ra, 4($fp)
addi $sp, $fp, 8
lw $t0, -4($fp)
lw $fp, 0($fp)
move $v0, $t0
jr $ra

mod:
addi $sp, $sp, -8
sw $fp, 0($sp)
sw $ra, 4($sp)
move $fp, $sp
addi $sp, $sp, -12
lw $t0, -4($fp)
lw $t1, 8($fp)
lw $t2, 12($fp)
div $t0, $t1, $t2
sw $t0, -4($fp)
lw $t0, -8($fp)
lw $t1, -4($fp)
lw $t2, 12($fp)
mul $t0, $t1, $t2
sw $t0, -8($fp)
lw $t0, -12($fp)
lw $t1, 8($fp)
lw $t2, -8($fp)
sub $t0, $t1, $t2
sw $t0, -12($fp)
lw $ra, 4($fp)
addi $sp, $fp, 8
lw $t0, -12($fp)
lw $fp, 0($fp)
move $v0, $t0
jr $ra

main:
addi $sp, $sp, -8
sw $fp, 0($sp)
sw $ra, 4($sp)
move $fp, $sp
addi $sp, $sp, -336
lw $t0, -4($fp)
li $t1, 0
li $t2, 8
sub $t0, $t1, $t2
sw $t0, -4($fp)
lw $t0, -8($fp)
lw $t1, -4($fp)
li $t2, 108
add $t0, $t1, $t2
sw $t0, -8($fp)
lw $t0, -12($fp)
lw $t1, -8($fp)
li $t2, 17
div $t0, $t1, $t2
sw $t0, -12($fp)
lw $t0, -12($fp)
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
li $t0, 7
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
li $t0, 11
lw $t1, -24($fp)
move $t1, $t0
sw $t1, -24($fp)
lw $t0, -28($fp)
lw $t1, -16($fp)
lw $t2, -20($fp)
add $t0, $t1, $t2
sw $t0, -28($fp)
lw $t0, -28($fp)
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
lw $t0, -36($fp)
lw $t1, -16($fp)
lw $t2, -20($fp)
add $t0, $t1, $t2
sw $t0, -36($fp)
lw $t0, -40($fp)
lw $t1, -24($fp)
li $t2, 1
div $t0, $t1, $t2
sw $t0, -40($fp)
lw $t0, -44($fp)
lw $t1, -36($fp)
lw $t2, -40($fp)
add $t0, $t1, $t2
sw $t0, -44($fp)
lw $t0, -44($fp)
lw $t1, -48($fp)
move $t1, $t0
sw $t1, -48($fp)
lw $t0, -52($fp)
lw $t1, -16($fp)
lw $t2, -20($fp)
mul $t0, $t1, $t2
sw $t0, -52($fp)
lw $t0, -56($fp)
lw $t1, -52($fp)
lw $t2, -24($fp)
sub $t0, $t1, $t2
sw $t0, -56($fp)
lw $t0, -56($fp)
lw $t1, -60($fp)
move $t1, $t0
sw $t1, -60($fp)
li $t0, 42
lw $t1, -64($fp)
move $t1, $t0
sw $t1, -64($fp)
li $t0, 4
lw $t1, -68($fp)
move $t1, $t0
sw $t1, -68($fp)
li $t0, 0
lw $t1, -72($fp)
move $t1, $t0
sw $t1, -72($fp)
li $t0, 0
lw $t1, -76($fp)
move $t1, $t0
sw $t1, -76($fp)
lw $t0, -96($fp)
lw $t1, -16($fp)
lw $t2, -20($fp)
add $t0, $t1, $t2
sw $t0, -96($fp)
lw $t0, -100($fp)
lw $t1, -96($fp)
lw $t2, -24($fp)
add $t0, $t1, $t2
sw $t0, -100($fp)
lw $t0, -104($fp)
lw $t1, -100($fp)
li $t2, 1500
add $t0, $t1, $t2
sw $t0, -104($fp)
lw $t0, -108($fp)
lw $t1, -104($fp)
lw $t2, -60($fp)
sub $t0, $t1, $t2
sw $t0, -108($fp)
lw $t0, -108($fp)
lw $t1, -60($fp)
move $t1, $t0
sw $t1, -60($fp)
label1:
lw $t0, -72($fp)
li $t1, 4
blt $t0, $t1, label2
j label3
label2:
lw $t0, -112($fp)
li $t1, 15
lw $t2, -72($fp)
mul $t0, $t1, $t2
sw $t0, -112($fp)
lw $t0, -112($fp)
lw $t1, -76($fp)
move $t1, $t0
sw $t1, -76($fp)
lw $t0, -116($fp)
li $t1, 4
lw $t2, -72($fp)
mul $t0, $t1, $t2
sw $t0, -116($fp)
lw $t0, -120($fp)
addi $t1, $fp, -92
lw $t2, -116($fp)
add $t0, $t1, $t2
sw $t0, -120($fp)
lw $t0, -76($fp)
lw $t1, -120($fp)
sw $t0, 0($t1)
lw $t0, -124($fp)
lw $t1, -72($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -124($fp)
lw $t0, -124($fp)
lw $t1, -72($fp)
move $t1, $t0
sw $t1, -72($fp)
j label1
label3:
label4:
lw $t0, -72($fp)
lw $t1, -60($fp)
blt $t0, $t1, label5
j label6
label5:
lw $t0, -128($fp)
lw $t1, -68($fp)
lw $t2, -68($fp)
mul $t0, $t1, $t2
sw $t0, -128($fp)
lw $t0, -128($fp)
lw $t1, -132($fp)
move $t1, $t0
sw $t1, -132($fp)
lw $t0, -136($fp)
lw $t1, -64($fp)
lw $t2, -132($fp)
add $t0, $t1, $t2
sw $t0, -136($fp)
lw $t0, -140($fp)
lw $t1, -72($fp)
li $t2, 12
mul $t0, $t1, $t2
sw $t0, -140($fp)
lw $t0, -144($fp)
lw $t1, -136($fp)
lw $t2, -140($fp)
add $t0, $t1, $t2
sw $t0, -144($fp)
lw $t0, -148($fp)
li $t1, 4
lw $t2, -68($fp)
mul $t0, $t1, $t2
sw $t0, -148($fp)
lw $t0, -152($fp)
lw $t1, -144($fp)
lw $t2, -148($fp)
sub $t0, $t1, $t2
sw $t0, -152($fp)
lw $t0, -156($fp)
lw $t1, -152($fp)
li $t2, 5
add $t0, $t1, $t2
sw $t0, -156($fp)
lw $t0, -160($fp)
lw $t1, -156($fp)
li $t2, 2
add $t0, $t1, $t2
sw $t0, -160($fp)
lw $t0, -160($fp)
lw $t1, -64($fp)
move $t1, $t0
sw $t1, -64($fp)
addi $sp, $sp, -4
lw $t0, -60($fp)
sw $t0, 0($sp)
jal process
addi $sp, $sp, 4
lw $t0, -164($fp)
move $t0, $v0
sw $t0, -164($fp)
lw $t0, -168($fp)
li $t1, 2
lw $t2, -16($fp)
mul $t0, $t1, $t2
sw $t0, -168($fp)
lw $t0, -172($fp)
lw $t1, -164($fp)
lw $t2, -168($fp)
add $t0, $t1, $t2
sw $t0, -172($fp)
lw $t0, -176($fp)
lw $t1, -172($fp)
lw $t2, -60($fp)
sub $t0, $t1, $t2
sw $t0, -176($fp)
lw $t0, -180($fp)
lw $t1, -24($fp)
lw $t2, -32($fp)
mul $t0, $t1, $t2
sw $t0, -180($fp)
lw $t0, -184($fp)
lw $t1, -176($fp)
lw $t2, -180($fp)
add $t0, $t1, $t2
sw $t0, -184($fp)
lw $t0, -184($fp)
lw $t1, -188($fp)
move $t1, $t0
sw $t1, -188($fp)
addi $sp, $sp, -4
li $t0, 2
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -60($fp)
sw $t0, 0($sp)
jal mod
addi $sp, $sp, 8
lw $t0, -192($fp)
move $t0, $v0
sw $t0, -192($fp)
lw $t0, -192($fp)
li $t1, 0
bgt $t0, $t1, label7
j label8
label7:
lw $t0, -196($fp)
lw $t1, -72($fp)
li $t2, 3
add $t0, $t1, $t2
sw $t0, -196($fp)
lw $t0, -196($fp)
lw $t1, -200($fp)
move $t1, $t0
sw $t1, -200($fp)
lw $t0, -204($fp)
lw $t1, -200($fp)
li $t2, 1
sub $t0, $t1, $t2
sw $t0, -204($fp)
lw $t0, -204($fp)
lw $t1, -200($fp)
move $t1, $t0
sw $t1, -200($fp)
lw $t0, -208($fp)
lw $t1, -200($fp)
li $t2, 3
add $t0, $t1, $t2
sw $t0, -208($fp)
lw $t0, -208($fp)
lw $t1, -200($fp)
move $t1, $t0
sw $t1, -200($fp)
lw $t0, -212($fp)
lw $t1, -200($fp)
li $t2, 6
sub $t0, $t1, $t2
sw $t0, -212($fp)
lw $t0, -212($fp)
lw $t1, -200($fp)
move $t1, $t0
sw $t1, -200($fp)
label8:
addi $sp, $sp, -4
lw $t0, -16($fp)
sw $t0, 0($sp)
jal process
addi $sp, $sp, 4
lw $t0, -216($fp)
move $t0, $v0
sw $t0, -216($fp)
lw $t0, -220($fp)
lw $t1, -16($fp)
li $t2, 3
add $t0, $t1, $t2
sw $t0, -220($fp)
lw $t0, -224($fp)
lw $t1, -220($fp)
li $t2, 2
sub $t0, $t1, $t2
sw $t0, -224($fp)
lw $t0, -228($fp)
lw $t1, -224($fp)
li $t2, 1
sub $t0, $t1, $t2
sw $t0, -228($fp)
addi $sp, $sp, -4
lw $t0, -228($fp)
sw $t0, 0($sp)
jal process
addi $sp, $sp, 4
lw $t0, -232($fp)
move $t0, $v0
sw $t0, -232($fp)
lw $t0, -216($fp)
lw $t1, -232($fp)
beq $t0, $t1, label9
j label10
label9:
lw $t0, -236($fp)
lw $t1, -60($fp)
li $t2, 2
sub $t0, $t1, $t2
sw $t0, -236($fp)
lw $t0, -240($fp)
lw $t1, -236($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -240($fp)
lw $t0, -240($fp)
lw $t1, -60($fp)
move $t1, $t0
sw $t1, -60($fp)
addi $sp, $sp, -4
li $t0, 4
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -60($fp)
sw $t0, 0($sp)
jal mod
addi $sp, $sp, 8
lw $t0, -244($fp)
move $t0, $v0
sw $t0, -244($fp)
lw $t0, -248($fp)
li $t1, 4
lw $t2, -244($fp)
mul $t0, $t1, $t2
sw $t0, -248($fp)
lw $t0, -252($fp)
addi $t1, $fp, -92
lw $t2, -248($fp)
add $t0, $t1, $t2
sw $t0, -252($fp)
lw $t0, -256($fp)
lw $t1, -252($fp)
lw $t1, 0($t1)
lw $t2, -200($fp)
add $t0, $t1, $t2
sw $t0, -256($fp)
lw $t0, -260($fp)
lw $t1, -256($fp)
lw $t2, -188($fp)
add $t0, $t1, $t2
sw $t0, -260($fp)
lw $t0, -264($fp)
lw $t1, -260($fp)
lw $t2, -48($fp)
sub $t0, $t1, $t2
sw $t0, -264($fp)
addi $sp, $sp, -4
li $t0, 4
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -60($fp)
sw $t0, 0($sp)
jal mod
addi $sp, $sp, 8
lw $t0, -268($fp)
move $t0, $v0
sw $t0, -268($fp)
lw $t0, -272($fp)
li $t1, 4
lw $t2, -268($fp)
mul $t0, $t1, $t2
sw $t0, -272($fp)
lw $t0, -276($fp)
addi $t1, $fp, -92
lw $t2, -272($fp)
add $t0, $t1, $t2
sw $t0, -276($fp)
lw $t0, -264($fp)
lw $t1, -276($fp)
sw $t0, 0($t1)
label10:
lw $t0, -280($fp)
lw $t1, -16($fp)
li $t2, 2
add $t0, $t1, $t2
sw $t0, -280($fp)
lw $t0, -284($fp)
lw $t1, -280($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -284($fp)
lw $t0, -284($fp)
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
lw $t0, -288($fp)
lw $t1, -72($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -288($fp)
lw $t0, -288($fp)
lw $t1, -72($fp)
move $t1, $t0
sw $t1, -72($fp)
lw $t0, -292($fp)
lw $t1, -72($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -292($fp)
lw $t0, -292($fp)
lw $t1, -72($fp)
move $t1, $t0
sw $t1, -72($fp)
j label4
label6:
lw $t0, -296($fp)
lw $t1, -16($fp)
lw $t2, -20($fp)
add $t0, $t1, $t2
sw $t0, -296($fp)
lw $t0, -296($fp)
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
lw $t0, -300($fp)
lw $t1, -16($fp)
lw $t2, -20($fp)
add $t0, $t1, $t2
sw $t0, -300($fp)
lw $t0, -300($fp)
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
lw $t0, -304($fp)
lw $t1, -16($fp)
lw $t2, -20($fp)
add $t0, $t1, $t2
sw $t0, -304($fp)
lw $t0, -304($fp)
lw $t1, -24($fp)
move $t1, $t0
sw $t1, -24($fp)
lw $t0, -308($fp)
lw $t1, -16($fp)
lw $t2, -20($fp)
add $t0, $t1, $t2
sw $t0, -308($fp)
lw $t0, -308($fp)
lw $t1, -60($fp)
move $t1, $t0
sw $t1, -60($fp)
lw $t0, -312($fp)
lw $t1, -16($fp)
lw $t2, -20($fp)
add $t0, $t1, $t2
sw $t0, -312($fp)
lw $t0, -312($fp)
lw $t1, -188($fp)
move $t1, $t0
sw $t1, -188($fp)
lw $t0, -316($fp)
lw $t1, -24($fp)
lw $t2, -60($fp)
add $t0, $t1, $t2
sw $t0, -316($fp)
lw $t0, -320($fp)
lw $t1, -316($fp)
lw $t2, -188($fp)
add $t0, $t1, $t2
sw $t0, -320($fp)
lw $t0, -320($fp)
move $a0, $t0
jal write
lw $t0, -324($fp)
addi $t1, $fp, -92
li $t2, 0
add $t0, $t1, $t2
sw $t0, -324($fp)
lw $t0, -324($fp)
lw $t0, 0($t0)
move $a0, $t0
jal write
lw $t0, -328($fp)
addi $t1, $fp, -92
li $t2, 4
add $t0, $t1, $t2
sw $t0, -328($fp)
lw $t0, -328($fp)
lw $t0, 0($t0)
move $a0, $t0
jal write
lw $t0, -332($fp)
addi $t1, $fp, -92
li $t2, 8
add $t0, $t1, $t2
sw $t0, -332($fp)
lw $t0, -332($fp)
lw $t0, 0($t0)
move $a0, $t0
jal write
lw $t0, -336($fp)
addi $t1, $fp, -92
li $t2, 12
add $t0, $t1, $t2
sw $t0, -336($fp)
lw $t0, -336($fp)
lw $t0, 0($t0)
move $a0, $t0
jal write
lw $ra, 4($fp)
addi $sp, $fp, 8
li $t0, 0
lw $fp, 0($fp)
move $v0, $t0
jr $ra
=======
li $t0, 3289972
li $t1, 28
li $t2, 10
div $t0, $t1, $t2
>>>>>>> b118fd67dc940220ba219284afc24f35ae07bcb1
