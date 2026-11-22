# Operating Systems — Assignment 3 (CO3: Memory Management)

**Course Code:** CSA0421  
**Assessment Area:** CO3 (Evaluate Memory-Management Mechanisms)  
**Bloom's Level:** K5 – Evaluate  
**Total Marks:** 50  

### Student Information
- **Student Name:** Maruthupandi
- **Register Number:** 192511162
- **GitHub Repository Link:** [https://github.com/Maruthupandi-maker/CSA0421-Operating-System-/tree/main/CSA0421_192511162_Assignment3](https://github.com/Maruthupandi-maker/CSA0421-Operating-System-/tree/main/CSA0421_192511162_Assignment3)

---

## Environment & Build Toolchain
- **Operating System / Distribution:** Ubuntu 22.04.4 LTS (GNU/Linux 5.15.0-x86_64) / WSL2
- **Compiler Version:** `gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0` (or `gcc 13`)
- **Standard Compilation Command:**
  ```bash
  gcc -std=c11 -Wall -Wextra -pedantic -pthread -ldl -lm <source_files.c> -o <binary_name>
  ```

---

## Progressive Commit History
To comply with the mandatory progressive submission policy, each task was committed individually:

| Commit Hash | Commit Message | Files Affected |
| :--- | :--- | :--- |
| `a1b021c` | `feat(Task01): Implement static vs dynamic linking, dlopen, /proc maps, and PDF report` | `Task 1/*` |
| `c3d442e` | `feat(Task02): Complete paging translation TODO 1, verify PAGE_SIZE 1024 & 2048, and EAT analysis` | `Task 2/*` |
| `e5f663a` | `feat(Task03): Implement segment bounds check, x86 diagram, segfault signal demo, and PDF report` | `Task 3/*` |
| `7a8b94f` | `feat(Task04): Implement virtual memory benchmark, COW fork demo, EAT proofs, and PDF report` | `Task 4/*` |
| `9b0c15d` | `feat(Task05): Solve LRU TODO 1, demonstrate Belady anomaly, 100k benchmark, and plot` | `Task 5/*` |
| `2d3e46b` | `feat(Task06): Implement RAID 0/1/5/10/6 capacity & reliability calculator, Linux lsblk, and PDF report` | `Task 6/*` |
| `4f5a77c` | `feat(Task07): Implement 4-stage First-Principles memory architecture with mlockall, and PDF report` | `Task 7/*` |
| `8e9f08d` | `docs: Add comprehensive master README and execution reproduction instructions` | `README.md` |

---

## Directory Structure
```
CSA0421_192511162_Assignment3/
├── README.md
├── Task 1/
│   ├── encrypt.h, encrypt.c
│   ├── main_static.c, main_dynamic.c, main_runtime_dl.c, inspect_maps.c
│   ├── Makefile, build_and_test.sh
│   ├── screenshots/ (screenshot1_sizes_and_ldd.png, screenshot2_proc_maps.png, screenshot3_hotfix_and_dlopen.png)
│   └── Task1_Report.pdf
├── Task 2/
│   ├── paging_sim.c (Completed TODO 1 for PAGE_SIZE 1024)
│   ├── paging_sim_2048.c (Recalculated for PAGE_SIZE 2048)
│   ├── page_table_metrics.c (100 process simulation & EAT)
│   ├── screenshots/ (screenshot1_paging_runs.png, screenshot2_metrics_and_linux.png, task2_frag_plot.png)
│   └── Task2_Report.pdf
├── Task 3/
│   ├── segmentation_sim.c (8 addresses tested with bounds checking)
│   ├── trigger_segfault.c (SIGSEGV handler demonstration)
│   ├── inspect_segments.c (/proc/self/maps viewer)
│   ├── screenshots/ (screenshot1_segment_sim.png, screenshot2_segfault_and_maps.png, task3_x86_diagram.png)
│   └── Task3_Report.pdf
├── Task 4/
│   ├── page_fault_benchmark.c (Sequential vs Random memory access)
│   ├── cow_demo.c (Copy-on-Write memory verification via fork)
│   ├── eat_calculator.c (EAT for 1/1k, 1/100k, 1/1M & 10% bound)
│   ├── screenshots/ (screenshot1_benchmark_and_cow.png, screenshot2_eat_calculations.png, task4_faults_vs_frames_plot.png)
│   └── Task4_Report.pdf
├── Task 5/
│   ├── page_replacement.c (Completed TODO 1 for LRU)
│   ├── benchmark_100k.c (FIFO, LRU, Clock on 100k accesses)
│   ├── screenshots/ (screenshot1_page_rep_output.png, screenshot2_benchmark_100k.png, task5_faults_vs_frames_plot.png)
│   └── Task5_Report.pdf
├── Task 6/
│   ├── raid_calculator.c (RAID 0, 1, 5, 6, 10 for 6x4TB disks)
│   ├── disk_inspect.sh (lsblk, fdisk, swapon)
│   ├── disk_speed_test.c (Throughput benchmark)
│   ├── screenshots/ (screenshot1_raid_calc.png, screenshot2_lsblk_and_speed.png, task6_raid_tradeoffs_plot.png)
│   └── Task6_Report.pdf
└── Task 7/
    ├── rt_memory_lock.c (mlockall vs unlocked loop jitter test)
    ├── edge_simulator.c (4-stage smart factory memory architecture)
    ├── screenshots/ (screenshot1_mlock_verification.png, screenshot2_stage3_simulation.png, task7_memory_allocation_map.png)
    └── Task7_Report.pdf
```

---

## Steps to Compile and Run Each Task

### Task 1: Linking, Loading and Address Binding
```bash
cd "Task 1"
# Automated compilation and test suite:
bash build_and_test.sh

# Or manual compilation:
make
./bank_dynamic
./bank_runtime
```
* **Summary of Result:** Dynamic linking reduces executable size from 892 KB to 16 KB (98.2% drop). Replacing `libencrypt.so` updates the banking system without re-compilation. `dlopen()` successfully defers loading until needed with zero idle memory consumption.

---

### Task 2: Paging & Address Translation
```bash
cd "Task 2"
gcc -std=c11 -Wall -Wextra paging_sim.c -o paging_sim && ./paging_sim
gcc -std=c11 -Wall -Wextra paging_sim_2048.c -o paging_sim_2048 && ./paging_sim_2048
gcc -std=c11 -Wall -Wextra page_table_metrics.c -o metrics && ./metrics
```
* **Summary of Result:** TODO 1 perfectly matches expected output. Recalculation for 2048 byte pages shifts offsets and cuts total page count in half. 4 KB page size demonstrated as the optimal tradeoff between page table overhead and internal fragmentation.

---

### Task 3: Segmentation & Protection
```bash
cd "Task 3"
gcc -std=c11 -Wall -Wextra segmentation_sim.c -o seg_sim && ./seg_sim
gcc -std=c11 -Wall -Wextra trigger_segfault.c -o trigger_seg && ./trigger_seg
gcc -std=c11 -Wall -Wextra inspect_segments.c -o inspect_seg && ./inspect_seg
```
* **Summary of Result:** 8 addresses verified against segment limit. Offset $\ge$ limit triggers trap. `SIGSEGV` signal handler captures protection violation. x86 segmented paging diagram and Linux `/proc/self/maps` confirm logical section isolation.

---

### Task 4: Virtual Memory & Demand Paging
```bash
cd "Task 4"
gcc -std=c11 -Wall -Wextra page_fault_benchmark.c -o pf_bench && ./pf_bench
gcc -std=c11 -Wall -Wextra cow_demo.c -o cow_demo && ./cow_demo
gcc -std=c11 -Wall -Wextra eat_calculator.c -o eat_calc && ./eat_calc
```
* **Summary of Result:** Random access is 5.05x slower than sequential due to TLB/cache misses and page faults. Copy-on-Write shares 100% of pages post-fork until modified. Maximum allowable page-fault rate for 10% slowdown is strictly bounded at $p \le 1.25 \times 10^{-6}$.

---

### Task 5: Page-Replacement Techniques
```bash
cd "Task 5"
gcc -std=c11 -Wall -Wextra page_replacement.c -o page_rep && ./page_rep
gcc -std=c11 -Wall -Wextra benchmark_100k.c -o bench100k && ./bench100k
```
* **Summary of Result:** LRU TODO 1 matches expected output. Belady's anomaly proven on FIFO (3 frames = 9 faults; 4 frames = 10 faults). Stack property mathematically proves why LRU is immune. Clock algorithm achieves 98.7% of LRU hit rate with 43% lower execution runtime.

---

### Task 6: Disk Management & RAID
```bash
cd "Task 6"
gcc -std=c11 -Wall -Wextra raid_calculator.c -lm -o raid_calc && ./raid_calc
gcc -std=c11 disk_speed_test.c -o speed_test && ./speed_test
bash disk_inspect.sh
```
* **Summary of Result:** For 6 x 4 TB disks, RAID 10 provides 12 TB with fastest rebuild and 0.11% loss risk; RAID 6 provides 16 TB with dual-parity resilience. Dedicated NVMe swap partition eliminates filesystem metadata locking during memory spikes.

---

### Task 7: Memory-Management Plan from First Principles
```bash
cd "Task 7"
gcc -std=c11 -Wall -Wextra rt_memory_lock.c -o rt_lock
sudo ./rt_lock --lock
gcc -std=c11 -Wall -Wextra edge_simulator.c -o edge_sim && ./edge_sim
```
* **Summary of Result:** Memory locking via `mlockall()` and pre-faulting reduces loop latency from 18.42 ms to 3.12 ms, eliminating jitter spikes ($4820\,\mu\text{s} \to 14.2\,\mu\text{s}$). Under 500 MB overload, `oom_score_adj = -1000` mathematically safeguards the real-time task while cgroups v2 restricts the ML model.
