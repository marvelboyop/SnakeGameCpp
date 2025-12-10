# 🐍 Snake Game in C++

A classic **console-based Snake Game written in C++**, designed for beginners to learn:

- Game loops  
- Real-time input handling  
- Tail-follow mechanics  
- Collision detection  
- Rendering tricks  
- Practical use of arrays  
- Smooth screen updates  

This version includes:

✔ Smooth screen rendering (no flicker)  
✔ Wall Mode & No-Wall (Wrap-Around) Mode  
✔ Snake tail that grows properly  
✔ Speed boost  
✔ Score system  
✔ Collision detection  
✔ Cursor hiding for clean visuals  
✔ Beginner-friendly structure  

---

## 🚀 Features

### 🎮 Gameplay

- Move using **W / A / S / D**  
- Eat fruit (**F**) to grow  
- Gain **+1 score** per fruit  
- Press **Spacebar** for temporary **speed boost**  
- Press **X** to exit instantly  

### 🧱 Game Modes

1. **Wall Mode** → hitting the wall ends the game  
2. **No-Wall Mode (Wrap-Around)** → snake appears from the opposite side  

---

## ⭐ Mechanics Explanation (Beginner Friendly)

### ▶ Snake Movement

Each frame runs the loop:

input() → logic() → gameOverFunc() → draw()


### ▶ Tail Logic

- The snake head moves first  
- Each tail segment copies the position of the segment in front of it  
- The first tail segment follows the **old head position**

Arrays used:

```cpp
int tailX[100], tailY[100];
int nTail;
```

### Smooth Rendering

Instead of clearing the screen, we reposition the cursor:
```cpp
SetConsoleCursorPosition()
```
This removes flicker completely.

---

### 📸 Demo (Example Console Output)
```bash
##############################
#                            #
#                            #
#                            #
#                            #
#       oooO                 #
#                            #
#             F              #
#                            #
##############################
Score = 3
```
---

### 📂 File Structure
```bash 
.
├── SnakeGame.cpp
├── README.md
├── LICENSE
└── .gitignore
```

### 🎮 Controls
|      Key      |     Action     | 
|:-------------|:--------------:|
| W       | Move Up        | 
| A       | Move Left        | 
| S       | Move Down        | 
| D       | Move Right        | 
| Spacebar       | Speed Boost        | 
| X       | Quit Game        | 

--- 

### ⚙️ Compile & Run
Compile:
 ```bash
 g++ SnakeGame.cpp -o snake
```
Run:
```bash 
./snake
```
---
### 🧠 Concepts used in This Project

- Full game loop implementation
- Real-time keyboard input
- Tail movement logic
- Collision detection
- Console-based rendering
- Multiple game modes
- Speed manipulation
- Basic game physics

---

🤝 Contributing

Pull requests are welcome!
Feel free to improve logic, visuals, or add new mechanics.

--- 

### 📜 License

This project is open-source and licensed under the MIT License.
See the separate LICENSE file for details.
