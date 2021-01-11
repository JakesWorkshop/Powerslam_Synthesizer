/* Hello, this little library will help you convert a voltage to a frequency.
 * It implements the two functions voltageToFrequency() and noteToFrequency(). Both return a float.
 * 
 * voltageToFrequency expects an int between 0 and 1023 (the output of the analogRead() Function at 10 Bit resolution)
 * noteToFrequency expects an int between 0 and 60 (you can use the map() function for example)
 * 
 * inputs outside this Range will return garbage or break something.
 * 
 * Both functions represent 5 Octaves, starting with C1 as their first Value and ending with C6 as their last note
 * this way you can use analogRead() to acheive a conversion with exactly 1Volt per octave
 * (0V = C1, 1V = C2, 2V = C3, 3V = C4, 4V = C5, 5V = C6)\
 * 
 * These Values were calculated from a polynom function, the frequencies may be off by up to 1Hz from absolute perfect values.
 * But it should serve as being "close enough" for most applications.
 * 
 * Find the project at https://github.com/JakesWorkshop/Powerslam_Synthesizer
 * Find me on Twitter: https://twitter.com/Jakesworkshop
 */

const float voltageFrequency[1024] PROGMEM = {
32.32, 32.45, 32.57, 32.70, 32.83, 32.96, 33.09, 33.22, 33.35, 33.47, 33.60, 33.73, 33.86, 33.99, 34.12, 34.25, 
34.38, 34.51, 34.64, 34.77, 34.90, 35.03, 35.16, 35.29, 35.42, 35.55, 35.68, 35.81, 35.95, 36.08, 36.21, 36.34, 
36.47, 36.60, 36.74, 36.87, 37.00, 37.13, 37.27, 37.40, 37.53, 37.67, 37.80, 37.94, 38.07, 38.21, 38.34, 38.48, 
38.61, 38.75, 38.88, 39.02, 39.16, 39.29, 39.43, 39.57, 39.71, 39.84, 39.98, 40.12, 40.26, 40.40, 40.54, 40.68, 
40.82, 40.96, 41.10, 41.24, 41.38, 41.52, 41.66, 41.81, 41.95, 42.09, 42.24, 42.38, 42.52, 42.67, 42.81, 42.96, 
43.10, 43.25, 43.40, 43.54, 43.69, 43.84, 43.99, 44.13, 44.28, 44.43, 44.58, 44.73, 44.88, 45.03, 45.18, 45.34, 
45.49, 45.64, 45.79, 45.95, 46.10, 46.26, 46.41, 46.57, 46.72, 46.88, 47.03, 47.19, 47.35, 47.51, 47.67, 47.83, 
47.98, 48.14, 48.31, 48.47, 48.63, 48.79, 48.95, 49.12, 49.28, 49.44, 49.61, 49.77, 49.94, 50.11, 50.27, 50.44, 
50.61, 50.78, 50.95, 51.11, 51.28, 51.46, 51.63, 51.80, 51.97, 52.14, 52.32, 52.49, 52.67, 52.84, 53.02, 53.19, 
53.37, 53.55, 53.73, 53.90, 54.08, 54.26, 54.44, 54.63, 54.81, 54.99, 55.17, 55.36, 55.54, 55.73, 55.91, 56.10, 
56.29, 56.47, 56.66, 56.85, 57.04, 57.23, 57.42, 57.61, 57.80, 58.00, 58.19, 58.39, 58.58, 58.78, 58.97, 59.17, 
59.37, 59.56, 59.76, 59.96, 60.16, 60.37, 60.57, 60.77, 60.97, 61.18, 61.38, 61.59, 61.79, 62.00, 62.21, 62.42, 
62.62, 62.83, 63.05, 63.26, 63.47, 63.68, 63.90, 64.11, 64.32, 64.54, 64.76, 64.97, 65.19, 65.41, 65.63, 65.85, 
66.07, 66.30, 66.52, 66.74, 66.97, 67.19, 67.42, 67.64, 67.87, 68.10, 68.33, 68.56, 68.79, 69.02, 69.26, 69.49, 
69.72, 69.96, 70.19, 70.43, 70.67, 70.91, 71.15, 71.39, 71.63, 71.87, 72.11, 72.36, 72.60, 72.85, 73.09, 73.34, 
73.59, 73.84, 74.09, 74.34, 74.59, 74.84, 75.09, 75.35, 75.60, 75.86, 76.12, 76.37, 76.63, 76.89, 77.15, 77.41, 
77.68, 77.94, 78.20, 78.47, 78.74, 79.00, 79.27, 79.54, 79.81, 80.08, 80.35, 80.63, 80.90, 81.17, 81.45, 81.73, 
82.00, 82.28, 82.56, 82.84, 83.12, 83.41, 83.69, 83.98, 84.26, 84.55, 84.84, 85.12, 85.41, 85.70, 86.00, 86.29, 
86.58, 86.88, 87.17, 87.47, 87.77, 88.07, 88.37, 88.67, 88.97, 89.27, 89.58, 89.88, 90.19, 90.50, 90.80, 91.11, 
91.42, 91.74, 92.05, 92.36, 92.68, 92.99, 93.31, 93.63, 93.95, 94.27, 94.59, 94.91, 95.24, 95.56, 95.89, 96.21, 
96.54, 96.87, 97.20, 97.53, 97.87, 98.20, 98.54, 98.87, 99.21, 99.55, 99.89, 100.23, 100.57, 100.91, 101.26, 101.60, 
101.95, 102.30, 102.65, 103, 103.35, 103.7, 104.06, 104.41, 104.77, 105.13, 105.49, 105.85, 106.21, 106.57, 106.93, 107.30, 
107.66, 108.03, 108.40, 108.77, 109.14, 109.52, 109.89, 110.26, 110.64, 111.02, 111.40, 111.78, 112.16, 112.54, 112.93, 113.31, 
113.70, 114.09, 114.48, 114.87, 115.26, 115.65, 116.05, 116.44, 116.84, 117.24, 117.64, 118.04, 118.45, 118.85, 119.26, 119.66, 
120.07, 120.48, 120.89, 121.30, 121.72, 122.13, 122.55, 122.97, 123.39, 123.81, 124.23, 124.66, 125.08, 125.51, 125.94, 126.37, 
126.80, 127.23, 127.66, 128.10, 128.54, 128.97, 129.41, 129.86, 130.30, 130.74, 131.19, 131.64, 132.08, 132.53, 132.99, 133.44, 
133.89, 134.35, 134.81, 135.27, 135.73, 136.19, 136.66, 137.12, 137.59, 138.06, 138.53, 139.00, 139.47, 139.95, 140.43, 140.90, 
141.38, 141.87, 142.35, 142.83, 143.32, 143.81, 144.30, 144.79, 145.28, 145.78, 146.27, 146.77, 147.27, 147.77, 148.28, 148.78, 
149.29, 149.79, 150.30, 150.82, 151.33, 151.84, 152.36, 152.88, 153.40, 153.92, 154.44, 154.97, 155.50, 156.03, 156.56, 157.09, 
157.62, 158.16, 158.70, 159.24, 159.78, 160.32, 160.86, 161.41, 161.96, 162.51, 163.06, 163.62, 164.17, 164.73, 165.29, 165.85, 
166.42, 166.98, 167.55, 168.12, 168.69, 169.26, 169.84, 170.41, 170.99, 171.57, 172.16, 172.74, 173.33, 173.92, 174.51, 175.10, 
175.69, 176.29, 176.89, 177.49, 178.09, 178.69, 179.30, 179.91, 180.52, 181.13, 181.75, 182.36, 182.98, 183.60, 184.23, 184.85, 
185.48, 186.11, 186.74, 187.37, 188.01, 188.65, 189.29, 189.93, 190.57, 191.22, 191.87, 192.52, 193.17, 193.82, 194.48, 195.14, 
195.80, 196.47, 197.13, 197.80, 198.47, 199.14, 199.82, 200.50, 201.18, 201.86, 202.54, 203.23, 203.92, 204.61, 205.30, 206.00, 
206.69, 207.39, 208.10, 208.80, 209.51, 210.22, 210.93, 211.65, 212.36, 213.08, 213.80, 214.53, 215.25, 215.98, 216.72, 217.45, 
218.19, 218.92, 219.67, 220.41, 221.16, 221.90, 222.66, 223.41, 224.17, 224.93, 225.69, 226.45, 227.22, 227.99, 228.76, 229.53, 
230.31, 231.09, 231.87, 232.66, 233.45, 234.24, 235.03, 235.82, 236.62, 237.42, 238.23, 239.03, 239.84, 240.66, 241.47, 242.29, 
243.11, 243.93, 244.76, 245.58, 246.42, 247.25, 248.09, 248.93, 249.77, 250.61, 251.46, 252.31, 253.17, 254.02, 254.88, 255.75, 
256.61, 257.48, 258.35, 259.23, 260.10, 260.99, 261.87, 262.75, 263.64, 264.54, 265.43, 266.33, 267.23, 268.14, 269.04, 269.95, 
270.87, 271.79, 272.71, 273.63, 274.55, 275.48, 276.42, 277.35, 278.29, 279.23, 280.18, 281.13, 282.08, 283.03, 283.99, 284.95, 
285.92, 286.88, 287.86, 288.83, 289.81, 290.79, 291.77, 292.76, 293.75, 294.75, 295.74, 296.75, 297.75, 298.76, 299.77, 300.79, 
301.80, 302.83, 303.85, 304.88, 305.91, 306.95, 307.99, 309.03, 310.08, 311.13, 312.18, 313.24, 314.30, 315.36, 316.43, 317.50, 
318.58, 319.66, 320.74, 321.83, 322.92, 324.01, 325.11, 326.21, 327.31, 328.42, 329.54, 330.65, 331.77, 332.90, 334.02, 335.16, 
336.29, 337.43, 338.57, 339.72, 340.87, 342.03, 343.19, 344.35, 345.52, 346.69, 347.86, 349.04, 350.22, 351.41, 352.60, 353.80, 
355.00, 356.20, 357.41, 358.62, 359.84, 361.06, 362.28, 363.51, 364.74, 365.98, 367.22, 368.46, 369.71, 370.97, 372.22, 373.49, 
374.75, 376.02, 377.30, 378.58, 379.86, 381.15, 382.44, 383.74, 385.04, 386.35, 387.66, 388.97, 390.29, 391.62, 392.94, 394.28, 
395.62, 396.96, 398.30, 399.66, 401.01, 402.37, 403.74, 405.11, 406.48, 407.86, 409.25, 410.64, 412.03, 413.43, 414.83, 416.24, 
417.65, 419.07, 420.49, 421.92, 423.35, 424.79, 426.23, 427.68, 429.13, 430.59, 432.05, 433.51, 434.99, 436.46, 437.95, 439.43, 
440.92, 442.42, 443.92, 445.43, 446.94, 448.46, 449.99, 451.51, 453.05, 454.59, 456.13, 457.68, 459.23, 460.79, 462.36, 463.93, 
465.51, 467.09, 468.67, 470.27, 471.86, 473.47, 475.08, 476.69, 478.31, 479.93, 481.57, 483.20, 484.84, 486.49, 488.14, 489.80, 
491.47, 493.14, 494.81, 496.49, 498.18, 499.88, 501.57, 503.28, 504.99, 506.71, 508.43, 510.16, 511.89, 513.63, 515.38, 517.13, 
518.89, 520.65, 522.42, 524.19, 525.98, 527.76, 529.56, 531.36, 533.17, 534.98, 536.80, 538.62, 540.45, 542.29, 544.13, 545.98, 
547.84, 549.70, 551.57, 553.45, 555.33, 557.22, 559.11, 561.01, 562.92, 564.83, 566.75, 568.68, 570.61, 572.55, 574.50, 576.45, 
578.41, 580.38, 582.35, 584.33, 586.32, 588.32, 590.32, 592.32, 594.34, 596.36, 598.39, 600.42, 602.46, 604.51, 606.57, 608.63, 
610.70, 612.77, 614.86, 616.95, 619.05, 621.15, 623.26, 625.38, 627.51, 629.64, 631.78, 633.93, 636.08, 638.25, 640.42, 642.59, 
644.78, 646.97, 649.17, 651.38, 653.59, 655.81, 658.04, 660.28, 662.52, 664.77, 667.03, 669.30, 671.58, 673.86, 676.15, 678.45, 
680.75, 683.07, 685.39, 687.72, 690.05, 692.40, 694.75, 697.11, 699.48, 701.86, 704.24, 706.64, 709.04, 711.45, 713.86, 716.29, 
718.72, 721.16, 723.61, 726.07, 728.54, 731.01, 733.49, 735.99, 738.49, 740.99, 743.51, 746.03, 748.57, 751.11, 753.66, 756.22, 
758.79, 761.36, 763.95, 766.54, 769.14, 771.75, 774.37, 777.00, 779.64, 782.29, 784.94, 787.60, 790.28, 792.96, 795.65, 798.35, 
801.06, 803.77, 806.50, 809.24, 811.98, 814.74, 817.50, 820.27, 823.05, 825.84, 828.64, 831.45, 834.27, 837.10, 839.94, 842.79, 
845.64, 848.51, 851.38, 854.27, 857.16, 860.07, 862.98, 865.91, 868.84, 871.78, 874.74, 877.70, 880.67, 883.66, 886.65, 889.65, 
892.66, 895.68, 898.72, 901.76, 904.81, 907.87, 910.95, 914.03, 917.12, 920.23, 923.34, 926.46, 929.60, 932.74, 935.90, 939.06, 
942.24, 945.42, 948.62, 951.83, 955.04, 958.27, 961.51, 964.76, 968.02, 971.29, 974.57, 977.87, 981.17, 984.48, 987.81, 991.14, 
994.49, 997.85, 1001.22, 1004.60, 1007.99, 1011.39, 1014.8, 1018.23, 1021.66, 1025.11, 1028.57, 1032.04, 1035.52, 1039.01, 1042.51, 1046.03
};

const float noteFrequency[61] PROGMEM = {
32.7, 34.6, 36.7, 38.9,
41.2, 43.7, 46.2, 49.0,
52.0, 55.0, 58.3, 61.7,
65.4, 69.3, 73.4, 77.8,
82.4, 87.3, 92.5, 98.0,
103.8, 110.0, 116.5, 123.5,
130.8, 138.6, 146.8, 155.6,
164.8, 174.6, 185.0, 196.0,
207.6, 220.0, 233.1, 246.9,
261.6, 277.2, 293.7, 311.1,
329.6, 349.2, 370.0, 392.0,
415.3, 440.0, 466.2, 493.9,
523.3, 554.4, 587.3, 622.3,
659.3, 698.5, 740.0, 784.0,
830.6, 880.0, 932.3, 987.8,
1046.5
};

float voltageToFrequency(int input){
  return pgm_read_float(&voltageFrequency[input]);
}

float noteToFrequency(int input){
  return pgm_read_float(&noteFrequency[input]);
}

//did you know you cannot access a PROGMERM array by its index?
//https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
