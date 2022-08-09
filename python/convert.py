import scipy.io
import csv

# Gyr / ACC
sample_count = 41500
with open('data/ArsAccel.csv', 'w', newline='') as csv_file:
    writer = csv.writer(csv_file, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
    mat = scipy.io.loadmat('data/ArsAccel.mat')

    for i in range(sample_count):
        ax = mat['fx'][i][0]  # (41500, 1)
        ay = mat['fy'][i][0]  # (41500, 1)
        az = mat['fz'][i][0]  # (41500, 1)
        writer.writerow([ax, ay, az])

with open('data/ArsGyro.csv', 'w', newline='') as csv_file:
    writer = csv.writer(csv_file, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
    mat = scipy.io.loadmat('data/ArsGyro.mat')

    for i in range(sample_count):
        p = mat['wx'][i][0]  # (41500, 1)
        q = mat['wy'][i][0]  # (41500, 1)
        r = mat['wz'][i][0]  # (41500, 1)
        writer.writerow([p, q, r])

# Sonar
sample_count = 500
with open('data/SonarAlt.csv', 'w', newline='') as csv_file:
    writer = csv.writer(csv_file, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
    mat = scipy.io.loadmat('data/SonarAlt.mat')

    for i in range(sample_count):
        val = mat['sonarAlt'][0][i]  # (1, 1501)
        writer.writerow([val])