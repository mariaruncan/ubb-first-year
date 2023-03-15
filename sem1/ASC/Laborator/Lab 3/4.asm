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
    a DB -4
    b DB 2
    c DB 3
    e DD -5
    x DQ -7

; our code starts here
segment code use32 class=code
    start:
        ; a/2+b*b-a*b*c+e+x= cu semn
        MOV AL, [a]         ; AL=a
        CBW                 ; AX=a
        MOV BL, 2
        IDIV BL             ; AL=a/2
        CBW                 ; AX=a/2
        MOV BX, AX          ; BX=a/2
       
        MOV AL, [b]
        IMUL byte [b]       ; AX=b*b
        
        ADD AX, BX          ; AX=a/2+b*b
        CWDE                ; EAX=a/2+b*b
        MOV EBX, EAX        ; EBX=a/2+b*b
        
        MOV AL, [a]         ; AL=a
        IMUL byte [b]       ; AX=a*b
        MOV DX, AX          ; DX=a*b
        MOV AL, [c]
        CBW                 ; AX=c
        IMUL DX             ; DX:AX=a*b*c
        
        PUSH AX
        PUSH DX
        POP EDX             ; EDX=a*b*c
        
        MOV EAX, EBX        ; EAX=a/2+b*b
        SUB EAX, EDX        ; EAX=a/2+b*b-a*b*c
        
        ADD EAX, dword [e]  ; EAX=a/2+b*b-a*b*c+e
        CDQ                 ; EDX:EAX=a/2+b*b-a*b*c+e
        
        ADD EAX, dword [x]
        ADC EDX, dword [x+4] ; EDX:EAX= a/2+b*b-a*b*c+e+x
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
