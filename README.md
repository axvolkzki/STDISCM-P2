# Looking for Group Synchronization
This program manages the **Looking for Group (LFG) dungeon queuing system** in an MMORPG. It ensures that parties of players are formed correctly and assigned to available dungeon instances, while maintaining proper synchronization to prevent deadlock and starvation.

***Key Features***
- **Concurrent Dungeon Instances**: Supports up to `n` simultaneous dungeon runs.
- **Party Formation**: A valid party consists of **1 Tank** (`t`), **1 Healer** (`h`), and **3 DPS players** (`dps`).
- **Dynamic Execution Time**: Each dungeon instance lasts for a randomly determined time t, which selected between a given minimum (`t1`) and maximum (`t2`).
- **Synchronization Mechanisms**: Implements **monitors**, **semaphores**, or **threading** to manage concurrent party assignments efficiently.
- **Real-Time Status Updates**: Displays the current state of each instance as either **"active"** or **"empty"**.
- **Summary Report**: Provides the number of parties served per instance and the total execution time at the end.

## Video Demonstration of Test Cases
For easy accessibility, the following links are provided:
- **Test Cases**: [Google Sheet](https://docs.google.com/spreadsheets/d/1e0z5vB4SOaV0w_Wq4z4OSu2m8SwCieR7PKlgZbW6jp0/edit?usp=sharing)
- **Video Links**: [Google Drive](https://drive.google.com/drive/folders/1ueuqQuExtBMd067cqu2JDHzUbrU3gIAI?usp=sharing)

## Build and Compile Instructions
1. Ensure that you have a C compiler installed on your machine.
2. Clone the repository or download the Zip file.
    ```
    https://github.com/axvolkzki/STDISCM-P2.git
    ```
3. Manually run the program on your local machine by navigating to the Project directory where the main.c is located.
    ```
    cd STDISCM-P2
    ```
4. Compile the program.
    ```
    g++ -std=c++20 Config/GlobalConfig.cpp Dungeon/DungeonInstance.cpp Dungeon/DungeonManager.cpp Utility/Colors.cpp main.cpp -o main.exe
    ```
5. Run the executable file.
    ```
    ./main.exe
    ```

## Slides
Access the [ABENOJA - P2 - Looking for Group Synchronization slides](https://docs.google.com/presentation/d/1Q2JxRiQNlhZNyfgzTACuJYdImLJTy7692Bak_n_IbZo/edit?usp=sharing) that covers the following topics:

- Explanation of potential deadlock and starvation scenarios.
- Overview of synchronization mechanisms used to address these issues.

## Developer
ABENOJA, Amelia Joyce L.     STDISCM - S14