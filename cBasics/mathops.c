#include "mathops.h"

float snek_score(int num_files, int num_contributors, int num_commits, float avg_bug_criticality) {
    int size_factor = num_files * num_commits;
    int complexity_factor = size_factor + num_contributors;
    return complexity_factor * avg_bug_criticality;
}
