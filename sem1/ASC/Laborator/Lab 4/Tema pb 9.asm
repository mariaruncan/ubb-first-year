bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se de cuvantul A si octetul B. Sa se obtina dublucuvantul C astfel:
    ; bitii 0-3 ai lui C coincid cu bitii 6-9 ai lui A
    ; bitii 4-5 ai lui C au valoarea 1
    ; bitii 6-7 ai lui C coincid cu bitii 1-2 ai lui B
    ; bitii 8-23 ai lui C coincid cu bitii lui A
    ; bitii 24-31 ai lui C coincid cu bitii lui B
 
    a DW 1010111101010000b
    b DB 11010110b
    c RESD 1
    
; our code starts here
segment code use32 class=code
    start:
        ; c = b7 b6 b5 b4 b3 b2 b1 b0    a15 a14 a13 a12 a11 a10 a9 a8   a7 a6 a5 a4 a3 a2 a1 a0    b2 b1 1 1 a9 a8 a7 a6
    MOV EBX, 0                 ; in EBX calculam rezultatul
    
    
    MOV EAX, 0
    MOV AX, [a]                ; izolam bitii 6-9 ai lui a
    AND AX, 0000001111000000b  ; AX = 0 0 0 0 0 0 a9 a8    a7 a6 0 0 0 0 0 0 
    MOV CL, 6
    ROR AX, CL                 ; rotim 6 poz spre dreapta   AX = 0 0 0 0 0 0 0 0   0 0 0 0 a9 a8 a7 a6
    OR EBX, EAX                ; punem bitii in rezultat    EBX = 0 0 0 0 0 0 0 0   0 0 0 0 0 0 0 0   0 0 0 0 0 0 0 0   0 0 0 0 a9 a8 a7 a6

    
    OR BL, 00110000b           ; facem bitii 4-5 din rezultat sa aiba valoarea 1
                               ; EBX = 0 0 0 0 0 0 0 0   0 0 0 0 0 0 0 0   0 0 0 0 0 0 0 0   0 0 1 1 a9 a8 a7 a6
    
    
    MOV EAX, 0
    MOV AL, [b]                ; izolam bitii 1-2 ai lui b
    AND AL, 00000110b          ; AL = 0 0 0 0 0 b2 b1 0
    MOV CL, 5
    ROL AL, CL                 ; rotim 5 poz spre stanga   AL = b2 b1 0 0 0 0 0 0
    OR EBX, EAX                ; punem bitii in rezultat   EBX = 0 0 0 0 0 0 0 0   0 0 0 0 0 0 0 0   0 0 0 0 0 0 0 0   b2 b1 1 1 a9 a8 a7 a6
    
    
    MOV EAX, 0
    MOV AX, [a]                ; EAX = 0 0 0 0 0 0 0 0   0 0 0 0 0 0 0 0   a15 a14 a13 a12 a11 a10 a9 a8    a7 a6 a5 a4 a3 a2 a1 a0
    MOV CL, 8
    ROL EAX, CL                ; rotim 8 poz spre stanga
                               ; EAX = 0 0 0 0 0 0 0 0   a15 a14 a13 a12 a11 a10 a9 a8    a7 a6 a5 a4 a3 a2 a1 a0   0 0 0 0 0 0 0 0
    OR EBX, EAX                ; punem bitii in rezultat  
                               ; EBX = 0 0 0 0 0 0 0 0   a15 a14 a13 a12 a11 a10 a9 a8    a7 a6 a5 a4 a3 a2 a1 a0   b2 b1 1 1 a9 a8 a7 a6
    
    
    MOV EAX, 0
    MOV AL, [b]                ; EAX = 0 0 0 0 0 0 0 0    0 0 0 0 0 0 0 0    0 0 0 0 0 0 0 0    b7 b6 b5 b4 b3 b2 b1 b0
    MOV CL, 24
    ROL EAX, CL                ; rotim 24 poz spre stanga
                               ; EAX = b7 b6 b5 b4 b3 b2 b1 b0    0 0 0 0 0 0 0 0    0 0 0 0 0 0 0 0    0 0 0 0 0 0 0 0
    OR EBX, EAX                ; punem bitii in rezultat
                               ; EBX = b7 b6 b5 b4 b3 b2 b1 b0   a15 a14 a13 a12 a11 a10 a9 a8    a7 a6 a5 a4 a3 a2 a1 a0   b2 b1 1 1 a9 a8 a7 a6

    MOV [c], EBX               ; punem rezultatul din registru in variabila rezultat
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
