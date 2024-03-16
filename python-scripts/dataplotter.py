import matplotlib.pyplot as pypl
import matplotlib.dates as pldate
import matplotlib.ticker as ticker
from datetime import datetime
import os 


def plot_glucose(fname: str):
    # EXPECTED .csv formatted insulin_value,time
    d = []
    t = []
    cut = 0
    with open(fname, "r") as f:
        for li in f:
            line = f.readline().rstrip("\n")
            if line != "":
                line = line.split(",")
                d += [float(line[0])]  # should be float
                time_list = line[1].split(":")
                if time_list[0] != "24":
                    cut += 1
                    seconds = [time_list[2][:2]]
                    t += [datetime.strptime(":".join(tuple(time_list[:2] + seconds)), "%H:%M:%S")]

    d = d[:cut]
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

    locator = pldate.MinuteLocator(range(0,1440,60))
    pypl.title(title)
    pypl.ylabel(y_label)
    # x label is for time
    ax = pypl.gca()
    t_num = pldate.date2num(t)

    fmt = pldate.DateFormatter("%H:%M:%S")
    ax.xaxis.set_major_formatter(fmt)
    ax.xaxis.set_major_locator(locator)
    pypl.xlabel("t(s)")
    pypl.xticks(rotation=25)
    pypl.grid(True, "major", "y")
    pypl.plot(t_num, d)
    ax.set_xlim(left=t_num[0], right=t_num[len(t_num)-1])
    pypl.show()
    return


if __name__ == '__main__':

    plot_glucose(os.getcwd()+"/glucose_data.csv")
