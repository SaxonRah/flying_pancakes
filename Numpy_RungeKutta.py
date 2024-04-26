import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Constants
g = 9.81  # gravitational acceleration (m/s^2)

# Parameters
m = 0.175  # disc mass (kg)
A = 0.057  # frontal area (m^2)
Cd = 0.24  # drag coefficient
Cl0 = 0.15  # lift coefficient at alpha = 0
alpha0 = 5  # angle of attack at alpha = 0 (degrees)
S = 0.5  # stability factor
rho = 1.225  # air density (kg/m^3)
SpinRate = 1000  # spin rate (rpm)
GyroscopicFactor = 1.0  # gyroscopic factor


# Function to compute lift coefficient based on angle of attack
def lift_coefficient(alpha):
    return Cl0 + 0.1 * (alpha - alpha0)


# Function to compute total forces
def total_forces(v, wind, alpha):
    # Velocity magnitude
    v_mag = np.linalg.norm(v)

    # Drag force
    F_drag = -0.5 * rho * Cd * A * v_mag ** 2 * v / np.linalg.norm(v)

    # Lift force
    lift_dir = np.cross(v, [0, 0, 1])  # perpendicular to velocity and z-axis
    lift_dir /= np.linalg.norm(lift_dir)
    Cl_alpha = lift_coefficient(alpha)
    F_lift = 0.5 * Cl_alpha * A * rho * v_mag ** 2 * lift_dir

    # Total force including wind
    F_total = F_drag + wind + F_lift

    return F_total


# Function to compute derivatives
def derivatives(t, state, wind, alpha):
    x, y, z, vx, vy, vz = state

    # Velocity vector
    v = np.array([vx, vy, vz])

    # Compute total forces
    F_total = total_forces(v, wind, alpha)

    # Derivatives
    dxdt = vx
    dydt = vy
    dzdt = vz
    dvxdt = F_total[0] / m
    dvydt = F_total[1] / m
    dvzdt = F_total[2] / m - g

    return [dxdt, dydt, dzdt, dvxdt, dvydt, dvzdt]


# Function for Runge-Kutta integration
def runge_kutta(state, t, dt, wind, alpha):
    k1 = derivatives(t, state, wind, alpha)
    k2 = derivatives(t + 0.5 * dt, [s + 0.5 * dt * k for s, k in zip(state, k1)], wind, alpha)
    k3 = derivatives(t + 0.5 * dt, [s + 0.5 * dt * k for s, k in zip(state, k2)], wind, alpha)
    k4 = derivatives(t + dt, [s + dt * k for s, k in zip(state, k3)], wind, alpha)

    next_state = [s + dt * (k1_i + 2 * k2_i + 2 * k3_i + k4_i) / 6 for s, k1_i, k2_i, k3_i, k4_i in
                  zip(state, k1, k2, k3, k4)]

    return next_state


# Initial conditions
x0, y0, z0 = 0, 0, 1  # initial position (m)
v0 = 15.0  # initial velocity magnitude (m/s)
launch_angle = np.radians(45)  # launch angle (radians)
vx0 = v0 * np.cos(launch_angle)  # initial x-component of velocity (m/s)
vy0 = v0 * np.sin(launch_angle)  # initial y-component of velocity (m/s)
vz0 = 0  # initial z-component of velocity (m/s)
alpha0 = 0  # initial angle of attack (degrees)

state0 = [x0, y0, z0, vx0, vy0, vz0]  # initial state

# Simulation parameters
dt = 0.01  # time step (s)
t_max = 10  # maximum simulation time (s)
timesteps = int(t_max / dt)  # number of timesteps

# Wind conditions
wind_speed = np.array([1, 0, 0])  # wind speed vector (m/s)

# Initialize arrays to store trajectory
trajectory = np.zeros((timesteps, 3))

# Run simulation
state = state0
alpha = alpha0
for i in range(timesteps):
    t = i * dt
    trajectory[i] = state[:3]
    state = runge_kutta(state, t, dt, wind_speed, alpha)

# Plot 3D trajectory
fig = plt.figure("Numpy RungeKutta")
ax = fig.add_subplot(111, projection='3d')
x_traj = trajectory[:, 0]
y_traj = trajectory[:, 1]
z_traj = trajectory[:, 2]
ax.plot(x_traj, y_traj, z_traj)
ax.set_xlabel('X (m)')
ax.set_ylabel('Y (m)')
ax.set_zlabel('Z (m)')
ax.set_title('Flight Path of the Disc')
plt.show()
