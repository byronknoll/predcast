predcast
https://code.google.com/p/predcast/
Made by Byron Knoll in 2013.

This project is in the public domain - attribution is appreciated but not required.

This project uses pattern recognition to perform time series forecasting: given a sequence of floating point numbers, the program will output predictions for the next N data points. It has linear time complexity and is robust to noisy input data. It has few parameters, so is easy to apply to new data sets. Although the algorithm can easily be extended to multi-dimensional input, this release only supports one-dimensional data.

The algorithm has two main components:

1) Context matching (memory.cpp). This component tries to find the portion of the input history that is the closest match to the most recent input. It uses cross-correlation to find the match. It uses least squares fitting to find linear trends in the data. It also supports data smoothing to increase robustness to noise.

2) Frequency analysis (brain.cpp). This component uses a discrete cosine transform (DCT) to separate different frequency components of the input data. DCT is performed on a sliding Hann window function. The context matching algorithm described above is used independently on each DCT component to predict future input. The high frequency DCT components can be discarded to increase robustness to noise.

This project contains two executables:

1) simple-predictor. This only uses the context matching component described above. It has three integer parameters:
	- num_predictions (default = 100): The number of future data point predictions to output.
	- context_length (default = 100): The size of the window used for context matching.
	- smoothing (default = 2): The smoothing factor (1 = no smoothing, higher values = more smoothing).

2) complex-predictor. This uses the frequency analysis component described above. It has five integer parameters:
	- num_predictions (default = 100): The number of future data point predictions to output.
	- window_size (default = 50): The size of the Hann window function.
	- memory_size (default = 3): The number of DCT components to use (should be less than or equal to window_size).
	- context_length (default = 100): The size of the window used for context matching.
	- smoothing (default = 2): The smoothing factor (1 = no smoothing, higher values = more smoothing).

Both of these programs use standard input/output. Input should be a sequence of floating point numbers separated by line breaks.
