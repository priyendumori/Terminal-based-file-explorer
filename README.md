
# Terminal Based File Explorer
A file explorer for linux systems that runs on terminal

## Compiling
* run make in the source code directory to compile.

## Running
```
* run ./tfe
```
It will open explorer in current folder
```
* run ./tfe <path_to_directory>
```
It will open explorer in specified folder

## Commands
* up, down, left, right, backspace, h keys work as described in assignment. Also 'q' can be used to quit the program.
* : can be used to get into command mode. Bottom line would be available to right command.
* After running one command, the bottom line gets cleared and is ready to accept more commands.
* ESC to go back to normal mode.
* Details about all the commands can be found [here](https://github.com/priyendumori/Terminal-based-file-explorer/blob/master/OS_Assignment_1.pdf)


## Assumptions
* Files with space in their name are not supported.
* Preferable mode of terminal is fullscreen.
* If width of terminal is less and output wraps around to new line, the code will not be able to handle this condition.
* Vertical scrolling was not implemented in the given time. So support of vertical scrolling is not available in this version.
* Error handling is very basic (i.e. only "error" is printed and no sophisticated error message). 
* When in command mode, backspace will work to edit command but arrow keys are not handled.
* 'q' can be typed in normal mode to quit the program.
* Files with no default application won't be opened.
