![README_Banner](images/midori_engine_banner.png)

# Real-time Application Engine built from the ground up!
This is an ongoing project used by me for educational purposes and fun!

## To include in your project
Add this repo as a submodule:
```
git submodule add <path where you want it> https://github.com/SzyJ/midori_engine
```
After cloning dont forget to init all the submodules (this can take a while):
```
cd <path to submodule>/midori_engine
git submodule init
git submodule update
```


In your root project directory, create a premake5.lua file.
```lua
workspace "<Workspace name>"
    architecture "x64"
    startproject "<Your Project's Name>"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }
```
... then add the engine like so ...
```lua
midori_path = "<Path where you added this project as a submodule>"
include (midori_path .. "premake_include_midori.lua")
```
... then define your project like so ...
```lua
project "<Your Project's Name>"
    location "<Path to your project>"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }
```
... Then add the necessary includes to your project and link to the engine ...
```lua
    includedirs {
        (midori_path .. "midori_engine/src"),
        (midori_path .. "midori_engine/3rd_party/glm"),
        (midori_path .. "midori_engine/3rd_party/spdlog/include"),
        (midori_path .. "midori_engine/3rd_party/imgui")
    }

    links {
        "midori_engine"
    }
```
... Then add any other configuration you need fo your project!


## To clone as a project
If you wish to clone this project, make sure to clone all the submodules too:
```
git clone --recursive https://github.com/SzyJ/midori_engine
```
or
```
git clone https://github.com/SzyJ/midori_engine
cd midori_engine
git submodule init
git submodule update
```

This project uses [premake](https://github.com/premake/premake-core) to generate desired project files.

### Generating Visual Studio solution
Generating a Visual Studio 2017 solution on windows, can be done through running the ```generate_vs2017.bat``` script.
