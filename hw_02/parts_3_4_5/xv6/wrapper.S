.globl __wrapper
__wrapper:
  pushl   %ebp
  movl    %esp, %ebp
  pushal
  call    *4(%ebp)
  popal
  movl    %ebp, %esp
  popl    %ebp
  add     $4, %esp
  ret

