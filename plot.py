import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
import os
from colour import Color

plt.style.use("bmh")
sns.color_palette("hls", 1)

import matplotlib
matplotlib.rc('xtick', labelsize=14)
matplotlib.rc('ytick', labelsize=14)
matplotlib.rcParams['mathtext.fontset'] = 'stix'
matplotlib.rcParams['font.family'] = 'STIXGeneral'

def get_data(filename, variables):
    df = pd.read_csv(filename,\
                    delim_whitespace=True, \
                    engine='python', \
                    names=variables)
    return df
    #using pandas to read the data files
red = Color("red")


data = get_data("data/mysen_2_sircle.txt", ["x", "y", "z"])

s = int(len(np.array(data["x"])))
a = np.linspace(0, s-1, s)
colors = list(red.range_to(Color("green"), s))

plt.scatter(np.array(data["x"]), np.array(data["y"]), s=2, c=a)
plt.axis("equal")
plt.show()
