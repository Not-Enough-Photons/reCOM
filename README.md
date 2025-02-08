![Isolated.png](https://github.com/Not-Enough-Photons/reCOM/blob/main/img/recom-logo.png?raw=true)

# Intro
This repository houses the reverse engineered code of the SOCOM games, alongside the engine, GameZ.

It is a work in progress, and a lot needs to make sure the SOCOM experience is one-to-one with the PlayStation 2.

# Compilation
1. Clone this project by doing ``git clone https://github.com/Not-Enough-Photons/reCOM`` into a directory of your choice, or by downloading the source code ZIP and extracting it anywhere
2. CD into the main directory of the project
3. Type ``premake5 vs2022`` or any other build profile you know
4. Open the project in an IDE and do Left Control + Shift + B, or click the play button
5. Drag all DLL files into ``output/debug`` or ``output/release``
6. That's it!

# ROM Information
- Name: **SCUS_972.05**
- Build Date: **May 13th, 2002 at 9:10:36 AM PST**
- sha256: **00c9cee7f75b921fda1e848d04f64881b5a0b7841300591cac91371bb23d4f8a**
- Compiler: **Metrowerks MIPS C Compiler v2.4.1.01**

# Source Trees
## Apps - Application Layer
| Module | Description |
| ------ | ----------- |
| [FTS](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/Apps/FTS) | App specific code such as the game HUD, entry point, and the games database. |

## gamez - Core Engine
| Module | Description |
| ------ | :---------- |
| [zAI](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zAI) | AI path generation, A* algorithm implementation, and AI state behavior |
| [zAnim](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zAnim) | Animation logic and animation keyframe logic; animation blending |
| [zArchive](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zArchive) | GameZ's primary format for storing binary data such as levels, readers, and meshes |
| [zAssetLib](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zAssetLib) | Asset library that contains models, textures, and palettes |
| [zBody](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zBody) | Skeleton classes, animation blending, body parts, etc. |
| [zCamera](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zCamera) | Camera behavior, FOV controls, and app-specific camera behavior |
| [zCharacter](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zCharacter) | NPC setup classes and settings definitions for NPCs |
| [zEntity](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zEntity) | Generic game entity definitions and interactions |
| [zFTS](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zFTS) | App foundation that provides implementations, like missions |
| [zGame](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zGame) | Game states and managers |
| [zIMGUI](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zIMGUI) | IMGUI debug interface (is not a part of the original source tree) |
| [zInput](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zInput) | Input handling for gamepads and keyboards |
| [zIntersect](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zIntersect) | Raycasts, intersections, and collision logic |
| [zMath](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zMath) | Math functions for vectors, quaternions, matricies, and more |
| [zMPEG](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zMPEG) | Video playback and video managers in-engine |
| [zNetwork](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zNetwork) | Network objects and managers for multiplayer, and for Medius |
| [zNode](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zNode) | GameZ's node-based system and node management |
| [zParticle](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zParticle) | GPU instanced particle system |
| [zPhysics](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zPhysics) | Physics engine for GameZ |
| [zReader](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zReader) | LISP processor for compiled and non-compiled data files |
| [zRender](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zRender) | Main GameZ rendering pipeline; renders nodes, visuals, etc. |
| [zSave](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zSave) | Saver/loader for GameZ saves and save states |
| [zSeal](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zSeal) | NPC code, player controller, and AI controller code for NPC objects |
| [zShader](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zShader) | GLSL/HLSL shader classes |
| [zSoftImage](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zSoftImage) | Autodesk SoftImage script parsers and object parsers |
| [zSound](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zSound) | Sound management, handling, and playback |
| [zSystem](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zSystem) | Game system management and memory management |
| [zTexture](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zTexture) | Textures, management of textures, and container types for textures |
| [zTwoD](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zTwoD) | 2D elements and handling of 2D elements to be drawn to the UI |
| [zUI](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zUI) | UI framework to house 2D elements |
| [zUtil](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zUtil) | Utilities for file I/O and buffered I/O, and more |
| [zValve](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zValve) | Game signals and counters to dispatch UI events and game events |
| [zVehicle](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zVehicle) | Manages character types and AI stats (NOT related to drivable vehicles) |
| [zVideo](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zVideo) | Render control and controls for the main framebuffer |
| [zVisual](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zVisual) | Interface for dealing with OpenFlight (.FLT) meshes, decals, and sub-meshes |
| [zWeapon](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zWeapon) | Generic weapon implementation and ammo |
| [zWorld](https://github.com/Not-Enough-Photons/reCOM/tree/main/src/gamez/zWorld) | Root parent class, CWorld, for all nodes |

# Background
Currently, I (adamdev) am the sole contributor to this project. I have been using Ghidra to reverse engineer the binaries of the games, to some luck.

I have sourced a demo disk that contains all debug symbols (thank you Zero1UP!), which is indispensable to this project.

# Disclaimer
This repository **will NOT** contain any copyrighted assets. If you are using this project to play SOCOM titles, you **MUST** own legal copies of the games for this to work.
We will not distribute illegal copies of the game.
All rights are reserved to Zipper Interactive and Sony Computer Entertainment.
