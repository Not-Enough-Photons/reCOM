![Isolated.png](https://github.com/Not-Enough-Photons/reCOM/blob/main/img/recom-logo.png?raw=true)

# Intro
This repository houses the reverse engineered code of the SOCOM games, alongside the engine, GameZ.

It is a work in progress, and a lot needs to make sure the SOCOM experience is one-to-one with the PlayStation 2.

# ROM Information
- Name: **SCUS_972.05**
- Build Date: **March 19th, 2002**
- sha256: **00c9cee7f75b921fda1e848d04f64881b5a0b7841300591cac91371bb23d4f8a**
- Compiler: **Metrowerks MIPS C Compiler v2.4.1.01**

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
| zBody | Skeleton classes, animation blending, body parts, etc. |
| zCamera | Camera behavior, FOV controls, and app-specific camera behavior |
| zCharacter | NPC setup classes and settings definitions for NPCs |
| zEntity | Generic game entity definitions and interactions |
| zFTS | App foundation that provides implementations, like missions |
| zGame | Game states and managers |
| zIMGUI | IMGUI debug interface (is not a part of the original source tree) |
| zInput | Input handling for gamepads and keyboards |
| zIntersect | Raycasts, intersections, and collision logic |
| zMath | Math functions for vectors, quaternions, matricies, and more |
| zMPEG | Video playback and video managers in-engine |
| zNetwork | Network objects and managers for multiplayer, and for Medius |
| zNode | GameZ's node-based system and node management |
| zParticle | GPU instanced particle system |
| zPhysics | Physics engine for GameZ |
| zReader | LISP processor for compiled and non-compiled data files |
| zRender | Main GameZ rendering pipeline; renders nodes, visuals, etc. |
| zSave | Saver/loader for GameZ saves and save states |
| zSeal | NPC code, player controller, and AI controller code for NPC objects |
| zShader | GLSL/HLSL shader classes |
| zSoftImage | Autodesk SoftImage script parsers and object parsers |
| zSound | Sound management, handling, and playback |
| zSystem | Game system management and memory management |
| zTexture | Textures, management of textures, and container types for textures |
| zTwoD | 2D elements and handling of 2D elements to be drawn to the UI |
| zUI | UI framework to house 2D elements |
| zUtil | Utilities for file I/O and buffered I/O, and string tables |
| zValve | Game signals and counters to dispatch UI events and game events |
| zVehicle | Manages character types and AI stats (NOT related to drivable vehicles) |
| zVideo | Render control and controls for the main framebuffer |
| zVisual | Interface for dealing with OpenFlight (.FLT) meshes, decals, and sub-meshes |
| zWeapon | Generic weapon implementation and ammo |
| zWorld | Root parent class, CWorld, for all nodes |

# Background
Currently, I (adamdev) am the sole contributor to this project. I have been using Ghidra to reverse engineer the binaries of the games, to some luck.

I have sourced a demo disk that contains all debug symbols (thank you Zero1UP!), which is indispensable to this project.

# Disclaimer
This repository **will NOT** contain any copyrighted assets. If you are using this project to play SOCOM titles, you **MUST** own legal copies of the games for this to work.
We will not distribute illegal copies of the game.
All rights are reserved to Zipper Interactive and Sony Computer Entertainment.
