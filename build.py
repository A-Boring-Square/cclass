#!/usr/bin/env python3
import os
import sys
import subprocess
import shutil
from pathlib import Path
import platform

# Configuration

CC = os.environ.get("CC", "clang")
SRC_DIR = Path("cclass_core/src")
BUILD_DIR = Path("bin")

# Detect platform

IS_WINDOWS = platform.system().lower().startswith("windows")

LIB_NAME = "cclass_rt" if IS_WINDOWS else "libcclass_rt"

# Clean previous build artifacts

if BUILD_DIR.exists():
    shutil.rmtree(BUILD_DIR)
BUILD_DIR.mkdir(parents=True, exist_ok=True)

# Move headers into bin/ structure

header_dest_root = BUILD_DIR / "cclass_core"
header_dest_root.mkdir(parents=True, exist_ok=True)

shutil.copy("cclass.h", BUILD_DIR)
for header in Path("cclass_core").glob("*.h"):
    shutil.copy(header, header_dest_root)

# Updated include directories relative to bin/

INCLUDE_DIRS = [f"-I{BUILD_DIR}", f"-I{header_dest_root}"]

# Gather source files

src_files = list(SRC_DIR.glob("*.c"))

# Compile each source file

obj_files = []
for src in src_files:
    obj = BUILD_DIR / (src.stem + ".o")
    cmd = [CC, "-c", str(src), "-o", str(obj)] + INCLUDE_DIRS + sys.argv[1:]
    print("Compiling:", " ".join(cmd))
    subprocess.run(cmd, check=True)
    obj_files.append(obj)

# Link into static library

lib_file = BUILD_DIR / (LIB_NAME + (".lib" if IS_WINDOWS else ".a"))
if IS_WINDOWS:
    cmd = ["llvm-ar", "rcs", str(lib_file)] + [str(o) for o in obj_files]
else:
    cmd = ["ar", "rcs", str(lib_file)] + [str(o) for o in obj_files]

print("Linking:", " ".join(cmd))
subprocess.run(cmd, check=True)

# Cleanup object files

for obj in obj_files:
    if obj.exists():
        obj.unlink()

print("Build completed:")
print(f"Static library -> {lib_file}")
print(f"Headers copied to -> {BUILD_DIR} and {header_dest_root}")
print("Include paths set relative to bin/")
print("Intermediate object files cleaned up")
