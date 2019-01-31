Protocol Independent Network Stack
===
This is a demo using Rubik to build `QUIC`, `GTP`, `PPTP` and `IP/TCP` network stack.

Front-end Python code
---
In the `protocols` folder, we described 16 protocols as infrastructures to build network stacks, including `AH`, `ARP`, `Ethernet`,  `GRE`, `GTP`, `IGMP`, `IP`, `PPP`, `PPPoED`, `QUIC`, `TCP` and `UDP`.

Files `GTP_stack.py`, `IP_TCP_stack.py`, `PPTP_stack.py` and `QUIC_stack.py` refer individual protocols from `protocols` folder, organize the stack's hierarchy and define customized events.

Since we have **not released the compiler** to convert Python code to C code, we are sorry about that you cannot play around with the Python code. However, we provide you with compiled C code and capture examples to demonstrate these four network stacks.

Back-end C code
---
In the `compilation` folder, we placed four network stack with required libraries but `libpcap`. Therefore, if you have not installed it, please refer [this](https://www.tcpdump.org) to install `libpcap` at first.

### Usage
Assume you want to check out the PPTP network stack.
First, enter the `compilation` folder. Then
```Shell
make pptp && ./run pptp
```
You will see the compilation process and basic information of the pptp capture.
This command also works for `gtp`, `quic` and `ip_tcp`.
