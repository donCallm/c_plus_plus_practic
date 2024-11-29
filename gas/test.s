.globl _start

.section .data
msg: .asciz "TEST\n"

.section .text
_start:
    movq $msg, %rsi
    movq $1, %rdi
    movq $5, %rdx
    movq $1, %rax
    syscall

    movq $50, %rdi  # rdi = 50
    addq $10, %rdi  # rdi += 10
    subq $10, %rdi  # rdi -= 10

    movq $10, %rcx  # rcx
    addq %rcx, %rdi # rdi += rcx || rdi += 10 
    subq %rcx, %rdi # rdi -= rcx || rdi -= 10

    incq %rdi       # ++rdi
    decq %rdi       # --rdi

    movq $4, %rax
    movq $4, %rbx
    mulq %rbx       # rax *= rbx == 4 * 4
    movq %rax, %rdi # rdi = rax || rax = 16

    movq $5, %rax
    movq $2, %rbx
    div $rbx        # rax %= 2 || (rax = 2 && rdx = 5)
    movq %rax, %rdi # rdi = 2
    movq %rdx, %rdi # rdi = 5

    movq $60, %rax
    syscall
