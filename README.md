#Clustering
The implementations of 4 algorithms.

1. vanilla k-means
2. k-means++
3. Hierachical Clustering
4. Fuzzy C-means

##Executing
The way to execute is pretty straight forward.

1. Execute the command *make*, to produce 4 **different** executables.

2. Navigate to bin folder and run 1 of the 4 executables. 
   * The executables in the bin folder will be:
     1. ./vanilla
     2. ./kpp
     3. ./hierarchical
     4. ./fcm
3. The values required for each implementation to run are: 
   * For k-means and k-means++:
      1. Total number of points.
      2. Total number of centers.
      3. Dimensions of the points.
      4. The test file with the points.
   *  For Hierarchical clustering:
      1. Total number of points.
      2. Dimensions of the points.
      3. The test file with the points. 
   *  For Fuzzy C-means:
      1. Total number of points.
      2. Total number of centers.
      3. Dimensions of the points.
      4. Fuzzy coefficient.
      5. Termination criterion.
      6. The test file with the points.

4. For your convience there is no need to enter the arguments in a specified order. Just add:
   * -t Before the testfile.
   * -n Before the number of points.
   * -k Before the number of centers.
   * -d Before the dimensions.
   * -f Before the fuzziness coefficient.
   * -e Before the termination criterion.
   
   The order you enter them **WILL NOT** matter.
   
5. Example input would be: 
   * ./bin/fcm -t < your_testfile > -n 10 -k 2 -d 3 -f 2.0 -e 0.00005
   
   
   
###License
Part of an ongoing research at DASlab (daslab.seas.harvard.edu) at Harvard.

####Author
Ioannis Pavlos Panteliadis