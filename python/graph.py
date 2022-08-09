import csv
from random import sample
import numpy as np
import matplotlib.pyplot as plt
from scipy import io

sample_count = 500
first_buffer = np.zeros(sample_count)
second_buffer = np.zeros(sample_count)
with open('data/output/Output_1st_SonarAlt.csv') as file:
    reader = csv.reader(file, delimiter=',')
    count = 0
    for row in reader:
        first_buffer[count] = float(row[0])
        count += 1

with open('data/output/Output_2nd_SonarAlt.csv') as file:
    reader = csv.reader(file, delimiter=',')
    count = 0
    for row in reader:
        second_buffer[count] = float(row[0])
        count += 1

dt = 0.02
t = np.arange(0, sample_count * dt, dt)

plt.plot(t, first_buffer, 'b-', label='LPF(alpha = 0.4)')
plt.plot(t, second_buffer, 'g-', label='LPF(alpha = 0.9)')
#plt.plot(t, Xmsaved, 'r.', label='Measured')
plt.legend(loc='upper left')
plt.ylabel('Altitude[m]')
plt.xlabel('Time [sec]')
#plt.savefig('result/03_low_pass_filter.png')
plt.show()
