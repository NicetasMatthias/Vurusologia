format MZ                       ;
       mov ebx, 0               ; symbol counter
       read:                    ; reading block:
              mov ah, 00h       ; read symbol
              int 16h           ; -
              push eax          ; push to stack
              mov ecx, eax      ;
              mov ah, 0Eh       ; write symbol
              int 10h           ; -
              mov eax, ecx      ; -
              add ebx, 1        ; increment counter
              cmp ah, 28        ; if symbol == \n?
              jne read          ; else another read
       mov eax, 0E0Ah           ; go to next string
       int 10h                  ; -
       mov eax, 0E0Dh           ; -
       int 10h                  ; -
       write:                   ; writing block:
              pop eax           ; pop from stack
              mov ah, 0Eh       ; write symbol
              int 10h           ; -
              add ebx, -1       ; decrement counter
              cmp ebx, 0        ; if counter == 0?
              jne write         ; else another write
       mov eax, 4C00h           ; exit
       int 21h                  ; -