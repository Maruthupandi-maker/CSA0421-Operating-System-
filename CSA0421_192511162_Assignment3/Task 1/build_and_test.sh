#!/bin/bash
set -e
echo "=========================================================="
echo "Task 01: Linking, Loading and Address Binding Verification"
echo "Student: Maruthupandi | Reg No: 192511162"
echo "=========================================================="

make clean
make

echo -e "\n[1] Comparing Binary Sizes:"
ls -lh bank_static bank_dynamic bank_runtime libencrypt.so

echo -e "\n[2] Checking Shared Library Dependencies with ldd:"
echo "--- Dynamic Binary ---"
ldd bank_dynamic
echo "--- Runtime dlopen Binary ---"
ldd bank_runtime
echo "--- Static Binary ---"
ldd bank_static || echo "(Not a dynamic executable - static binary has zero shared dependencies)"

echo -e "\n[3] Memory Mapping (/proc/self/maps):"
./inspect_maps

echo -e "\n[4] Running Dynamic Executable:"
./bank_dynamic

echo -e "\n[5] Demonstrating Security Patch Update Without Recompilation:"
sed -i 's/v1.2.0-SECURE-PATCHED/v2.0.0-HOTFIX-APPLIED/' encrypt.c
gcc -std=c11 -fPIC -shared encrypt.c -o libencrypt.so
echo "Updated libencrypt.so to v2.0.0. Re-running bank_dynamic WITHOUT recompiling:"
./bank_dynamic

echo -e "\n[6] Testing Missing Shared Library Failure:"
mv libencrypt.so libencrypt.so.bak
echo "Attempting to run bank_dynamic with missing library:"
./bank_dynamic || echo "[Expected Error]: Dynamic linker failed to load shared object!"

echo -e "\n[7] Testing Runtime dlopen Graceful Fallback:"
./bank_runtime || echo "[Expected Graceful Handling]: Process captured missing library and continued safely."

mv libencrypt.so.bak libencrypt.so
echo -e "\nTask 01 Verification Completed Successfully."
