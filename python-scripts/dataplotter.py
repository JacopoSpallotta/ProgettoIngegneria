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

    title = "empty"
    y_label = "empty"
    if "glucose" in fname.lower():
        print("glucose")
        title = "glucose evolution"
        y_label = "glucose(mg/dL)"
    elif "insulin" in fname.lower():
        print("insulin")
        title = "insulin evolution"
        y_label = "insulin(mg/dL)"

    pypl.title(title)
    pypl.ylabel(y_label)
    pypl.plot(d, t)
    pypl.xlabel("t(s)")
    pypl.show()
    return


if __name__ == '__main__':

    plot_glucose(os.getcwd()+"/glucose_data.csv")
