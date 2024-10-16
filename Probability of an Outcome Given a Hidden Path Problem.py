# Updated Data
x = "yyzyyyyxzzxzyzyyyxzyzyzyxxxyzzxyzzzzyzyyzyxxzyyyzz"
pi = "AAABABBBAAABAAAABBBBBBBAAABABABAABBABBABABAAAAAAAB"

# Updated Emission Matrix
emission_matrix = {
    'A': {'x': 0.238, 'y': 0.389, 'z': 0.373},
    'B': {'x': 0.475, 'y': 0.261, 'z': 0.264}
}

# Ensure both strings are of the same length
if len(x) != len(pi):
    raise ValueError("The emission string and hidden path must be of the same length.")

# Calculate Pr(x | pi)
prob = 1.0
for emission, state in zip(x, pi):
    prob *= emission_matrix[state][emission]

# Due to the small probability, it's better to use logarithms
import math

log_prob = 0.0
for emission, state in zip(x, pi):
    log_prob += math.log(emission_matrix[state][emission])

# To get the probability back from log_prob
prob_from_log = math.exp(log_prob)

print(f"Pr(x | pi) = {prob}")
print(f"Log Pr(x | pi) = {log_prob}")
print(f"Pr(x | pi) from log = {prob_from_log}")
