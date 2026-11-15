# NUCLEO-H753ZI projects

Projects for the STM32 development board NUCLEO-H753ZI.

This board features the STM32H7532ZI processor.

## Links

https://www.st.com/en/microcontrollers-microprocessors/stm32h753zi.html

https://www.st.com/en/evaluation-tools/nucleo-h753zi.html


## Documents in this repo

[user manual](resources/user_manual_nucleo144_boards.pdf)

[overview NUCLEO-144 boards](resources/overview_nucleo144_boards.pdf)

[Schematics revision E](resources/schematics_mb1364_h753zi_revision_e01.pdf)

[Bill of Materials](resources/MB1364-H753ZI-E01_BOM.xlsx)

[board pinout](resources/board_pinout_cn7_cn8_cn9_cn10.md)

More resources available in the resources folder.


## Install tools

Install the following tools:

* STM32CubeCLT (https://www.st.com/en/development-tools/stm32cubeclt.html)
* STM32CubeMX (https://www.st.com/en/development-tools/stm32cubemx.html)
* STMCubeProgrammer (https://www.st.com/en/development-tools/stm32cubeprog.html)

Open VS Code:

* STM32CubeIDE extension for VS Code


## Create project

In VS Code in the left bar is the STM32Cube icon. Click the icon to open the STM32Cube panel.

Fist run STM32CubeMX or STM32CubeMX2 depending on the platform. For this board use STM32CubeMX.
Configure the project using the STM32CubeMX. Take the following into account:

* Project location: `<repo_root>`
* Tool chain folder: `<repo_root>/<project_name>`
* Application structure: Basic
* Toolchain: CMake
* Default compiler: GCC

Generate the code. There will be quite some files added.
To make sure the project keeps building reliable all files should be added to git.

Now restart VS Code to see if the project is configured successfully.

In the project folder create a folder named `App` for the application code (next to `Src`).

Create an `app.c` and an `app.h` file.

Create two functions in the `app.c` file:

* `void APP_Init(void)`
* `void APP_Run(void)`

One is for your app initialization code and one is run in the while loop from `main.c`.

Expose both functions in `app.h`.

Include the `app.h` in the `main.c` (the path is relative to the `Src` folder):

```c
/* USER CODE BEGIN Includes */
#include "../App/app.h"
/* USER CODE END Includes */
```

Add the call to the initalization code in the `main.c`:

```c
/* USER CODE BEGIN 2 */
APP_Init();
/* USER CODE END 2 */
```

Add the call to the run code in the `main.c`:

```c
while (1)
{
  APP_Run();
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}
```

Add the `app.c` file to the `CMakeLists.txt`:

```cmake
# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    App/app.c
)
```

Later add other source files here as well.

Now build the project (CMake: Build).

After successful buid, click the run and debug button in the left bar.
On the run and debug panel, click the run and debug button.
Make sure the board is connected using STLink.
The board should be listed under STM32Cube Devices and Boards.

After clicking the run and debug button, select the debugger: `STM32 Launch STLink GDB Server`.
There are two things that needs to be configured for proper debugging.
In the `.vscode/launch.json` set the following properties in the configuration:

```json
{
    ...
    "configurations": [
        {
            ...
            "deviceName": "STM32H753ZI",
            "deviceCore": "Cortex-M7",
            ...
        },
        ...
    ]
}
```

After updating click the run and debug button.
Now the debugger should run and stop at the temporary break point.
Click `Continue (F5)` to start the firmware.
Click `Stop (Shift+F5)` to stop the debugger. The firmware will keep running on the board.
