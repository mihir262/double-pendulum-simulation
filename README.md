# Double Pendulum (Raylib)

This is a double pendulum simulation. Small angles behave almost like a linear system; large angles are nonlinear and chaotic.


## Controls

Press **Space** to restart with a new random start.

## Build and Run

```sh
make
./main
```

Or:

```sh
make run
```

## Parameters

Edit the parameters in `main.c`:

1. `L1`, `L2`, `g` are constants.
2. `m1`, `m2`, and the initial angles are set in `init_solver()`.

## Math

Assumptions: the rods are massless and rigid, and the masses are point masses. Below is a direct Newtonian derivation of the equations of motion.

### Kinematics of the Double Pendulum

Kinematics describes position, velocity, and acceleration without considering forces.

![Double pendulum diagram](assets/double-pendulum-diagram.png)

Let:

- $x$ is horizontal position
- $y$ is vertical position
- $\theta$ is the angle ($0$ = straight down, counter-clockwise is positive)
- $L$ is rod length (constant)



Positions:

$$x_1 = L_1 \sin\theta_1$$
$$y_1 = -L_1 \cos\theta_1$$
$$x_2 = x_1 + L_2 \sin\theta_2$$
$$y_2 = y_1 - L_2 \cos\theta_2$$

Velocities (time derivatives):

$$x_1' = \theta_1' L_1 \cos\theta_1$$
$$y_1' = \theta_1' L_1 \sin\theta_1$$
$$x_2' = x_1' + \theta_2' L_2 \cos\theta_2$$
$$y_2' = y_1' + \theta_2' L_2 \sin\theta_2$$

Accelerations (second derivatives):

$$x_1'' = -\theta_1'^2 L_1 \sin\theta_1 + \theta_1'' L_1 \cos\theta_1 \quad (1)$$
$$y_1'' = \theta_1'^2 L_1 \cos\theta_1 + \theta_1'' L_1 \sin\theta_1 \quad (2)$$
$$x_2'' = x_1'' - \theta_2'^2 L_2 \sin\theta_2 + \theta_2'' L_2 \cos\theta_2 \quad (3)$$
$$y_2'' = y_1'' + \theta_2'^2 L_2 \cos\theta_2 + \theta_2'' L_2 \sin\theta_2 \quad (4)$$

### Forces in the Double Pendulum

Define:

- $T$ = tension in a rod  
- $m$ = mass of a pendulum  
- $g$ = gravitational constant

Upper mass forces are $T_1$, $T_2$, and gravity $-m_1 g$:

$$m_1 x_1'' = -T_1 \sin\theta_1 + T_2 \sin\theta_2 \quad (5)$$
$$m_1 y_1'' = T_1 \cos\theta_1 - T_2 \cos\theta_2 - m_1 g \quad (6)$$

Lower mass forces are $T_2$ and gravity $-m_2 g$:

$$m_2 x_2'' = -T_2 \sin\theta_2 \quad (7)$$
$$m_2 y_2'' = T_2 \cos\theta_2 - m_2 g \quad (8)$$

### Direct Method for Finding Equations of Motion

Solve (7) and (8) for $T_2 \sin\theta_2$ and $T_2 \cos\theta_2$, then substitute into (5) and (6):

$$m_1 x_1'' = -T_1 \sin\theta_1 - m_2 x_2'' \quad (9)$$
$$m_1 y_1'' = T_1 \cos\theta_1 - m_2 y_2'' - m_2 g - m_1 g \quad (10)$$

Multiply (9) by $\cos\theta_1$ and (10) by $\sin\theta_1$:

$$T_1 \sin\theta_1 \cos\theta_1 = -\cos\theta_1 (m_1 x_1'' + m_2 x_2'') \quad (11)$$
$$T_1 \sin\theta_1 \cos\theta_1 = \sin\theta_1 (m_1 y_1'' + m_2 y_2'' + m_2 g + m_1 g) \quad (12)$$

Therefore:

$$\sin\theta_1 (m_1 y_1'' + m_2 y_2'' + m_2 g + m_1 g) = -\cos\theta_1 (m_1 x_1'' + m_2 x_2'') \quad (13)$$


Multiply (7) by $\cos\theta_2$ and (8) by $\sin\theta_2$:

$$T_2 \sin\theta_2 \cos\theta_2 = -\cos\theta_2 (m_2 x_2'') \quad (14)$$
$$T_2 \sin\theta_2 \cos\theta_2 = \sin\theta_2 (m_2 y_2'' + m_2 g) \quad (15)$$

Therefore:

$$\sin\theta_2 (m_2 y_2'' + m_2 g) = -\cos\theta_2 (m_2 x_2'') \quad (16)$$

Solve (13) and (16) together with (1)–(4) for $\theta_1''$ and $\theta_2''$:

$$\theta_1'' = \frac{-g (2 m_1 + m_2) \sin\theta_1 - m_2 g \sin(\theta_1 - 2\theta_2) - 2 \sin(\theta_1 - \theta_2) m_2 (\theta_2'^2 L_2 + \theta_1'^2 L_1 \cos(\theta_1 - \theta_2))}{L_1 \left(2 m_1 + m_2 - m_2 \cos(2\theta_1 - 2\theta_2)\right)}$$

$$\theta_2'' = \frac{2 \sin(\theta_1 - \theta_2) \left(\theta_1'^2 L_1 (m_1 + m_2) + g (m_1 + m_2) \cos\theta_1 + \theta_2'^2 L_2 m_2 \cos(\theta_1 - \theta_2)\right)}{L_2 \left(2 m_1 + m_2 - m_2 \cos(2\theta_1 - 2\theta_2)\right)}$$

These are the equations of motion for the double pendulum.
