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

main:
addi $sp, $sp, -8
sw $fp, 0($sp)
sw $ra, 4($sp)
move $fp, $sp
addi $sp, $sp, -72
li $t0, 1lw $t1, -4($fp)
move $t1, $t0
sw $t1, -4($fp)
li $t0, 11lw $t1, -8($fp)
move $t1, $t0
sw $t1, -8($fp)
li $t0, 39lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
li $t0, 0lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
lw $t0, -20($fp)
li $t1, 0lw $t2, -4($fp)
sub $t0, $t1, $t2
sw $t0, -20($fp)
lw $t0, -24($fp)
lw $t1, -20($fp)
lw $t2, -12($fp)
add $t0, $t1, $t2
sw $t0, -24($fp)
lw $t0, -28($fp)
li $t1, 17lw $t2, -4($fp)
mul $t0, $t1, $t2
sw $t0, -28($fp)
lw $t0, -32($fp)
li $t1, 0lw $t2, -28($fp)
sub $t0, $t1, $t2
sw $t0, -32($fp)
lw $t0, -4($fp)
lw $t1, -24($fp)
lw $t2, -32($fp)
add $t0, $t1, $t2
sw $t0, -4($fp)
lw $t0, -4($fp)
move $a0, $t0
jal write
lw $t0, -36($fp)
li $t1, 11lw $t2, -8($fp)
mul $t0, $t1, $t2
sw $t0, -36($fp)
lw $t0, -40($fp)
lw $t1, -4($fp)
lw $t2, -4($fp)
mul $t0, $t1, $t2
sw $t0, -40($fp)
lw $t0, -44($fp)
lw $t1, -12($fp)
lw $t2, -40($fp)
add $t0, $t1, $t2
sw $t0, -44($fp)
lw $t0, -48($fp)
lw $t1, -44($fp)
lw $t2, -4($fp)
mul $t0, $t1, $t2
sw $t0, -48($fp)
lw $t0, -8($fp)
lw $t1, -36($fp)
lw $t2, -48($fp)
sub $t0, $t1, $t2
sw $t0, -8($fp)
lw $t0, -8($fp)
move $a0, $t0
jal write
lw $t0, -52($fp)
lw $t1, -4($fp)
lw $t2, -8($fp)
div $t0, $t1, $t2
sw $t0, -52($fp)
lw $t0, -56($fp)
lw $t1, -4($fp)
lw $t2, -52($fp)
mul $t0, $t1, $t2
sw $t0, -56($fp)
lw $t0, -12($fp)
lw $t1, -56($fp)
lw $t2, -12($fp)
add $t0, $t1, $t2
sw $t0, -12($fp)
lw $t0, -12($fp)
move $a0, $t0
jal write
lw $t0, -60($fp)
li $t1, 4lw $t2, -4($fp)
mul $t0, $t1, $t2
sw $t0, -60($fp)
lw $t0, -64($fp)
lw $t1, -8($fp)
li $t2, 17div $t0, $t1, $t2
sw $t0, -64($fp)
lw $t0, -68($fp)
lw $t1, -60($fp)
lw $t2, -64($fp)
add $t0, $t1, $t2
sw $t0, -68($fp)
lw $t0, -72($fp)
lw $t1, -4($fp)
lw $t2, -12($fp)
mul $t0, $t1, $t2
sw $t0, -72($fp)
lw $t0, -16($fp)
lw $t1, -68($fp)
lw $t2, -72($fp)
add $t0, $t1, $t2
sw $t0, -16($fp)
lw $t0, -16($fp)
move $a0, $t0
jal write
lw $ra, 4($fp)
addi $ra, $fp, 8
lw $fp, 0($fp)
li $t0, 0move $v0, $t0
jr $ra
