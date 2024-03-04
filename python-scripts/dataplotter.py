import matplotlib.pyplot as pypl
import random as rdm
import os 


def plot_glucose(d: str):
    # EXPECTED .csv formatted insulin_value,time
    g = []
    t = []
    with open(d, "r") as f:
        for li in f:
            line = f.readline().rstrip("\n")
            if line != "":
                line = line.split(",")
                g += [int(line[0])]  # should be float
                t += [int(line[1])]

    pypl.plot(g, t)
    pypl.title("glucose evolution")
    pypl.xlabel("t(s)")
    pypl.ylabel("glucose(mg/dL)")
    pypl.show()

    return


if __name__ == '__main__':
    l1 = [_ for _ in range(0, 101)]
    l2 = [_ for _ in range(100, 201)]

    with open(os.getcwd()+"/demofile.txt", "w") as wr:
        for i in range(len(l1)):
            s = "" + str(l1[i]) + "," + str(l2[i]) + "\n"
            wr.write(s)

    plot_glucose(os.getcwd()+"/demofile.txt")
