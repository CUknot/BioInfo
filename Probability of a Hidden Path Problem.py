import math
observed_sequence = "AAABBBABABAABAAABAAABBBBAABBBABBAABABBABAABAAAAABA"
observations = ['A', 'B']

transition_probs = {
    'A': {'A': 0.514, 'B': 0.486},
    'B': {'A': 0.342, 'B': 0.658}
}
log_prob = math.log(0.5);
for i in range(len(observed_sequence) - 1):
    state = observed_sequence[i]
    next_state = observed_sequence[i + 1]
    log_prob += math.log(transition_probs[state][next_state])

print(math.e**log_prob)