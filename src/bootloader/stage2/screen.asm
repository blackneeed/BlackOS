
CLEAR_SCREEN:
	pusha
	mov ah, 0x00
	mov al, 0x03
	int 0x10
	popa
	ret

PUT_STRING:
	push ax
	push bx
	.Loop:
	cmp [bx], byte 0
	je .Ret
	mov ah, 0x0e
	mov al, [bx]
	int 0x10
	inc bx
	jmp .Loop
	.Ret:
	pop ax
	pop bx
	ret