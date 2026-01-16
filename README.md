# imgui-starter

**Built for (and tested on) Windows.**

Rigging up this logging system took a bit of trial and error. I used [Graham's example code](https://github.com/gdevine-ucsc/imgui-starter) to search the ImGui library for relevant tools in window creation, and to understand the order in which to call them. I also referred to [ImGui's example code](https://github.com/aegismichael4/imgui-starter/blob/main/CMakeLists.txt) for additional help. 

After I got a basic Logger class made, I moved on to stylizing outputs with different colors for different levels. Then, I did some refactoring: instead of calling `LogInfo()` and `LogGameEvent()`, I consolidated my logic into a single `Log()` function, which takes a message, a level, and a type (where type can be `DEFAULT` or `GAME`). I used enums to set the level and type.

The most challenging thing so far was trying to figure out how to write the log to a file. Originally, I expected to use a tool from the ImGui library, but I wound up using the Standard Library instead.

### TODO/Future Improvements
* [ ] revisit using ImGui tools for file output.
* [ ] add timestamps to log files
* [ ] maybe rename log files with timestamp data? (or otherwise prevent overwrites)
