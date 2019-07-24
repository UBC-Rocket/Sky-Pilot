# Main code. Feeds data to Arduino. Hit any button to exit program.

import time #for timing
import sys #to be able to exit
import csv #for access to the pressure data set
import os # for files
import math # for logarithms
import random # for random value generation

import matplotlib.pyplot as plt #plotting
import numpy as np # for the linear algebra





# ---------------------  Constants  --------------------------
FILE_NAME = 'SkyPilot_IREC_2019_Dataset_Post_Motor_Burnout.csv'
# Available file names:
# SkyPilot_IREC_2019_Dataset_Post_Motor_Burnout.csv


CONST_R = 287.058
CONST_T = 30 + 273.15
CONST_g = 9.81

CONST_APOGEE_CHECKS = 5
# # -------------------------------------------- --------
# print(__file__)
# input()


print("Opening file")
try:
    testDataFile = open(os.path.join(__file__, '..', FILE_NAME), 'r')
    testDataReader = csv.reader(testDataFile, dialect='excel', quoting=csv.QUOTE_NONNUMERIC)
except Exception as e:
    print("Failed to open file. Error:")
    print(e)
    print("Press any key to exit")
    input()
    sys.exit()

time.sleep(0.5) # let file settle

print("File opened. Press any key to begin...")
input()

#Filtering variables -----------------------------------

#state vectors - [position, velocity]
xOld = np.empty((2, 1))
xNew = np.empty((2, 1))

#State covariances
POld = np.empty((2,2))
PNew = np.empty((2,2))

#propagation matrix
F = np.empty((2,2))

#process noise
# At 20 m/s^2 acceleration, over 0.05 s, velocity changes by 1 m/s,
# error in position is 0.025 (1/2 * a * t^2)
Q = np.array([0.025, 1])

#innovation vector & covariance
y = np.empty((2, 1))
S = np.empty((2, 2))

#measurement vector & covariance
z = np.empty((2, 1))
R = np.array([
    [0.9, 0], #0.9 in upper left is uncertainty of barometer
    [0, 0.9*2/0.05] # I think that's how propagation of uncertainty works for velocity calc?
])



# Setup file -------------------------------

# Version 1: First row is version number.
# 2nd row contains initial altitude, velocity, covariance matrix,
#           (row major order), initial time (ms), baseline pressure
try:
    csvData = next(testDataReader) #First row is 'version', version number
    assert(csvData[0] == 1) #only have version 1 so far

    csvData = next(testDataReader) #Collect data from 2nd row
    xNew = np.reshape(csvData[0:2], (2,1))
    PNew = np.reshape(csvData[2:6], (2,2))
    tOld = csvData[6]
    CONST_BASE_PRESSURE = csvData[7]


except StopIteration:
    print("No data available. Press any key to exit.")
    input()
    sys.exit()
except AssertionError:
    print("Unrecognized file version. Press any key to exit.")
    input()
    sys.exit()

# https://en.wikipedia.org/wiki/Hypsometric_equation
presToAlt = lambda pres : CONST_R * CONST_T / CONST_g * math.log(CONST_BASE_PRESSURE / pres)

apogeeCount = 0

# Plotting variables ----------------------------------
tPlot = []
measPlot = []
xPlot = []
vPlot = []
#main loop ------------------------------------
while True:
    try: #Pull next set of data
        csvData = next(testDataReader)
    except StopIteration:
        print("Reached end of file. Press any key to exit.")
        input()
        sys.exit()

    tNew = csvData[0] / 1000
    dt = tNew - tOld

    xOld = xNew
    POld = PNew
    tOld = csvData[0] / 1000

    #Propagation, assuming constant velocity
    F = np.array(
        [[1, dt],
         [0, 1]]
    )

    xPred = F @ xOld
    PPred = F @ POld @ F.T + Q

    #Take in "measurement"
    z[0] =  presToAlt(csvData[1])
    z[1] = (z[0] - xOld[0]) / dt
    y = z - xPred
    S = PPred + R

    # Update step
    K = PPred @ np.linalg.inv(S)
    xNew = xPred + K @ y
    PNew = (np.identity(2) - K) * PPred

    # Save for plotting
    tPlot.append(tNew)
    xPlot.append(xNew[0])
    vPlot.append(xNew[1])
    measPlot.append(presToAlt(csvData[1]))

    if (xNew[0] < xOld[0]):
        apogeeCount += 1
    else:
        apogeeCount = 0

    if apogeeCount >= CONST_APOGEE_CHECKS:
        print("Reached apogee at time {}".format(tNew))
        break



#Reached apogee; plot results
plt.subplot(121)
plt.plot(tPlot, xPlot, tPlot, measPlot)
plt.subplot(122)
plt.plot(tPlot, vPlot)
plt.show()

input()
