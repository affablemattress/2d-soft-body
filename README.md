# 2d-soft-body
A soft-body simulation written in C++. 2D bodies are formed by point masses joined by spring-damper couples. Uses Euler's method to numerically solve for positions and velocities. 

I'm currently rewriting the codebase to incorporate Velocity Verlet integration instead of Euler's, due to the huge errors caused by Euler's method being only a first order approximation. I'm also moving towards a more component based architecture.

Uses raylib as the graphics API/OpenGL wrapper and raygui for the UI.
