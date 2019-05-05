.globl do_echo
do_echo:                        # start of function do_echo
    pushq     %rbx              # save callee-saved register
    pushq     %rbp              # save callee-saved register
    pushq     %rdi              # save callee-saved register
    pushq     %rsi              # save callee-saved register
    pushq     %r12              # save callee-saved register
    pushq     %r13              # save callee-saved register
    pushq     %r14              # save callee-saved register
    pushq     %r15              # save callee-saved register
    pushq     %rbx              # store value of base pointer on stack
    movq      %rsp, %rbx        # copy value of stack pointer into base pointer
    subq      $16, %rsp         # align the stack pointer by 16 bytes
    subq      $4, %rsp          # allocate space for the variable
    movq      -4(%rbp), %rax    # access variable 'i'
    pushq     %rax
    call      echo
    popq      %rax              # discard expr output
do_echo.exit:                   # end of function do_echo
    movq      %rbx, %rsp        # restore stack pointer value to base pointer value
    popq      %rbx              # restore base pointer value
    popq      %r15              # restore callee-saved register
    popq      %r14              # restore callee-saved register
    popq      %r13              # restore callee-saved register
    popq      %r12              # restore callee-saved register
    popq      %rsi              # restore callee-saved register
    popq      %rdi              # restore callee-saved register
    popq      %rbp              # restore callee-saved register
    popq      %rbx              # restore callee-saved register
    retq                        # return to the caller
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
    pushq     %rbx              # store value of base pointer on stack
    movq      %rsp, %rbx        # copy value of stack pointer into base pointer
    subq      $16, %rsp         # align the stack pointer by 16 bytes
    call      do_echo
    popq      %rax              # discard expr output
    pushq     $0
    popq      %rax              # return a value
    jmp       main.exit         # exit function
main.exit:                      # end of function main
    movq      %rbx, %rsp        # restore stack pointer value to base pointer value
    popq      %rbx              # restore base pointer value
    popq      %r15              # restore callee-saved register
    popq      %r14              # restore callee-saved register
    popq      %r13              # restore callee-saved register
    popq      %r12              # restore callee-saved register
    popq      %rsi              # restore callee-saved register
    popq      %rdi              # restore callee-saved register
    popq      %rbp              # restore callee-saved register
    popq      %rbx              # restore callee-saved register
    retq                        # return to the caller
