import math
import matplotlib.pyplot as plt

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
    v_mag = math.sqrt(v[0] ** 2 + v[1] ** 2 + v[2] ** 2)

    # Drag force
    F_drag = [-0.5 * rho * Cd * A * v_mag ** 2 * vi / v_mag for vi in v]

    # Lift direction (perpendicular to velocity and z-axis)
    lift_dir = [v[1], -v[0], 0]
    lift_dir_mag = math.sqrt(lift_dir[0] ** 2 + lift_dir[1] ** 2 + lift_dir[2] ** 2)
    lift_dir = [ld / lift_dir_mag for ld in lift_dir]

    # Lift force
    Cl_alpha = lift_coefficient(alpha)
    lift_mag = 0.5 * Cl_alpha * A * rho * v_mag ** 2
    F_lift = [lift_mag * li for li in lift_dir]

    # Total force including wind
    F_total = [F_drag[i] + wind[i] + F_lift[i] for i in range(3)]

    return F_total


# Function to compute derivatives
def derivatives(t, state, wind, alpha):
    x, y, z, vx, vy, vz = state

    # Compute total forces
    F_total = total_forces([vx, vy, vz], wind, alpha)

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
launch_angle = math.radians(45)  # launch angle (radians)
vx0 = v0 * math.cos(launch_angle)  # initial x-component of velocity (m/s)
vy0 = v0 * math.sin(launch_angle)  # initial y-component of velocity (m/s)
vz0 = 0  # initial z-component of velocity (m/s)
alpha0 = 0  # initial angle of attack (degrees)

state0 = [x0, y0, z0, vx0, vy0, vz0]  # initial state

# Simulation parameters
dt = 0.01  # time step (s)
t_max = 10  # maximum simulation time (s)
timesteps = int(t_max / dt)  # number of timesteps

# Wind conditions
wind_speed = [1, 0, 0]  # wind speed vector (m/s)

# Initialize arrays to store trajectory
trajectory = [[0, 0, 0] for _ in range(timesteps)]

# Run simulation
state = state0
alpha = alpha0
for i in range(timesteps):
    t = i * dt
    trajectory[i] = state[:3]
    state = runge_kutta(state, t, dt, wind_speed, alpha)

# Plot 3D trajectory
fig = plt.figure("PurePython RungeKutta")
ax = fig.add_subplot(111, projection='3d')
x_traj = [point[0] for point in trajectory]
y_traj = [point[1] for point in trajectory]
z_traj = [point[2] for point in trajectory]
ax.plot(x_traj, y_traj, z_traj)
ax.set_xlabel('X (m)')
ax.set_ylabel('Y (m)')
ax.set_zlabel('Z (m)')
ax.set_title('Flight Path of the Disc')
plt.show()
