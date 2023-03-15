bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se dau 2 siruri de octeti A si B. Sa se construiasca sirul R care sa contina elementele lui B in ordine inversa urmate de elementele in ordine inversa ale lui A.
    ; Exemplu:
    ; A: 2, 1, -3, 0
    ; B: 4, 5, 7, 6, 2, 1
    ; R: 1, 2, 6, 7, 5, 4, 0, -3, 1, 2
    A db 2, 1, -3, 0
    LA equ $-A
    B db 4, 5, 7, 6, 2, 1
    LB equ $-B
    R resb LA+LB

; our code starts here
segment code use32 class=code
    start:
        ; ...
        MOV ESI, B+LB-1     ; ESI pointeaza spre ultimul elem din B
        MOV EDI, R          ; EDI pointeaza spre primul elem din R
        MOV ECX, LB         ; in ECX avem numarul de pasi
        
        JECXZ Final_Muta_B
        
        Muta_B:
            MOV AL, [ESI]
            MOV [EDI], AL
            DEC ESI             ; cu ESI mergem invers in B
            INC EDI             ; cu EDI mergem normal in R
        LOOP Muta_B
        
        Final_Muta_B:
        
        MOV ESI, A+LA-1     ; ESI pointeaza spre ultimul elem din A
                            ; EDI pointeaza deja spre pozitia la care am ramas in completarea sirului R
        MOV ECX, LA         ; in ECX avem numarul de pasi
        
        JECXZ Final_Muta_A
        
        Muta_A:
            MOV AL, [ESI]
            MOV [EDI], AL
            DEC ESI             ; cu ESI mergem invers in B
            INC EDI             ; cu EDI mergem normal in R
        LOOP Muta_A
        
        Final_Muta_A:
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
