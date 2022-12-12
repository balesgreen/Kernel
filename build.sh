as --32 boot.S -o boot.o

g++ -c -fno-stack-protector -m32 kernel.cpp -o kernel.o -std=c++11 -ffreestanding -O2 -Wall -Wextra

ld -m -z noexecstack elf_i386 -T linker.ld kernel.o boot.o -o SimpleKernel.bin -nostdlib

grub-file --is-x86-multiboot SimpleKernel.bin

mkdir -p isodir/boot/grub
cp SimpleKernel.bin isodir/boot/grub/SimpleKernel.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o SimpleKernel.iso isodir
