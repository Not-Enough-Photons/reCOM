![Isolated.png](https://github.com/Not-Enough-Photons/reCOM/blob/main/img/recom-logo.png?raw=true)

# Intro
This repository houses the reverse engineered code of SOCOM's engine, GameZ.

It is a work in progress, and a lot needs to make sure the SOCOM experience is one-to-one with the PlayStation 2.

# ROM Information
| Name | Build Date |sha256 |
| SCUS_972.05 | March 19th, 2002 | 00c9cee7f75b921fda1e848d04f64881b5a0b7841300591cac91371bb23d4f8a |

# Source Trees
## Apps - Application Layer
| Module | Description |
| ------ | ----------- |
| FTS | App specific code such as the game HUD, entry point, and the games database. |

## gamez - Core Engine
| Module | Description |
| ------ | :---------- |
| zAI | AI path generation, A* algorithm implementation, and AI state behavior |
| zAnim | Animation logic and animation keyframe logic; animation blending |
| zArchive | GameZ's primary format for storing binary data such as levels, readers, and meshes |
| zAssetLib | Asset library that contains models, textures, and palettes |
| zCamera | Camera behavior, FOV controls, and app-specific camera behavior |
| zEntity | Generic game entity definitions and interactions |
| zFTS | App foundation that provides implementations, like missions |
| zGame | Game states and managers |
| zInput | Input handling for gamepads and keyboards |
| zMath | Math functions for vectors, quaternions, matricies, and more |
| zNetwork | Network objects and managers for multiplayer, and for Medius |
| zNode | GameZ's node-based system and node management |
| zReader | LISP processor for compiled and non-compiled data files |
| zRender | Main GameZ rendering pipeline; renders nodes, visuals, etc. |
| zRender/zParticle | GPU instanced particle system |
| zRender/zVisual | Abstractions for 3D models to be passed to the graphics API (Meshes, sub-meshes, decals, etc.) |
| zSeal | NPC code, player controller, and AI controller code for NPC objects |
| zSound | Sound management, handling, and playback |
| zSystem | Game system management and memory management |
| zTexture | Textures, management of textures, and container types for textures |
| zTwoD | 2D elements and handling of 2D elements to be drawn to the UI |
| zUI | UI framework to house 2D elements |
| zUtil | Utilities for file I/O and buffered I/O, and string tables |
| zValve | Game signals and counters to dispatch UI events and game events |
| zVideo | Render control and controls for the main framebuffer |
| zWeapon | Generic weapon implementation and ammo |


# To-Do List (Not In Order)
- Loaders for ZAR (Zipper Archive), ZDB (Zipper Database), and other proprietary formats
- Support for level creation and editing
- Rendering pipelines
- Asset editor for the aforementioned data formats
- ZAR property serialization/deserialization
- Engine templates to port games over

# Background
Currently, I (adamdev) am the sole contributor to this project. A few weeks ago I got started on using Ghidra to reverse engineer the binaries of the games, to some luck.

I scoured demo disks, beta copies of the game, and even release builds to find strings and start building context of the games binary to see how it ticks.

Now I am on the stage of using the Metrowerks IDE (what Zipper used to develop the game) to compile C++ code into MIPS assembly to closely match what they're doing, down to a ground truth.

My final goal with this engine is that it will eventually get to a state where we can tackle all SOCOM PlayStation games and bring those titles to PC, using this engine as a base.

Stay tuned, and you are free to contribute any findings you see fit.

# Disclaimer
This repository **will NOT** contain any copyrighted assets. If you are using this engine to load reCOM, you **MUST** own the original SOCOM games for this to work.
We will not distribute illegal copies of the game.
All rights are reserved to Zipper Interactive and Sony Computer Entertainment.
