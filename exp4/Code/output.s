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
addi $sp, $sp, -116
li $t0, 3
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
li $t0, 36
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $t0, -8($fp)
lw $t1, 8($fp)
li $t2, 321
mul $t0, $t1, $t2
sw $t0, -8($fp)
lw $t0, -12($fp)
lw $t1, -8($fp)
li $t2, 2
mul $t0, $t1, $t2
sw $t0, -12($fp)
lw $t0, -16($fp)
lw $t1, 8($fp)
lw $t2, -4($fp)
mul $t0, $t1, $t2
sw $t0, -16($fp)
lw $t0, -20($fp)
lw $t1, -12($fp)
lw $t2, -16($fp)
add $t0, $t1, $t2
sw $t0, -20($fp)
lw $t0, -24($fp)
lw $t1, -20($fp)
lw $t2, 8($fp)
sub $t0, $t1, $t2
sw $t0, -24($fp)
lw $t0, -28($fp)
lw $t1, -4($fp)
lw $t2, 8($fp)
mul $t0, $t1, $t2
sw $t0, -28($fp)
lw $t0, -32($fp)
lw $t1, -24($fp)
lw $t2, -28($fp)
add $t0, $t1, $t2
sw $t0, -32($fp)
lw $t0, -36($fp)
lw $t1, -4($fp)
lw $t2, -4($fp)
mul $t0, $t1, $t2
sw $t0, -36($fp)
lw $t0, -40($fp)
lw $t1, -32($fp)
lw $t2, -36($fp)
add $t0, $t1, $t2
sw $t0, -40($fp)
lw $t0, -44($fp)
lw $t1, -40($fp)
lw $t2, 8($fp)
add $t0, $t1, $t2
sw $t0, -44($fp)
lw $t0, -48($fp)
lw $t1, -44($fp)
lw $t2, 8($fp)
add $t0, $t1, $t2
sw $t0, -48($fp)
lw $t0, -52($fp)
lw $t1, -48($fp)
li $t2, 23
sub $t0, $t1, $t2
sw $t0, -52($fp)
lw $t0, -56($fp)
lw $t1, -52($fp)
li $t2, 45
add $t0, $t1, $t2
sw $t0, -56($fp)
lw $t0, -56($fp)
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $t0, -60($fp)
lw $t1, -4($fp)
li $t2, 3
div $t0, $t1, $t2
sw $t0, -60($fp)
lw $t0, -64($fp)
lw $t1, -60($fp)
li $t2, 336
add $t0, $t1, $t2
sw $t0, -64($fp)
lw $t0, -68($fp)
lw $t1, 8($fp)
li $t2, 12
mul $t0, $t1, $t2
sw $t0, -68($fp)
lw $t0, -72($fp)
lw $t1, -68($fp)
li $t2, 4
div $t0, $t1, $t2
sw $t0, -72($fp)
lw $t0, -76($fp)
lw $t1, -64($fp)
lw $t2, -72($fp)
sub $t0, $t1, $t2
sw $t0, -76($fp)
lw $t0, -80($fp)
lw $t1, -76($fp)
li $t2, 60
sub $t0, $t1, $t2
sw $t0, -80($fp)
lw $t0, -84($fp)
lw $t1, -4($fp)
li $t2, 12
div $t0, $t1, $t2
sw $t0, -84($fp)
lw $t0, -88($fp)
lw $t1, -84($fp)
li $t2, 24
mul $t0, $t1, $t2
sw $t0, -88($fp)
lw $t0, -92($fp)
lw $t1, -80($fp)
lw $t2, -88($fp)
add $t0, $t1, $t2
sw $t0, -92($fp)
lw $t0, -96($fp)
lw $t1, -92($fp)
li $t2, 36
add $t0, $t1, $t2
sw $t0, -96($fp)
lw $t0, -100($fp)
li $t1, 3
li $t2, 2
div $t0, $t1, $t2
sw $t0, -100($fp)
lw $t0, -104($fp)
lw $t1, -96($fp)
lw $t2, -100($fp)
add $t0, $t1, $t2
sw $t0, -104($fp)
lw $t0, -104($fp)
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $t0, -108($fp)
lw $t1, 8($fp)
li $t2, 24
add $t0, $t1, $t2
sw $t0, -108($fp)
lw $t0, -112($fp)
li $t1, 3
li $t2, 2
div $t0, $t1, $t2
sw $t0, -112($fp)
lw $t0, -116($fp)
lw $t1, -108($fp)
lw $t2, -112($fp)
add $t0, $t1, $t2
sw $t0, -116($fp)
lw $t0, -116($fp)
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $ra, 4($fp)
addi $sp, $fp, 8
lw $t0, -4($fp)
lw $fp, 0($fp)
move $v0, $t0
jr $ra

main:
addi $sp, $sp, -8
sw $fp, 0($sp)
sw $ra, 4($sp)
move $fp, $sp
addi $sp, $sp, -288
lw $t0, -4($fp)
li $t1, 5
li $t2, 2
div $t0, $t1, $t2
sw $t0, -4($fp)
lw $t0, -8($fp)
lw $t1, -4($fp)
li $t2, 14
add $t0, $t1, $t2
sw $t0, -8($fp)
lw $t0, -12($fp)
lw $t1, -8($fp)
li $t2, 3
sub $t0, $t1, $t2
sw $t0, -12($fp)
lw $t0, -12($fp)
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
lw $t0, -20($fp)
li $t1, 35
li $t2, 2
div $t0, $t1, $t2
sw $t0, -20($fp)
lw $t0, -24($fp)
lw $t1, -20($fp)
li $t2, 3
add $t0, $t1, $t2
sw $t0, -24($fp)
lw $t0, -24($fp)
lw $t1, -28($fp)
move $t1, $t0
sw $t1, -28($fp)
lw $t0, -32($fp)
li $t1, 1
li $t2, 2
div $t0, $t1, $t2
sw $t0, -32($fp)
lw $t0, -36($fp)
li $t1, 15
lw $t2, -32($fp)
sub $t0, $t1, $t2
sw $t0, -36($fp)
lw $t0, -36($fp)
lw $t1, -40($fp)
move $t1, $t0
sw $t1, -40($fp)
lw $t0, -44($fp)
lw $t1, -16($fp)
lw $t2, -28($fp)
add $t0, $t1, $t2
sw $t0, -44($fp)
lw $t0, -48($fp)
lw $t1, -44($fp)
lw $t2, -40($fp)
add $t0, $t1, $t2
sw $t0, -48($fp)
lw $t0, -48($fp)
lw $t1, -52($fp)
move $t1, $t0
sw $t1, -52($fp)
lw $t0, -56($fp)
lw $t1, -16($fp)
lw $t2, -28($fp)
mul $t0, $t1, $t2
sw $t0, -56($fp)
lw $t0, -60($fp)
lw $t1, -40($fp)
li $t2, 2
div $t0, $t1, $t2
sw $t0, -60($fp)
lw $t0, -64($fp)
lw $t1, -56($fp)
lw $t2, -60($fp)
add $t0, $t1, $t2
sw $t0, -64($fp)
lw $t0, -64($fp)
lw $t1, -68($fp)
move $t1, $t0
sw $t1, -68($fp)
lw $t0, -72($fp)
lw $t1, -16($fp)
lw $t2, -28($fp)
sub $t0, $t1, $t2
sw $t0, -72($fp)
lw $t0, -76($fp)
lw $t1, -72($fp)
lw $t2, -40($fp)
sub $t0, $t1, $t2
sw $t0, -76($fp)
lw $t0, -76($fp)
lw $t1, -80($fp)
move $t1, $t0
sw $t1, -80($fp)
li $t0, 42
lw $t1, -84($fp)
move $t1, $t0
sw $t1, -84($fp)
li $t0, 0
lw $t1, -88($fp)
move $t1, $t0
sw $t1, -88($fp)
lw $t0, -92($fp)
lw $t1, -16($fp)
lw $t2, -28($fp)
add $t0, $t1, $t2
sw $t0, -92($fp)
lw $t0, -96($fp)
lw $t1, -92($fp)
lw $t2, -40($fp)
add $t0, $t1, $t2
sw $t0, -96($fp)
lw $t0, -100($fp)
lw $t1, -96($fp)
li $t2, 2000
add $t0, $t1, $t2
sw $t0, -100($fp)
lw $t0, -104($fp)
lw $t1, -100($fp)
lw $t2, -80($fp)
sub $t0, $t1, $t2
sw $t0, -104($fp)
lw $t0, -104($fp)
lw $t1, -80($fp)
move $t1, $t0
sw $t1, -80($fp)
label1:
lw $t0, -108($fp)
lw $t1, -16($fp)
lw $t2, -28($fp)
add $t0, $t1, $t2
sw $t0, -108($fp)
lw $t0, -108($fp)
lw $t1, -80($fp)
blt $t0, $t1, label2
j label3
label2:
lw $t0, -112($fp)
lw $t1, -88($fp)
li $t2, 12
mul $t0, $t1, $t2
sw $t0, -112($fp)
lw $t0, -116($fp)
lw $t1, -84($fp)
lw $t2, -112($fp)
add $t0, $t1, $t2
sw $t0, -116($fp)
lw $t0, -120($fp)
lw $t1, -116($fp)
li $t2, 4
add $t0, $t1, $t2
sw $t0, -120($fp)
lw $t0, -124($fp)
lw $t1, -120($fp)
li $t2, 5
add $t0, $t1, $t2
sw $t0, -124($fp)
lw $t0, -128($fp)
li $t1, 7
li $t2, 3
div $t0, $t1, $t2
sw $t0, -128($fp)
lw $t0, -132($fp)
lw $t1, -124($fp)
lw $t2, -128($fp)
add $t0, $t1, $t2
sw $t0, -132($fp)
lw $t0, -132($fp)
lw $t1, -84($fp)
move $t1, $t0
sw $t1, -84($fp)
addi $sp, $sp, -4
lw $t0, -80($fp)
sw $t0, 0($sp)
jal process
addi $sp, $sp, 4
lw $t0, -136($fp)
move $t0, $v0
sw $t0, -136($fp)
lw $t0, -140($fp)
li $t1, 2
lw $t2, -16($fp)
mul $t0, $t1, $t2
sw $t0, -140($fp)
lw $t0, -144($fp)
lw $t1, -136($fp)
lw $t2, -140($fp)
add $t0, $t1, $t2
sw $t0, -144($fp)
lw $t0, -148($fp)
lw $t1, -144($fp)
lw $t2, -80($fp)
sub $t0, $t1, $t2
sw $t0, -148($fp)
lw $t0, -152($fp)
lw $t1, -40($fp)
lw $t2, -52($fp)
mul $t0, $t1, $t2
sw $t0, -152($fp)
lw $t0, -156($fp)
lw $t1, -148($fp)
lw $t2, -152($fp)
add $t0, $t1, $t2
sw $t0, -156($fp)
lw $t0, -156($fp)
lw $t1, -160($fp)
move $t1, $t0
sw $t1, -160($fp)
lw $t0, -164($fp)
lw $t1, -88($fp)
lw $t2, -88($fp)
add $t0, $t1, $t2
sw $t0, -164($fp)
lw $t0, -164($fp)
lw $t1, -88($fp)
move $t1, $t0
sw $t1, -88($fp)
lw $t0, -168($fp)
lw $t1, -88($fp)
lw $t2, -88($fp)
add $t0, $t1, $t2
sw $t0, -168($fp)
lw $t0, -168($fp)
lw $t1, -88($fp)
move $t1, $t0
sw $t1, -88($fp)
lw $t0, -172($fp)
lw $t1, -88($fp)
lw $t2, -88($fp)
add $t0, $t1, $t2
sw $t0, -172($fp)
lw $t0, -172($fp)
lw $t1, -88($fp)
move $t1, $t0
sw $t1, -88($fp)
lw $t0, -176($fp)
lw $t1, -88($fp)
lw $t2, -88($fp)
add $t0, $t1, $t2
sw $t0, -176($fp)
lw $t0, -176($fp)
lw $t1, -88($fp)
move $t1, $t0
sw $t1, -88($fp)
lw $t0, -180($fp)
lw $t1, -88($fp)
lw $t2, -88($fp)
add $t0, $t1, $t2
sw $t0, -180($fp)
lw $t0, -180($fp)
lw $t1, -88($fp)
move $t1, $t0
sw $t1, -88($fp)
lw $t0, -184($fp)
lw $t1, -88($fp)
li $t2, 3
add $t0, $t1, $t2
sw $t0, -184($fp)
lw $t0, -184($fp)
lw $t1, -188($fp)
move $t1, $t0
sw $t1, -188($fp)
lw $t0, -192($fp)
lw $t1, -188($fp)
li $t2, 1
sub $t0, $t1, $t2
sw $t0, -192($fp)
lw $t0, -192($fp)
lw $t1, -188($fp)
move $t1, $t0
sw $t1, -188($fp)
lw $t0, -196($fp)
lw $t1, -188($fp)
li $t2, 3
add $t0, $t1, $t2
sw $t0, -196($fp)
lw $t0, -196($fp)
lw $t1, -188($fp)
move $t1, $t0
sw $t1, -188($fp)
lw $t0, -200($fp)
lw $t1, -188($fp)
li $t2, 6
sub $t0, $t1, $t2
sw $t0, -200($fp)
lw $t0, -200($fp)
lw $t1, -188($fp)
move $t1, $t0
sw $t1, -188($fp)
addi $sp, $sp, -4
lw $t0, -16($fp)
sw $t0, 0($sp)
jal process
addi $sp, $sp, 4
lw $t0, -204($fp)
move $t0, $v0
sw $t0, -204($fp)
lw $t0, -208($fp)
lw $t1, -16($fp)
li $t2, 3
add $t0, $t1, $t2
sw $t0, -208($fp)
lw $t0, -212($fp)
lw $t1, -208($fp)
li $t2, 2
sub $t0, $t1, $t2
sw $t0, -212($fp)
lw $t0, -216($fp)
lw $t1, -212($fp)
li $t2, 1
sub $t0, $t1, $t2
sw $t0, -216($fp)
addi $sp, $sp, -4
lw $t0, -216($fp)
sw $t0, 0($sp)
jal process
addi $sp, $sp, 4
lw $t0, -220($fp)
move $t0, $v0
sw $t0, -220($fp)
lw $t0, -204($fp)
lw $t1, -220($fp)
beq $t0, $t1, label4
j label5
label4:
lw $t0, -224($fp)
lw $t1, -80($fp)
li $t2, 2
sub $t0, $t1, $t2
sw $t0, -224($fp)
lw $t0, -228($fp)
lw $t1, -224($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -228($fp)
lw $t0, -228($fp)
lw $t1, -80($fp)
move $t1, $t0
sw $t1, -80($fp)
label5:
lw $t0, -232($fp)
lw $t1, -16($fp)
li $t2, 2
add $t0, $t1, $t2
sw $t0, -232($fp)
lw $t0, -236($fp)
lw $t1, -232($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -236($fp)
lw $t0, -236($fp)
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
j label1
label3:
lw $t0, -240($fp)
lw $t1, -84($fp)
li $t2, 12
sub $t0, $t1, $t2
sw $t0, -240($fp)
lw $t0, -240($fp)
lw $t1, -188($fp)
move $t1, $t0
sw $t1, -188($fp)
label6:
lw $t0, -188($fp)
lw $t1, -84($fp)
blt $t0, $t1, label7
j label8
label7:
lw $t0, -244($fp)
li $t1, 58
lw $t2, -16($fp)
add $t0, $t1, $t2
sw $t0, -244($fp)
lw $t0, -244($fp)
lw $t1, -80($fp)
move $t1, $t0
sw $t1, -80($fp)
lw $t0, -248($fp)
lw $t1, -84($fp)
li $t2, 12
sub $t0, $t1, $t2
sw $t0, -248($fp)
lw $t0, -248($fp)
lw $t1, -160($fp)
move $t1, $t0
sw $t1, -160($fp)
lw $t0, -252($fp)
lw $t1, -188($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -252($fp)
lw $t0, -252($fp)
lw $t1, -188($fp)
move $t1, $t0
sw $t1, -188($fp)
lw $t0, -84($fp)
lw $t1, -160($fp)
move $t1, $t0
sw $t1, -160($fp)
lw $t0, -256($fp)
lw $t1, -16($fp)
lw $t2, -28($fp)
add $t0, $t1, $t2
sw $t0, -256($fp)
lw $t0, -256($fp)
lw $t1, -88($fp)
move $t1, $t0
sw $t1, -88($fp)
lw $t0, -260($fp)
lw $t1, -16($fp)
lw $t2, -28($fp)
add $t0, $t1, $t2
sw $t0, -260($fp)
lw $t0, -260($fp)
lw $t1, -40($fp)
move $t1, $t0
sw $t1, -40($fp)
j label6
label8:
lw $t0, -80($fp)
move $a0, $t0
jal write
lw $t0, -264($fp)
lw $t1, -16($fp)
lw $t2, -28($fp)
add $t0, $t1, $t2
sw $t0, -264($fp)
lw $t0, -264($fp)
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
lw $t0, -268($fp)
lw $t1, -16($fp)
lw $t2, -28($fp)
add $t0, $t1, $t2
sw $t0, -268($fp)
lw $t0, -268($fp)
lw $t1, -28($fp)
move $t1, $t0
sw $t1, -28($fp)
lw $t0, -272($fp)
lw $t1, -16($fp)
lw $t2, -28($fp)
add $t0, $t1, $t2
sw $t0, -272($fp)
lw $t0, -272($fp)
lw $t1, -40($fp)
move $t1, $t0
sw $t1, -40($fp)
lw $t0, -276($fp)
lw $t1, -16($fp)
lw $t2, -28($fp)
add $t0, $t1, $t2
sw $t0, -276($fp)
lw $t0, -276($fp)
lw $t1, -80($fp)
move $t1, $t0
sw $t1, -80($fp)
lw $t0, -280($fp)
lw $t1, -16($fp)
lw $t2, -28($fp)
add $t0, $t1, $t2
sw $t0, -280($fp)
lw $t0, -280($fp)
lw $t1, -160($fp)
move $t1, $t0
sw $t1, -160($fp)
lw $t0, -284($fp)
lw $t1, -40($fp)
lw $t2, -80($fp)
add $t0, $t1, $t2
sw $t0, -284($fp)
lw $t0, -288($fp)
lw $t1, -284($fp)
lw $t2, -160($fp)
add $t0, $t1, $t2
sw $t0, -288($fp)
lw $t0, -288($fp)
move $a0, $t0
jal write
lw $ra, 4($fp)
addi $sp, $fp, 8
li $t0, 0
lw $fp, 0($fp)
move $v0, $t0
jr $ra
