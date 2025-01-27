SUB INLINE
$INLINE

'    INLINE procedure on this page is:

'      program segment   ; begin program segment
'      assume cs:program

      push BP           ; save the Base Pointer
      mov  BP,SP        ; move stack pointer to BP
      les  DI,[BP+6]    ; offset address of parameter
      mov  AX, 64h      ; constant to fill
      mov  CX, C8h      ; length of fill
      cld               ; clear the direction flag
      rep               ; fill the words
      stosw
      pop  BP           ; restore Base Pointer

      program ends      ; end program segment
      ends              ; end compilation


'    Note that there is no RET at the end of the routine. You may
'    run this code through The MicroSoft Assembler to generate the
'    code listed in the manual.
END SUB