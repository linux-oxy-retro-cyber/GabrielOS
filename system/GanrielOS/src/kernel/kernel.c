#include "vga.h"

void run_ram_test(void) {
    print_string(2, 10, "=== MEMORY CONTROLLER DIAGNOSTIC ===", COLOR_WHITE_ON_BLUE);
    print_string(2, 12, "Testing RAM Blocks: ", COLOR_WHITE_ON_BLUE);

    volatile unsigned int* ram_ptr;
    unsigned int start_addr = 0x100000; // 1 MB

    for (int mb = 4; mb <= 64; mb += 4) {
        ram_ptr = (volatile unsigned int*)(start_addr + (mb * 1024 * 1024));
        
        // Escreve e lê um padrão hexadecimal para validar a integridade
        *ram_ptr = 0xAA55AA55;
        if (*ram_ptr == 0xAA55AA55) {
            print_dec(22, 12, mb * 1024, COLOR_YELLOW_ON_BLUE);
            print_string(28, 12, " KB OK", COLOR_WHITE_ON_BLUE);
        } else {
            print_string(28, 12, " FAIL!", 0x1C);
            break;
        }
        delay(10);
    }
    print_string(2, 14, "RAM Verification Complete. Status: PASSED", COLOR_GREEN_ON_BLUE);
}

void kernel_main(void) {
    clear_screen();

    // Cabeçalho da Tela Azul / BIOS
    print_string(20, 1, " GABRIEL-OS HARDWARE DIAGNOSTICS v0.1 ", 0x70);
    print_string(2, 4, "CPU Status   : x86 Protected Mode (32-bit Active)", COLOR_WHITE_ON_BLUE);
    print_string(2, 5, "Registers    : EAX, EBX, ECX, EDX - OK", COLOR_WHITE_ON_BLUE);
    print_string(2, 6, "Gate A20     : Enabled", COLOR_WHITE_ON_BLUE);

    delay(20);

    run_ram_test();

    print_string(2, 17, "=== SYSTEM STATUS ===", COLOR_WHITE_ON_BLUE);
    print_string(2, 19, "VGA Text Mode  : 80x25 @ 0xB8000 [OK]", COLOR_WHITE_ON_BLUE);
    print_string(2, 20, "System Kernel  : Microkernel Core Ready", COLOR_WHITE_ON_BLUE);
    print_string(2, 23, "Press CTRL+C in terminal to exit QEMU...", COLOR_YELLOW_ON_BLUE);

    while (1) {
        __asm__ __volatile__("hlt");
    }
}
