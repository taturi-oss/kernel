#define WHITE_TXT 0x07
#define BUF_SIZE 128

void kernel_clear_screen();
unsigned int kernel_printf(char *message, unsigned int line);
void kernel_process_command(char *cmd);
void kernel_print_prompt();
char kernel_get_char();
int kernel_strcmp(const char *str1, const char *str2);
int kernel_strncmp(const char *str1, const char *str2, unsigned int n);

char command_buffer[BUF_SIZE];

void kernel_main() 
{
    kernel_clear_screen();
    kernel_printf("Taturi Successfully Booted.\n", 0);

    while (1) {
        kernel_print_prompt();
        kernel_process_command(command_buffer);
    }
};

void kernel_clear_screen()
{
    char *vidmem = (char *) 0xb8000;
    unsigned int i = 0;
    while (i < (80 * 25 * 2)) {
        vidmem[i] = ' ';
        i++;
        vidmem[i] = WHITE_TXT;
        i++;
    }
};

unsigned int kernel_printf(char *message, unsigned int line)
{
    char *vidmem = (char *) 0xb8000;
    unsigned int i = 0;

    i = (line * 80 * 2);

    while (*message != 0) {
        if (*message == '\n') {
            line++;
            i = (line * 80 * 2);
            *message++;
        } else {
            vidmem[i] = *message;
            *message++;
            i++;
            vidmem[i] = WHITE_TXT;
            i++;
        }
    }

    return (1);
}

void kernel_print_prompt()
{
    kernel_printf("\n> ", 1);
}

void kernel_process_command(char *cmd)
{
    if (kernel_strcmp(cmd, "help") == 0) {
        kernel_printf("\nAvailable commands:\n", 1);
        kernel_printf("help - Show this help message\n", 2);
        kernel_printf("clear - Clear the screen\n", 3);
        kernel_printf("echo <message> - Echo the message\n", 4);
    } else if (kernel_strcmp(cmd, "clear") == 0) {
        kernel_clear_screen();
        kernel_printf("Screen cleared.\n", 1);
    } else if (kernel_strncmp(cmd, "echo", 4) == 0) {
        kernel_printf("\n", 1);
        kernel_printf(cmd + 5, 2);
        kernel_printf("\n", 3);
    } else {
        kernel_printf("\nUnknown command: %s\n", 1);
    }
}

char kernel_get_char()
{
    return 'a';
}

int kernel_strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

int kernel_strncmp(const char *str1, const char *str2, unsigned int n)
{
    while (n-- && *str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    if (n == (unsigned int)-1) return 0;
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}
