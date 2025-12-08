# Physics-Simulation-in-C-using-Integral-Calculus

# Background

This project was originally developed for our Calculus II course at CSU, Chico to demonstrate the application of integrals to physical concepts such as velocity, acceleration, and displacement.

Our objective was to create an accurate real-time simulation that continuously updated an object's properties. To accomplish this, we implemented integral expressions governing changes in velocity and position over time.

We developed a C++ program capable of efficiently performing the calculations required to model an object moving through space. The program also generated a final presentation of our results, which included a runtime analysis evaluating performance under varying computational loads. Graphs were provided to illustrate the relationship between simulation time and the number of rendered objects.

Because computational values are discrete rather than continuous, we used Monte Carlo Integration to approximate the necessary integrals. This method allowed faster evaluation than a standard Riemann sum while maintaining acceptable accuracy. A key objective was to determine the optimal number of subdivisions sufficient to produce reliable results while minimizing performance overhead.

# How it works (The code and Monte Carlo Integration)
Monte Carlo integration estimates an integral by sampling random points instead of dividing the interval into equal pieces. To estimate the integral, the program randomly picks several values
between 0 and dt and computes the velocity at each sampled point, averaging them, and multiplying them by dt. More samples give a more accurate estimate, while fewer samples run faster but introduce more randomness. 

The program simulates particles moving under constant acceleration, with velocity being updated at each step using the equation: vnew = v + a * dt.
Position is updated using an estimate of the integral of velocity over the same interval. Users choose how many particles to simulate, how many time steps to run, how many samples to use for the numerical estimation, and the acceleration at which the particles move. After the simulation finishes, the program compares the simulated results to the exact physics formulas to show how accurate the method was.

# How to run this application on your local machine:

1. Make sure you have:
  - Git
  - A C++17 compiler, for example

2. Clone the repo:
  git clone https://github.com/MaxDieterle317/Physics-Simulation-in-C-using-Integral-Calculus.git
  cd Physics-Simulation-in-C-using-Integral-Calculus

3. Build the project:
  g++ -std=c++17 *.cpp -o sim

4. Run the simulation:
  ./sim

5. Output files: In addition to console output, the program also appends timing data to a CSV file timings.csv. You can open this file in any plotting tool of your choice.

*NOTE: Make sure to recompile after any change, simply by:
  g++ -std=c++17 *.cpp -o sim
  ./sim

# TODO:

Asymptotic Analysis (Show the runtime of monte carlo function, pretty sure its just O(n))
Finish Latex file



