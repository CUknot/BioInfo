import numpy as np
from scipy.cluster.hierarchy import linkage, to_tree
from scipy.spatial.distance import squareform

# Function to convert scipy tree to Newick format
def to_newick(node, leaf_names, parentdist=0):
    if node.is_leaf():
        return f"{leaf_names[node.id]}:{parentdist - node.dist:.6f}"
    else:
        left_newick = to_newick(node.get_left(), leaf_names, node.dist)
        right_newick = to_newick(node.get_right(), leaf_names, node.dist)
        return f"({left_newick},{right_newick}):{parentdist - node.dist:.6f}"

# Input species and distance matrix
species = ['Chimp', 'Human', 'Seal', 'Whale']
distance_matrix = np.array([
    [0, 3, 6, 4],
    [3, 0, 7, 5],
    [6, 7, 0, 2],
    [4, 5, 2, 0]
])

# Convert distance matrix to a condensed form suitable for linkage function
condensed_matrix = squareform(distance_matrix)

# Perform hierarchical clustering using UPGMA method (average linkage)
linkage_matrix = linkage(condensed_matrix, method='average')

# Get the root node
tree, _ = to_tree(linkage_matrix, rd=True)

# Convert the scipy tree to Newick format
newick_tree = to_newick(tree, species)

# Function to adjust Newick string to ensure "Human" is the root
def make_human_root(newick_str):
    # Find the portion of the string that needs adjustment
    human_index = newick_str.find('Human')
    if human_index == -1:
        raise ValueError("Human not found in the Newick string")

    # Extract the part of the string after "Human"
    pre_human_part = newick_str[:human_index]
    human_part = newick_str[human_index:]
    
    # Fix the string to ensure "Human" is at the root
    # Remove the "Human" part from its current place
    trimmed_human_part = human_part.split(')')[0] + ')'
    
    # Build the new Newick string with "Human" as the root
    adjusted_newick = f"({pre_human_part[1:]}{trimmed_human_part})Human:0.000"
    
    return adjusted_newick

# Get the final Newick string with "Human" as the root
human_root_newick = make_human_root(newick_tree)

# Output the final Newick tree
print(human_root_newick)
