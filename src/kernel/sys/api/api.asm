[bits 64]

section .text
global _hcf

_hcf:
    cli
    .halt:
    hlt
    jmp .halt