.section .text

.globl setjmp, longjmp

setjmp:
    movq %rbp, 0(%rdi)
    movq %rsp, 8(%rdi)
    movq 0(%rsp), %rdx
    movq %rdx, 16(%rdi)
    movq $0, %rax
    retq

longjmp:
    movq 0(%rdi), %rbp
    movq 8(%rdi), %rsp
    movq 16(%rdi), %rdx
    movq %rdx, 0(%rsp)
    movq $1, %rax
    retq