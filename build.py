#!/usr/bin/env python3
import os
import sys
import subprocess
import shutil
from pathlib import Path
import platform
import tempfile

# Configuration
CC = os.environ.get("CC", "clang")
SRC_DIR = Path("cclass_core/src")
BUILD_DIR = Path("bin")

IS_WINDOWS = platform.system().lower().startswith("windows")

BASE_LIB_NAME = "cclass_rt" if IS_WINDOWS else "libcclass_rt"

# --- Helper functions ---

def detect_compiler():
    cc_lower = CC.lower()
    if "clang" in cc_lower:
        return "clang"
    elif "gcc" in cc_lower:
        return "gcc"
    elif "cl" in cc_lower or "msvc" in cc_lower:
        return "msvc"
    else:
        return "unknown"

def detect_os():
    os_name = platform.system().lower()
    if os_name.startswith("linux"):
        return "linux"
    elif os_name.startswith("darwin"):
        return "macos"
    elif os_name.startswith("windows"):
        return "windows"
    else:
        return os_name

def detect_arch():
    arch = platform.machine().lower()
    mapping = {"amd64": "x86_64", "x86_64": "x86_64", "i386": "x86", "i686": "x86",
               "arm64": "arm64", "aarch64": "arm64", "arm": "arm"}
    return mapping.get(arch, arch)

def detect_simd(cc):
    # Generate tiny C file to check SIMD macros
    simd_macros = [
        ("avx512", ["__AVX512F__"]),
        ("avx2", ["__AVX2__"]),
        ("avx", ["__AVX__"]),
        ("sse4.2", ["__SSE4_2__"]),
        ("sse4.1", ["__SSE4_1__"]),
        ("sse2", ["__SSE2__"]),
    ]
    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as f:
        f.write("#include <stdio.h>\nint main() {return 0;}\n")
        tmpfile = f.name
    detected = "nosimd"
    for name, macros in simd_macros:
        cmd = [cc, "-dM", "-E", tmpfile]  # preprocess only
        try:
            result = subprocess.run(cmd, capture_output=True, text=True, check=True)
            defines = result.stdout
            if all(m in defines for m in macros):
                detected = name
                break
        except Exception:
            continue
    os.unlink(tmpfile)
    return detected

# --- Detect target info ---

COMPILER = detect_compiler()
OS_NAME = detect_os()
ARCH = detect_arch()
SIMD = detect_simd(CC)

LIB_NAME = f"{BASE_LIB_NAME}-{COMPILER}-{OS_NAME}-{ARCH}-{SIMD}"

# --- Prepare build directories ---

if BUILD_DIR.exists():
    shutil.rmtree(BUILD_DIR)
BUILD_DIR.mkdir(parents=True, exist_ok=True)

header_dest_root = BUILD_DIR / "cclass_core"
header_dest_root.mkdir(parents=True, exist_ok=True)
shutil.copy("cclass.h", BUILD_DIR)
for header in Path("cclass_core").glob("*.h"):
    shutil.copy(header, header_dest_root)

INCLUDE_DIRS = [f"-I{BUILD_DIR}", f"-I{header_dest_root}"]

# --- Compile source files ---

src_files = list(SRC_DIR.glob("*.c"))
obj_files = []

for src in src_files:
    obj = BUILD_DIR / (src.stem + ".o")
    cmd = [CC, "-c", str(src), "-o", str(obj)] + INCLUDE_DIRS + sys.argv[1:]
    print("Compiling:", " ".join(cmd))
    subprocess.run(cmd, check=True)
    obj_files.append(obj)

# --- Link static library ---

lib_file = BUILD_DIR / (LIB_NAME + (".lib" if IS_WINDOWS else ".a"))
if IS_WINDOWS:
    cmd = ["llvm-ar", "rcs", str(lib_file)] + [str(o) for o in obj_files]
else:
    cmd = ["ar", "rcs", str(lib_file)] + [str(o) for o in obj_files]

print("Linking:", " ".join(cmd))
subprocess.run(cmd, check=True)

# --- Cleanup object files ---

for obj in obj_files:
    if obj.exists():
        obj.unlink()

# --- Done ---

print("Build completed:")
print(f"Static library -> {lib_file}")
print(f"Headers copied to -> {BUILD_DIR} and {header_dest_root}")
print("Include paths set relative to bin/")
print("Intermediate object files cleaned up")