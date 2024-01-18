#!/usr/bin/env python
import os
import sys
import platform
import subprocess

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# Execute system


def sys_exec(args):
    if platform.system() == "Windows":
        args.insert(0, "powershell.exe")
    proc = subprocess.Popen(args, stdout=subprocess.PIPE, text=True)
    (out, err) = proc.communicate()
    return out.rstrip("\r\n").lstrip()

# Compile using CMake


def compile(base_dir):
    env.Append(CPPPATH=["{}/{}/export".format(base_dir, env["target"])])
    sys_exec(["mkdir", "{}/{}".format(base_dir, env["target"])])
    if env["platform"] == "osx":
        sys_exec(["cmake", "-DCMAKE_OSX_ARCHITECTURES=arm64;x86_64", "-DCMAKE_BUILD_TYPE={}".format(
            cmake_target), "-B{}/{}".format(base_dir, env["target"]), "-S{}".format(base_dir)])
    else:
        sys_exec(["cmake", "-DCMAKE_BUILD_TYPE={}".format(cmake_target),
                 "-B{}/{}".format(base_dir, env["target"]), "-S{}".format(base_dir)])
    sys_exec(["cmake", "--build", "{}/{}".format(base_dir,
             env["target"]), "--config", cmake_target])
    if env["platform"] == "windows":
        env.Append(LIBPATH=[env.Dir(
            "{}/{}/lib/{}/".format(simpleble_base, env["target"], cmake_target))])
    else:
        env.Append(
            LIBPATH=[env.Dir("{}/{}/lib/".format(base_dir, env["target"]))])


env = SConscript("external/godot-cpp/SConstruct")

# Add library
simpleble_base = "external/SimpleBLE/simpleble"
simplebluez_base = "external/SimpleBLE/simplebluez"
simpledbus_base = "external/SimpleBLE/simpledbus"

cmake_target = "Debug"
# cmake_target = "Release"

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["extension/src/"])

if env["platform"] == "macos":
    env.Append(CPPPATH=["{}/include".format(simpleble_base)])
    env.Append(LIBS=["libsimpleble.a"])
else:
    env.Append(CPPPATH=["{}/include".format(simpleble_base)])
    # TODO: Why is this compiled with debug?
    env.Append(LIBS=["libsimpleble-debug.a"])
    env.Append(LIBS=["libsimplebluez.a"])
    env.Append(LIBS=["libsimpledbus.a"])
    env.Append(LIBS=["libdbus-1.so"])

    # SimpleBluez
    compile(simplebluez_base)

    # SimpleDBus
    compile(simpledbus_base)

# SimpleBLE
compile(simpleble_base)


sources = Glob("extension/src/*.cpp")
if env["platform"] == "macos":
    library = env.SharedLibrary(
        "gdextensionsimpleble/bin/libgdextensionsimpleble.{}.{}.framework/libgdextensionsimpleble.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )

else:
    library = env.SharedLibrary(
        "gdextensionsimpleble/bin/libgdextensionsimpleble{}{}".format(
            env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
