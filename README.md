# uart_printf_freertos_stm32
## STM32F7 Thread-Safe Printf Implementation

A robust thread-safe implementation of printf and scanf for STM32F7 microcontrollers using FreeRTOS and UART.

## Features

- Thread-safe printf implementation
- Thread-safe scanf support
- UART3 communication
- FreeRTOS mutex protection
- Minimal overhead
- Easy integration

## Implementation Files

- `print.c`: Core implementation of thread-safe IO functions
- `print.h`: Header file with function declarations

## Requirements

- STM32F7 series microcontroller
- FreeRTOS
- Configured UART3
- HAL drivers

## Usage

1. Add `print.c` and `print.h` to your project
2. Initialize UART3 in your hardware configuration
3. Call `print_init()` before starting the scheduler
4. Use standard `printf()` and `scanf()` functions in your code

## Example

```c
#include "print.h"
#include <stdio.h>

int main(void) {
    // Initialize peripherals
    
    print_init();
    
    // Your code here
    printf("Hello World!\n");
    
    // Start scheduler
}
```

## Distribution
The implementation can be used as standalone files or integrated into larger projects.

## License
MIT License

Copyright (c) 2025

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

