*This project has been created as part of the 42 curriculum by rpaganon.*

# ft_printf

## Description

**ft_printf** is a re-implementation of the C standard library function `printf()`, packaged as a static library (`libftprintf.a`).

The goal of the project is to learn how **variadic functions** work in C (`<stdarg.h>`: `va_list`, `va_start`, `va_arg`, `va_end`) and to design clean, extensible code that parses a format string and dispatches each conversion to a dedicated function.

Prototype:

```c
int ft_printf(const char *format, ...);
```

Like the original, it returns the number of characters written on the standard output.

### Supported conversions

| Specifier | Description                                                              |
|-----------|--------------------------------------------------------------------------|
| `%c`      | Prints a single character                                                |
| `%s`      | Prints a string (`(null)` if the pointer is `NULL`)                      |
| `%p`      | Prints a `void *` in hexadecimal (`0x...`, or `(nil)` for `NULL`)        |
| `%d`      | Prints a signed decimal number                                           |
| `%i`      | Prints a signed integer in base 10                                       |
| `%u`      | Prints an unsigned decimal number                                        |
| `%x`      | Prints an unsigned number in lowercase hexadecimal                       |
| `%X`      | Prints an unsigned number in uppercase hexadecimal                       |
| `%%`      | Prints a percent sign                                                    |

The buffer management of the original `printf()` is intentionally **not** implemented: every conversion writes directly with `write()`.

### Library overview

`libftprintf.a` is built from the following files, all located at the root of the repository:

| File             | Role                                                                                  |
|------------------|---------------------------------------------------------------------------------------|
| `ft_printf.h`    | Header with all prototypes                                                            |
| `ft_printf.c`    | `ft_printf()` main loop, `is_arg()` validator and `ft_printf_arg()` dispatcher        |
| `ft_putchar.c`   | `ft_putchar()` – writes one character                                                 |
| `ft_putstr.c`    | `ft_putstr()` – writes a string (handles `NULL`)                                      |
| `ft_putnbr.c`    | `ft_putnbr()`, `ft_print_unsigned()`, `ft_putnbr_hex()`, `ft_putnbr_hex_ul()`         |
| `ft_putptr.c`    | `ft_putptr()` – pointer printing                                                      |
| `ft_strlen.c`    | `ft_strlen()` – string length                                                         |
| `Makefile`       | Builds the library (`NAME`, `all`, `clean`, `fclean`, `re`)                           |

## Instructions

### Compilation

The library is compiled with `cc -Wall -Wextra -Werror` and archived with `ar rcs` (`libtool` is not used). From the root of the repository:

```bash
make        # builds libftprintf.a
make clean  # removes object files
make fclean # removes object files and libftprintf.a
make re     # fclean + all
```

The Makefile does not relink if nothing has changed.

### Usage

Include the header in your source file and link against the library:

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello %s! %d + %d = %i\n", "world", 40, 2, 42);
    ft_printf("hex: %x / %X, unsigned: %u, ptr: %p, percent: %%\n",
              255, 255, 42u, (void *)0);
    return (0);
}
```

```bash
make
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o test
./test
```

### Testing

Compare the output and the return value of `ft_printf()` with those of the original `printf()` on the same format strings. Edge cases to check: `INT_MIN`, `INT_MAX`, `UINT_MAX`, `0`, `NULL` string, `NULL` pointer, `%` at the end of the string.

## Detailed description of the library

### Format string parsing

`ft_printf()` makes a single linear pass over the format string (`O(n)`), with no dynamic allocation and no intermediate buffer:

1. Initialise the argument list with `va_start`.
2. Walk through the string character by character.
3. If the current character is `%` and the next one is a valid specifier (checked by `is_arg()` against `"cspdiuxX%"`), call `ft_printf_arg()` and skip the specifier.
4. Otherwise, print the character as is.
5. Accumulate the number of written characters, close the list with `va_end`, and return the total.

### Dispatcher

`ft_printf_arg()` is a simple `if / else if` dispatcher. It receives the specifier and a **pointer to the `va_list`** (`va_list *`), retrieves the next argument with `va_arg` using the right type, and calls the matching print function. Passing the `va_list` by pointer guarantees that the argument position advances correctly in the caller.

Adding a new conversion only requires a new print function, one new branch, and the new specifier in `is_arg()`, which keeps the code **extensible**.

### Number conversion

No data structure is needed: numbers are printed with **recursion**.

- To print a number in base `b`, the function first prints `n / b` recursively (if `n >= b`), then prints the last digit `base[n % b]`. Digits are emitted in the right order without any buffer or string reversal.
- Each function returns the number of characters written, so the total is simply summed along the recursion.
- **Signed integers (`%d`, `%i`)**: the value is stored in a `long` before taking its absolute value, which safely handles `INT_MIN`.
- **Unsigned integers (`%u`)**: same recursive approach on an `unsigned int`.
- **Hexadecimal (`%x`, `%X`)**: digits are taken from `"0123456789abcdef"` or `"0123456789ABCDEF"` depending on the specifier.
- **Pointers (`%p`)**: the address is converted to `unsigned long` and printed in hexadecimal after the `0x` prefix. A `NULL` pointer prints `(nil)`, like glibc's `printf()`.
- **Strings (`%s`)**: a `NULL` string prints `(null)`, like glibc.

Complexity: `O(log_b n)` per number (number of digits), with a recursion depth of at most 20 calls for a 64-bit value in base 10 and 16 calls for a 64-bit value in base 16.

## Resources

### References

- `man 3 printf` – behaviour of the original function
- `man 3 stdarg` – `va_start`, `va_arg`, `va_copy`, `va_end`
- `man 2 write`
- [The GNU C Library – Formatted Output](https://www.gnu.org/software/libc/manual/html_node/Formatted-Output.html)
- [cppreference – `printf`](https://en.cppreference.com/w/c/io/fprintf)
- [cppreference – Variadic arguments](https://en.cppreference.com/w/c/variadic)

### Use of AI
 
AI tools were used only as a learning and support resource during this project.
 
They helped me understand the subject, clarify how certain C concepts and functions work (such as variadic functions, `va_list`, `va_start`, `va_arg` and `va_end`), and better understand the expected behaviour of the standard `printf()` function.
 
AI was also used to help review and clean up this README for clarity and readability.
 
**No code was generated by AI.** All implementation, logic and problem-solving were done by me.