# uart_printf_freertos_stm32

## STM32F7 Thread-Safe Printf Implementation

A robust thread-safe implementation of printf and scanf for STM32F7 microcontrollers using FreeRTOS and UART.

## Features

- Thread-safe printf implementation
- UART communication (default - UART3)
- FreeRTOS Queue protection
- Minimal overhead
- Easy integration

## Implementation Files

- `print.c`: Core implementation of thread-safe IO functions
- `print.h`: Header file with function declarations
  
```c
#define PRINT_QUEUE_SIZE 64
#define MAX_PRINT_MSG_LEN 128
```

## Feature

- Thread-safe printf implementation using FreeRTOS Queue
- UART communication (default - UART3)
- FreeRTOS Queue-based protection
- Minimal overhead
- Easy integration

  ## Usage

  Clone the repository:

  ```bash
  git clone https://github.com/elkanamol/uart_printf_freertos_stm32.git
  ```

  1. Add the files to your project:

- Copy `print.c` and `print.h` to your source directory
- Add them to your build system
  1. Initialize UART3 in your hardware configuration
  2. Configure queue settings if needed:
- `PRINT_QUEUE_SIZE`
- `MAX_PRINT_MSG_LEN`
  1. Initialize print system before scheduler start
  2. Use standard `printf()` or `DEBUG_*` macros in your code

  ## Example

  ```c
  #include "print.h"
  #include <stdio.h>

  int main(void) {
      // Initialize peripherals
      BaseType_t xReturn;
    
      // Initialize print system with priority check
      xReturn = xPrintInit(PRINT_TASK_PRIORITY);
      if (xReturn != pdPASS) {
          // Handle initialization error
          for(;;);
      }

      // Debug print examples
      DEBUG_INFO("System initialized\n");
      DEBUG_WARNING("System warning example\n");
    
      // Standard printf usage
      printf("Hello from printf!\r\n");

      // Start the scheduler
      vTaskStartScheduler();

      // Should never reach here
      for(;;);
  }
  ```

  The debug print system provides three levels of output:
  - `DEBUG_ERROR()` - For critical errors
  - `DEBUG_WARNING()` - For warning conditions
  - `DEBUG_INFO()` - For general information

  Each debug message includes:
  - Timestamp
  - Message level (ERROR/WARN/INFO)
  - Current task name
  - User message

  To disable debug prints, comment out:

  ```c
  #define DEBUG_PRINT_ENABLED
  ```

  The implementation uses a FreeRTOS queue for thread-safe operation, with configurable timeout and message size limits.

## Debug Print Features

The implementation now includes debug print levels with timestamps and task names:

- ERROR level: `DEBUG_ERROR("message", args...)`
- WARNING level: `DEBUG_WARNING("message", args...)`
- INFO level: `DEBUG_INFO("message", args...)`

### Debug Print Usage

```c
// Enable debug prints by keeping this defined
#define DEBUG_PRINT_ENABLED

// In your code:
DEBUG_ERROR("Failed to initialize: %d", error_code);
DEBUG_WARNING("Battery low: %d%%", battery_level);
DEBUG_INFO("System started successfully");
```

Output format: `[timestamp][LEVEL][TaskName] message`

### Disable Debug Prints

Comment out the following line in print.h to disable all debug prints:

```c
// #define DEBUG_PRINT_ENABLED
```

## Changelog

### v1.1.0 (Latest)

New Features:

- Added hierarchical debug print system with ERROR, WARNING, and INFO levels
- Debug prints now include timestamps and FreeRTOS task names
- Added ability to globally enable/disable debug prints
- Improved documentation and usage examples

### v1.0.0 (Initial Release)

- Thread-safe printf implementation
- UART3 communication support
- FreeRTOS mutex protection
- Basic print queue system

## Distribution

The implementation can be used as standalone files or integrated into larger projects.

## License

MIT License - see the [LICENSE](LICENSE) file for details.
