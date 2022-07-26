# 2d-soft-body
A 2D soft body simulation that uses Euler integration. I'm currently rewriting the whole codebase to incorporate Velocity Verlet integration instead of Euler's, due to the huge errors caused by Euler's method being only a first order approximation.

Uses raylib as the graphics API/OpenGL wrapper and raygui for the UI.
