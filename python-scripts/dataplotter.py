import matplotlib.pyplot as pypl
import random as rdm
import os 


def plot_glucose(d: str):
    # EXPECTED .csv formatted insulin_value,time
    g = []
    t = []
    with open(d, "r") as f:
        for i in f:
            line = f.readline().rstrip("\n")
            line = line.split(",")
            print(line)
            g += [int(line[0])] # should be float
            t += [int(line[1])]

    pypl.plot(g,t)
    pypl.xlabel("t(s)")
    pypl.ylabel("glucose(mg/dL)")
    pypl.title("glucose evolution")
    pypl.show()

    return


if __name__ == '__main__':

    with open(os.getcwd()+"/demofile.txt", "w") as wr:
        for i in range(100):
            s = "" + str(rdm.randint(1, 10)) + "," + str(rdm.randint(11,20)) + "\n"
            wr.write(s)

    plot_glucose(os.getcwd()+"/demofile.txt")

