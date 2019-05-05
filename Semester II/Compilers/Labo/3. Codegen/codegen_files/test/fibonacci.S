.globl main
main:                           # start of function main
    pushq     $1
    call      echo
    pushq     0xABCDEF          # void sentinel value
    popq      %rax              # discard expr output
    pushq     $0
    popq      %rax              # return a value
    jmp       main.exit         # exit function
main.exit:                      # end of function main
    retq                        # return to the caller
