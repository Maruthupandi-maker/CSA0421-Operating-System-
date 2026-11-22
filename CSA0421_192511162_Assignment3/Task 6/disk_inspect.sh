#!/bin/bash
echo "=== LINUX SYSTEM STORAGE & PARTITION INSPECTION ==="
echo "--- Block Device Hierarchy (lsblk -f) ---"
lsblk -f
echo ""
echo "--- Active Swap Partitions / Files (swapon --show) ---"
swapon --show
echo ""
echo "--- Disk Partitions (fdisk -l) ---"
sudo fdisk -l | head -n 30
