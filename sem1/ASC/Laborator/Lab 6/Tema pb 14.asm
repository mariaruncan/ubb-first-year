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
    ; Sa se obtina sirul D format din octetii dublucuvintelor din sirul D sortati in ordine crescatoare in interpretarea fara semn.
    ; Exemplu:
    ; s DD 12345607h, 1A2B3C15h
    ; d DB 07h, 12h, 15h, 1Ah, 2Bh, 34h, 3Ch, 56h
    s dd 12345607h, 1A2B3C15h
    len equ ($-s)/4        ; lungimea lui s (octeti)
    d resb len
    
; our code starts here
segment code use32 class=code
    start:
        MOV ESI, s
        MOV EDI, d          ; d este sirul destinatie
        CLD                 ; DF=0 - parcurgem de la stanga la dreapta
        MOV ECX, len
        
        Muta_octeti:
            MOV EBX, ECX    ; salvam valoarea din ecx
            MOV CL, 8
            LODSD           ; in eax avem un element
            STOSB           ; stocam in [edi] ocetetul din al si incrementam edi 
            SHR EAX, CL     ; shiftam eax pt a obtine urmatorul octet si apoi il stocam in d, cele doua intructiuni fiind repetate de 3 ori
            STOSB
            SHR EAX, CL
            STOSB
            SHR EAX, CL
            STOSB
            MOV ECX, EBX    ; ecx revine la valoarea sa de dinaintea shiftarilor
        LOOP Muta_octeti
        
        MOV ECX, len*4-1    ; in ecx avem indexul ultimului elem din sirul nesortat
        MOV ESI, 0          ; d este sir sursa si folosim ESI ca si contor
        
        Bubble_sort:
            CMP ECX, ESI  
            JZ Pass         ; daca ne aflam cu adresa ESI pe ultimul elem din sir, Pass            
            MOV AL, [d+ESI]
            MOV BL, [d+ESI+1]
            CMP AL, BL
            JA Swap         ; jump if AL>BL <=> octet1>octet2
            INC ESI
            JMP Bubble_sort
            
    Swap:
        MOV [d+ESI], BL
        MOV [d+ESI+1], AL
        INC ESI
        JMP Bubble_sort
                
    Pass:
        MOV ESI, 0
        DEC ECX         ; revenim cu contorul la 0 si vom parcurge sirul pana la elementul cu indexul ecx-1, deoarece elem cu indexul ecx este pe pozitia corespunzatoare
        CMP ECX, 0
        JNZ Bubble_sort  ; daca ecx este diferit de 0, adica avem cel putin 2 elem in sir ce trebuie sortate in continuare, ne intoarcem la Bubble_sort 
                
                
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
