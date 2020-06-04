Building
---
----
### Dependencies

#### Platform dependencies
* CMake and a build tool (GNU Make or Visual Studio)
* A C++ compiler, such as: 
  * GCC
  * CLang
  * Visual Studio


#### CMake dependencies
* [Vulkan SDK](https://vulkan.lunarg.com/sdk/home)
* [RxCpp](https://github.com/ReactiveX/RxCpp)


##### Windows instructions
* Getting c++ dependencies is easiest when being done through 
[vcpkg](https://github.com/Microsoft/vcpkg). Make sure to clone the vcpkg
tool in a directory that is wasy to access and or adding its pwd to the machine
 $PATH.
  * Some notes on vcpkg.

    Make sure to install the correct version of the triplet of the package in question. 
    On windows you can specify if you want the package for x64 x86 or thhe respective 
    arm packages as well.
    
    
    CMake will not see the package if the correct triplet is not set when installing the package. 
    As a example installing rxcpp through vcpkg will look like the snippet below if done for a 64 
    bit destination executable. 
    ```
    vcpkg install rxcpp:x64-windows
    ```

    When completing the [vcpkg](https://github.com/Microsoft/vcpkg) installation make sure
     to take note of thhe instructions after the
    ```
    vcpkg integrate install
    ```
    command as thhe instructions will give a variable to pipe in to the cmake command so that 
    the build system know where to find the modules installed by the vcpkg tool.

# Packages required

    * rxcpp
    * protobuff