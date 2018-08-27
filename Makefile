all: clean brute_force_knapsack.out greedy_algorithm.out dynamic_programming_knapsack.out

brute_force_knapsack.out:
		gcc -std=c11 brute_force_knapsack.c -o brute_force_knapsack.out

greedy_algorithm.out:
		gcc -std=c11 greedy_algorithm.c -o greedy_algorithm.out

dynamic_programming_knapsack.out:
		gcc -std=c11 dynamic_programming_knapsack.c -o dynamic_programming_knapsack.out

clean:
	rm -f brute_force_knapsack.out greedy_algorithm.out dynamic_programming_knapsack.out
