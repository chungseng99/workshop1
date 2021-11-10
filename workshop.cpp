
#include<iostream>
#include<iomanip>
#include<string>
#include<mysql.h>
#include<conio.h>

using namespace std;

//global variable declaration
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

string StaffID,position;
int option = 0;
char choice;


//function declaration
void Connection();
void MainMenu();
void Login();
void AdminMenu();
void StaffMenu();
void ShowStock();
void ShowListOfBooks();
void ShowBook();
void SupplyList();
void AddStock();
void CheckAvailability();
void DeleteStock();
void ModifyStock();
void SupplyAndOrder();
void ShowSummary();
void ColorCode(unsigned short);
//End of function declaration

//connection to database
 void Connection()
	{
	 system("cls");
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "localhost", "root", "", "dbworkshop1", 3306, NULL, 0);
		if (conn)
		{
			cout << "Database Connected To dbworkshop1" << endl;
			cout << "Press any key to continue..." << endl;
			_getch();
			system("cls");

		}
		else
			cout << "Failed To Connect!" << mysql_errno(conn) << endl;
	}


//Main Function
int main() 
{
	//connect to database
	Connection();
	MainMenu();
	
	cout << "1. Login " << endl;
	cout << "2. Exit " << endl;
	cout << "Please select one option: ";
	cin >> option;

	switch (option)
	{
	case 1:
		Login();
		break;
	case 2:
		cout << "\n**Exiting program."<<endl;
			cout<<"Press Enter to continue...";
		_getch();
		exit(0);//exit program
		break;
	default:
		if (!cin) {
			cout << "\nInvalid Option";
			cout << "\n**Please choose between 1 and 2." << endl;
			cout << "Press Enter to Continue...";
			cin.clear();
			cin.ignore(256, '\n');
			_getch();
			main();

		}
		cout << "\n**Please choose between 1 and 2."<<endl;
			cout<<"Press Enter to continue... ";
		_getch();//pause console
		system("cls");//clear screen
		main();
		break;
	}
}

 
//Print Interface for Main Menu
void MainMenu()
{
	
	cout <<"\t\t*********************************************************" << endl;
	cout << "\t\t* \t\t Welcome to Bookshop Stock \t\t*"<<endl;
	cout << "\t\t*   \t\t     Management System \t\t\t*" << endl;
	cout<< "\t\t*********************************************************" << endl;
	cout << "--------------------------------------------------------------------------------------------"<<endl;
}


//login page
void Login()
{
	string username;
	string password;

	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	
	//select query based on username and password entered
	string checkUser_query = "SELECT * FROM workforce WHERE Staff_Username = '" + username + "' AND Staff_Password = '" + password + "' ";
	const char* check = checkUser_query.c_str(); // convert checkUser and return to check
	qstate = mysql_query(conn, check);//execute query

	if (!qstate)
	{
		res = mysql_store_result(conn); //store result
		if (res->row_count == 1) //found user
		{
			while (row = mysql_fetch_row(res))//loop each row to get data
			{
				StaffID = row[0]; //store Staff_ID 
				position = row[3]; //store position
				
					if (position == "Manager" || position == "manager")
						AdminMenu();
					else
						StaffMenu();
			}
			
		}
				
	else
		{
			
			cout << "Invalid username or password. \nDo you want to try again?(Y/N): ";
			cin >> choice;
			if (choice == 'Y' ||choice == 'y')
				Login();
			else
				main();
		}

	}
}


//Admin Menu
void AdminMenu()
{
	//admin menu and option to choose 
	system("cls");
	
	//print option
	cout << "Bookshop Stock Management System" << endl;
	cout << "=================================================================" << endl;
	cout << "Main Menu" << endl<<endl;
	cout << "1. Show Stock" << endl;
	cout << "2. Show List Of Books" << endl;
	cout << "3. Add Stock" << endl;
	cout << "4. Check Availability" << endl;
	cout << "5. Delete Stock" << endl;
	cout << "6. Modify Stock" << endl;
	cout << "7. Show Supply List And Order Item" << endl;
	cout << "8. Show Summary" << endl;
	cout << "9. Exit" << endl;
	cout << "\n Please select an option : ";
	cin >> option;

	
	//option
	switch(option) 
	{
		case 1:	
		{
			cout << "Showing Stock.\nPress Enter to Continue..." << endl;
			_getch();
			system("cls");
			ShowStock();
			break;
		}
			
		case 2:
		{
			cout << "Showing Book Details.\nPress Enter to Continue..." << endl;
			_getch();
			system("cls");
			ShowListOfBooks();
			break;
		}
		
		case 3:
		{
			system("cls");
			
			AddStock();
			break;
		}

		case 4:
		{
			system("cls");
			CheckAvailability();
			break;
		}

		case 5:
		{
			system("cls");
			cout << "Bookshop Stock Management System" << endl;
			cout << "=================================================================" << endl;
			DeleteStock();
			break;
		}

		case 6:
		{
			system("cls");
			cout << "Bookshop Stock Management System" << endl;
			cout << "================================================================="<<endl;
			ModifyStock();
			break;
		}

		case 7:
		{
			system("cls");		
			
			SupplyAndOrder();
			break;

		}

		case 8:
		{
			system("cls");
			
			ShowSummary();
			break;
		}

		case 9:
		{
			
			cout << "\n**Exiting program."<<endl;
			cout << "Press Enter to continue...";
			_getch();
			exit(0);//exit program
			break;
		}

		default:
		{
			if (!cin) {
				cout << "\nInvalid Option";
				cout << "\n**Please Select An OptionFrom 1-9." <<endl;
				cout << "Press Enter to Continue...";
				cin.clear();
				cin.ignore(256, '\n');
				_getch();
				AdminMenu();

			}
			cout << "\nInvalid Option";
			cout << "\n**Please Select An Option From 1-9." << endl;
			cout << "Press Enter to Continue...";
			_getch();
			AdminMenu();
			break;
		}


	}
}


//Staff Menu
void StaffMenu()
{
	//staff menu and option to choose
	system("cls");
	
	//print option
	cout << "Bookshop Stock Management System" << endl;
	cout << "=================================================================" << endl;
	cout << "Staff Menu" << endl<<endl;
	cout << "1. Show Stock" << endl;
	cout << "2. Show List Of Books" << endl;
	cout << "3. Add Stock" << endl;
	cout << "4. Check Availability" << endl;
	cout << "5. Exit" << endl;
	cout << "\nPlease select an option : ";
	cin >> option;

	//option
	switch (option)
	{
		case 1:
		{
		cout << "Showing Stock.\nPress Enter to Continue..." << endl;
		_getch();
		system("cls");
		ShowStock();
		break;
		}

		case 2:
		{
			cout << "Showing Book Details.\nPress Enter to Continue..." << endl;
			_getch();
			system("cls");
			ShowListOfBooks();
			break;
		}

		case 3:
		{
		system("cls");
		
		AddStock();
		break;
		}

		case 4:
		{
		system("cls");
		CheckAvailability();
		break;
		}

		case 5:
		{
			cout << "\n**Exiting program."<<endl;
			cout << "Press Enter to continue...";
			_getch();
			exit(0);//exit program
			break;
		}

		default:
		{
			if (!cin) {
				cout << "\nInvalid Option";
				cout << "\n**Please Select An Option From 1-5." << endl;
				cout << "Press Enter to Continue...";
				cin.clear();
				cin.ignore(256, '\n');
				_getch();
				StaffMenu();

			}
		cout << "\nInvalid Option";
		cout << "\n**Please Select An Option From 1-5." << endl;
		cout << "Press Enter to Continue...";
		_getch();
		StaffMenu();
		break;
		}

	}
}


//Show Stock
void ShowStock()
{
	cout << "Bookshop Stock Management System" << endl;
	cout << "=================================================================" ;
	cout << "=================================================================="<<endl<<endl;
	
	
		//execute query
		qstate = mysql_query(conn, "SELECT inventory.Book_ID, book.Book_Name, book.Category, book.Book_Price, inventory.Stock_Quantity, inventory.Receive_Date FROM inventory LEFT JOIN book ON inventory.Book_ID = book.Book_ID");

		cout << setw(7) << "Book ID" << setw(40) << "Book Name" << setw(38) << "Category" << setw(13) << "Price" << setw(14) << "Quantity" << setw(16) << "Date Received" << endl;

		if (!qstate)
		{
			res = mysql_store_result(conn); //store result in res
			while (row = mysql_fetch_row(res))//loop every row to get data
			{
				cout << setw(6) << row[0] << setw(60) << row[1] << setw(20) << row[2] << setw(9) << "RM " << row[3] << setw(10) << row[4] << setw(17) << row[5] << endl;
			}
		}
		
		cout << "\nPress Enter to Return to Main Menu...";
		_getch();
		if (position == "Manager" || position == "manager")
		{
			system("cls");
			AdminMenu();
		}
		else
		{
			system("cls");
			StaffMenu();
		}
		


}


//Show Book Details
void ShowListOfBooks() 
{
	cout << "Bookshop Stock Management System" << endl;
	cout << "=================================================================";
	cout << "=================================================================";
	cout << "===============";
	cout << "==================================================================" << endl<<endl;


	//execute query
	qstate = mysql_query(conn, "SELECT book.*,inventory.Stock_Quantity,inventory.Receive_Date FROM book LEFT JOIN inventory ON inventory.Book_ID = book.Book_ID");

	cout << setw(7) << "Book ID" << setw(40) << "Book Name" << setw(38) << "Author Name" << setw(30) << "Publisher" << setw(20) << "Date Published" << setw(18) << "Category" << setw(17)<<"Price"<<setw(17)<<"Quantity"<<setw(20)<<"Date Received "<<endl;
	if (!qstate)
	{
		res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))//loop every row to get data
			{
				cout << setw(6) << row[0] << setw(60) << row[1] << setw(25) << row[2] << setw(25) << row[3] << setw(17) << row[4] << setw(20) << row[5] << setw(12)<<"RM "<<row[6]<<setw(15)<<row[7]<<setw(18)<<row[8]<<endl;
			}
	}

	cout << "\nPress Enter to Return to Main Menu...";
	_getch();
	if (position == "Manager" || position == "manager")
	{
		system("cls");
		AdminMenu();
	}
	else
	{
		system("cls");
		StaffMenu();
	}
	

}


//to be displayed in ModifyStock and DeleteStock
void ShowBook()
{
	cout << "Bookshop Stock Management System" << endl;
	cout << "=================================================================";
	cout << "=================================================================";
	cout << "===============";
	cout << "==================================================================" << endl<<endl;


	//execute query
	qstate = mysql_query(conn, "SELECT book.*,inventory.Stock_Quantity,inventory.Receive_Date FROM book LEFT JOIN inventory ON inventory.Book_ID = book.Book_ID");

	cout << setw(7) << "Book ID" << setw(40) << "Book Name" << setw(38) << "Author Name" << setw(30) << "Publisher" << setw(20) << "Date Published" << setw(18) << "Category" << setw(17) << "Price" << setw(17) << "Quantity" << setw(20) << "Date Received " << endl;
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))//loop every row to get data
		{
			cout << setw(6) << row[0] << setw(60) << row[1] << setw(25) << row[2] << setw(25) << row[3] << setw(17) << row[4] << setw(20) << row[5] << setw(12) << "RM " << row[6] << setw(15) << row[7] << setw(18) << row[8] << endl;
		}
	}
}


//to be displayed in SupplyAndOrder
void SupplyList()
{
	cout << "Bookshop Stock Management System" << endl;
	cout << "=================================================================";
	cout << "=================================================================";
	cout << "===============";
	cout << "==================================================================" << endl<<endl;

	qstate =mysql_query(conn, "SELECT supply_list.Supplier_ID,supplier.Supplier_Name,supply_list.Book_ID,book.Book_Name,supply_list.Supply_Price FROM supply_list LEFT JOIN book ON supply_list.Book_ID = book.Book_ID LEFT JOIN supplier ON supply_list.Supplier_ID= supplier.Supplier_ID");
	res = mysql_store_result(conn);

	if (!qstate)
	{
		cout << setw(11) << "Supplier ID" << setw(30) << "Supplier Name" << setw(17) << "Book ID" << setw(40) << "Book Name" << setw(40) << "Supply Price"<<endl;

		while (row = mysql_fetch_row(res))
		{
			cout << setw(8) << row[0] << setw(40) << row[1] << setw(10) << row[2] << setw(60) << row[3] << setw(12) << "RM " << row[4]<<endl;
		}
	}
}


//Add Stock
void AddStock() 
{
	int supplyprice = 0;
	int price = 0;
	int quantity = 0;
	int stock = 0;

	cout << "Bookshop Stock Management System" << endl;
	cout << "=================================================================";
		
	//print option
	cout << "\nAdd Stock :- "<<endl<<endl;
	cout << "1. Add Stock for Existing Book"<<endl;
	cout << "2. Add Stock for New Book" << endl;
	cout << "3. Return to Main Menu" << endl;
	cout << "\nSelect An Option : ";
	cin >> option;

	//option to choose
	switch (option)
	{

		case 1:
		{
			string BookID,NewQuantity,DateReceived;
			cout << "Enter BookID : ";
			cin >> BookID;
			
			//search query to find book based on BookID entered
			string search_query = "SELECT inventory.Book_ID, book.Book_Name, inventory.Stock_Quantity, inventory.Receive_Date FROM inventory LEFT JOIN book ON inventory.Book_ID = book.Book_ID WHERE inventory.Book_ID='" + BookID + "'";
			const char* update = search_query.c_str(); //convert search_query and return to update
			qstate = mysql_query(conn, update);//execute query
			res = mysql_store_result(conn);//store result in res

			if (!qstate)
			{
				if (mysql_num_rows(res)) //check if the BookID entered exist in database
				{
					row = mysql_fetch_row(res); //store data in row
					cout << "Details of the book:-" << endl;
					cout << "\nBook ID : " << row[0] << endl;
					cout << "Book Name : " << row[1] << endl;
					cout << "Quantity : " << row[2] << endl;
					cout << "Date Received : " << row[3] << endl;

					stock = stoi(row[2]);//convert string to integer,stock now store result of Stock_Quantity 

					cout << "\nEnter quantity to be added : ";
					cin >> quantity;

					while (!cin) {
						cout << "\nInvalid Input";
						cout << "\nEnter quantity to be added : ";
						cin.clear();
						cin.ignore(256, '\n');
						cin >> quantity;

					}

					NewQuantity = to_string(stock + quantity); //calculate new quantity
					string update_query = "UPDATE inventory SET Stock_Quantity='" + NewQuantity + "' WHERE Book_ID='" + BookID + "'"; //update query
					const char* StockUpdate = update_query.c_str();//convert update_query and return to StockUpdate
					qstate = mysql_query(conn, StockUpdate);//execute query

					cout << "Enter new date received(YYYY-MM-DD) : ";
					cin.ignore(1, '\n');
					getline(cin, DateReceived);
										
					string update1_query = "UPDATE inventory SET  Receive_Date='" + DateReceived + "' WHERE Book_ID='" + BookID + "'";//update query
					const char* DateUpdate = update1_query.c_str();//convert update1_query and return to DateUpdate
					qstate = mysql_query(conn, DateUpdate);//execute query

					if (!qstate)//notify user if query able/unable to run
						cout << "Successfully updated the stock!" << endl;
					else
						cout << "Failed to update the stock!" << endl;

					//Prompt user to add more stock or return
					cout << "\nDo you want to add another stock?(Y/N): ";
					cin >> choice;
					if (choice == 'Y' || choice == 'y')
					{
						system("cls");
						AddStock();
					}
					else
					{
						//check position of the user and return to the menu
						if (position == "Manager" || position == "manager")
						{
							cout << "Returning to Main Menu." << endl;
							cout << "Press Enter to Continue..." << endl;
							_getch();
							system("cls");
							AdminMenu();
						}
						else
						{
							cout << "Returning to Main Menu." << endl;
							cout << "Press Enter to Continue..." << endl;
							_getch();
							system("cls");
							StaffMenu();
						}
					}
				}
				else //if item does not exist
				{
					cout << "Invalid Book ID." << endl;
					cout << "Do you want to try again? (Y/N)" << endl;
					cin >> choice;

					//prompt user to try again
					if (choice == 'Y' || choice == 'y')
					{
						system("cls");
						AddStock();
					}
					else
					{
						system("cls");
						AdminMenu();
					}
				}

			}
			break;
		}

		case 2:
		{
			string BookID, BookName, AuthorName, Publisher, DatePublished, Category, Price, Quantity, DateReceived, SupplierID, SupplyPrice;

			//promt user to input new item
			cout << "\nInsert new stock" << endl;
			cin.ignore(1, '\n');
			cout << "Enter BookID : ";
			getline(cin, BookID);

			
			cout << "Enter Book Name : ";
			getline(cin, BookName);

			
			cout << "Enter Author Name : ";
			getline(cin, AuthorName);

			
			cout << "Enter Publisher : ";
			getline(cin, Publisher);

			
			cout << "Enter Date Published(YYYY-MM-DD) : ";
			getline(cin, DatePublished);

			
			cout << "Enter Category : ";
			getline(cin, Category);

			cout << "Enter Price : RM ";
			cin >> price;

			while (!cin) {
				cout << "\nInvalid Input";
				cout << "Enter Price : RM ";
				cin.clear();
				cin.ignore(256, '\n');
				cin >> quantity;

			}
			Price = to_string(price);


			cout << "Enter Quantity : ";
			cin >> quantity;

			while (!cin) {
				cout << "\nInvalid Input";
				cout << "\nEnter Quantity : ";
				cin.clear();
				cin.ignore(256, '\n');
				cin >> quantity;

			}
			Quantity = to_string(quantity);

			cin.ignore(1, '\n');
			cout << "Enter Date Received(YYYY-MM-DD) : ";
			getline(cin, DateReceived);

			
			cout << "Enter Supplier ID: ";
			getline(cin, SupplierID);

			
			cout << "Enter Supply Price: RM ";
			cin >> supplyprice;

			while (!cin) {
				cout << "\nInvalid Input";
				cout << "\nEnter Supply Price : RM ";
				cin.clear();
				cin.ignore(256, '\n');
				cin >> supplyprice;

			}
			SupplyPrice = to_string(supplyprice);

			//query to insert new items into book, inventory, supply_list
			string insert_query = "INSERT INTO book (Book_ID, Book_Name, Author_Name, Publisher, Date_Published, Category, Book_Price) VALUES ('" + BookID + "','" + BookName + "','" + AuthorName + "','" + Publisher + "','" + DatePublished + "','" + Category + "','" + Price + "')";
			string insert2_query = "INSERT INTO inventory(Book_ID,Stock_Quantity,Receive_Date) VALUES ('" + BookID + "','" + Quantity + "','" + DateReceived + "')";
			string insert3_query = "INSERT INTO supply_list(Supplier_ID,Book_ID,Supply_Price) VALUES ('" + SupplierID + "','" + BookID + "','" + SupplyPrice + "')";
			const char* insertBook = insert_query.c_str();//convert insert_query and return to insertBook
			const char* insertInventory = insert2_query.c_str();//convert insert2_query and return to insertInventory
			const char* insertSupplyList = insert3_query.c_str();//convert insert3_query and return to insertSupplyList
			qstate = mysql_query(conn, insertBook); //execute query
			qstate = mysql_query(conn, insertInventory); //execute query
			qstate = mysql_query(conn, insertSupplyList); //execute query

			//notify user if query able/unable to run
			if (!qstate)
				cout << "Item successfully added!" << endl;
			else
				cout << "Failed to add item!" << endl;

			//Promt user to add more stock or return 
			cout << "\nDo you want to add another stock?(Y/N): ";
			cin >> choice;
			if (choice == 'Y' || choice == 'y')
			{
				system("cls");
				AddStock();
			}
			else
			{
				//check position of the user and return to the menu
				if (position == "Manager" || position == "manager")
				{
					cout << "Returning to Main Menu." << endl;
					cout << "Press Enter to Continue..." << endl;
					_getch();
					system("cls");
					AdminMenu();
				}
				else
				{
					cout << "Returning to Main Menu." << endl;
					cout << "Press Enter to Continue..." << endl;
					_getch();
					system("cls");
					StaffMenu();
				}
			}
			break;

		}
		
		case 3:
		{
			//check position of the user and return to the menu
			if (position == "Manager" || position == "manager")
			{
				cout << "Returning to Main Menu." << endl;
				cout << "Press Enter to Continue..." << endl;
				_getch();
				system("cls");
				AdminMenu();
			}
			else
			{
				cout << "Returning to Main Menu." << endl;
				cout << "Press Enter to Continue..." << endl;
				_getch();
				system("cls");
				StaffMenu();
			}
			break;
		}

		default:
		{
			if (!cin) {
				cout << "\nInvalid Option";
				cout << "\n**Please Select An Option From 1-3." << endl;
				cout << "Press Enter to Continue...";
				cin.clear();
				cin.ignore(256, '\n');
				_getch();
				system("cls");
				AddStock();

			}
			cout << "\nInvalid Option"<<endl;
			cout << "Please Select An Option From 1-3." << endl;
			cout << "Press Enter to Continue..." << endl;
			_getch();
			system("cls");
			AddStock();
			break;
		}

	}
	



}


//Search book by particular input 
void CheckAvailability()
{
	cout << "Bookshop Stock Management System" << endl;
	cout << "=================================================================";
	string BookName, Category,Quantity;
	int quantity;
	
	//print option
	cout << "\nSearch item by :-" << endl<<endl;
	cout << "1. Book Name \n2. Category \n3. Stock Quantity  \n4. Return to Main Menu"<<endl;
	cout << "\nSelect An Option : ";
	cin >> option;

	switch (option)
	{
		
		case 1:
		{
				cout << "Enter Book Name to be searched (at least 5 characters): ";
				cin.ignore(1, '\n');
				getline(cin, BookName);
				while (BookName.length() <= 3)
				{
					cout << "Enter Book Name to be searched (at least 5 characters): ";
					cin.ignore(1, '\n');
					getline(cin, BookName);

				}
			
			cout << "\n";

			//search query based on BookName
			string search_query = "SELECT book.Book_ID, book.Book_Name, book.Category, book.Book_Price, inventory.Stock_Quantity FROM inventory LEFT JOIN book ON inventory.Book_ID = book.Book_ID WHERE book.Book_Name LIKE '%" + BookName + "%'";
			const char* SearchName = search_query.c_str();//convert search_query and return to SearchName
			qstate = mysql_query(conn, SearchName);//execute query

			if (!qstate)
			{
				cout << setw(7) << "Book ID" << setw(40) << "Book Name" << setw(34) << "Category" << setw(13) << "Price" << setw(14) << "Quantity" << endl;
				res = mysql_store_result(conn);//store result in res
				while (row = mysql_fetch_row(res))//loop every row to get data
				{
				cout << setw(6) << row[0] << setw(60) << row[1] << setw(16) << row[2] << setw(9) << "RM " << row[3] << setw(10) << row[4] << endl;
			
				}	
					
				//Prompt user to add more stock or return
					cout << "\nDo you want to search another stock?(Y/N): ";
					cin >> choice;
					if (choice == 'Y' || choice == 'y')
					{
						system("cls");
						CheckAvailability();						}
					else
					{
						//check position of the user and return to the menu
						if (position == "Manager" || position == "manager")
						{
							cout << "Returning to Main Menu." << endl;								
							cout << "Press Enter to Continue..." << endl;
							_getch();
							system("cls");
							AdminMenu();
						}
						else
						{
							cout << "Returning to Main Menu." << endl;
							cout << "Press Enter to Continue..." << endl;								
							_getch();
							system("cls");
							StaffMenu();
						}
					}
					

				
			



			}
			break;




		}

		case 2:
		{
			cout << "Enter Category to be searched (at least 3 character): ";
			cin.ignore(1, '\n');
			getline(cin, Category);

			while(Category.length()<2){
				cout << "Enter Category to be searched (at least 3 character): ";
				cin.ignore(1, '\n');
				getline(cin, Category);

			}
			cout << "\n";

			//search query based on Category
			string search_query= "SELECT book.Book_ID, book.Book_Name, book.Category, book.Book_Price, inventory.Stock_Quantity FROM inventory LEFT JOIN book ON inventory.Book_ID = book.Book_ID WHERE book.Category LIKE '%" + Category + "%'";
			const char* SearchCategory = search_query.c_str();//convert search_query and return to SearchCategory
			qstate = mysql_query(conn, SearchCategory);//execute query

			if (!qstate)
			{
				cout << setw(7) << "Book ID" << setw(40) << "Book Name" << setw(38) << "Category" << setw(13) << "Price" << setw(14) << "Quantity" << endl;
				res = mysql_store_result(conn);//store result in res
				while (row = mysql_fetch_row(res))//loop every row to get data
				{
					cout << setw(6) << row[0] << setw(60) << row[1] << setw(18) << row[2] << setw(9) << "RM " << row[3] << setw(10) << row[4] << endl;

				}
				//Prompt user to add more stock or return
				cout << "\nDo you want to search another stock?(Y/N)";
				cin >> choice;
				if (choice == 'Y' || choice == 'y')
				{
					system("cls");
					CheckAvailability();
				}
				else
				{
					//check position of the user and return to the menu
					if (position == "Manager" || position == "manager")
					{
						cout << "Returning to Main Menu." << endl;
						cout << "Press Enter to Continue..." << endl;
						_getch();
						system("cls");
						AdminMenu();
					}
					else
					{
						cout << "Returning to Main Menu." << endl;
						cout << "Press Enter to Continue..." << endl;
						_getch();
						system("cls");
						StaffMenu();
					}
				}

			}
			break;
		}

		case 3:
		{		
				cout << "Enter Stock Quantity to be searched : <";
				cin >> quantity;

				//keep looping if input error
				while (!cin) {
					cout << "\nInvalid Input"<<endl;
					cout << "Enter Stock Quantity to be searched : <";
					cin.clear();
					cin.ignore(256, '\n');
					cin >> quantity;

				}
			
			Quantity=to_string(quantity);
			cout <<"\n";
			string search_query= "SELECT book.Book_ID, book.Book_Name, book.Category, book.Book_Price, inventory.Stock_Quantity FROM inventory LEFT JOIN book ON inventory.Book_ID = book.Book_ID WHERE inventory.Stock_Quantity <='"+ Quantity +"' ORDER BY inventory.Stock_Quantity ASC";
			const char* SearchQuantity = search_query.c_str();
			qstate = mysql_query(conn, SearchQuantity);

			if (!qstate)
			{
				cout << setw(7) << "Book ID" << setw(40) << "Book Name" << setw(38) << "Category" << setw(13) << "Price" << setw(14) << "Quantity" << endl;
				res = mysql_store_result(conn);//store result in res
				while (row = mysql_fetch_row(res))//loop every row to get data
				{
					cout << setw(6) << row[0] << setw(60) << row[1] << setw(18) << row[2] << setw(9) << "RM " << row[3] << setw(10) << row[4] << endl;
				}	

				cout << "\n**Items with stock quantity less than 10 are recommended to order." << endl;
				
				if (position == "Manager" || position == "manager")//check position=manager,only manager can order item
				{
					cout << "\nDo you want to order?(Y/N): ";
					cin>>choice;
					if (choice == 'Y' || choice=='y')
					{
						system("cls");
						SupplyAndOrder();
					}
					else
					{
						cout << "\nDo you want to search for another item?(Y/N): ";
						cin >> choice;
						if (choice == 'Y' || choice == 'y')
						{
							system("cls");
							CheckAvailability();

						}
						else
						{
							cout << "Returning to Main Menu." << endl;
							cout << "Press Enter to Continue..." << endl;
							_getch();
							system("cls");
							AdminMenu();
						}
					}
				}
				else
				{
					cout << "Returning to Main Menu." << endl;
					cout << "Press Enter to Continue..." << endl;
					_getch();
					system("cls");
					StaffMenu();
				}
				
				
							
					
					
				
			}	
			break;

		}	

		case 4:
		{
			//check position of the user and return to the menu
			if (position == "Manager" || position == "manager")
			{
				cout << "Returning to Main Menu." << endl;
				cout << "Press Enter to Continue..." << endl;
				_getch();
				system("cls");
				AdminMenu();
			}
			else
			{
				cout << "Returning to Main Menu." << endl;
				cout << "Press Enter to Continue..." << endl;
				_getch();
				system("cls");
				StaffMenu();
			}
			break;
		}

		default:
		{
			if (!cin) {
				cout << "\nInvalid Option";
				cout << "\n**Please Select An Option From 1-4." << endl;
				cout << "Press Enter to Continue...";
				cin.clear();
				cin.ignore(256, '\n');
				_getch();
				system("cls");
				CheckAvailability();

			}
			cout << "\nInvalid Option"<<endl;
			cout << "Please Select An Option From 1-4." << endl;
			cout << "Press Enter to Continue..." << endl;
			_getch();
			system("cls");
			CheckAvailability();
			break;
		}
	}
}


//Delete Stock
void DeleteStock() 
{

	string BookID;
	int quantity;
	system("cls");
	ShowBook();
	cout << "\nPlease Enter Book ID of the item to be deleted: ";
	cin >> BookID;

	//search query based on BookID
	string search_query = "SELECT book.*,inventory.Stock_Quantity,inventory.Receive_Date FROM book LEFT JOIN inventory ON inventory.Book_ID = book.Book_ID WHERE book.Book_ID='" + BookID + "'";
	const char* SearchBook = search_query.c_str();//convert search_query,return to SearchBook
	qstate = mysql_query(conn, SearchBook);//execute query
	res = mysql_store_result(conn);//store result

	if (!qstate)
	{
		if (mysql_num_rows(res))//check if the BookID exist
		{	
			system("cls");
			cout << "Bookshop Stock Management System" << endl;
			cout << "=================================================================";
			cout << "\nItem to be deleted: " << endl<<endl;

			while (row = mysql_fetch_row(res))//loop each row to get data
			{

				cout << "Book ID: " << row[0] << endl;
				cout << "Book Name: " << row[1] << endl;
				cout << "Author Name: " << row[2] << endl;
				cout << "Publisher: " << row[3] << endl;
				cout << "Date Published: " << row[4] << endl;
				cout << "Category: " << row[5] << endl;
				cout << "Price: RM " << row[6] << endl;
				cout << "Stock Quantity: " << row[7] << endl;
				cout << "Date Received: " << row[8] << endl;
				quantity = stoi(row[7]);
			}

			if (quantity != 0) {

				cout << "\nItem quantity is not 0, item cannot be deleted!"<<endl<<endl;
				cout << "Returning to Main Menu." << endl;
				cout << "Press Enter to Continue..." << endl;
				_getch();
				system("cls");
				AdminMenu();

			}
			else {
				cout << "\nAre you sure to delete this item?(Y/N): ";
				cin >> choice;
				if (choice == 'Y' || choice == 'y')
				{
					string delete_query = "DELETE FROM book WHERE Book_ID='" + BookID + "'";
					const char* DeleteBook = delete_query.c_str();
					qstate = mysql_query(conn, DeleteBook);

					if (!qstate)
					{
						cout << "\nItem has been deleted." << endl;
						cout << "Do you want to delete another item?(Y/N): ";
						cin >> choice;

						if (choice == 'Y' || choice == 'y')
						{

							DeleteStock();
						}
						else
						{
							cout << "\nReturning to Main Menu." << endl;
							cout << "Press Enter to Continue..." << endl;
							_getch();
							system("cls");
							AdminMenu();

						}
					}


				}
				else
				{
					cout << "\nReturning to Main Menu." << endl;
					cout << "Press Enter to Continue..." << endl;
					_getch();
					system("cls");
					AdminMenu();

				}
			}
			
			

		}
		else //if item does not exist
		{
			cout << "Invalid Book ID." << endl;
			cout << "Do you want to try again? (Y/N)" << endl;
			cin >> choice;

			//prompt user to try again
			if (choice == 'Y' || choice == 'y')
			{
				system("cls");
				DeleteStock();
			}
			else
			{
				system("cls");
				AdminMenu();
			}
		}

	}



}



//Modify Stock
void ModifyStock() 
{
	int quantity;
	string BookID,NBookID,BookName,AuthorName,Publisher,DatePublished,Category,Price,Quantity,DateReceived;

	system("cls");
	ShowBook();
	cout << "\nEnter Book ID  of the item to be edited: ";
	cin >> BookID;
 
	do
	{
	//search query based on BookID
	string search_query = "SELECT book.*,inventory.Stock_Quantity,inventory.Receive_Date FROM book LEFT JOIN inventory ON inventory.Book_ID = book.Book_ID WHERE book.Book_ID='" + BookID + "'";
	const char* SearchBook = search_query.c_str();//convert search_query,return to SearchBook
	qstate = mysql_query(conn, SearchBook);//execute query
	res = mysql_store_result(conn);//store result

	if (!qstate)
	{
		

		if (mysql_num_rows(res))//check if the BookID exist
		{
			
				system("cls");
				cout << "Bookshop Stock Management System" << endl;
				cout << "=================================================================" << endl;
				cout << "Item to be edited: " << endl << endl;

				while(row=mysql_fetch_row(res))//loop each row to get data
				{ 
			
				cout << "1. Book ID: " << row[0]<<endl;
				cout << "2. Book Name: " << row[1] << endl;
				cout << "3. Author Name: " << row[2] << endl;
				cout << "4. Publisher: " << row[3] << endl;
				cout << "5. Date Published: " << row[4] << endl;
				cout << "6. Category: " << row[5] << endl;
				cout << "7. Price: RM " << row[6] << endl;
				cout << "8. Stock Quantity: " << row[7] << endl;
				cout << "9. Date Received: " << row[8] << endl;
				cout << "0. Return to Main Menu"<<endl;

				}
			
				cout << "\nSelect an option to edit: ";
				cin >> option;

				switch (option)
				{
				case 1 :
				{
				cout << "Enter New Book ID: ";
				cin >> NBookID;

				//update Book_ID 
				string update_query = "UPDATE book SET Book_ID='" + NBookID + "'WHERE Book_ID='" + BookID + "'";
				const char* UpdateBookID = update_query.c_str();//convert update_query, return to UpdateBookID
				mysql_query(conn, UpdateBookID);//execute query
				break;
			}
			
				case 2:
				{
				cout << "Enter New Book Name: ";
				cin.ignore(1,'\n');
				getline(cin, BookName);

				//update Book_Name
				string update_query = "UPDATE book SET Book_Name='" + BookName + "'WHERE Book_ID='" + BookID + "'";
				const char* UpdateBookName = update_query.c_str();//convert update_query, return to UpdateBookName
				mysql_query(conn, UpdateBookName);//execute query
				break;
			}

				case 3:
				{
				cout << "Enter New Author Name: ";
				cin.ignore(1, '\n');
				getline(cin, AuthorName);;

				//update Author_Name
				string update_query = "UPDATE book SET Author_Name='" + AuthorName + "'WHERE Book_ID='" + BookID + "'";
				const char* UpdateAuthorName = update_query.c_str();//convert update_query, return to UpdateAuthorName
				mysql_query(conn, UpdateAuthorName);//execute query
				break;
			}

				case 4:
				{
				cout << "Enter New Publisher: ";
				cin.ignore(1, '\n');
				getline(cin, Publisher);;

				//update Publisher
				string update_query = "UPDATE book SET Publisher='" + Publisher + "'WHERE Book_ID='" + BookID + "'";
				const char* UpdatePublisher = update_query.c_str();//convert update_query, return to UpdatePublisher
				mysql_query(conn, UpdatePublisher);//execute query
				break;
			}
				
				case 5:
				{
				cout << "Enter New Date Published(YYYY-MM-DD): ";
				cin.ignore(1, '\n');
				getline(cin, DatePublished);

				//update Date_Published
				string update_query = "UPDATE book SET Date_Published='" + DatePublished + "'WHERE Book_ID='" + BookID + "'";
				const char* UpdateDatePublished = update_query.c_str();//convert update_query, return to UpdateDatePublished
				mysql_query(conn, UpdateDatePublished);//execute query
				break;
			}

				case 6:
				{
				cout << "Enter New Category: ";
				cin.ignore(1, '\n');
				getline(cin, Category);

				//update Category
				string update_query = "UPDATE book SET Category='" + Category + "'WHERE Book_ID='" + BookID + "'";
				const char* UpdateCategory = update_query.c_str();//convert update_query, return to UpdateCategory
				mysql_query(conn, UpdateCategory);//execute query
				break;
			}

				case 7:
				{
				cout << "Enter New Price: RM ";
				cin.ignore(1, '\n');
				getline(cin, Price);

				//update Book_Price
				string update_query = "UPDATE book SET Book_Price='" + Price + "'WHERE Book_ID='" + BookID + "'";
				const char* UpdatePrice = update_query.c_str();//convert update_query, return to UpdatePrice
				mysql_query(conn, UpdatePrice);//execute query
				break;
			}

				case 8:
				{
					
				cout << "Enter New Quantity: ";
				cin >> quantity;

				//keep looping if error input
				while (!cin){	

						cout << "\nInvalid Input" << endl;
						cin.clear();
						cin.ignore(256, '\n');
						cout << "Enter New Quantity: ";
						cin >> quantity;

					} 

				Quantity = to_string(quantity);

				//update Stock_Quantity
				string update_query = "UPDATE inventory SET Stock_Quantity='" + Quantity + "'WHERE Book_ID='" + BookID + "'";
				const char* UpdateQuantity = update_query.c_str();//convert update_query, return to UpdateQuantity
				mysql_query(conn, UpdateQuantity);//execute query
				break;
			}

				case 9:
				{
				cout << "Enter New Date Received(YYYY-MM-DD): ";
				cin.ignore(1, '\n');
				getline(cin, DateReceived);

				//update Date_Received
				string update_query = "UPDATE inventory SET Date_Received='" + DateReceived + "'WHERE Book_ID='" + BookID + "'";
				const char* UpdateDateReceived = update_query.c_str();//convert update_query, return to UpdateDateReceived
				mysql_query(conn, UpdateDateReceived);//execute query
				break;
			}

				case 0:
				{
				cout << "\nReturning to Main Menu..." << endl;
				cout << "Do you want to modify another item?(Y/N): ";
				cin >> choice;

				if (choice == 'Y' || choice == 'y')
				{
					
					ModifyStock();
				}
				else
				{
					
					cout << "Press Enter to Continue..." << endl;
					_getch();
					AdminMenu();
				}
			}

				default:
				{
					
				cout << "\nInvalid Option"<<endl;
				cout << "Please Select An Option From 0-9."<<endl;
				cout << "Press Enter to Continue..." << endl;
				_getch();
				}

			}
			

		}
		else
		{
			cout << "Invalid BookID entered."<<endl;
			cout << "Do you want to try again?(Y/N): ";
			cin >> choice;

			if (choice == 'Y' || choice == 'y')
			{
				ModifyStock();
			}
			else
			{
				cout << "Returning to Main Menu." << endl;
				cout << "Press Enter to Continue..." << endl;
				_getch();
				AdminMenu();
			}
			
		}
		

		
	}
	}while (true);//keep looping if valid input
}


//Make Order
void SupplyAndOrder() 
{
	cout << "Bookshop Stock Management System" << endl;
	cout << "================================================================="<<endl;
	cout << "1. Show order" << endl;
	cout << "2. Order item " << endl;
	cout << "3. Return to Main Menu " << endl;
	cout << "\nPlease Select An Option : ";
	cin >> option;

	switch (option)
	{
	case 1://show orderlist
	{
		system("cls");
		cout << "Bookshop Stock Management System" << endl;
		cout << "=================================================================";
		cout << "=================================================================";
		cout << "==================================================================" << endl << endl;

		//show order list - GROUP_CONCAT--> group ordered item in 1 row
		qstate = mysql_query(conn, "SELECT tblorder.Order_ID, tblorder.Supplier_ID, tblorder.Staff_ID, GROUP_CONCAT(tblorderlist.Book_ID) AS 'Book_ID', GROUP_CONCAT(tblorderlist.Order_Quantity) AS 'Order_Quantity', tblorder.Order_Date, tblorder.Supply_Date, Total_Price FROM tblorder JOIN tblorderlist ON tblorder.Order_ID = tblorderlist.Order_ID GROUP BY tblorder.Order_ID");
		res = mysql_store_result(conn);

		if (!qstate)
		{
			cout << setw(9) << "Order_ID" << setw(14) << "Supplier_ID" << setw(12) << "Staff_ID" << setw(35) << "Book_ID" << setw(27) << "Order_Quantity" << setw(19) << "Order_Date" << setw(15) << "Supply_Date" << setw(18) << "Total_Price"<<endl;

			while (row = mysql_fetch_row(res))
			{
				cout << setw(9) << row[0] << setw(11) << row[1] << setw(14) << row[2] << setw(40) << row[3] << setw(20) << row[4] << setw(21) << row[5] << setw(15) << row[6] << setw(11) << "RM " << row[7] << endl;
			}
		}

		cout << "\n*The item with supply date 0000-00-00 is the item that have not being received yet."<<endl;
		cout << "\nPress Enter to Return to Menu...";
		_getch();
		system("cls");
		SupplyAndOrder();
		break;

	}

	case 2: //order item
	{
		string BookID;
		system("cls");
		SupplyList();
		cout << "\nEnter Book ID : ";
		cin >> BookID;

		//search query based on BookID 
		string search_query = "SELECT supply_list.Supplier_ID,supplier.Supplier_Name,supply_list.Book_ID,book.Book_Name,supply_list.Supply_Price FROM supply_list LEFT JOIN book ON supply_list.Book_ID = book.Book_ID LEFT JOIN supplier ON supply_list.Supplier_ID= supplier.Supplier_ID WHERE supply_list.Book_ID='" + BookID + "' ";
		const char* SearchBookID = search_query.c_str();//convert search_query,return to SearchBookID
		qstate = mysql_query(conn, SearchBookID);//execute query
		res = mysql_store_result(conn);//store result in res

		if (!qstate)
		{

			int quantity;
			double price;

			string  OrderID, SupplierID, OrderDate, SupplyDate, TotalPrice, Quantity;

			if (mysql_num_rows(res))//check if item exist
			{
				system("cls");
				row = mysql_fetch_row(res);//get data

				cout << "Bookshop Stock Management System" << endl;
				cout << "=================================================================" << endl;
				cout << "Details of the item to be ordered : " << endl<<endl;
				cout << "Supplier ID : " << row[0] << endl;
				cout << "Supplier Name : " << row[1] << endl;
				cout << "Book ID : " << row[2] << endl;
				cout << "Book Name : " << row[3] << endl;
				cout << "Supply Price : " << row[4] << endl;

				BookID = row[2];
				price = stoi(row[4]);//convert string to integer
				SupplierID = row[0];

				
				cout << "\nEnter quantity to be ordered : ";
				cin >> quantity;
				 
				while (!cin){
				cout << "\nInvalid Input";
				cout << "\nEnter quantity to be ordered : ";
				cin.clear();
				cin.ignore(256, '\n');
				cin >> quantity;

				} 

				Quantity = to_string(quantity);

				cout << "Enter OrderDate(YYYY-MM-DD) : ";
				cin.ignore(1, '\n');
				getline(cin, OrderDate);



				TotalPrice = to_string(quantity * price);//calculate total price


				string insert_query = "INSERT INTO tblorder (Order_ID, Supplier_ID, Staff_ID, Order_Date, Supply_Date, Total_Price) VALUES ('NULL','" + SupplierID + "', '" + StaffID + "','" + OrderDate + "','NULL','" + TotalPrice + "')";
				string insert2_query = "INSERT INTO tblorderlist(Order_ID, Book_ID, Order_Quantity) VALUES ('NULL','" + BookID + "','" + Quantity + "')";
				const char* InsertOrder = insert_query.c_str();
				const char* InsertOrderList = insert2_query.c_str();
				qstate = mysql_query(conn, InsertOrder);
				qstate = mysql_query(conn, InsertOrderList);


				if (!qstate)
				{
					cout << "Order successful!" << endl;
					cout << "Do you want to order another item?(Y/N): ";
					cin >> choice;

					if (choice == 'Y' || choice == 'y')
					{
						system("cls");
						SupplyAndOrder();
					}
					else
					{
						cout << "Returning to Main Menu." << endl;
						cout << "Press Enter to Continue..." << endl;
						_getch();
						AdminMenu();
					}

				}
				else
				{
					cout << "Order Failed!" << endl;
					cout << "Do you want to order another item?(Y/N): ";
					cin >> choice;

					if (choice == 'Y' || choice == 'y')
					{
						system("cls");
						SupplyAndOrder();
					}
					else
					{
						cout << "Returning to Admin Menu." << endl;
						cout << "Press Enter to Continue..." << endl;
						_getch();
						AdminMenu();
					}

				}



			}
			else
			{
				cout << "Invalid BookID entered." << endl;
				cout << "Do you want to try again?(Y/N): ";
				cin >> choice;

				if (choice == 'Y' || choice == 'y')
				{
					system("cls");
					SupplyAndOrder();
				}
				else
				{
					cout << "Returning to Admin Menu." << endl;
					cout << "Press Enter to Continue..." << endl;
					_getch();
					AdminMenu();
				}

			}


		}
		break;

	}

	case 3:
	{
		cout << "\nReturning to Main Menu." << endl;
		cout << "Press Enter to Continue..." << endl;
		_getch();
		system("cls");
		AdminMenu();
		break;
	}

	default:
	{
		if (!cin) {
			cout << "\nInvalid Option";
			cout << "\n**Please Select An Option From 1-3." << endl;
			cout << "Press Enter to Continue...";
			cin.clear();
			cin.ignore(256, '\n');
			_getch();
			system("cls");
			SupplyAndOrder();

		}
		cout << "\nInvalid Option"<<endl;
		cout << "Please Select From 1-3" << endl;
		cout << "Press Enter to Continue..." << endl;
		_getch();
		system("cls");
		SupplyAndOrder();
		break;
	}



	}

	
	
									
			
					

			
		

		



}


//show summary
void ShowSummary() 
{
	
	cout << "Bookshop Stock Management System" << endl;
	cout << "=================================================================" << endl;
	cout << "1. Show cost of monthly order from supplier" << endl;
	cout << "2. Show total cost ordered from different supplier" << endl;
	cout << "3. Show profit of each book" << endl;
	cout << "4. Return to Main Menu" << endl;

	cout << "\nPlease Select An Option : ";
	cin >> option;

	switch (option)
	{
	case 1:
	{
		system("cls");
		cout << "Bookshop Stock Management System" << endl;
		cout << "=================================================================";
		cout << "=================================================================";
		cout << "=================================================================" << endl;
		cout << "\n";

		//Start of table
		for (int i = 0; i < 158; i++)
		{
			cout << "_";
		}
		cout << endl;
		cout << "|" << setw(15) << "Supplier" << setw(15) << "|" << setw(60) << " Cost of Monthly order (RM) " << setw(67) << "|" << endl;

		for (int i = 0; i < 155; i++)
		{
			if (i == 0 || i == 29)
			{
				cout << "|";
			}

			cout << "_";
		}
		cout << "|" << endl;

		cout << "|" << setw(30) << "|";
		cout << setw(10) << "January |" << setw(10) << "February |" << setw(10) << "March |" << setw(10) << "April |" << setw(10) << "May |" << setw(10) << "June |" << setw(10) << "July |" << setw(10) << "August |" << setw(13) << "September |" << setw(10) << "October |" << setw(12) << "November |" << setw(12) << "December |" << endl;

		for (int i = 0; i < 144; i++)
		{
			if (i == 0 || i == 29 || i == 38 || i == 47 || i == 56 || i == 65 || i == 74 || i == 83 || i == 92 || i == 101 || i == 113 || i == 122 || i == 133)
			{
				cout << "|";
			}



			cout << "_";
		}
		cout << "|" << endl;

		//query for fetching data-COALESCE(,0)--->set NULL to 0
		qstate = mysql_query(conn, "SELECT Supplier_ID , COALESCE(SUM(CASE WHEN month = 1 THEN Total_Price END),0) January , COALESCE(SUM(CASE WHEN month = 2 THEN Total_Price END),0) February , COALESCE(SUM(CASE WHEN month = 3 THEN Total_Price END),0) March , COALESCE(SUM(CASE WHEN month = 4 THEN Total_Price END),0)April , COALESCE(SUM(CASE WHEN month = 5 THEN Total_Price END),0) May , COALESCE(SUM(CASE WHEN month = 6 THEN Total_Price END),0) June , COALESCE(SUM(CASE WHEN month = 7 THEN Total_Price END),0) July , COALESCE(SUM(CASE WHEN month = 8 THEN Total_Price END),0) August , COALESCE(SUM(CASE WHEN month = 9 THEN Total_Price END),0) September , COALESCE(SUM(CASE WHEN month = 10 THEN Total_Price END),0) October , COALESCE(SUM(CASE WHEN month = 11 THEN Total_Price END),0) November , COALESCE(SUM(CASE WHEN month = 12 THEN Total_Price END),0) December FROM (SELECT tblorder.* , EXTRACT(MONTH FROM Order_Date) month FROM tblorder ) tblorder GROUP BY Supplier_ID");
		
		//body table
		if (!qstate)
		{
			
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				cout << "|"<<setw(21) << row[0]<<setw(9)<<"|" << setw(9) << row[1]<<"|" << setw(9) << row[2] <<"|"<< setw(9) << row[3]<<"|" << setw(9) << row[4]<<"|" << setw(9) << row[5]<<"|" << setw(9) << row[6]<<"|" << setw(9) << row[7]<<"|" << setw(9) << row[8]<<"|" << setw(12) << row[9] <<"|"<< setw(9) << row[10]<<"|" << setw(11) << row[11]<<"|" << setw(11) << row[12] <<"|"<< endl;
			}

			
		}
		for (int i = 0; i < 144; i++)
		{
			if (i == 0 || i == 29 || i == 38 || i == 47 || i == 56 || i == 65 || i == 74 || i == 83 || i == 92 || i == 101 || i == 113 || i == 122 || i == 133)
			{
				cout << "|";
			}



			cout << "_";
		}
		cout << "|" << endl;
		//endl of table

		cout << "\n\n";
		cout << "Supplier:" << endl;		
		cout << "P42372 - Horizon Books Sdn Bhd" << endl;
		cout << "P69453 - Basheer Graphic Books Sdn Bhd" << endl;
		cout << "P77382 - Metro Book Distributor" << endl;

		cout << "\nPress Enter to Return to Menu";
		_getch();
		system("cls");
		ShowSummary();
		break;
	}

	case 2:
	{
		double TotalPrice;
		int bar = 0;
		system("cls");
		cout << "Bookshop Stock Management System" << endl;
		cout << "=================================================================" << endl;

		//execute query
		qstate =mysql_query(conn, "SELECT tblorder.Supplier_ID, supplier.Supplier_Name, SUM(tblorder.Total_Price)AS Total_Price FROM tblorder LEFT JOIN supplier ON tblorder.Supplier_ID = supplier.Supplier_ID  GROUP BY supplier.Supplier_Name");
		
		if (!qstate)
		{
			res = mysql_store_result(conn);//store result
			
			while (row = mysql_fetch_row(res))//fetch data
			{
				cout << endl << endl;
				cout << setw(10) << row[0]<<"  ";//print out Supplier ID
				TotalPrice = atof(row[2]);//convert string to double
				bar = TotalPrice / 150;//set 1 bar = RM500
				ColorCode(255);//change colour of the text to produce white bar

				for (int i = 0; i < bar; i++)//1st loop to produce white bar
				{
					cout << "|";//white bar
				}
				cout << endl;
				
				ColorCode(7);
				cout << setw(12)<<"            " ;//space
				ColorCode(255);

				for (int i = 0; i < bar; i++)//2nd loop to make white bar wider
				{									
						cout << "|";//white bar								
				}

				ColorCode(7);
				cout << " RM " <<fixed <<setprecision(2)<< TotalPrice;
			}

			cout << "\n\nX-axis: Total price of the order over the year"<<endl;
			cout << "Y-axis: Supplier" << endl;
			cout << "-----------------------------------------------------------------------------------------------------------" << endl;
			cout << "\nLegend:"<<endl;
			cout << "P42372- Horizon Books Sdn Bhd" << endl;
			cout << "P69453- Basheer Graphic Books Sdn Bhd" << endl;
			cout << "P77382- Metro Book Distributor" << endl;


			cout << "\nPress Enter to Return to Menu";
			_getch();
			system("cls");
			ShowSummary();
			break;
			
			
		}
		else
		{
			cout << "Query error";
		}
	}	

	case 3:
	{

		system("cls");
		cout << "Bookshop Stock Management System" << endl;
		cout << "=================================================================";
		cout << "=================================================================";
		cout << "=================================================================" << endl<<endl;

		//execute query to show profit
		qstate = mysql_query(conn, "SELECT book.Book_ID,book.Book_Name, book.Book_Price, supply_list.Supply_Price,(book.Book_Price-supply_list.Supply_Price) AS Profit FROM book LEFT JOIN supply_list ON supply_list.Book_ID = book.Book_ID");
		
		cout << setw(10) << "Book ID" << setw(45) << "Book Name" << setw(40) << "Selling Price Per Unit" << setw(27) << "Supply Price Per Unit" << setw(20) << "Profit Per Unit"<<endl;//add total Profit

		if (!qstate)
		{
			res = mysql_store_result(conn);//store result in res

			while (row = mysql_fetch_row(res))//loop every row to get data
			{
				cout << setw(10) << row[0] << setw(60) << row[1] << setw(15) << "RM "<<row[2] << setw(20)<<"RM " << row[3] << setw(19) <<"RM "<< row[4]<<endl;
			}


		}

		cout << "\nPress Enter to Return to Menu";
		_getch();
		system("cls");
		ShowSummary();
		break;
	}

	case 4:
	{
		cout << "\nReturning to Main Menu." << endl;
		cout << "Press Enter to Continue..." << endl;
		_getch();
		system("cls");
		AdminMenu();
		break;
	}

	default:
	{
		if (!cin) {
			cout << "\nInvalid Option";
			cout << "\n**Please Select An Option From 1-3." << endl;
			cout << "Press Enter to Continue...";
			cin.clear();
			cin.ignore(256, '\n');
			_getch();
			system("cls");
			ShowSummary();

		}
		cout << "\nInvalid Option"<<endl;
		cout << "Please Select From 1-3" << endl;
		cout << "Press Enter to Continue..." << endl;
		_getch();
		system("cls");
		ShowSummary();
		break;
	}





	}
	
	


}


//change colour of the text
void ColorCode(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}