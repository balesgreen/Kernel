.set MAGIC, 0x1BADB002

.set FLAGS, 0

.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot

#define type to long for each data defined as above
.long MAGIC
.long FLAGS
.long CHECKSUM

stackBottom:
.skip 1024

#set the stack top which grows from higher to lower
stackTop:
.section .text
.global _start
.type _start, @function

_start:
	mov $stackTop, %esp
	call kernel_entry

	cli

hltLoop:
	hlt
	jmp hltLoop

.size _start, . - _start
