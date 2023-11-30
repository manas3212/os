import os

def demonstrate_system_calls():
    # 1. Get the current working directory
    current_directory = os.getcwd()
    print("Current Working Directory:", current_directory)

    # 2. List files in the current directory
    files_in_directory = os.listdir(current_directory)
    print("Files in Current Directory:")
    for file in files_in_directory:
        print(file)

    # 3. Create a new directory
    new_directory = "example_directory"
    os.mkdir(new_directory)
    print(f"\nCreated new directory: {new_directory}")

if __name__ == "__main__":
    demonstrate_system_calls()