# CPU Information Retrieval

grabs information on CPU 

## Features

- Retrieves CPU vendor name.
- Retrieves CPU model details including family, model, and stepping.
- Detects if only one CPU is present or multiple CPUs.
- Checks if hyper-threading is enabled or disabled.
- Retrieves cache information including level, type, size, sets, associativity, and line size.

## Prerequisites

- C++ compiler

## Example Output

```
CPU Vendor: GenuineIntel
CPU Model: Family 6, Model 158, Stepping 10
CPU Name: Intel(R) Core(TM) i7-10750H CPU @ 2.60GHz
Number of Processors: More than one CPU detected.
Hyper-Threading: Enabled

Cache Information:
Level 1 Cache:
Type: 1
Size: 512 KB
Sets: 64
Associativity: 8
Line Size: 64 bytes

Level 2 Cache:
Type: 2
Size: 4 MB
Sets: 1024
Associativity: 16
Line Size: 64 bytes

Level 3 Cache:
Type: 3
Size: 12 MB
Sets: 4096
Associativity: 12
Line Size: 64 bytes```
