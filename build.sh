nasm -f elf32 ./src/bootloader.asm -o ./build/bootloader.o

gcc -m32 -c ./src/kernel.c -o ./build/kernel.o

ld -m elf_i386 -T ./src/link.ld -o ./build/kernel ./build/bootloader.o ./build/kernel.o


if [ $? -eq 0 ]; then
    echo "Kernel built successfully: ./build/kernel"
else
    echo "Build failed."
    exit 1
fi
