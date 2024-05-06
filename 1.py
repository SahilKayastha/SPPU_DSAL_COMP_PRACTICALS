#Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client‘s telephone number.

size = int(input("Enter the size of the hash table: "))
client_list = [None] * size

def add_client():
    client_id = int(input("Enter client id: "))
    name = input("Enter client name: ")
    telephone = input("Enter client telephone: ")
    client_details = [client_id, name, telephone]

    index = client_id % size
    # Inserting record using linear probing in case of collision
    for i in range(size):
        if client_list[index] == None:
            client_list[index] = client_details
            print("Client added successfully.")
            break
        else:
            index = (index + 1) % size
    else:
        print("Failed to add client. Hash table is full.")

def search_client():
    client_id = int(input("Enter client id to search: "))
    index = client_id % size
    for i in range(size):
        if client_list[index] != None:
            if client_list[index][0] == client_id:
                print("Client found at index", index, ":", client_list[index])
                break
        index = (index + 1) % size
    else:
        print("Client not found.")

def delete_client():
    client_id = int(input("Enter client id to delete: "))
    index = client_id % size
    for i in range(size):
        if client_list[index] != None:
            if client_list[index][0] == client_id:
                client_list[index] = None
                print("Client deleted successfully.")
                break
        index = (index + 1) % size
    else:
        print("Client not found.")

while True:
    print("\nMenu:")
    print("1. Add Client")
    print("2. Search Client")
    print("3. Delete Client")
    print("4. Exit")

    choice = int(input("Enter your choice: "))

    if choice == 1:
        add_client()
    elif choice == 2:
        search_client()
    elif choice == 3:
        delete_client()
    elif choice == 4:
        print("Exiting program.")
        break
    else:
        print("Invalid choice. Please enter a number from 1 to 4.")
