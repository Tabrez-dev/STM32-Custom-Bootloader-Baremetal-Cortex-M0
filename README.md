# STM32F072RBT6 Custom Bootloader 🚀

## Overview
This project implements a **custom bootloader** for the STM32F072RBT6, enabling dynamic selection between multiple firmware images stored in flash. The bootloader accepts inputs (**1,2,3,4**) from UART RX (tested with Minicom) to load the corresponding firmware. If the **user button** is not pressed on reset, the bootloader skips execution, and the default firmware (which blinks **LD3**) runs automatically.  

## Demo Videos 🎥
🔹 **Bootloader Switching Between Applications**  

https://github.com/user-attachments/assets/6a4843df-7626-44ca-8d22-ecfd783b1e58

🔹 **Default Application**  

https://github.com/user-attachments/assets/28c10977-9d8a-4b6a-8dab-a2a20c3ca114

## Bootloader Flow Chart and Memory Model of flash

<p align="center">
  <img src="https://github.com/user-attachments/assets/3ddd2915-21d2-4c03-87cf-d6a16f038900" alt="Untitled-2025-04-03-1539">
</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/051f6641-99c2-4bfb-92f6-b8aaafad2b44" alt="Image">
</p>



## Features
- ✅ **Multi-application support** (Bootloader selects firmware based on user button conditions on reset)
- ✅ **Interrupt handling via Bootloader's Vector Table**
- ✅ **Efficient UART communication (without hardware flow control issues)**
- ✅ **Function pointer-based API for shared services**
- ✅ **Accurate Delay generated by SysTick timer**


## Challenges Faced & Solutions
### 1️⃣ **Handling Interrupts Without VTOR (Cortex-M0 Limitation)**
**Problem:** Cortex-M0 lacks the **Vector Table Offset Register (VTOR)**, making it difficult to relocate the vector table for different firmware images.

✅ **Solution:** There are 2 ways to solve this either copy each firmwares vector table to SRAM or use bootloader vector table. Since this is a simple applciation i went with using the bootlaoders vector table as it was giving a stable output. when I copied VT to SRAM the application was not stable.

### 2️⃣ **UART TX Issue in Minicom (Hardware Flow Control)**
**Problem:** Minicom wasn’t transmitting data because **hardware flow control (CTS/RTS) was enabled**.

✅ **Solution:** Disabling hardware flow control in Minicom resolved the issue, allowing TX (sending commands from keyboard of PC) to work correctly.

### 3️⃣ **Custom memory functions were not working as expected**
**Problem:** A **struct holding function pointers that point to commonly used functions accross all the firmwares** was stored in a shared memory region, but modifying the struct (e.g., changing order, adding/removing members) in the respective firmwares led to unpredictable function calls.

✅ **Solution:** The struct definition must be **identical in both Bootloader and Firmware**. Function pointers inside a struct rely on a **fixed memory layout**. If the struct is modified inconsistently across firmware versions, the function pointers will point to **incorrect or invalid addresses**, leading to crashes or unexpected behavior.

## Build & Flash Instructions
Followed STM32CubeIDE build and flash process and debugged using the built in debug software.

## Contributing
Open to contributions! Feel free to **submit PRs** or open an **Issue** if you find something to improve. 🚀

