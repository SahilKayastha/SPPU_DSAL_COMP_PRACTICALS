#Implement all the functions of a dictionary (ADT) using hashing and handle collisions using chaining with / without replacement. Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable, Keys must be unique Standard Operations: Insert(key, value), Find(key), Delete(key)

def hash_function(key, size):
    return hash(key) % size

def insert_with_replacement(table, key, value, size):
    index = hash_function(key, size)
    for i, (k, v) in enumerate(table[index]):
        if k == key:
            table[index][i] = (key, value)
            return
    table[index].append((key, value))

def insert_without_replacement(table, key, value, size):
    index = hash_function(key, size)
    for i, (k, v) in enumerate(table[index]):
        if k == key:
            return  # Key already exists, no replacement
    table[index].append((key, value))

def find(table, key, size):
    index = hash_function(key, size)
    for k, v in table[index]:
        if k == key:
            return v  # Return value if key found
    return None  # Key not found

def delete(table, key, size):
    index = hash_function(key, size)
    for i, (k, v) in enumerate(table[index]):
        if k == key:
            del table[index][i]  # Delete key-value pair
            return
    raise KeyError("Key not found")

def print_table(table):
    for i, chain in enumerate(table):
        print(f"Index {i}: {chain}")

def menu():
    size = int(input("Enter the size of the hash table: "))
    table = [[] for _ in range(size)]
    
    while True:
        print("\nMENU:")
        print("1. Insert with replacement")
        print("2. Insert without replacement")
        print("3. Find")
        print("4. Delete")
        print("5. Print table")
        print("6. Exit")

        choice = int(input("Enter your choice: "))

        if choice == 1:
            key = input("Enter the key: ")
            value = input("Enter the value: ")
            insert_with_replacement(table, key, value, size)
        elif choice == 2:
            key = input("Enter the key: ")
            value = input("Enter the value: ")
            insert_without_replacement(table, key, value, size)
        elif choice == 3:
            key = input("Enter the key to find: ")
            value = find(table, key, size)
            if value is not None:
                print(f"Value found: {value}")
            else:
                print("Key not found")
        elif choice == 4:
            key = input("Enter the key to delete: ")
            try:
                delete(table, key, size)
                print("Key deleted successfully")
            except KeyError as e:
                print(e)
        elif choice == 5:
            print_table(table)
        elif choice == 6:
            print("Exiting program...")
            break
        else:
            print("Invalid choice, please try again")

menu()