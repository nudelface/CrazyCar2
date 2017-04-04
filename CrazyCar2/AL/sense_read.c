/*
 * sense_read.c
 *
 *  Created on: 09.01.2017
 *      Author: Sebo
 */
#include "sense_read.h"


 float sense_left[410]={80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,77.826,75.652,74.167,72.976,71.786,70.595,68.81,66.429,64.048,61.667,59.651,58.488,57.326,56.163,55,53.864,52.727,51.591,50.455,49.286,48.095,46.905,45.714,44.63,43.704,42.778,41.852,40.926,40,39.444,38.889,38.333,37.778,37.222,36.667,36.111,35.556,35,34.412,33.824,33.235,32.647,32.059,31.471,30.882,30.294,29.762,29.286,28.81,28.333,27.857,27.381,26.905,26.429,25.952,25.476,25,24.669,24.338,24.007,23.675,23.344,23.013,22.682,22.351,22.02,21.689,21.358,21.026,20.695,20.364,20.033,19.803,19.585,19.367,19.148,18.93,18.712,18.493,18.275,18.057,17.838,17.62,17.402,17.183,16.965,16.747,16.528,16.31,16.092,15.873,15.655,15.437,15.218,15,14.846,14.691,14.537,14.383,14.228,14.074,13.92,13.765,13.611,13.457,13.302,13.148,12.994,12.84,12.685,12.531,12.377,12.222,12.068,11.914,11.759,11.605,11.451,11.296,11.142,10.988,10.833,10.679,10.525,10.37,10.216,10.062,9.9444,9.8519,9.7593,9.6667,9.5741,9.4815,9.3889,9.2963,9.2037,9.1111,9.0185,8.9259,8.8333,8.7407,8.6481,8.5556,8.463,8.3704,8.2778,8.1852,8.0926,8,7.9074,7.8148,7.7222,7.6296,7.537,7.4444,7.3519,7.2593,7.1667,7.0741,6.9871,6.9223,6.8576,6.7929,6.7282,6.6634,6.5987,6.534,6.4693,6.4045,6.3398,6.2751,6.2104,6.1456,6.0809,6.0162,5.9515,5.8867,5.822,5.7573,5.6926,5.6278,5.5631,5.4984,5.4337,5.3689,5.3042,5.2395,5.1748,5.11,5.0453,4.981,4.9177,4.8544,4.7911,4.7278,4.6646,4.6013,4.538,4.4747,4.4114,4.3481,4.2848,4.2215,4.1582,4.0949,4.0316,3.9741,3.9223,3.8705,3.8187,3.7668,3.715,3.6632,3.6114,3.5596,3.5078,3.456,3.4041,3.3523,3.3005,3.2487,3.1969,3.1451,3.0933,3.0415,2.9923,2.9538,2.9154,2.8769,2.8385,2.8,2.7615,2.7231,2.6846,2.6462,2.6077,2.5692,2.5308,2.4923,2.4538,2.4154,2.3769,2.3385,2.3,2.2615,2.2231,2.1846,2.1462,2.1077,2.0692,2.0308,1.9908,1.9448,1.8989,1.8529,1.8069,1.7609,1.7149,1.669,1.623,1.577,1.531,1.4851,1.4391,1.3931,1.3471,1.3011,1.2552,1.2092,1.1632,1.1172,1.0713,1.0253,0.97931,0.93333,0.88736,0.84138,0.7954,0.74943,0.70345,0.65747,0.61149,0.56552,0.51954,0.47356,0.42759,0.38161,0.33563,0.28966,0.24368,0.1977,0.15172,0.10575,0.05977,0.013793,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

 float sense_right[410]={78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,78.704,76.852,75,72.5,70,68.837,67.674,66.512,65.349,63.409,61.136,58.864,56.591,54.643,53.452,52.262,51.071,49.881,48.69,47.5,46.31,45.119,43.953,42.791,41.628,40.465,39.545,38.788,38.03,37.273,36.515,35.758,35,34.438,33.876,33.315,32.753,32.191,31.629,31.067,30.506,29.952,29.471,28.99,28.51,28.029,27.548,27.067,26.587,26.106,25.625,25.144,24.762,24.422,24.082,23.741,23.401,23.061,22.721,22.381,22.041,21.701,21.361,21.02,20.68,20.34,20,19.765,19.531,19.296,19.061,18.826,18.592,18.357,18.122,17.887,17.653,17.418,17.183,16.948,16.714,16.479,16.244,16.009,15.775,15.54,15.305,15.07,14.889,14.729,14.57,14.411,14.252,14.092,13.933,13.774,13.615,13.455,13.296,13.137,12.978,12.818,12.659,12.5,12.341,12.182,12.022,11.863,11.704,11.545,11.385,11.226,11.067,10.908,10.748,10.589,10.43,10.271,10.111,9.9706,9.8725,9.7745,9.6765,9.5784,9.4804,9.3824,9.2843,9.1863,9.0882,8.9902,8.8922,8.7941,8.6961,8.598,8.5,8.402,8.3039,8.2059,8.1078,8.0098,7.9118,7.8137,7.7157,7.6176,7.5196,7.4216,7.3235,7.2255,7.1275,7.0294,6.9466,6.8702,6.7939,6.7176,6.6412,6.5649,6.4885,6.4122,6.3359,6.2595,6.1832,6.1069,6.0305,5.9542,5.8779,5.8015,5.7252,5.6489,5.5725,5.4962,5.4198,5.3435,5.2672,5.1908,5.1145,5.0382,4.9742,4.9227,4.8711,4.8196,4.768,4.7165,4.6649,4.6134,4.5619,4.5103,4.4588,4.4072,4.3557,4.3041,4.2526,4.201,4.1495,4.0979,4.0464,3.9949,3.9439,3.8929,3.8418,3.7908,3.7398,3.6888,3.6378,3.5867,3.5357,3.4847,3.4337,3.3827,3.3316,3.2806,3.2296,3.1786,3.1276,3.0765,3.0255,2.9762,2.9286,2.881,2.8333,2.7857,2.7381,2.6905,2.6429,2.5952,2.5476,2.5,2.4524,2.4048,2.3571,2.3095,2.2619,2.2143,2.1667,2.119,2.0714,2.0238,1.9823,1.9469,1.9115,1.8761,1.8407,1.8053,1.7699,1.7345,1.6991,1.6637,1.6283,1.5929,1.5575,1.5221,1.4867,1.4513,1.4159,1.3805,1.3451,1.3097,1.2743,1.2389,1.2035,1.1681,1.1327,1.0973,1.0619,1.0265,0.99115,0.95575,0.92035,0.88496,0.84956,0.81416,0.77876,0.74336,0.70796,0.67257,0.63717,0.60177,0.56637,0.53097,0.49558,0.46018,0.42478,0.38938,0.35398,0.31858,0.28319,0.24779,0.21239,0.17699,0.14159,0.10619,0.070796,0.035398,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

float sense_mid[410]={185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,185.56,180,168.89,166.11,163.33,160.56,157.14,153.57,150,145.24,140.48,136.25,132.08,128.78,126.34,123.9,121.46,119.07,116.74,114.42,112.09,109.77,107.44,105.12,102.79,100.47,98.182,95.909,93.636,91.364,89.42,87.971,86.522,85.072,83.623,82.174,80.725,79.419,78.256,77.093,75.93,74.773,73.636,72.5,71.364,70.227,69.355,68.548,67.742,66.935,66.129,65.323,64.231,62.949,61.667,60.385,59.478,58.731,57.985,57.239,56.493,55.746,55,54.275,53.551,52.826,52.101,51.377,50.652,49.94,49.337,48.735,48.133,47.53,46.928,46.325,45.723,45.12,44.615,44.135,43.654,43.173,42.692,42.212,41.731,41.25,40.769,40.288,39.839,39.435,39.032,38.629,38.226,37.823,37.419,37.016,36.613,36.21,35.806,35.403,35,34.667,34.333,34,33.667,33.333,33,32.667,32.333,32,31.667,31.333,31,30.667,30.333,30,29.73,29.459,29.189,28.919,28.649,28.378,28.108,27.838,27.568,27.297,27.027,26.757,26.486,26.216,25.946,25.676,25.405,25.135,24.897,24.691,24.486,24.28,24.074,23.868,23.663,23.457,23.251,23.045,22.84,22.634,22.428,22.222,22.016,21.811,21.605,21.399,21.193,20.988,20.782,20.576,20.37,20.165,19.967,19.801,19.636,19.47,19.305,19.139,18.974,18.808,18.642,18.477,18.311,18.146,17.98,17.815,17.649,17.483,17.318,17.152,16.987,16.821,16.656,16.49,16.325,16.159,15.993,15.828,15.662,15.497,15.331,15.166,15,14.858,14.716,14.574,14.432,14.29,14.148,14.006,13.864,13.722,13.58,13.438,13.295,13.153,13.011,12.869,12.727,12.585,12.443,12.301,12.159,12.017,11.875,11.733,11.591,11.449,11.307,11.165,11.023,10.881,10.739,10.597,10.455,10.313,10.17,10.028,9.8763,9.7216,9.567,9.4124,9.2577,9.1031,8.9485,8.7938,8.6392,8.4845,8.3299,8.1753,8.0206,7.866,7.7113,7.5567,7.4021,7.2474,7.0928,6.9385,6.7846,6.6308,6.4769,6.3231,6.1692,6.0154,5.8615,5.7077,5.5538,5.4,5.2462,5.0923,4.9322,4.7627,4.5932,4.4237,4.2542,4.0847,3.9219,3.7656,3.6094,3.4531,3.2969,3.1406,2.9615,2.5769,2.1923,1.8864,1.6591,1.4318,1.2045,0.97727,0.75,0.52273,0.29545,0.068182,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


 float Distleft (long i)
 {
	 return sense_left[i/10];
 }
 float Distright (long i)
 {
	 return sense_right[i/10];
 }
 float Distmid (long i)
 {
	 return sense_mid[i/10];
 }