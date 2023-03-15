bits 32
       
segment code use32 class=code public
global adauga_la_sir 

    adauga_la_sir:
    
    ; [esp]    - adresa de revenire in main
    ; [esp+4]  - offset-ul sirului in care se face adaugarea
    ; [esp+8]  - offset-ul sirului ce contine caracterele de adaugat
    ; [esp+12] - valoarea contorului

        mov ebx, [esp+12]   ; ebx=valoare contor
        
        mov esi, [esp+8]    ; esi=offset sir ce contine caracterele de adaugat
        
        mov edi, [esp+4]    ; edi=offset sir in care se adauga
        add edi, ebx
        
        bucla:
            mov al, [esi]
            cmp al, 0Ah
            je gata
            mov [edi], al
            inc esi
            inc edi
            inc ebx
        jmp bucla
        
        gata:
            mov al, " "
            stosb
            inc ebx
    
    ret