bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se da un sir S de dublucuvinte.
    ; Sa se obtina sirul D format din octetii dublucuvintelor din sirul S sortati in ordine crescatoare in interpretarea fara semn.
    S dd 12345607h, 102B3C15h
    l equ $-S
    D times l db 0
    
; our code starts here
segment code use32 class=code
    start:
        ;
    MOV ESI, S
    MOV EDI, D
    CLD             ; DF=0
    MOV ECX, l      ; l=nr de octeti din S
    
    rep MOVSB       ; muta octetii din S in D
    
    ; algoritm de sortare
    
    MOV DL, 1       ; DL=variabila semafor pentru verificare daca sirul este sortati; DL=1 pt sir neosrtat, altfel DL=0 
    
    Bubble_sort:
        CMP DL, 0
        JZ Sfarsit
        MOV DL, 0
        MOV ECX, l-1            ; in loop Comparare facem l-1 comparari
        MOV ESI, D              ; acum D este sir sursa
        Comparare:
            MOV AL, [ESI]
            MOV BL, [ESI+1]
            CMP AL, BL          ; comparam doua elemente consecutive ale sirului
            JBE Pass
            MOV [ESI], BL
            MOV [ESI+1], AL     ; in caz ca el1>el2, le interschimbam si DL devine 1
            MOV DL, 1
            
            Pass:
                INC ESI
        LOOP Comparare
        
        JMP Bubble_sort
        
    Sfarsit:


        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
