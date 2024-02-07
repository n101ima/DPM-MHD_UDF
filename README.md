# DPM-MHD_UDF
The mag_gradient function calculates the magnetic gradient components using the equation:

$$\nabla \mathbf{B} = \begin{bmatrix}
\frac{\partial B_x}{\partial x} & \frac{\partial B_x}{\partial y} & \frac{\partial B_x}{\partial z} \
\frac{\partial B_y}{\partial x} & \frac{\partial B_y}{\partial y} & \frac{\partial B_y}{\partial z} \
\frac{\partial B_z}{\partial x} & \frac{\partial B_z}{\partial y} & \frac{\partial B_z}{\partial z} \
\end{bmatrix}$$

where $\mathbf{B} = (B_x, B_y, B_z)$ is the magnetic field vector.

This equation means that the magnetic gradient is a matrix that contains the partial derivatives of the magnetic field components with respect to the spatial coordinates. The magnetic gradient describes how the magnetic field changes in space and direction. For example, the element $\frac{\partial B_x}{\partial y}$ represents the rate of change of the magnetic field component $B_x$ along the $y$-axis.

The magnetophoresis function calculates the magnetic force acting on a particle using the equation:

$$\mathbf{F}_m = \frac{1}{6} \pi d^3 \chi \nabla \mathbf{B} \cdot \mathbf{B}$$

where $d$ is the particle diameter, $\chi$ is the magnetic susceptibility of the particle, and $\nabla \mathbf{B}$ is the magnetic gradient matrix.

This equation means that the magnetic force is proportional to the volume of the particle, the magnetic susceptibility of the particle, and the dot product of the magnetic gradient and the magnetic field. The magnetic force depends on the shape and orientation of the particle, as well as the strength and direction of the magnetic field. The magnetic susceptibility is a measure of how easily the particle is magnetized by an external magnetic field. The dot product of the magnetic gradient and the magnetic field is a scalar that represents the magnitude of the magnetic force along the direction of the magnetic field.

The normalized magnetic force is obtained by dividing the magnetic force by the particle mass and the Hartmann number:

$$\frac{\mathbf{F}_m}{m H} = \frac{1}{6} \pi d^3 \chi \nabla \mathbf{B} \cdot \mathbf{B} \frac{1}{m H}$$

where $m$ is the particle mass and $H$ is the Hartmann number.

This equation means that the normalized magnetic force is a dimensionless quantity that expresses the ratio of the magnetic force to the inertial force. The inertial force is the product of the particle mass and the Hartmann number, which is a dimensionless parameter that characterizes the interaction between the fluid flow and the magnetic field. The Hartmann number is defined as:

$$H = \frac{B L \sqrt{\sigma \rho}}{\mu}$$

where $B$ is the magnetic field strength, $L$ is the characteristic length, $\sigma$ is the electrical conductivity, $\rho$ is the fluid density, and $\mu$ is the dynamic viscosity. The Hartmann number indicates the relative importance of the magnetic force and the viscous force in the fluid flow. A high Hartmann number means that the magnetic force dominates, while a low Hartmann number means that the viscous force dominates.
