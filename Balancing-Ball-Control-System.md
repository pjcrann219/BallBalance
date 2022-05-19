Worked with two other undergraduates(Gregory Mitelman, Gabe Nadelstein) in mechatronics course. My contribution included writing all of the code.

Goal was to design and build a system capable of controling a ball on a surface thorugh varrying the surface tilt. A 4-wire resistive touch screen was used to sense the balls current position, two servo motors to control each tilt angle of the surface, and PD control was used to calculate the servo angle.

Limitations:
  Touch screen was bought used due to budget constraints and had a few dead spots that gave innaccurate/no readings.
  Due to time/budget constraints, the connections between the motors and surfface were made of wood and were not very secure.
  Very hard to calibrate due to wooden frame, had to re-callibrate whenever it was moved.
  
Improvements:
  Filter the touch sensor data to lessen the effect of noise/innacurate readings.
  More stable connection between servo/surface and surface/support.
  Added support for automatic calibration/ Integral control.
