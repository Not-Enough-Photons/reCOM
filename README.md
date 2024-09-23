![Isolated.png](https://github.com/Not-Enough-Photons/ZIEngine/blob/main/img/ziengine_banner.png?raw=true)

# Intro
This repository houses the reverse engineered code of Zipper Interactive's engine.

It is a work in progress, and a lot needs to make sure the SOCOM experience is one-to-one with the PlayStation 2.

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
