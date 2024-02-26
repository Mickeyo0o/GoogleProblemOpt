# Optimization of the problem statement for the Online Qualification Round of Hash Code 2020 in C++

This repository contains an algorithm for efficiently assigning libraries to scan books within a given time frame. The algorithm combines Simulated Annealing and Heuristic Sorting to calculate the solution within 5 minutes for any input data. The exact problem statement and rules can be found [here](problem_statement.pdf).

## Theoretical Part

### Current solution Methods

* <b>Simulated Annealing:</b> preprocesses the data for large instances, reducing the number of libraries to be considered in the second part of the algorithm. This algorithm is chosen for its ability to efficiently reject uninteresting libraries without considering the best ordering of libraries, making it suitable for preprocessing large solution landscapes.
Heuristic Sorting

* <b>Heuristic Sorting:</b> sorts the preprocessed data according to a heuristic function to determine the final assignment of libraries and books. This algorithm is chosen for its deterministic time convergence, ensuring the algorithm produces a sufficiently good solution within a given time frame. However, due to the nature of the heuristic function, sorting is done with an insertion sort algorithm, resulting in 𝑂(𝑛2) time complexity, necessitating problem size reduction for large instances.

### Other Considered Methods

* <b>Combinatorial Particle Swarm:</b> Initially attempted but did not yield score improvements over random solutions.
* <b>Binary Particle Swarm:</b> Changed from combinatorial version but did not produce satisfactory results.
* <b>Branch and Bound:</b> Considered but deemed impractical due to computational time requirements.

## Implementation Part

1. Data about libraries and books is loaded into vectors, and a HashMap is created to store the number of libraries where each book can be found. Additionally, the sum of libraries' signup time is calculated, and books in each library are sorted by score.

2. If the number calculated by $\frac{daysAvailable}{sumOfSignupTimes}$ exceeds the threshold selected by us, preprocessing with Simulated Annealing is executed. The state in the algorithm is represented as an array of Boolean values indicating libraries worth considering. The annealing process runs for a specified number of iterations, stopping if no improvement is recorded or a time limit is reached. Heuristic score of each state is calculated by the formula $\left( \sum_{library ∈ librariesInAssignment} booksPerDay(library) \times \sum_{book ∈ library} \frac{score(book)}{bookFoundInLibraries(book)} \right)$
$- 1000 \times remainingDays - 1000 \times | \frac{daysAvailable}{sumOfSignupTimes} \times L - librariesAmount|$.

3. After preprocessing, a new vector of libraries is created. If preprocessing was needed, only selected libraries are added. Sorting is then executed until the allocated scanning time is exceeded, selecting the best library in each iteration according to a formula as follows: $\frac{\sum_{\substack{book | book \in library ∧ book \notin usedBooks}} \frac{score(book)}{bookFoundInLibraries(book)}}{(maxDays - signupTime(library)) \times signupTime(library)}$.

4. At the end, the solution is printed.

## Conclusion

The algorithm balances computational efficiency with solution quality within time constraints. While not reaching theoretical upper bounds, it provides reasonable results within given time limits. Stochastic methods were deemed impractical due to time restrictions, emphasizing the importance of choosing suitable algorithms for problem size and constraints.

## Usage

Please make sure you have at least g++ version 6.0 and make installed. Exemplary files to test the program have been provided as *.txt files.

After that go to the directory with a makefile in the terminal and type:
    
    make

After that, to run, please execute the command

    ./output 

To load data from the file and run program

    ./output < path_of_the_input_file.txt 

To save results into a file 

    ./output > path_of_the_output_file.txt

To do both

    ./output < path_of_the_input_file.txt > path_of_the_output_file.txt

## Creators

* Kajetan Sulwiński (ekohachi22)
* Mikołaj Marmurowicz (Mickeyo0o)
