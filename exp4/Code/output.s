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
li $t0, 3289972
li $t1, 28
li $t2, 10
div $t0, $t1, $t2
