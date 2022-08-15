import csv
from random import sample
import numpy as np
import matplotlib.pyplot as plt
from scipy import io

def draw_lpf():
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

def draw_kf():
    sample_count = 41500
    buffer = np.zeros([sample_count, 3])
    with open('data/output/Output_EulerKF.csv') as file:
        reader = csv.reader(file, delimiter=',')
        count = 0
        for row in reader:
            roll = float(row[0])
            pitch = float(row[1])
            yaw = float(row[2])
            buffer[count] = (roll, pitch, yaw)
            count += 1

    dt = 0.01
    t = np.arange(0, sample_count * dt ,dt)

    PhiSaved = buffer[:,0]
    ThetaSaved = buffer[:,1]
    PsiSaved = buffer[:,2]

    plt.figure()
    plt.plot(t, PhiSaved)
    plt.xlabel('Time [Sec]')
    plt.ylabel('Roll angle [deg]')
    #plt.savefig('result/11_EulerKalman_roll.png')

    plt.figure()
    plt.plot(t, ThetaSaved)
    plt.xlabel('Time [Sec]')
    plt.ylabel('Pitch angle [deg]')
    #plt.savefig('result/11_EulerKalman_pitch.png')
    plt.show()

#draw_lpf()
draw_kf()