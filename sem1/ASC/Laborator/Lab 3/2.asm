bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - byte, b - word, c - double word, d - qword - Interpretare cu semn
    a DB 1
    b DW 3
    c DD 5
    d DQ 7

; our code starts here
segment code use32 class=code
    start:
        ; c+b-(a-d+b)
    MOV AL, [a]         ;  AL=a
    CBW                 ;  AX=a
    CWDE                ;  EAX=a
    CDQ                 ;  EDX:EAX=a
    SUB EAX, dword [d]
    SBB EDX, dword[d+4] ;  EDX:EAX=a-d
    MOV ECX, EDX
    MOV EBX, EAX        ;  ECX:EBX=a-d
    
    MOV AX, [b]         ;  AX=b
    CWDE                ;  EAX=b
    CDQ                 ;  EDX:EAX=b
    
    ADD EBX, EAX
    ADC ECX, EDX        ;  ECX:EBX=a-d+b
    
    MOV AX, [b]         ;  AX=b
    CWDE                ;  EAX=b
    ADD EAX, [c]        ;  EAX=c+b
    CDQ                 ;  EDX:EAX=c+b
    
    SUB EAX, EBX
    SBB EDX, ECX        ;  EDX:EAX=c+b-(a-d+b)
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
