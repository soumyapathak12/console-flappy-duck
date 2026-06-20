# 🦆 Flappy Duck

A **console-based Flappy Bird inspired game written in C** for the Windows terminal. Control the duck, dodge incoming pipes, and try to beat your high score in this colorful arcade-style console game.

---

## 🎮 About the Game

**Flappy Duck** is a terminal game where the player controls a duck and must avoid colliding with pipes while surviving as long as possible. The game features real-time keyboard controls, randomized obstacles, score tracking, and a persistent high-score system.

This project was built in **C using the Windows API** and uses ANSI escape codes for colored console rendering.

---

## ✨ Features

* 🦆 Duck movement with gravity and flap controls
* 🌿 Randomly generated moving pipes
* 💥 Collision detection with pipes and borders
* 🏆 Score tracking and persistent high score saving
* 🎨 Colored console graphics using ANSI escape codes
* ⌨️ Real-time keyboard controls
* 🔁 Replay option after game over
* 🔊 Simple sound effects using `Beep()`
* 🖥️ Smooth frame-based console rendering

---

## 🛠️ Tech Stack

* **Language:** C
* **Platform:** Windows
* **Libraries / APIs Used:**

  * `windows.h`
  * `wincon.h`
  * `stdio.h`
  * `stdlib.h`
  * `time.h`
  * `string.h`

---

## 📂 Project Structure

```bash
flappy-duck/
│── FlappyDuck_source_code.c   # Main source code
│── highscore.txt              # Stores the high score
│── README.md                  # Project documentation
```

> `highscore.txt` is automatically created/updated when the game runs and stores the highest score achieved.

---

## 🎯 How to Play

The objective is simple:

* Control the duck
* Avoid crashing into the pipes
* Don’t hit the top or bottom walls
* Survive as long as possible and score by passing pipes

Each pipe you successfully pass increases your score by **1**.

---

## 🎮 Controls

| Key           | Action                     |
| ------------- | -------------------------- |
| `↑` Arrow Key | Flap upward                |
| `W`           | Flap upward                |
| `Q`           | Quit the game              |
| `Y`           | Play again after game over |
| `N`           | Exit after game over       |

---

## ▶️ How to Run

### 1. Clone the repository

```bash
git clone https://github.com/your-username/flappy-duck.git
cd flappy-duck
```

### 2. Compile the program

Use **GCC / MinGW** on Windows:

```bash
gcc FlappyDuck_source_code.c -o flappy_duck
```

### 3. Run the executable

```bash
flappy_duck.exe
```

---

## ⚠️ Requirements

This game is designed for **Windows only** because it uses:

* `windows.h`
* `GetAsyncKeyState()`
* `Sleep()`
* `Beep()`
* Windows console APIs

So it **will not run directly on Linux/macOS** without modifications.

---

## 🧠 Game Logic Overview

The game works using a continuous loop where:

1. The duck responds to keyboard input
2. Gravity pulls the duck downward over time
3. Pipes move from right to left across the screen
4. New pipes are generated when old ones leave the screen
5. Collision detection checks for hits with pipes or boundaries
6. Score updates when the duck successfully passes a pipe
7. The screen is redrawn frame by frame to create animation

---

## 🏆 High Score System

The game stores the highest score in a file named **`highscore.txt`**.

* When the game starts, it loads the saved high score
* If the player beats it, the score is updated and saved automatically

This allows the high score to persist between game sessions.

---

## 🎨 Console Design

The game uses ANSI escape codes and console manipulation to create a more visually appealing terminal experience, including:

* Colored score display
* Colored pipes
* Blue sky-style background
* A duck-shaped player sprite
* Intro and game-over screens

---

## 📸 Gameplay Preview



```md
## 📸 Preview
<img width="477" height="240" alt="flappyduck1" src="https://github.com/user-attachments/assets/193d37c9-2f73-4752-914a-e041b1a2c760" />
<img width="518" height="355" alt="flappyduck2" src="https://github.com/user-attachments/assets/9e89e877-c402-41d2-897d-7b38e4b5eac5" />
<img width="500" height="347" alt="flappyduck3" src="https://github.com/user-attachments/assets/65c0058b-6cca-4b28-92f5-4a3615f637c3" />
<img width="192" height="168" alt="flappyduck4" src="https://github.com/user-attachments/assets/68db9165-6b69-4078-8a12-f969fe61e2a8" />
---

## 📚 What I Learned

This project helped me practice:

* Game loops in C
* Real-time keyboard input handling
* Console rendering and animation
* Collision detection
* File handling for saving game data
* Using Windows API functions in C
* Structs and game object management

---

## 🤝 Contributing

Contributions, suggestions, and improvements are welcome.

If you'd like to improve the game:

1. Fork the repository
2. Create a new branch
3. Make your changes
4. Submit a pull request

---


## 👩‍💻 Author

Made with C and a lot of debugging 😄
**Soumya Pathak**
