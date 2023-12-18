The repo contains an Omnetp++ project that simulates a distributed dataflow platform. The platform is able to process integer key-value pairs following the map-reduce paradigm. 
The coordinator can parse an arbitrarily long sequence of map operations followed by a single reduce, as specified in a JSON file. The operations are then executed in parallel on multiple workers. The input data is fed to the system through a CSV file and split into partitions, according to the JSON file. 
The coordinator is able to detect and handle failures, by rescheduling failed operations. 
We assume that workers may fail at any time while the coordinator and the links are reliable, intermediate results are stored in memory on each worker and are lost in case of failures. 
