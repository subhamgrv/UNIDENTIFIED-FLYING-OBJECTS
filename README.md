# UNIDENTIFIED FLYING OBJECTS

**Timeline:** April 2021 – July 2021

## Project Overview
This project is a 3D simulation of Unidentified Flying Objects (UFOs) implemented using C and the OpenGL API (specifically GLUT). The program visualizes a fleet of UFOs flying in complex, mathematical 3D orbits over a gradient background. It acts as a simulation of control functions, providing interactive menu-based and keyboard controls to manage the fleet, such as adding UFOs, removing UFOs, and toggling their animation.

## Key Features & Responsibilities
- **Interactive Controls:** Designed interactive controls utilizing a right-click drop-down menu for adding and removing UFOs, as well as starting and stopping the motion. 
- **Motion Control & Math:** Implemented mathematically calculated motion control. The UFOs fly in parametric orbits utilizing trigonometric functions (`sin` and `cos`). It supports dynamic direction changes aligning the UFO's rotation to the direction of its trajectory.
- **Rendering Optimization:** Optimized the rendering behavior to support multiple UFOs concurrently on the screen (up to a predefined maximum limit of 15 UFOs).
- **3D Modeling through Primitives:** UFOs are constructed using primitive 3D shapes. The design features a wireframe spherical dome (`glutWireSphere`), a solid teapot for the main body (`glutSolidTeapot`), and a solid cone acting as a beam or propulsion exhaust (`glutSolidCone`).
- **Aesthetics:** Included a smooth gradient background using smoothed polygons (`GL_SMOOTH`) to give a space-like or atmospheric feel.

## Technologies Used
- **C** (Programming Language)
- **OpenGL** (Graphics API)
- **GLUT** (OpenGL Utility Toolkit)

## Controls
### Right-Click Menu
A context menu is available by right-clicking anywhere in the application window:
- **Add UFO:** Spawns a new UFO with a random starting position and velocity direction.
- **Remove UFO:** Removes the most recently added UFO from the screen.
- **Start Motion:** Enables the continuous animation of all UFOs on the screen.
- **Stop Motion:** Pauses the animation.
- **Exit:** Closes the application.

### Keyboard Controls
- **Spacebar (` `):** If the animation is currently stopped, pressing the spacebar advances the simulation by a single frame/tick.
- **Escape (`ESC`):** Exits the application immediately.

## Technical Details
- The maximum number of simultaneous UFOs is hardcoded to 15 (`MAX_OBJECTS 15`).
- The viewing projection is configured using `glFrustum`, establishing a solid 3D perspective.
- Each UFO tracks its own `theta` (angle/time), `velocity`, `posX`, `posY`, `posZ`, and `rotation`.
- The simulation automatically starts with 3 UFOs on the screen upon launch.

## How to Compile and Run
To compile this project on a Unix/Linux environment with GCC and OpenGL installed, run:
```bash
gcc OpenGL_UFO.c -o ufo_sim -lm -lGL -lGLU -lglut
```
Then execute it:
```bash
./ufo_sim
```
*(On Windows, you may need to link against `opengl32.lib`, `glu32.lib`, and `glut32.lib` using MinGW or MSVC).*
