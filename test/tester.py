import subprocess
TEST_FILENAME = "tests.txt"
PATH_TO_EXECUTABLE = "../build/cache"

class Test:
    number      = 0
    status      = False
    input       = []
    ref_output  = []
    real_output = []

    def __init__(self):
        self.number      = 0
        self.status      = False
        self.input       = []
        self.ref_output  = []
        self.real_output = []

    def read_test(self, buffer):
        self.number = int((buffer[0].split())[1])
        self.input = (buffer[1].split())[1::]
        self.ref_output = (buffer[2].split())[1::]

test_file = open(TEST_FILENAME, "r")
lines_buffer = test_file.readlines()

tests_array = []

# input tests
for i in range(int(len(lines_buffer) / 3)):
    current_test = Test()
    current_test.read_test(lines_buffer[(i*3)::])

    tests_array.append(current_test)

# make testing
for i in range(len(tests_array)):
    args = [PATH_TO_EXECUTABLE]

    prog_input = ' '.join(tests_array[i].input)

    result = subprocess.run(args, input=prog_input.encode(), capture_output=True)

    result_output = result.stdout.decode().split()
    ref_output = tests_array[i].ref_output
    tests_array[i].real_output = result_output

    tests_array[i].status = True

    if len(result_output) != len(ref_output):
        tests_array[i].status = False
        break

    for cur_val in range(len(result_output)):
        if result_output[cur_val] != ref_output[cur_val]:
            tests_array[i].status = False
            break

# output result
passed_tests = 0
failed_tests = 0
for test in tests_array:
    if not(test.status):
        print("Test number: " + str(test.number) + " failed!")
        print("Reference output: " + ' '.join(test.ref_output))
        print("Real output: " + ' '.join(test.real_output))
        failed_tests += 1
    else:
        passed_tests += 1

print("\nPassed tests: " + str(passed_tests))
print("Failed tests: " + str(failed_tests))
print("All: " + str(failed_tests + passed_tests))
    

test_file.close()