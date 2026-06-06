# MicroDiff: Embedded Text Analysis Engine 🚀

## Overview
MicroDiff is a lightweight, hardware-integrated text analysis engine designed specifically for memory-constrained embedded systems. It performs real-time comparison of text strings (such as system configuration plans) using a highly optimized Longest Common Subsequence (LCS) algorithm. 

Bridging the gap between theoretical computer science and bare-metal mechatronics, this system processes data with extreme memory efficiency and makes physical actuation decisions based on textual similarity percentages. This project was developed to demonstrate advanced algorithmic principles in applied engineering contexts as part of academic coursework at Amirkabir University of Technology.

## 🧠 Engineering Analysis: Space Optimization
The standard dynamic programming implementation of the LCS algorithm requires a 2D matrix, resulting in a space complexity of $O(m \times n)$. On a standard microcontroller with severely limited SRAM (e.g., 2KB), this approach immediately results in a stack overflow or memory crash for even moderately sized texts.

**The Solution:**
MicroDiff implements a bitwise space-optimized approach. By recognizing that the calculation only ever requires the current and previous rows of the DP matrix, the algorithm continuously toggles between two rows using bitwise AND (`i & 1`). This drastically reduces the memory footprint.

* **Time Complexity:** $O(m \times n)$
* **Space Complexity:** $O(\min(m, n))$

## ⚙️ Hardware Architecture
The system architecture relies on minimal GPIO usage by leveraging serial communication protocols.

* **Processing Unit:** Arduino Uno (ATmega328P) showcasing aggressive memory management.
* **Display Output:** 16x2 LCD operating over the **I2C protocol** to display analysis progress and match percentage.
* **Physical Actuator:** PWM-controlled Servo Motor acting as a mechatronic gate/lock that physically reacts if the file variance exceeds a defined safety threshold.
* **Data Pipeline:** Designed to read distinct data sets (e.g., `plan5` vs `plan6`).

## 📂 Repository Structure
* `src/`: Contains the core C++ logic (`main.ino`) featuring the optimized algorithm.
* `simulation/`: Includes the `diagram.json` mapping for rapid reproduction in Wokwi.
* `data/`: Sample text targets utilized for difference analysis.
* `docs/`: Project documentation and architecture details.

## 🚀 How to Run (Simulation Environment)
You can deploy and test this system entirely in the cloud without physical hardware:

1. Clone this repository.
2. Open the [Wokwi Simulator](https://wokwi.com) and create a new Arduino project.
3. Replace the default code with the contents of `src/main.ino`.
4. Replace the environment mapping with `simulation/diagram.json`.
5. Add the **LiquidCrystal I2C** library via the Wokwi Library Manager.
6. Run the simulation to observe the text analysis, percentage calculation, and automated servo actuation.

---
*This repository reflects a deep interest in algorithm design, operating system resource constraints, and hardware-level execution.*
