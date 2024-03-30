[bits 16]

jmp EnablePM

EnableA20Line:
	in al, 0x92
	or al, 2
	out 0x92, al
	ret

EnablePM:
	call EnableA20Line
	cli
	lgdt [GDT_DESC]
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp CODE_SEGMENT:StartPM

%include "gdt.asm"

[bits 32]

%include "CPUid.asm"
%include "IdentityPaging.asm"

StartPM:

	mov ax, DATA_SEGMENT
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov [0xb8000], byte 'S'
	mov [0xb8002], byte 't'
	mov [0xb8004], byte 'a'
	mov [0xb8006], byte 'r'
	mov [0xb8008], byte 't'
	mov [0xb800a], byte 'e'
	mov [0xb800c], byte 'd'
	mov [0xb800e], byte ' '
	mov [0xb8010], byte '3'
	mov [0xb8012], byte '2'
	mov [0xb8014], byte '-'
	mov [0xb8016], byte 'b'
	mov [0xb8018], byte 'i'
	mov [0xb801a], byte 't'
	mov [0xb801c], byte ' '
	mov [0xb801e], byte 'm'
	mov [0xb8020], byte 'o'
	mov [0xb8022], byte 'd'
	mov [0xb8024], byte 'e'
	mov [0xb8026], byte '!'

	call DetectCPUID
	call DetectLongMode
	call EnablePaging
	call EditGDT

	jmp CODE_SEGMENT:Start64

[bits 64]
[extern KStart]
[extern KLoop]

Start64:
	call ActivateSSE
	call KStart
	.loop:
	call KLoop
	jmp .loop
	jmp $ ; This should never happen

ActivateSSE:
	mov eax, 0x1
	cpuid
	test edx, 1<<25
	jz .NoSSE
	ret

.NoSSE:
	cli
	mov [0xb8000], byte 's' ; Stands for SSE (failure)
	.halt:
	hlt
	jmp .halt

times 2048-($-$$) db 0