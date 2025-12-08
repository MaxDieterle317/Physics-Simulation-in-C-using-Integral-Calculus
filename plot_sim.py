import argparse
import numpy as np
import matplotlib.pyplot as plt

def plot_velocity_vs_position(traj_file, particle_id, save_prefix=None):
    # Load data: timestep,particle,x,v
    data = np.genfromtxt(traj_file, delimiter=',', skip_header=0)
    if data.ndim == 1:
        data = data.reshape(1, -1)

    timesteps = data[:, 0]
    particles = data[:, 1].astype(int)
    x = data[:, 2]
    v = data[:, 3]

    # filter for the chosen particle
    mask = (particles == particle_id)
    if not np.any(mask):
        print(f"No data found for particle {particle_id} in {traj_file}")
        return

    x_p = x[mask]
    v_p = v[mask]

    plt.figure()
    plt.plot(x_p, v_p)
    plt.title(f"Velocity vs Position (particle {particle_id})")
    plt.xlabel("Position (x)")
    plt.ylabel("Velocity (v)")
    plt.grid(True)

    if save_prefix:
        fname = save_prefix + "_vel_vs_pos.png"
        plt.savefig(fname, bbox_inches='tight')
        print(f"Saved {fname}")
    else:
        plt.show()

    plt.close()


def plot_inputs_vs_time(timing_file, x_axis="particleCount", save_prefix=None):
    # Expect columns: particleCount,numSteps,dt,time_ms
    data = np.genfromtxt(timing_file, delimiter=',', skip_header=1)
    if data.ndim == 1:
        data = data.reshape(1, -1)

    particleCount = data[:, 0]
    numSteps = data[:, 1]
    dt = data[:, 2]
    time_ms = data[:, 3]

    # Choose what to use as "input size"
    if x_axis == "particleCount":
        X = particleCount
        x_label = "Number of Particles"
    elif x_axis == "numSteps":
        X = numSteps
        x_label = "Number of Steps"
    elif x_axis == "work":
        # e.g. total updates ~ particleCount * numSteps
        X = particleCount * numSteps
        x_label = "Total Updates (particleCount * numSteps)"
    else:
        raise ValueError("x_axis must be one of 'particleCount', 'numSteps', or 'work'")

    # Sort by X for nicer plot
    idx = np.argsort(X)
    X = X[idx]
    time_ms = time_ms[idx]

    plt.figure()
    plt.plot(X, time_ms, marker='o')
    plt.title(f"Runtime vs {x_label}")
    plt.xlabel(x_label)
    plt.ylabel("Time (ms)")
    plt.grid(True)

    if save_prefix:
        fname = save_prefix + "_inputs_vs_time.png"
        plt.savefig(fname, bbox_inches='tight')
        print(f"Saved {fname}")
    else:
        plt.show()

    plt.close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Plot C++ particle simulation data")
    parser.add_argument("--traj", type=str, default="",
                        help="CSV file with timestep,particle,x,v")
    parser.add_argument("--timings", type=str, default="",
                        help="CSV file with particleCount,numSteps,dt,time_ms")
    parser.add_argument("--particle", type=int, default=0,
                        help="Which particle ID to plot for velocity vs position")
    parser.add_argument("--xaxis", type=str, default="particleCount",
                        choices=["particleCount", "numSteps", "work"],
                        help="What to use as x-axis for time plot")
    parser.add_argument("--save_prefix", type=str, default="",
                        help="If set, save plots as PREFIX_*.png instead of showing")

    args = parser.parse_args()

    if args.traj:
        plot_velocity_vs_position(args.traj, args.particle, args.save_prefix or "traj")

    if args.timings:
        plot_inputs_vs_time(args.timings, args.xaxis, args.save_prefix or "timings")

    if not args.traj and not args.timings:
        print("Nothing to do: pass --traj, --timings, or both.")
