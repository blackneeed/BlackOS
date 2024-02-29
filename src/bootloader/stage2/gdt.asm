
GDT_NULL:
	dd 0
	dd 0	
GDT_CODE:
	dw 0xFFFF			; Limit
	dw 0x0000			; Low base
	db 0x00				; Medium base
	db 10011010b		; Flags
	db 11001111b		; Flags and Upper Limit
	db 0x00				; High base
GDT_DATA:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10010010b
	db 11001111b
	db 0x00

GDT_END:

GDT_DESC:
	GDT_SIZE: 
		dw GDT_END - GDT_NULL - 1
		dq GDT_NULL

CODE_SEGMENT equ GDT_CODE - GDT_NULL
DATA_SEGMENT equ GDT_DATA - GDT_NULL

[bits 32]

EditGDT:
	mov [GDT_CODE + 6], byte 10101111b
	mov [GDT_DATA + 6], byte 10101111b
	ret

[bits 16]