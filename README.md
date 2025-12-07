# Physics-Simulation-in-C-using-Integral-Calculus

Originally created for our Calculus II course at CSU, Chico, this project demonstrated concepts such as velocity, acceleration, and displacement using integrals.

Our goal was to build an accurate real-time simulation that continuously updated an object's properties—such as speed, acceleration, and, when relevant, mass. To achieve this, we implemented integrals involving changes in velocity as well as changes in position with respect to that velocity.

We developed a small program in C++ that was capable of efficiently performing the calculations required to model an object moving through space.

Additionally, we included a presentation of our results at the end of the program, which featured runtime analysis to evaluate the application's performance under various levels of stress. We provided graphs illustrating the time spent simulating physics relative to the number of objects that were rendered.

Because values on a computer were discrete rather than continuous, we used Riemann sums to approximate the necessary integrals. As a result, one of our objectives was to determine the optimal number of subdivisions—enough to ensure accurate results while minimizing the performance impact.

# How to run this application on your local machine:


