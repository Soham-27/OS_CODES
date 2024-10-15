#!/bin/sh
# Function to create an address book
create_addressbook() {
touch addressbook.txt
echo "Address book created."
}

# Function to view the address book
view_addressbook() {
if [ -f addressbook.txt ]; then
cat addressbook.txt
else
echo "Address book not found. Please create one first."
fi
}

# Function to insert a record
insert_record() {
echo "Enter name:"
read name
echo "Enter phone number:"
read phone
echo "$name, $phone" >> addressbook.txt
echo "Record inserted."
}

# Function to delete a record
delete_record() {
echo "Enter name of the record to delete:"
read name

grep -v "^$name," addressbook.txt > temp.txt && mv temp.txt
addressbook.txt
echo "Record deleted."
}

# Function to modify a record
modify_record() {
echo "Enter name of the record to modify:"
read name
grep -v "^$name," addressbook.txt > temp.txt
mv temp.txt addressbook.txt
echo "Enter new phone number:"
read phone
echo "$name, $phone" >> addressbook.txt
echo "Record modified."

}
# Main menu
while true; do
echo "Choose an option:"
echo "1. Create address book"
echo "2. View address book"
echo "3. Insert a record"
echo "4. Delete a record"
echo "5. Modify a record"
echo "6. Exit"
read choice

case $choice in
1) create_addressbook ;;
2) view_addressbook ;;
3) insert_record ;;
4) delete_record ;;

5) modify_record ;;
6) exit 0 ;;
*) echo "Invalid option" ;;
esac
done

addressbook.sh
Open with
Displaying addressbook.sh.
