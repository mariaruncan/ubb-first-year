bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; d+[(a+b)*5-(c+c)*5]
    a DB 2
    b DB 3
    c DB 1
    d DW 5

; our code starts here
segment code use32 class=code
    start:
        ; ...
    MOV AL,[a] ; AL=02h
    ADD AL,[b] ; AL=05h
    MOV DL,5 ; DL=05h
    MUL DL ; AX=AL*DL=05h*05h=0019h
    MOV DX,AX ; DX=AX=0019h=(a+b)*5
    MOV AL,[c] ; AL=01h
    ADD AL,[c] ; AL=02h
    MOV BL,5 ; BL=05h
    MUL BL ; AX=AL*BL=02h*05h=000Ah=(c+c)*5
    SUB DX,AX ; DX=0019h-000Ah=000Fh=[(a+b)*5-(c+c)*5]
    MOV AX,[d] ; AX=0005h
    ADD AX,DX ; AX=0005h+000Fh=0014h=d+[(a+b)*5-(c+c)*5]
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
