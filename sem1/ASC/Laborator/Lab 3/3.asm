bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a,b,c-byte; e-doubleword; x-qword
    a DB 4
    b DB 6
    c DB 1
    e DD 3
    x DQ 5

; our code starts here
segment code use32 class=code
    start:
        ; a/2+b*b-a*b*c+e+x=22 fara semn
        
        MOV AL, [a]
        MOV AH, 0       ; AX=a
        MOV BL, 2
        DIV BL          ; AL=a/2
        MOV BL, AL      ; BL=a/2
        MOV BH, 0       ; BX=a/2
        
        MOV AL, [b]
        MUL AL          ; AX=b*b
        
        ADD BX, AX      ; BX=a/2+b*b
        MOV CX, 0       ; CX:BX=a/2+b*b
        
        MOV AL, [a]     ; AL=a
        MUL byte [b]    ; AX=a*b
        MOV DL, [c]
        MOV DH, 0       ; DX=c
        MUL DX          ; DX:AX=a*b*c
        
        SUB BX, AX
        SBB CX, DX      ; BX:CX=a/2+b*b-a*b*c
        
        ADD CX, word [e]
        ADC BX, word [e+2] ; BX:CX=a/2+b*b-a*b*c-e
        
        PUSH BX
        PUSH CX
        POP EAX         ; EAX=a/2+b*b-a*b*c-e
        MOV EDX, 0      ; EDX:EAX=a/2+b*b-a*b*c-e
        
        SUB EAX, dword[x]
        SBB EDX, dword[x+4] ; EDX:EAX=a/2+b*b-a*b*c-e-x
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
