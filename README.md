### HermiteSpline ~ Assignment a ~ CSC 473

## Task

Build a Hermite Spline system and a simulator

## Criteria
- Hermite spline class with a maximum of 40 control points. 
- Catmull-Rom initialization with second-order accurate boundary conditions using the following command:
> system <name> cr
- Manipulation of control points and tangents using the console:
> system <name> set tangent  <index> <x y z>
> system <name> set point <index> <x y z>
> system <name> add point <x y z sx sy sz>  # adds a point with the given tangent at the end of the spline.
- Arc Length parameterization using a piecewise linear approximation and lookup table. 
> system <name> getArcLength <t>
- Input/output from/to a file.
> system <name> load "<file name>"
> system <name> export "<file name>"
- Loading the path for the object:
> system objectpath load "<spline file>"
- You need to align the major axis of the object with the tangent of the path as it moves. Twist along the major axis can be ignored. 
- The moving object should start and stop in an easy-in easy-out way and should have a constant speed during the rest of the motion.
- 

## Summary
I have implemented the assignment according to the specifications listed

The object following the Hermite Spline always stays upright and rotates based on the spline's curves:

![Screenshot (6)](https://user-images.githubusercontent.com/77686772/227577245-e4423d00-234f-46af-8564-48ace3ecdd8e.png)

![Screenshot (7)](https://user-images.githubusercontent.com/77686772/227577698-f1fbbeff-ddce-4fdd-8886-85b4ff8fd0b0.png)

![Screenshot (8)](https://user-images.githubusercontent.com/77686772/227577810-d2de61f9-b381-407a-b569-6a92e9956b57.png)

## Functionality
My project first deals with the input text file by reading it and creating a hermite spline path based on the given control points. 

Once The Hermite Spline is loaded (all done within HermiteSpline.cpp), on user input command "s", the simulator is activated. An animation of a car appears traversing the
entire Spline. The car is always up-right and turns based on the Spline's curves. The car speeds up for the first 10% of the spline, then drives at a constant speed and looses 
acceleration for the last 10% before coming to a stop at the end of the spline.

## Grade received
96.77% - I left a mistake in my "export command" by leaving an infinite loop. Oh well! 

