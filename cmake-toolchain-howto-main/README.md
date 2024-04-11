## How to use a CMake toolchain file

CMake toolchain files are the official way to perform cross compilation using CMake.

In this example, I build a project using an out-of-source build, which effectively means we will make a build directory outside of the source directory, and run `cmake ..` from inside that build directory. This project contains a main.c file that has its own `vv_add_int32`. It also includes a small and unoptimized blas library I use for another project. I included this to show how I setup separate modules within the `src` directory, where each module is built and used as a library. In this case, we are building a subset of `linalg` module that only contains the blas source and header file. Take a look at the CMakeLists.txt file in the root directory of the repository as well as the CMakeLists.txt file that is located in `src/linalg`. 

I am assuming you are building on the BRG server that has the GNU RISCV Toolchain installed and that you will also be using `spike` to run the statically compiled binary. The static compilation part is important as I will use the toolchain file to ensure that the `-static` C flag is included during compilation when compiling for `riscv64` for `spike`.

First let's setup the environment:
```
source setup-brg.sh
source setup-python3.sh
module load scl-8
source ${BARE_PKGS_GLOBAL_PREFIX}/brg-riscv-tools/setup.sh
```

Now lets build main to run natively on the server.
```
mkdir build && cd build
cmake ..
make
```
We can run the main binary and check the objdump:
```
# To run the main binary
bin/main

# You can also check the objdump
less obj/main-objdump.txt
```

Now to cross compile with the GNU RISCV Toolchain, we will use a CMake Toolchain file. When calling cmake we will now include a `-DCMAKE_TOOLCHAIN_FILE` flag. Take a look at the toolchain file located in the project root called `riscv64.cmake` and read the comments to understand its structure.

Now let's cross compile in a separate build directory we will called `build-spike`:
```
mkdir build-spike & cd build-spike
cmake .. -DCMAKE_TOOLCHAIN_FILE=../riscv64.cmake
make
```

Similar to above, we can run the main binary, but on `spike`, and also check the objdump:
```
# Run main binary on spike
spike pk bin/main

# Check objdump
less obj/main_objdump.txt
```

