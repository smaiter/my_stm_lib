.equ STACK_TOP, 0x20000800
.equ DEMCR, 0xE000EDFC
.equ DWT_CTRL, 0xE0001000
.equ DWT_CYCCNT, 0xE0001004
.thumb
.cpu cortex-m3
.syntax unified
.text
.global _start

  .word STACK_TOP
  .word _start+1
_start:
//TRCENA on
  //ldr r0, =DEMCR
  //LDR r1, [r0]
  //orr r1, (1<<24)
  //str r1, [r0]
//DWT enable count
  //ldr r0, =DWT_CTRL
  //ldr r1, [r0]
  //orr r1, 1
  //str r1, [r0]
b main
.end
