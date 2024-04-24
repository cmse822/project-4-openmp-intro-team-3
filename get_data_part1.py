import subprocess
import re
import numpy as np
import matplotlib.pyplot as plt

def main():

    # Create Ns
    Ns = np.array([20, 100, 1000])
    f = open("Data_serial.txt", "a")
    threads = np.array([1, 2, 4, 8, 16, 32, 64])

    time1 = np.zeros(len(threads)) 
    time2 = np.zeros(len(threads)) 
    
    # Iterate over Ns
    for N in Ns:
      c = -1
      for thread in threads:
          print(N)
          print(thread)

          c = c+1
          sum1 = 0
          sum2 = 0
          # Iterate multiple times for each N to reduce fluctuations
          for i in range(1):
              output = subprocess.getoutput("./mul " + str(N) + " " + str(thread))
              
              match1 = re.search(r'Parallel:\s+(\d+(\.\d+)?)', output)
#              match2 = re.search(r'Serial:\s+(\d+(\.\d+)?)', output)

              sum1 += float(match1.group(1))
#              sum2 += float(match2.group(1))

          res1 = sum1/5
#          res2 = sum2/5
          time1[c] = res1
#          time2[c] = res2
          
#          f.write(str(N) + "," + str(thread) + "," + str(res1) + "," + str(res2) + "\n")
          f.write(str(N) + "," + str(thread) + "," + str(res1) + "\n")
          
    f.close()

main()