bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; (e+g-2*b)/c, b,c byte, e,g word    
    b DB 1
    c DB 5
    e DW 3
    g DW 7
; our code starts here
segment code use32 class=code
    start:
        ; ...
    MOV AL,2 ; AL=02h
    MUL BYTE [b] ; AX=AL*b=02h*01h=0002h
    MOV DX,AX ; DX=0002h=2*b
    MOV AX,[e] ; AX=0003h
    ADD AX,[g] ; AX=000Ah
    SUB AX,DX ; AX=000Ah-0002h=0008h=e+g-2*b
    DIV byte [c] ; AL=0008h/05h=01h    AH=0008h%05h=03h
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
