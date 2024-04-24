# Flying Pancakes
A comprehensive mathematical model for simulating the flight dynamics of a disc in a disc golf game.

The model incorporates various physical forces and factors including projectile motion, aerodynamic lift and drag, wind effects, disc spin, stability, and gyroscopic effects.

The whitepaper is under construction, I have yet to publish it. It needs work.

## LICENSE (Sorry, but this is required).
[![CC BY-NC-ND 4.0][cc-by-nc-nd-shield]][cc-by-nc-nd]

This work is licensed under a
[Creative Commons Attribution-NonCommercial-NoDerivs 4.0 International License][cc-by-nc-nd].

[![CC BY-NC-ND 4.0][cc-by-nc-nd-image]][cc-by-nc-nd]

[cc-by-nc-nd]: http://creativecommons.org/licenses/by-nc-nd/4.0/
[cc-by-nc-nd-image]: https://licensebuttons.net/l/by-nc-nd/4.0/88x31.png
[cc-by-nc-nd-shield]: https://img.shields.io/badge/License-CC%20BY--NC--ND%204.0-lightgrey.svg

Obviously mathematical formulas cannot be copyrighted.
I can not stop you from implementing this math YOURSELF. You're welcome to.
However the whitepaper and implementations provided here are under the license.

# Probably mathematically wrong, but it's close.
## Initial velocity components:
```math
v_{0x} = v_0 \cdot \sin(\theta)
```
```math
v_{0y} = v_0 \cdot \cos(\theta)
```
```math
v_{0z} = v_0 \cdot \sin(\theta)
```
## Position at time \( t \):
```math
x(t) = x_0 + v_{0x} \cdot t + \int_{0}^{t} \left(\frac{F_{\text{total}_x}}{m}\right) d\tau
```
```math
y(t) = y_0 + v_{0y} \cdot t + \int_{0}^{t} \left(\frac{F_{\text{total}_y}}{m}\right) d\tau
```
```math
z(t) = z_0 + v_{0z} \cdot t - \frac{1}{2} g \cdot t^2 + \int_{0}^{t} \left(\frac{F_{\text{total}_z}}{m}\right) d\tau
```
## Force components:
```math
F_{\text{total}_x} = -\frac{1}{2} \rho \cdot C_d \cdot A \cdot \| \mathbf{v} \|^2 + F_{\text{wind}_x}
```
```math
F_{\text{total}_y} = -\frac{1}{2} \rho \cdot C_d \cdot A \cdot \| \mathbf{v} \|^2 + F_{\text{wind}_y}
```
```math
F_{\text{total}_z} = m \cdot g -\frac{1}{2} \rho \cdot C_d \cdot A \cdot \| \mathbf{v} \|^2 + F_{\text{wind}_z} + F_{\text{lift}_z}
```
```math
F_{\text{lift}_z} = \frac{1}{2} C_l \cdot A \cdot \rho \cdot \| \mathbf{v} \| \cdot \text{SpinRate} \cdot \text{GyroscopicFactor} \cdot S
```

## Variables and their descriptions
```math
x_0, y_0, z_0 = \text{initial positions.} 
```
```math
v_0  = \text{initial velocity.}
```
```math
v_{0x}, v_{0y}, v_{0z} = \text{initial velocity components.}
```
```math
\theta = \text{launch angle.}
```
```math
C_d = \text{drag coefficient.}
```
```math
C_l = \text{lift coefficient.}
```
```math
A = \text{frontal area of the disc.}
```
```math
v = \text{magnitude of the velocity vector.}
```
```math
g = \text{acceleration due to gravity.}
```
```math
m = \text{mass of the disc.}
```
```math
\rho = \text{air density.}
```
```math
F_{\text{wind}_x} = \text{wind force in the x direction.}
```
```math
F_{\text{wind}_y} = \text{wind force in the y direction.}
```
```math
F_{\text{wind}_z} = \text{wind force in the z direction.}
```
```math
S = \text{disc stability factor.}
```
```math
\text{SpinRate} = \text{spin rate of the disc.}
```
```math
\text{GyroscopicFactor} = \text{gyroscopic factor affecting the lift force.}
```
```math
F_{\text{lift}_z} = \text{lift force in the z direction.}
```
```math
F_{\text{total}_x} = \text{total forces in the x direction.}
```
```math
F_{\text{total}_y} = \text{total forces in the y direction.}
```
```math
F_{\text{total}_z} = \text{total forces in the z direction.}
```
```math
t = \text{time variable}
```
