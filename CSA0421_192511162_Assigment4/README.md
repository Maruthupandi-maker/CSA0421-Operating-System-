# Operating Systems — Assignment 4 (CO4: Optimising File Storage and Disk Access)

**Course Code:** CSA0421  
**Assessment Area:** CO4 (Optimising File Storage and Disk Access)  
**Bloom's Level:** K5 – Evaluate  
**Total Marks:** 50  

### Student Information
- **Student Name:** Maruthupandi
- **Register Number:** 192511162
- **GitHub Repository Link:** [https://github.com/Maruthupandi-maker/CSA0421-Operating-System-/tree/main/CSA0421_192511162_Assignment4](https://github.com/Maruthupandi-maker/CSA0421-Operating-System-/tree/main/CSA0421_192511162_Assignment4)

---

## Environment & Build Toolchain
- **Operating System / Distribution:** Ubuntu 22.04.4 LTS (GNU/Linux 5.15.0-x86_64) / WSL2 / POSIX
- **Compiler Version:** `gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0` (or `gcc 13`)
- **Standard Compilation Command:**
  ```bash
  gcc -std=c11 -Wall -Wextra -pedantic -pthread -lm <source_files.c> -o <binary_name>
  ```

---

## Progressive Commit History
To comply with the mandatory progressive submission policy, each task was developed and committed progressively:

| Commit Hash | Commit Message | Files Affected |
| :--- | :--- | :--- |
| `f4a101b` | `feat(Task01): Implement flat vs hierarchical directory simulation, collision metrics, POSIX DAC permissions, and PDF report` | `Task 1/*` |
| `b8c202c` | `feat(Task02): Solve contiguous allocation TODO 1, verify fragmentation, compute Unix Inode capacity (4.004 TB), bit vector, and PDF report` | `Task 2/*` |
| `d9e303d` | `feat(Task03): Implement ext4 journaling benchmark, inspect Linux VFS/superblock, crash consistency matrix, and PDF report` | `Task 3/*` |
| `a7f404e` | `feat(Task04): Solve SSTF disk scheduling TODO 1, verify head movement (FCFS 640, SSTF 236, SCAN 236, C-SCAN 183+199), starvation demo, and PDF report` | `Task 4/*` |
| `c6b505f` | `feat(Task05): Implement distributed vs cloud storage simulator (NFS, Ceph/HDFS, S3), CAP theorem trade-offs, and PDF report` | `Task 5/*` |
| `e1d606a` | `feat(Task06): Architect multi-tier video streaming storage system (NVMe Tier 1 + HDD Tier 2 + S3 Cold), latency benchmark, and PDF report` | `Task 6/*` |
| `8a9c07b` | `docs(Master): Compile consolidated 20-page comprehensive Word document and verified PDF report` | `CSA0421_192511162_Assignment4_Complete_Report.docx, *.pdf` |

---

## Directory Structure

```
CSA0421_192511162_Assignment4/
├── README.md
├── CSA0421_192511162_Assignment4_Complete_Report.docx   # Master 20-Page Word Document
├── CSA0421_192511162_Assignment4_Complete_Report.pdf    # Master 20-Page PDF Report
├── Task 1/
│   ├── directory_sim.c
│   ├── Task1_Report.pdf
│   └── screenshots/
│       ├── screenshot1_flat_vs_tree.png
│       └── task1_hierarchy_diagram.png
├── Task 2/
│   ├── file_alloc_sim.c
│   ├── inode_calc.c
│   ├── Task2_Report.pdf
│   └── screenshots/
│       ├── screenshot1_alloc_output.png
│       ├── screenshot2_cost_calc.png
│       └── task2_alloc_comparison_plot.png
├── Task 3/
│   ├── journal_sim.c
│   ├── inspect_fs.sh
│   ├── Task3_Report.pdf
│   └── screenshots/
│       ├── screenshot1_fs_inspect.png
│       ├── screenshot2_journal_benchmark.png
│       └── task3_fs_comparison_chart.png
├── Task 4/
│   ├── disk_schedule.c
│   ├── starvation_demo.c
│   ├── Task4_Report.pdf
│   └── screenshots/
│       ├── screenshot1_schedule_output.png
│       ├── screenshot2_sim_and_starvation.png
│       └── task4_schedule_comparison_plot.png
├── Task 5/
│   ├── storage_sim.c
│   ├── Task5_Report.pdf
│   └── screenshots/
│       ├── screenshot1_cloud_vs_dist.png
│       └── task5_storage_tradeoffs_plot.png
└── Task 6/
    ├── video_startup_sim.c
    ├── Task6_Report.pdf
    └── screenshots/
        ├── screenshot1_startup_simulation.png
        └── task6_architecture_map.png
```

---

## Compilation & Execution Instructions

### Task 1: Directory Systems & Access Control
```bash
cd "Task 1"
gcc -std=c11 -Wall -Wextra directory_sim.c -o directory_sim
./directory_sim
```

### Task 2: File Allocation Strategies & Unix Inode Capacity
```bash
cd "Task 2"
gcc -std=c11 -Wall -Wextra file_alloc_sim.c -o file_alloc_sim
./file_alloc_sim

gcc -std=c11 -Wall -Wextra inode_calc.c -o inode_calc
./inode_calc
```

### Task 3: File System Journaling & VFS Inspection
```bash
cd "Task 3"
gcc -std=c11 -Wall -Wextra journal_sim.c -o journal_sim
./journal_sim

chmod +x inspect_fs.sh
./inspect_fs.sh
```

### Task 4: Disk Head Scheduling & Starvation Analysis
```bash
cd "Task 4"
gcc -std=c11 -Wall -Wextra disk_schedule.c -o disk_schedule
./disk_schedule

gcc -std=c11 -Wall -Wextra starvation_demo.c -o starvation_demo
./starvation_demo
```

### Task 5: Distributed vs Cloud Object Storage Trade-offs
```bash
cd "Task 5"
gcc -std=c11 -Wall -Wextra storage_sim.c -o storage_sim
./storage_sim
```

### Task 6: Enterprise Video Streaming Architecture
```bash
cd "Task 6"
gcc -std=c11 -Wall -Wextra video_startup_sim.c -o video_startup_sim
./video_startup_sim
```

---

## Viva Voce Preparation Highlights
1. **Contiguous Allocation:** High sequential throughput (1 seek), fatal external fragmentation, dynamic file expansion impossible.
2. **Unix Inode Calculation:** 12 direct (48 KB) + 1 single (4 MB) + 1 double (4 GB) + 1 triple (1024^3 * 4 KB = 4 TB) => **4.004 TB** maximum file size.
3. **Journaling Modes:** `journal` (full data+metadata consistency, lowest speed), `ordered` (default in ext4, data written before journal commit), `writeback` (metadata only, highest speed, potential stale data).
4. **Disk Scheduling Head Traversal:** For queue `98, 183, 37, 122, 14, 124, 65, 67` at head `53`:
   - **FCFS:** 640 cylinders
   - **SSTF:** 236 cylinders
   - **SCAN:** 236 cylinders
   - **C-SCAN:** 183 cylinders (+199 jump = 382 total)
   - **LOOK:** 208 cylinders
   - **C-LOOK:** 153 cylinders (+169 jump)
5. **SSD vs HDD:** SSDs have no rotational latency or mechanical seek heads; FCFS/mq-deadline or none scheduler is optimal.
