import numpy as np
from functools import reduce

all_case = np.arange(23)

case_1 = np.array([4, 8, 18])
case_2 = np.array([4, 7, 18])
case_3 = np.array([4, 18])
case_4 = np.array([4, 11, 13])
case_5 = np.array([0, 4, 5, 11, 13])
case_6 = np.array([2, 4, 12, 10])

result = reduce(np.union1d, (case_1, case_2, case_3, case_4, case_5, case_6))

print("Bug found in " + str(result) + " (" + str(result.size) + ")")
print(str(np.setdiff1d(all_case, result)) + " left ("+ str(all_case.size-result.size) + ")")
