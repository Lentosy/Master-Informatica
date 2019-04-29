.globl main
main:                           # start of function main
    pushq     %rbx              # save callee-saved register
    pushq     %rbp              # save callee-saved register
    pushq     %rdi              # save callee-saved register
    pushq     %rsi              # save callee-saved register
    pushq     %r12              # save callee-saved register
    pushq     %r13              # save callee-saved register
    pushq     %r14              # save callee-saved register
    pushq     %r15              # save callee-saved register
    movq      %rsp, %rbx        # set the base pointer
    subq      $16, %rsp         # align the stack pointer by 16 bytes
    pushq     $1
    popq      %rax              # discard expr output
    pushq     $0
    popq      %rax              # return a value
    jmp       main.exit         # exit function
main.exit:                      # end of function main
    addq      $16, %rsp         # restore the stack pointer
    popq      %rax              # restore callee-saved register
    popq      %r15              # restore callee-saved register
    popq      %r14              # restore callee-saved register
    popq      %r13              # restore callee-saved register
    popq      %r12              # restore callee-saved register
    popq      %rsi              # restore callee-saved register
    popq      %rdi              # restore callee-saved register
    popq      %rbp              # restore callee-saved register
    retq                        # return to the caller
