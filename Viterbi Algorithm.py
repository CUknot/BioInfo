import numpy as np

# Define states and observations
states = ['A', 'B', 'C', 'D']
observations = ['x', 'y', 'z'] 
observed_sequence = "zzyzyxxyxxxzyzyyzyxyzxzyxzzxzyxxxxzzyzzyzzxxyzxyxyzzxyxzxxzyyxxxzzxyxxzzzxxyyyyyxzxyyxzxxyyzxzyxzyyx"

# Define the transition probabilities
transition_probs = {
    'A': {'A': 0.236, 'B': 0.183, 'C': 0.291, 'D': 0.291},
    'B': {'A': 0.150, 'B': 0.167, 'C': 0.535, 'D': 0.148},
    'C': {'A': 0.411, 'B': 0.231, 'C': 0.241, 'D': 0.117},
    'D': {'A': 0.181, 'B': 0.243, 'C': 0.379, 'D': 0.197}
}

# Define the emission probabilities
emission_probs = {
    'A': {'x': 0.559, 'y': 0.435, 'z': 0.006},
    'B': {'x': 0.592, 'y': 0.027, 'z': 0.381},
    'C': {'x': 0.390, 'y': 0.258, 'z': 0.352},
    'D': {'x': 0.106, 'y': 0.266, 'z': 0.628}
}

# Initialize the Viterbi algorithm
def viterbi(observed_sequence):
    n = len(observed_sequence)
    m = len(states)

    # Initialize the Viterbi table and the backpointer table
    V = np.zeros((m, n))
    path = np.zeros((m, n), dtype=int)

    # Base case: Initialize the first column of Viterbi table
    for s in range(m):
        state = states[s]
        V[s, 0] = (1 / m) * emission_probs[state].get(observed_sequence[0], 0)

    # Fill the Viterbi table
    for t in range(1, n):
        for s in range(m):
            state = states[s]
            max_prob = -1
            max_state = -1
            for s_prev in range(m):
                prev_state = states[s_prev]
                prob = V[s_prev, t - 1] * transition_probs[prev_state][state] * emission_probs[state].get(observed_sequence[t], 0)
                if prob > max_prob:
                    max_prob = prob
                    max_state = s_prev
            V[s, t] = max_prob
            path[s, t] = max_state

    # Backtrack to find the most likely state sequence
    max_prob = -1
    best_last_state = -1
    for s in range(m):
        if V[s, n - 1] > max_prob:
            max_prob = V[s, n - 1]
            best_last_state = s

    best_path = [best_last_state]
    for t in range(n - 1, 0, -1):
        best_last_state = path[best_last_state, t]
        best_path.insert(0, best_last_state)

    return "".join([states[state] for state in best_path]), max_prob

# Execute the Viterbi algorithm
predicted_states, probability = viterbi(observed_sequence)

# Display the results
print(f"Predicted states: {predicted_states}")
print(f"Probability of the observed sequence: {probability:.6f}")
