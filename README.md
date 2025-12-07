# Physics-Simulation-in-C-using-Integral-Calculus

This project was originally developed for our Calculus II course at CSU, Chico to demonstrate the application of integrals to physical concepts such as velocity, acceleration, and displacement.

Our objective was to create an accurate real-time simulation that continuously updated an object's properties. To accomplish this, we implemented integral expressions governing changes in velocity and position over time.

We developed a C++ program capable of efficiently performing the calculations required to model an object moving through space. The program also generated a final presentation of our results, which included a runtime analysis evaluating performance under varying computational loads. Graphs were provided to illustrate the relationship between simulation time and the number of rendered objects.

Because computational values are discrete rather than continuous, we used Monte Carlo Integration to approximate the necessary integrals. This method allowed faster evaluation than a standard Riemann sum while maintaining acceptable accuracy. A key objective was to determine the optimal number of subdivisions sufficient to produce reliable results while minimizing performance overhead.

# TODO:

Asymptotic Analysis (Show the runtime of monte carlo function, pretty sure its just O(n))
Add graph generation at the end
Finish Latex file
Write steps to run app on local machine

# How to run this application on your local machine:


