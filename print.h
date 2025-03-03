#ifndef __PRINT_H
#define __PRINT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#define PRINT_QUEUE_SIZE 64
#define MAX_PRINT_MSG_LEN 128

  /* Debug Print Configuration */
#define DEBUG_PRINT_ENABLED // Comment out to disable all debug prints

  // Debug levels
  typedef enum
  {
    DEBUG_LEVEL_ERROR = 0,
    DEBUG_LEVEL_WARNING = 1,
    DEBUG_LEVEL_INFO = 2
  } DebugLevel_t;

/**
 * @brief Enables or disables all debug print statements in the project.
 *
 * When DEBUG_PRINT_ENABLED is defined, all debug print statements (DEBUG_ERROR, DEBUG_WARNING, DEBUG_INFO)
 * will be enabled and printed. When it is not defined, all debug print statements will be disabled.
 */
#ifdef DEBUG_PRINT_ENABLED
#define DEBUG_PRINT_LEVEL(level, fmt, ...)                                                   \
  do                                                                                         \
  {                                                                                          \
    TickType_t currentTime = xTaskGetTickCount();                                            \
    const char *taskName = pcTaskGetName(NULL);                                              \
    printf("[%lu][%s][%s] " fmt,                                                             \
           currentTime,                                                                      \
           (level == DEBUG_LEVEL_ERROR) ? "ERROR" : (level == DEBUG_LEVEL_WARNING) ? "WARN"  \
                                                                                   : "INFO", \
           taskName,                                                                         \
           ##__VA_ARGS__);                                                                   \
  } while (0)

/**
 * @brief Prints an error-level debug message with the current task name and timestamp.
 *
 * This macro is used to print error-level debug messages. It includes the current task name and the timestamp
 * of when the message was printed. The message is formatted using the provided format string and arguments.
 *
 * @param fmt The format string for the debug message.
 * @param ... The arguments to be formatted and printed.
 */
#define DEBUG_ERROR(fmt, ...) DEBUG_PRINT_LEVEL(DEBUG_LEVEL_ERROR, fmt, ##__VA_ARGS__)

/**
 * @brief Prints a warning-level debug message with the current task name and timestamp.
 *
 * This macro is used to print warning-level debug messages. It includes the current task name and the timestamp
 * of when the message was printed. The message is formatted using the provided format string and arguments.
 *
 * @param fmt The format string for the debug message.
 * @param ... The arguments to be formatted and printed.
 */
#define DEBUG_WARNING(fmt, ...) DEBUG_PRINT_LEVEL(DEBUG_LEVEL_WARNING, fmt, ##__VA_ARGS__)

/**
 * @brief Prints an info-level debug message with the current task name and timestamp.
 *
 * This macro is used to print info-level debug messages. It includes the current task name and the timestamp
 * of when the message was printed. The message is formatted using the provided format string and arguments.
 *
 * @param fmt The format string for the debug message.
 * @param ... The arguments to be formatted and printed.
 */
#define DEBUG_INFO(fmt, ...) DEBUG_PRINT_LEVEL(DEBUG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ERROR(fmt, ...) ((void)0)   // set to `NULL` to disable all debug prints
#define DEBUG_WARNING(fmt, ...) ((void)0) // set to `NULL` to disable all debug prints
#define DEBUG_INFO(fmt, ...) ((void)0)    // set to `NULL` to disable all debug prints

#endif // DEBUG_PRINT_ENABLED

  /**
   * @brief Represents a print message to be sent to the print queue.
   *
   * This structure holds the `buffer` containing the message to be printed, as well as the length
   * of the message. It is used to pass print messages between the application and the print task.
   */
  typedef struct
  {
    char buffer[MAX_PRINT_MSG_LEN];
    uint16_t len;
  } PrintMessage_t;

  extern QueueHandle_t xPrintQueue;     // Queue for printing messages. set at print.c
  extern TaskHandle_t xPrintTaskHandle; // Handle for the print task. set at print.c

  /**
   * @brief Initializes the print subsystem by creating a print queue and a print task.
   *
   * This function sets up the necessary infrastructure for the print subsystem to operate.
   * It creates a queue (`xPrintQueue`) to hold print messages, and a task (`vStartPrintTask`)
   * that will dequeue messages from the queue and transmit them to the UART.
   *
   * The `uxPriority` parameter specifies the priority of the print task. This should be
   * set to an appropriate value based on the requirements of the system.
   *
   * This function should be called during system initialization, before any print operations
   * are performed.
   *
   * @param uxPriority The priority of the print task.
   * @return `pdPASS` if the print subsystem was initialized successfully, `pdFAIL` otherwise.
   */
  BaseType_t xPrintInit(UBaseType_t uxPriority);

  /**
   * @brief Deinitializes the print subsystem by destroying the print queue and print task.
   *
   * This function cleans up the resources used by the print subsystem. It deletes the print
   * queue (`xPrintQueue`) and the print task (`xPrintTaskHandle`). This function should be
   * called when the print subsystem is no longer needed, such as during system shutdown.
   */
  void print_deinit(void);

  /**
   * @brief Prints an error message and enters an infinite loop.
   *
   * This function is used to print an error message to the console and then enter an infinite loop,
   * effectively halting the program execution. This is typically used for critical errors that
   * the program cannot recover from.
   *
   * @param msg The error message to be printed.
   */
  void print_error(const char *msg);

#ifdef __cplusplus
}
#endif

#endif /* __PRINT_H */
