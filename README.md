# Flying Pancakes : Under Construction 
A comprehensive mathematical model for simulating the flight dynamics of a disc in a disc golf game.

The model incorporates various physical forces and factors including projectile motion, aerodynamic lift and drag, wind effects, disc spin, stability, and gyroscopic effects.

The whitepaper and implementations are under construction, I have yet to publish the paper. It needs major work as the implemenation has driven the formulas. The formulas and the Python implementations look correct and seem to match, although it could be wrong still. It should be noted that runge-kutta is used in the implementations where the formula has explicit integration.

## LICENSE (Sorry, it's required).
Obviously mathematical formulas cannot be copyrighted.

I can not stop you from implementing this math YOURSELF. You're welcome to.

However the whitepaper and implementations provided here are under the license given.

This work is licensed under a [Creative Commons Attribution-NonCommercial-NoDerivs 4.0 International License][cc-by-nc-nd].

[![CC BY-NC-ND 4.0][cc-by-nc-nd-shield]][cc-by-nc-nd]

[![CC BY-NC-ND 4.0][cc-by-nc-nd-image]][cc-by-nc-nd]

[cc-by-nc-nd]: http://creativecommons.org/licenses/by-nc-nd/4.0/
[cc-by-nc-nd-image]: https://licensebuttons.net/l/by-nc-nd/4.0/88x31.png
[cc-by-nc-nd-shield]: https://img.shields.io/badge/License-CC%20BY--NC--ND%204.0-lightgrey.svg

# Model Plots :

## Pure Python Plot ---------------------v Numpy Python Plot -----------------v
<img src="https://github.com/SaxonRah/flying_pancakes/blob/main/plots/PurePython_RungeKutta_Plot.png" width="401" height="344"> <img src="https://github.com/SaxonRah/flying_pancakes/blob/main/plots/Numpy_RungeKutta_Plot.png" width="401" height="344">

# Probably mathematically incorrect, but it's close.
The equations describe the motion of a disc-like projectile in three-dimensional space. They take into account forces such as gravity, drag, wind, and lift. The trajectory equations describe the position of the disc-like object over time, while the total force equations account for the various forces like spin and gyroscopic effect acting on the disc-like object.

1. **Initial Velocity Components**:
   - $v_{0x}$: Initial velocity component in the x-direction.
   - $v_{0y}$: Initial velocity component in the y-direction.
   - $v_{0z}$: Initial velocity component in the z-direction.
   - $v_0$: Initial velocity magnitude.
   - $\theta$: Launch angle (angle with respect to the horizontal plane).
   - $\phi$: Angle of spin (angle with respect to the x-y plane).

```math
v_{0x} = v_0 \cdot \cos(\theta)
```
```math
v_{0y} = v_0 \cdot \sin(\theta)
```
```math
v_{0z} = v_0 \cdot \cos(\theta) \cdot \sin(\phi)
```

2. **Trajectory Equations**:
   - $x(t)$: Horizontal position at time ($t$).
   - $y(t)$: Depth position at time ($t$).
   - $z(t)$: Vertical position at time ($t$).
   - $x_0$: Initial horizontal position.
   - $y_0$: Initial depth position.
   - $z_0$: Initial vertical position.
   - $t$: Time.
   - $g$: Acceleration due to gravity.

```math
x(t) = x_0 + v_{0x} \cdot t + \int_{0}^{t} \left(\frac{F_{\text{total}_x}}{m}\right) d\tau
```
```math
y(t) = y_0 + v_{0y} \cdot t + \int_{0}^{t} \left(\frac{F_{\text{total}_y}}{m}\right) d\tau
```
```math
z(t) = z_0 + v_{0z} \cdot t - \frac{1}{2} g \cdot t^2 + \int_{0}^{t} \left(\frac{F_{\text{total}_z}}{m}\right) d\tau
```

3. **Total Force Components**:
   - $F_{\text{total}_x}$: Total force acting in the x-direction.
   - $F_{\text{total}_y}$: Total force acting in the y-direction.
   - $F_{\text{total}_z}$: Total force acting in the z-direction.
   - $\rho$: Density of the medium through which the object is moving (e.g., air density).
   - $C_d$: Drag coefficient, a dimensionless coefficient that characterizes the drag or resistance of an object moving through a fluid.
   - $A$: Cross-sectional area of the object.
   - $\|\| \mathbf{v} \|\|$: Magnitude of velocity vector.
   - $F_{\text{wind}_x}$: Wind force acting in the x-direction.
   - $F_{\text{wind}_y}$: Wind force acting in the y-direction.
   - $F_{\text{wind}_z}$: Wind force acting in the z-direction.
   - $m$: Mass of the object.

```math
F_{\text{total}_x} = -\frac{1}{2} \rho \cdot C_d \cdot A \cdot \| \mathbf{v} \|^2 + F_{\text{wind}_x}
```
```math
F_{\text{total}_y} = -\frac{1}{2} \rho \cdot C_d \cdot A \cdot \| \mathbf{v} \|^2 + F_{\text{wind}_y}
```
```math
F_{\text{total}_z} = m \cdot g -\frac{1}{2} \rho \cdot C_d \cdot A \cdot \| \mathbf{v} \|^2 + F_{\text{wind}_z} + F_{\text{lift}_z}
```

4. **Lift Force Component**:
   - $F_{\text{lift}_z}$: Lift force acting in the z-direction.
   - $C_l$: Lift coefficient, a dimensionless coefficient that characterizes the lift generated by an object moving through a fluid.
   - $\text{SpinRate}$: Spin rate of the object.
   - $\text{GyroscopicFactor}$: Gyroscopic factor, a factor that accounts for gyroscopic effects.
   - $S$: Surface area of the object.

```math
F_{\text{lift}_z} = \frac{1}{2} C_l \cdot A \cdot \rho \cdot \| \mathbf{v} \| \cdot \text{SpinRate} \cdot \text{GyroscopicFactor} \cdot S
```
