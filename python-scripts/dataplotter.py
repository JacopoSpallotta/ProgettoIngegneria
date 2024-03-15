import matplotlib.pyplot as pypl
import random as rdm
import os 


def plot_glucose(fname: str):
    # EXPECTED .csv formatted insulin_value,time
    d = []
    t = []
    with open(fname, "r") as f:
        for li in f:
            line = f.readline().rstrip("\n")
            if line != "":
                line = line.split(",")
                d += [int(line[0])]  # should be float
                t += [int(line[1])]

    if "glucose" in fname:
        pypl.title("glucose evolution")
        pypl.ylabel("glucose(mg/dL)")

    elif "insulin" in fname:
        pypl.title("insulin evolution")
        pypl.ylabel("insulin(mg/dL)")

    pypl.plot(d, t)
    pypl.xlabel("t(s)")
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
