# 2d-soft-body
A soft-body simulation written in C++. 2D bodies consist of point masses joined by spring-damper couples. Uses Euler's method to numerically solve for positions and velocities. 

Velocity Verlet causes a ton of energy drift which is, luckily, compensated by the dampers if the damping coefficient is large enough. If the damping coefficient is set to a very small value or zero, energy drift will cause the soft body to be *very* unstable. To fix this issue I might implement a higher order integrator instead of Velovity Verlet in the future.

Uses raylib as the graphics API/OpenGL wrapper and raygui for the UI.
