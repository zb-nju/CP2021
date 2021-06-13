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

fact:
addi $sp, $sp, -8
sw $fp, 0($sp)
sw $ra, 4($sp)
move $fp, $sp
addi $sp, $sp, -12
lw $t0, 8($fp)
li $t1, 0
ble $t0, $t1, label1
j label2
label1:
lw $ra, 4($fp)
addi $sp, $fp, 8
lw $fp, 0($fp)
li $t0, 1
move $v0, $t0
jr $ra
j label3
label2:
lw $t0, -4($fp)
lw $t1, 8($fp)
li $t2, 1
sub $t0, $t1, $t2
sw $t0, -4($fp)
addi $sp, $sp, -4
lw $t0, -4($fp)
sw $t0, 0($sp)
jal fact
addi $sp, $sp, 4
lw $t0, -8($fp)
move $t0, $v0
sw $t0, -8($fp)
lw $t0, -12($fp)
lw $t1, 8($fp)
lw $t2, -8($fp)
mul $t0, $t1, $t2
sw $t0, -12($fp)
lw $ra, 4($fp)
addi $sp, $fp, 8
lw $fp, 0($fp)
lw $t0, -12($fp)
move $v0, $t0
jr $ra
label3:

isqrt:
addi $sp, $sp, -8
sw $fp, 0($sp)
sw $ra, 4($sp)
move $fp, $sp
addi $sp, $sp, -28
li $t0, 0
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
label4:
lw $t0, -4($fp)
lw $t1, 8($fp)
blt $t0, $t1, label5
j label6
label5:
lw $t0, -8($fp)
lw $t1, -4($fp)
lw $t2, -4($fp)
mul $t0, $t1, $t2
sw $t0, -8($fp)
lw $t0, -8($fp)
lw $t1, 8($fp)
ble $t0, $t1, label9
j label8
label9:
lw $t0, -12($fp)
lw $t1, -4($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -12($fp)
lw $t0, -16($fp)
lw $t1, -4($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -16($fp)
lw $t0, -20($fp)
lw $t1, -12($fp)
lw $t2, -16($fp)
mul $t0, $t1, $t2
sw $t0, -20($fp)
lw $t0, -20($fp)
lw $t1, 8($fp)
bgt $t0, $t1, label7
j label8
label7:
lw $ra, 4($fp)
addi $sp, $fp, 8
lw $fp, 0($fp)
lw $t0, -4($fp)
move $v0, $t0
jr $ra
label8:
lw $t0, -24($fp)
lw $t1, -4($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -24($fp)
lw $t0, -24($fp)
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
j label4
label6:
lw $t0, -28($fp)
li $t1, 0
li $t2, 1
sub $t0, $t1, $t2
sw $t0, -28($fp)
lw $ra, 4($fp)
addi $sp, $fp, 8
lw $fp, 0($fp)
lw $t0, -28($fp)
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
lw $fp, 0($fp)
lw $t0, -12($fp)
move $v0, $t0
jr $ra

main:
addi $sp, $sp, -8
sw $fp, 0($sp)
sw $ra, 4($sp)
move $fp, $sp
addi $sp, $sp, -4284
li $t0, 1331
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
li $t0, 1217
lw $t1, -8($fp)
move $t1, $t0
sw $t1, -8($fp)
lw $t0, -12($fp)
li $t1, 0
li $t2, 22121
sub $t0, $t1, $t2
sw $t0, -12($fp)
lw $t0, -12($fp)
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
li $t0, 5
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
lw $t0, -24($fp)
lw $t1, -8($fp)
li $t2, 7
mul $t0, $t1, $t2
sw $t0, -24($fp)
lw $t0, -28($fp)
lw $t1, -24($fp)
lw $t2, -4($fp)
div $t0, $t1, $t2
sw $t0, -28($fp)
lw $t0, -32($fp)
lw $t1, -8($fp)
li $t2, 23
add $t0, $t1, $t2
sw $t0, -32($fp)
lw $t0, -36($fp)
li $t1, 2080
lw $t2, -32($fp)
div $t0, $t1, $t2
sw $t0, -36($fp)
lw $t0, -40($fp)
lw $t1, -28($fp)
lw $t2, -36($fp)
add $t0, $t1, $t2
sw $t0, -40($fp)
lw $t0, -40($fp)
lw $t1, -44($fp)
move $t1, $t0
sw $t1, -44($fp)
lw $t0, -48($fp)
lw $t1, -8($fp)
li $t2, 20
add $t0, $t1, $t2
sw $t0, -48($fp)
lw $t0, -52($fp)
lw $t1, -48($fp)
li $t2, 3
add $t0, $t1, $t2
sw $t0, -52($fp)
lw $t0, -56($fp)
li $t1, 19990
lw $t2, -52($fp)
div $t0, $t1, $t2
sw $t0, -56($fp)
lw $t0, -56($fp)
lw $t1, -60($fp)
move $t1, $t0
sw $t1, -60($fp)
li $t0, 0
lw $t1, -64($fp)
move $t1, $t0
sw $t1, -64($fp)
li $t0, 0
lw $t1, -68($fp)
move $t1, $t0
sw $t1, -68($fp)
li $t0, 0
lw $t1, -72($fp)
move $t1, $t0
sw $t1, -72($fp)
label10:
addi $sp, $sp, -4
lw $t0, -8($fp)
sw $t0, 0($sp)
jal isqrt
addi $sp, $sp, 4
lw $t0, -4076($fp)
move $t0, $v0
sw $t0, -4076($fp)
addi $sp, $sp, -4
lw $t0, -4076($fp)
sw $t0, 0($sp)
jal isqrt
addi $sp, $sp, 4
lw $t0, -4080($fp)
move $t0, $v0
sw $t0, -4080($fp)
addi $sp, $sp, -4
lw $t0, -4080($fp)
sw $t0, 0($sp)
jal fact
addi $sp, $sp, 4
lw $t0, -4084($fp)
move $t0, $v0
sw $t0, -4084($fp)
lw $t0, -64($fp)
lw $t1, -4084($fp)
blt $t0, $t1, label11
j label12
label11:
addi $sp, $sp, -4
li $t0, 4
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -64($fp)
sw $t0, 0($sp)
jal mod
addi $sp, $sp, 8
lw $t0, -4088($fp)
move $t0, $v0
sw $t0, -4088($fp)
addi $sp, $sp, -4
lw $t0, -4088($fp)
sw $t0, 0($sp)
jal fact
addi $sp, $sp, 4
lw $t0, -4092($fp)
move $t0, $v0
sw $t0, -4092($fp)
lw $t0, -4096($fp)
li $t1, 4
lw $t2, -64($fp)
mul $t0, $t1, $t2
sw $t0, -4096($fp)
lw $t0, -4100($fp)
addi $t1, $fp, -4072
lw $t2, -4096($fp)
add $t0, $t1, $t2
sw $t0, -4100($fp)
lw $t0, -4092($fp)
lw $t1, -4100($fp)
sw $t0, 0($t1)
lw $t0, -4104($fp)
lw $t1, -64($fp)
li $t2, 4
div $t0, $t1, $t2
sw $t0, -4104($fp)
lw $t0, -4108($fp)
lw $t1, -4104($fp)
li $t2, 4
mul $t0, $t1, $t2
sw $t0, -4108($fp)
lw $t0, -4112($fp)
lw $t1, -64($fp)
lw $t2, -4108($fp)
add $t0, $t1, $t2
sw $t0, -4112($fp)
lw $t0, -4112($fp)
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $t0, -4116($fp)
lw $t1, -64($fp)
li $t2, 4
div $t0, $t1, $t2
sw $t0, -4116($fp)
lw $t0, -4120($fp)
lw $t1, -4116($fp)
li $t2, 4
mul $t0, $t1, $t2
sw $t0, -4120($fp)
lw $t0, -4124($fp)
lw $t1, -4($fp)
lw $t2, -4120($fp)
add $t0, $t1, $t2
sw $t0, -4124($fp)
lw $t0, -4124($fp)
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $t0, -4128($fp)
lw $t1, -64($fp)
li $t2, 4
div $t0, $t1, $t2
sw $t0, -4128($fp)
lw $t0, -4132($fp)
lw $t1, -4128($fp)
li $t2, 4
mul $t0, $t1, $t2
sw $t0, -4132($fp)
lw $t0, -4136($fp)
lw $t1, -4($fp)
lw $t2, -4132($fp)
add $t0, $t1, $t2
sw $t0, -4136($fp)
lw $t0, -4136($fp)
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $t0, -4140($fp)
lw $t1, -64($fp)
li $t2, 4
div $t0, $t1, $t2
sw $t0, -4140($fp)
lw $t0, -4144($fp)
lw $t1, -4140($fp)
li $t2, 4
mul $t0, $t1, $t2
sw $t0, -4144($fp)
lw $t0, -4148($fp)
lw $t1, -4($fp)
lw $t2, -4144($fp)
add $t0, $t1, $t2
sw $t0, -4148($fp)
lw $t0, -4148($fp)
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
label13:
lw $t0, -4152($fp)
lw $t1, -20($fp)
lw $t2, -20($fp)
mul $t0, $t1, $t2
sw $t0, -4152($fp)
lw $t0, -4156($fp)
lw $t1, -4152($fp)
lw $t2, -20($fp)
mul $t0, $t1, $t2
sw $t0, -4156($fp)
lw $t0, -16($fp)
lw $t1, -4156($fp)
blt $t0, $t1, label14
j label15
label14:
addi $sp, $sp, -4
li $t0, 10
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -4($fp)
sw $t0, 0($sp)
jal mod
addi $sp, $sp, 8
lw $t0, -4160($fp)
move $t0, $v0
sw $t0, -4160($fp)
lw $t0, -4164($fp)
lw $t1, -4160($fp)
li $t2, 10
add $t0, $t1, $t2
sw $t0, -4164($fp)
lw $t0, -4168($fp)
lw $t1, -4164($fp)
lw $t2, -16($fp)
add $t0, $t1, $t2
sw $t0, -4168($fp)
lw $t0, -4172($fp)
lw $t1, -4168($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -4172($fp)
lw $t0, -4176($fp)
lw $t1, -4172($fp)
lw $t2, -44($fp)
add $t0, $t1, $t2
sw $t0, -4176($fp)
lw $t0, -4180($fp)
lw $t1, -4176($fp)
lw $t2, -60($fp)
sub $t0, $t1, $t2
sw $t0, -4180($fp)
lw $t0, -4180($fp)
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
j label13
label15:
addi $sp, $sp, -4
lw $t0, -16($fp)
sw $t0, 0($sp)
jal isqrt
addi $sp, $sp, 4
lw $t0, -4184($fp)
move $t0, $v0
sw $t0, -4184($fp)
addi $sp, $sp, -4
li $t0, 10
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -4184($fp)
sw $t0, 0($sp)
jal mod
addi $sp, $sp, 8
lw $t0, -4188($fp)
move $t0, $v0
sw $t0, -4188($fp)
addi $sp, $sp, -4
lw $t0, -4188($fp)
sw $t0, 0($sp)
jal fact
addi $sp, $sp, 4
lw $t0, -4192($fp)
move $t0, $v0
sw $t0, -4192($fp)
lw $t0, -4196($fp)
lw $t1, -16($fp)
lw $t2, -4192($fp)
add $t0, $t1, $t2
sw $t0, -4196($fp)
lw $t0, -4196($fp)
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
lw $t0, -4200($fp)
lw $t1, -64($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -4200($fp)
lw $t0, -4200($fp)
lw $t1, -64($fp)
move $t1, $t0
sw $t1, -64($fp)
j label10
label12:
li $t0, 0
lw $t1, -64($fp)
move $t1, $t0
sw $t1, -64($fp)
label16:
lw $t0, -64($fp)
li $t1, 10
blt $t0, $t1, label17
j label18
label17:
li $t0, 0
lw $t1, -68($fp)
move $t1, $t0
sw $t1, -68($fp)
label19:
lw $t0, -68($fp)
li $t1, 10
blt $t0, $t1, label20
j label21
label20:
lw $t0, -64($fp)
li $t1, 0
beq $t0, $t1, label25
j label23
label25:
lw $t0, -68($fp)
li $t1, 0
beq $t0, $t1, label22
j label23
label22:
li $t0, 1
lw $t1, -72($fp)
move $t1, $t0
sw $t1, -72($fp)
j label24
label23:
li $t0, 0
lw $t1, -72($fp)
move $t1, $t0
sw $t1, -72($fp)
label24:
label26:
lw $t0, -72($fp)
li $t1, 10
blt $t0, $t1, label27
j label28
label27:
lw $t0, -4204($fp)
lw $t1, -64($fp)
li $t2, 10
mul $t0, $t1, $t2
sw $t0, -4204($fp)
lw $t0, -4208($fp)
lw $t1, -4204($fp)
li $t2, 10
mul $t0, $t1, $t2
sw $t0, -4208($fp)
lw $t0, -4212($fp)
lw $t1, -68($fp)
li $t2, 10
mul $t0, $t1, $t2
sw $t0, -4212($fp)
lw $t0, -4216($fp)
lw $t1, -4208($fp)
lw $t2, -4212($fp)
add $t0, $t1, $t2
sw $t0, -4216($fp)
lw $t0, -4220($fp)
lw $t1, -4216($fp)
lw $t2, -72($fp)
add $t0, $t1, $t2
sw $t0, -4220($fp)
lw $t0, -4224($fp)
li $t1, 4
lw $t2, -4220($fp)
mul $t0, $t1, $t2
sw $t0, -4224($fp)
lw $t0, -4228($fp)
addi $t1, $fp, -4072
lw $t2, -4224($fp)
add $t0, $t1, $t2
sw $t0, -4228($fp)
lw $t0, -4232($fp)
lw $t1, -20($fp)
lw $t2, -4228($fp)
lw $t2, 0($t2)
add $t0, $t1, $t2
sw $t0, -4232($fp)
lw $t0, -4236($fp)
lw $t1, -64($fp)
li $t2, 10
mul $t0, $t1, $t2
sw $t0, -4236($fp)
lw $t0, -4240($fp)
lw $t1, -4236($fp)
li $t2, 10
mul $t0, $t1, $t2
sw $t0, -4240($fp)
lw $t0, -4244($fp)
lw $t1, -68($fp)
li $t2, 10
mul $t0, $t1, $t2
sw $t0, -4244($fp)
lw $t0, -4248($fp)
lw $t1, -4240($fp)
lw $t2, -4244($fp)
add $t0, $t1, $t2
sw $t0, -4248($fp)
lw $t0, -4252($fp)
lw $t1, -4248($fp)
lw $t2, -72($fp)
add $t0, $t1, $t2
sw $t0, -4252($fp)
lw $t0, -4256($fp)
lw $t1, -4252($fp)
li $t2, 1
sub $t0, $t1, $t2
sw $t0, -4256($fp)
lw $t0, -4260($fp)
li $t1, 4
lw $t2, -4256($fp)
mul $t0, $t1, $t2
sw $t0, -4260($fp)
lw $t0, -4264($fp)
addi $t1, $fp, -4072
lw $t2, -4260($fp)
add $t0, $t1, $t2
sw $t0, -4264($fp)
lw $t0, -4268($fp)
lw $t1, -4232($fp)
lw $t2, -4264($fp)
lw $t2, 0($t2)
sub $t0, $t1, $t2
sw $t0, -4268($fp)
lw $t0, -4268($fp)
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
lw $t0, -4272($fp)
lw $t1, -72($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -4272($fp)
lw $t0, -4272($fp)
lw $t1, -72($fp)
move $t1, $t0
sw $t1, -72($fp)
j label26
label28:
lw $t0, -4276($fp)
lw $t1, -68($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -4276($fp)
lw $t0, -4276($fp)
lw $t1, -68($fp)
move $t1, $t0
sw $t1, -68($fp)
j label19
label21:
lw $t0, -4280($fp)
lw $t1, -64($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -4280($fp)
lw $t0, -4280($fp)
lw $t1, -64($fp)
move $t1, $t0
sw $t1, -64($fp)
j label16
label18:
lw $t0, -4284($fp)
lw $t1, -20($fp)
lw $t2, -16($fp)
add $t0, $t1, $t2
sw $t0, -4284($fp)
lw $t0, -4284($fp)
lw $t1, -64($fp)
move $t1, $t0
sw $t1, -64($fp)
lw $t0, -64($fp)
move $a0, $t0
jal write
lw $ra, 4($fp)
addi $sp, $fp, 8
lw $fp, 0($fp)
li $t0, 0
move $v0, $t0
jr $ra
