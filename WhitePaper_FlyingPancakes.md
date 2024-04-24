# Flying Pancakes:
## A Flight Dynamics Model for Disc Golf Simulation

**Abstract:**
This paper presents a comprehensive mathematical model for simulating the flight dynamics of a disc in a disc golf game. The model incorporates various physical forces and factors including projectile motion, aerodynamic lift and drag, wind effects, disc spin, stability, and gyroscopic effects. By integrating these elements into a cohesive framework, the model provides a realistic representation of disc flight trajectories in different environmental conditions.

**Introduction:**
Disc golf is a popular sport that combines elements of traditional golf with the use of flying discs, often referred to as discs or frisbees. Similar to traditional golf, players aim to complete a course in the fewest throws possible, with each throw starting from a designated tee area and ending in a target basket. The flight dynamics of a disc play a crucial role in determining its trajectory and ultimately, the outcome of a player's throw. Understanding and accurately simulating these dynamics is essential for creating realistic disc golf simulations in virtual environments.

**Model Overview:**
The flight dynamics model presented in this paper considers the following key components:

1. **Initial Velocity Components:**
   - Upon release, a disc exhibits an initial velocity vector ($v_0$), which undergoes decomposition into its constituent components along the Cartesian axes. This decomposition, facilitated by the launch angle ($\theta\$), delineates the contributions of velocity along the ($x$, $y$, and $z$) axes. This fundamental step is paramount for subsequent calculations, as it delineates the initial kinematic parameters governing the disc's trajectory.

```math
v_{0x} = v_0 \cdot \sin(\theta)
```
```math
v_{0y} = v_0 \cdot \cos(\theta)
```
```math
v_{0z} = v_0 \cdot \sin(\theta)
```

2. **Position at Time $t$:**
   - The disc's position at any temporal instant ($t$) is intricately determined by integrating its velocity components over time. Beginning from the designated initial positions ($x_0$, $y_0$, $z_0$), this integration encapsulates the cumulative effects of forces acting upon the disc, encompassing the gravitational, aerodynamic, and wind-induced influences. The resultant position equations yield a comprehensive depiction of the disc's spatial dynamics.

```math
x(t) = x_0 + v_{0x} \cdot t + \int_{0}^{t} \left(\frac{F_{\text{total}_x}}{m}\right) d\tau
```
```math
y(t) = y_0 + v_{0y} \cdot t + \int_{0}^{t} \left(\frac{F_{\text{total}_y}}{m}\right) d\tau
```
```math
z(t) = z_0 + v_{0z} \cdot t - \frac{1}{2} g \cdot t^2 + \int_{0}^{t} \left(\frac{F_{\text{total}_z}}{m}\right) d\tau
```

3. **Force Components:**
   - The net forces exerted on the disc in each spatial dimension ($F_{total_x}$, $F_{total_y}$, and $F_{total_z}$) are meticulously computed, synthesizing myriad factors. Aerodynamic drag, contingent upon the disc's frontal area ($A$) and drag coefficient ($C_d$), opposes its motion, while lift force, intricately dependent upon parameters such as the lift coefficient ($C_l$), disc stability factor ($S$), and air density ($\rho\$), imparts vertical perturbations. Gravity, a ubiquitous force, manifests vertically downward, whereas wind forces ($F_{wind_x}$, $F_{wind_y}$, $F_{wind_z}$) introduce external perturbations. This holistic force analysis affords a nuanced understanding of the disc's dynamic equilibrium.
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

4. **Variables and Descriptions:**
    - The model includes various parameters such as initial positions ($x_0$, $y_0$, and $z_0$), initial velocity ($v_0$), launch angle ($\theta\$), aerodynamic coefficients ($C_d$ and $C_l$), frontal area ($A$), air density ($\rho\$), gravitational acceleration ($g$), disc mass ($m$), wind forces ($\text{Fwind}_x$, $\text{Fwind}_y$, and $\text{Fwind}_z$), disc stability factor ($S$), spin rate ($\text{SpinRate}$), and gyroscopic factor ($\text{GyroscopicFactor}$).

**Conclusion:**
The elucidation and integration of these multifaceted elements within a rigorous mathematical framework yield a model poised to comprehensively explicate the intricacies of disc flight dynamics in disc golf simulations. By encapsulating the nuanced interplay of physical forces and environmental conditions, this model furnishes a robust foundation for the precise emulation of disc trajectories across diverse scenarios. Thus, it stands as an indispensable tool for scholarly inquiry, pedagogical elucidation, and practical application within the realm of disc golf simulation and analysis.
