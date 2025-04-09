# EarthquakeDataAnalysisLinkedLists
Earthquakes Data Analysis with linked lists

Input Format:
The data is stored in a file where each line represents an earthquake entry in the following comma-separated format:

Place, Year, Month, Day, Magnitude, Latitude, Longitude, Tsunami

Example:
Country1, 2016, 11, 13, 4.9, -42.2914, 173.8065, 1

Program Structure:

Each country or ocean is represented by a node in a main linked list.

Each of these nodes contains another linked list of earthquakes specific to that location.

Program Features:

Load earthquake data from file.

Allow the user to remove earthquakes below a given magnitude threshold.

Display the number of earthquakes, tsunami count, and average magnitude for a specific location.

Required Functions:

load_data:
Loads data from a file and builds the linked list structure.
Input: file name
Output: data structure representing the full list

remove_earthquake:
Removes earthquakes below a user-defined magnitude from all lists.
Input: data structure, magnitude threshold
Output: void

average_magnitude:
Calculates average magnitude for a specific country or ocean.
Input: linked list of earthquakes
Output: average magnitude (float)

count_earthquakes:
Counts number of earthquakes for a specific location.
Input: linked list of earthquakes
Output: number of earthquakes (int)
