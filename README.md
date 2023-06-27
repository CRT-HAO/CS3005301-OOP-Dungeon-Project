# Dungeon Project

<img width="912" alt="截圖 2023-06-27 上午11 47 18" src="https://github.com/CRT-HAO/CS3005301-OOP-Dungeon-Project/assets/31580253/2f3524d2-0095-42b0-a864-2a593ec0de0b">
<img width="912" alt="截圖 2023-06-27 上午11 47 57" src="https://github.com/CRT-HAO/CS3005301-OOP-Dungeon-Project/assets/31580253/56ffd29b-21b6-45b0-b1e3-cd928ab92fb4">


## Support Platforms
 - Windows MSVC
 - MacOS AppleClang
 - Linux GCC/Clang

## Build

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

## What have we done?

- Basic operation and game logic.
- There are at least two types of enemies with different behavior patterns.
- There are at least two or more props that provide different effects.
- There are at least three or more different playable levels
- Can save and read files.

## Keymap

| Key     | Function       |
| ------- | -------------- |
| W/A/S/D | Move Player    |
| O       | Load Save File |
| P       | Save File      |
| J       | Attack         |
| Enter   | Open Door      |
