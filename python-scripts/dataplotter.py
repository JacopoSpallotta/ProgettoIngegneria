import matplotlib.pyplot as pypl


def plot_insulin(d: str):
    #EXPECTED .csv formatted insulin_value, time
    with open(d, "r") as f:
        for line in f:
            f.readline()