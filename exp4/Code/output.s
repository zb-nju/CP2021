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

quick_power_mod:
addi $sp, $sp, -8
sw $fp, 0($sp)
sw $ra, 4($sp)
move $fp, $sp
addi $sp, $sp, -20
li $t0, 1
lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
lw $t0, 8($fp)
li $t1, 0
ble $t0, $t1, label1
j label5
label5:
lw $t0, 12($fp)
li $t1, 0
ble $t0, $t1, label1
j label4
label4:
lw $t0, 16($fp)
li $t1, 0
ble $t0, $t1, label1
j label2
label1:
lw $t0, -8($fp)
li $t1, 0
li $t2, 1
sub $t0, $t1, $t2
sw $t0, -8($fp)
lw $ra, 4($fp)
addi $sp, $fp, 8
lw $fp, 0($fp)
lw $t0, -8($fp)
move $v0, $t0
jr $ra
j label3
label2:
addi $sp, $sp, -4
lw $t0, 16($fp)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, 8($fp)
sw $t0, 0($sp)
jal mod
addi $sp, $sp, 8
lw $t0, 8($fp)
move $t0, $v0
sw $t0, 8($fp)
label6:
lw $t0, 12($fp)
li $t1, 0
bne $t0, $t1, label7
j label8
label7:
addi $sp, $sp, -4
li $t0, 2
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, 12($fp)
sw $t0, 0($sp)
jal mod
addi $sp, $sp, 8
lw $t0, -12($fp)
move $t0, $v0
sw $t0, -12($fp)
lw $t0, -12($fp)
li $t1, 1
beq $t0, $t1, label9
j label10
label9:
lw $t0, -16($fp)
lw $t1, -4($fp)
lw $t2, 8($fp)
mul $t0, $t1, $t2
sw $t0, -16($fp)
addi $sp, $sp, -4
lw $t0, 16($fp)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -16($fp)
sw $t0, 0($sp)
jal mod
addi $sp, $sp, 8
lw $t0, -4($fp)
move $t0, $v0
sw $t0, -4($fp)
label10:
lw $t0, 12($fp)
lw $t1, 12($fp)
li $t2, 2
div $t0, $t1, $t2
sw $t0, 12($fp)
lw $t0, -20($fp)
lw $t1, 8($fp)
lw $t2, 8($fp)
mul $t0, $t1, $t2
sw $t0, -20($fp)
addi $sp, $sp, -4
lw $t0, 16($fp)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -20($fp)
sw $t0, 0($sp)
jal mod
addi $sp, $sp, 8
lw $t0, 8($fp)
move $t0, $v0
sw $t0, 8($fp)
j label6
label8:
lw $ra, 4($fp)
addi $sp, $fp, 8
lw $fp, 0($fp)
lw $t0, -4($fp)
move $v0, $t0
jr $ra
label3:

main:
addi $sp, $sp, -8
sw $fp, 0($sp)
sw $ra, 4($sp)
move $fp, $sp
addi $sp, $sp, -40
li $t0, 0
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
label11:
lw $t0, -16($fp)
li $t1, 3
blt $t0, $t1, label12
j label13
label12:
lw $t0, -20($fp)
li $t1, 4
lw $t2, -16($fp)
mul $t0, $t1, $t2
sw $t0, -20($fp)
lw $t0, -24($fp)
addi $t1, $fp, -12
lw $t2, -20($fp)
add $t0, $t1, $t2
sw $t0, -24($fp)
jal read
lw $t0, -24($fp)
lw $t0, 0($t0)
move $t0, $v0
sw $t0, -24($fp)
lw $t0, -16($fp)
lw $t1, -16($fp)
li $t2, 1
add $t0, $t1, $t2
sw $t0, -16($fp)
j label11
label13:
lw $t0, -28($fp)
addi $t1, $fp, -12
li $t2, 0
add $t0, $t1, $t2
sw $t0, -28($fp)
lw $t0, -32($fp)
addi $t1, $fp, -12
li $t2, 4
add $t0, $t1, $t2
sw $t0, -32($fp)
lw $t0, -36($fp)
addi $t1, $fp, -12
li $t2, 8
add $t0, $t1, $t2
sw $t0, -36($fp)
addi $sp, $sp, -4
lw $t0, -36($fp)
lw $t0, 0($t0)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -32($fp)
lw $t0, 0($t0)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -28($fp)
lw $t0, 0($t0)
sw $t0, 0($sp)
jal quick_power_mod
addi $sp, $sp, 12
lw $t0, -40($fp)
move $t0, $v0
sw $t0, -40($fp)
lw $t0, -40($fp)
move $a0, $t0
jal write
lw $ra, 4($fp)
addi $sp, $fp, 8
lw $fp, 0($fp)
li $t0, 0
move $v0, $t0
jr $ra
