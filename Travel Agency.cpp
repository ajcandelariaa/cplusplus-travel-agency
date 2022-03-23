#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <windows.h>	
#include <cstdlib>
#include <ctime>
#include <string>


using namespace std;

string month_name[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

time_t t = time(NULL);
tm* timePtr = localtime(&t);
int real_second = timePtr->tm_sec;
int real_minute = timePtr->tm_min;
int real_hour = timePtr->tm_hour;
int real_day = timePtr->tm_mday;
int real_month = (timePtr->tm_mon)+1;
int real_year = (timePtr->tm_year)+1900;

void header()
{
	cout << "==========================================" << endl;
	cout << "    MAI OTOME A TRAVEL AGENCY SYSTEM" << endl ;
	cout << "==========================================" << endl<< endl << endl << endl;
}

void disp_choice()
{
	cout << "Enter your choice: ";
}

void menu()
{
	header();
	cout << "\t   MAIN MENU" << endl << endl;
	cout << "---------------------------------" << endl;
	cout << "|\t[1] Tour Packages\t|" << endl; 
	cout << "|\t[2] Local Travel\t|" << endl; 
	cout << "|\t[0] Exit\t\t|" << endl; 
	cout << "---------------------------------" << endl << endl;
}

void local_travel_menu()
{
	header();
	cout <<"\t     LOCAL TRAVEL" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "|\t[1] List of Local Flights\t|" << endl; 
	cout << "|\t[2] Add Local Flights\t\t|" << endl; 
	cout << "|\t[3] Delete Local Flights\t|" << endl; 
	cout << "|\t[4] Transaction\t\t\t|" << endl; 
	cout << "|\t[R] Return\t\t\t|" << endl;
	cout << "|\t[0] Exit\t\t\t|" << endl;
	cout << "-----------------------------------------" << endl << endl;
	disp_choice();
}

void transaction_menu()
{
	cout << "===============================" << endl;
	cout <<"        TRANSACTION" << endl;
	cout << "===============================" << endl;
	cout << "[1] Book a flight" << endl;
	cout << "[2] View Transaction" << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	cout << "Choice: ";
}

void list_of_airports()
{
	string city, airport, number;
	int x = 0;
	cout << "======================================================" << endl;
	cout << "           LIST OF DOMESTIC AIRPORTS IN JAPAN" << endl;
	cout << "======================================================" << endl;
	ifstream data_city("Local Travel\\city.txt");
	ifstream data_airport("Local Travel\\airport.txt");
	ifstream data_number("Local Travel\\number.txt");
	while(getline(data_number, number) && getline(data_city, city) && getline(data_airport, airport))
	{
		cout << "[" << number << "] " <<  city << " - " <<  airport << endl;
		x++;
	}
	data_city.close(); data_airport.close(); data_number.close();
	if(x == 0)
	{
		cout << "NO AIRLINES LISTED" << endl;
	}
}


int check_numbers(char x[])
{
	for(int i=0; i<strlen(x); i++)
	{
		if(x[i] != '1' && x[i] != '2' && x[i] != '3' && x[i] != '4' && x[i] != '5' && x[i] != '6' && x[i]!= '7' && x[i] != '8' && x[i] != '9' && x[i] != '0')
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}



float function_price (string arrival_name, string departure_name, int month, int day, int year)
{
	float anumber, dnumber;
	float temp_multiplier;
	string t_depname, t_arrname;
	float fixed_price = 26831;
	float travel_tax = 0.32;
	float env_fee = 536;
	float temp_total, temp_total2;
	float senior_discount;
	float id;
	
	ifstream f_number("Local Travel\\number.txt");
	ifstream f_city("Local Travel\\city.txt");
	
	//Travel Tax = 32%
	//Insurance = 5% to 12% upon selection
	//Environmental fee = 5 USD
	//Discounts - Senior Citizen - 12%
	
	//Senior Citizen Discount
	
	//june 2 1959   june 22 2019
	if(year <= real_year)
	{
			if((real_year - year) == 60)
			{
				if(month < real_month)
				{
					senior_discount = .12;
				}
				else if(month == real_month)
				{
					if(day <= real_day)
					{
						senior_discount = .12;
					}
					else
					{
						senior_discount = 0;
					}
				}
				else
				{
					senior_discount = 0;
				}
			}
			else if((real_year - year) > 60)
			{
				senior_discount = .12;
			}
			else
			{
				senior_discount = 0;
			}
	}
	else
	{
		senior_discount = 0;
	}
	
	while(f_number >> id && getline(f_city, t_depname))
	{
		if(departure_name == t_depname)
		{
			dnumber = id;
		}
	}
	
	while(f_number >> id && getline(f_city, t_arrname))
	{
		if(arrival_name == t_arrname)
		{
			anumber = id;
		}
	}
	f_number.close(); f_city.close();
	
	if(dnumber > anumber)
	{
		temp_multiplier = dnumber - anumber;
	}
	if(anumber > dnumber)
	{
		temp_multiplier = anumber - dnumber;	
	}
	float t_insurance;
	if(temp_multiplier == 1) {	t_insurance = .05;	}
	if(temp_multiplier == 2) {	t_insurance = .06;	}
	if(temp_multiplier == 3) {	t_insurance = .07;	}
	if(temp_multiplier == 4) {	t_insurance = .08;	}
	if(temp_multiplier == 5) {	t_insurance = .09;	}
	if(temp_multiplier == 6) {	t_insurance = .10;	}
	if(temp_multiplier == 7) {	t_insurance = .11;	}
	if(temp_multiplier >= 8) {	t_insurance = .12;	}
	
	float temp_env, temp_travel_tax, temp_insurance;
	temp_total = fixed_price * temp_multiplier;
	temp_travel_tax = temp_total * travel_tax; //.32   //8585
	temp_insurance = temp_total * t_insurance;
	
	float tax_env_total;
	tax_env_total = temp_total + env_fee + temp_travel_tax + temp_insurance; //kulang pa insurance dito, 536
	float overall_total;
	overall_total = tax_env_total - (tax_env_total * senior_discount); //.12 or 1
				printf("--------------------------------------------------------------\n");
				printf("| %-18s | %-38f |\n", "Price: ", temp_total);
				printf("| %-18s | %-38f |\n", "Travel Tax: ", temp_travel_tax);
				printf("| %-18s | %-38f |\n", "Insurance: ", temp_insurance);
                printf("--------------------------------------------------------------\n");
				printf("| %-18s | %-38f |\n", "Total Tax: ", tax_env_total);
				printf("| %-18s | %-38f |\n", "Senior Discount: ", senior_discount);
				printf("| %-18s | %-38f |\n", "Total Price: ", overall_total);
                printf("--------------------------------------------------------------\n");
	return overall_total;
}

int local_travel_booking_oneway()
{
		ifstream count_users("Local Travel\\Transactions\\One way\\id.txt");
		int add_id, latest_id = 0;	//VARIABLE
		while(count_users >> add_id)
		{
			latest_id = add_id;
		}
		count_users.close();
		
		ifstream count_t_number("Local Travel\\Transactions\\One way\\ticketnumber.txt");
		int temp_t, latest_ticket_num=0;  //VARIABLE
		while(count_t_number >> temp_t)
		{
			latest_ticket_num = temp_t;
		}
		if(latest_ticket_num == 0)
		{
			latest_ticket_num = 532;
		}
		count_t_number.close();
		
		ifstream count_f_number("Local Travel\\Transactions\\One way\\flightnumber.txt");
		int temp_fl, latest_flight_num=0;	//VARIABLE
		while(count_f_number >> temp_fl)
		{
			latest_flight_num = temp_fl;
		}
		if(latest_flight_num == 0)
		{
			latest_flight_num = 7023;
		}
		count_f_number.close();
		
		cout << endl << endl;
		list_of_airports();
		cout << "[R] Return" << endl;
		cout << "[0] Exit" << endl;
		cout << endl << "PASSENGER/S TRANSACTION SLIP" << endl;
		
		//VARIABLE
		string dep_choice, arrival_choice;
		string temp_num, temp_city, temp_num2, temp_city2;
		string latest_city, latest_city2;
		int temp11, temp21;
		int k=0;
		cin.ignore();
	do
	{
		cout << "Enter Departure Location: ";
		getline(cin, dep_choice);
		if(dep_choice[0] == 'R' || dep_choice[0] == 'r') { system("cls"); return 9;	}
		if(dep_choice[0] == '0') { exit(0);	}
		if(dep_choice[0] == ' ') { temp11 = 1;	}
		
		ifstream check_num("Local Travel\\number.txt");
		ifstream check_city("Local Travel\\city.txt");
		while(getline(check_num, temp_num) && getline(check_city, temp_city))
		{
			if(dep_choice == temp_num)
			{
				latest_city = temp_city;
				temp11 = 1;
			}
		}
		check_num.close(); check_city.close();
		if(dep_choice[0] == ' ') { temp11 = 0;	}
		if (temp11 != 1) { cout << "Invalid Input! Try again" << endl;	}
	} while (temp11 != 1);
	
	do
	{
		do
		{
			cout << "Enter Arrival Location: ";
			getline(cin, arrival_choice);
			if(arrival_choice[0] == 'R' || arrival_choice[0] == 'r') { system("cls"); return 9;	}
			if(arrival_choice[0] == '0') { exit(0);	}
			if(arrival_choice[0] == ' ') { temp21 = 1;	}
			
			ifstream check_num("Local Travel\\number.txt");
			ifstream check_city("Local Travel\\city.txt");
			while(getline(check_num, temp_num2) && getline(check_city, temp_city2))
			{
				if(arrival_choice == temp_num2)
				{
					latest_city2 = temp_city2;
					temp21 = 1;
				}
			}
			check_num.close(); check_city.close();
			if(arrival_choice[0] == ' ') { temp21 = 0;	}
			if (temp21 != 1) { cout << "Invalid Input! Try again" << endl;	}
		} while (temp21 != 1);
		if(arrival_choice == dep_choice) { cout << "Please do not enter the same city" << endl; 	}
	} while(arrival_choice == dep_choice);
	
	
	int arr, dep, pricee = 20000;	//VARIABLE
	istringstream(arrival_choice) >> arr;
	istringstream(dep_choice) >> dep;
	
	cout << endl;
	cout << "======================" << endl;
	cout << "   " << latest_city << " to " << latest_city2 << endl;
	cout << "======================" << endl << endl;
	
	int temp1, temp2, temp3, temp4, month, day, year, day_loop, hm_passengers, x = 0;	//VARIABLE
	
	do
	{
		do
		{
			do
			{
				do
				{	
					char t_month[20], t_day[20], t_year[20];	//VARIABLE
					cout << endl << "One Way" << endl;
					cout << "Departure Date: " << endl;
					cout << "(e.g   5  18  2019)" << endl; 
					cout << "Month: ";
					cin.getline(t_month, 20);
					temp1 = check_numbers(t_month);
					cout << "Day: ";
					cin.getline(t_day, 20);
					temp2 = check_numbers(t_day);
					cout << "Year: ";
					cin.getline(t_year, 20);
					temp3 = check_numbers(t_year);
						if (temp1 == 1 || temp2 == 1 || temp3 == 1)
						{
							cout << "Invalid Input! Please enter the correct date!" << endl;
						}
						else
						{	
							istringstream(t_month) >> month;	
							istringstream(t_day) >> day;
							istringstream(t_year) >> year;
						}
				} while (temp1 == 1 || temp2 == 1 || temp3 == 1);		
				
				if(year < real_year || year > 2050)
				{
					cout << "Year not accepted. Please enter the correct Year!" << endl;
				}
				
			} while(year < real_year || year > 2050);
				
				if(year == real_year && month < real_month)
				{
					cout << "Month not accepted. Please enter the correct Month!" << endl;
					x=0;
				}
				else if(year == real_year && month == real_month && day < real_day)
				{
					cout << "Day not accepted. Please enter the correct Day!" << endl;
					x=0;
				}
				else
				{
					x = 1;
				}
		}  while(x == 0);
				if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				{
					if(day < 1 || day > 31)
					{
						cout << "Day not accepted. Please enter the correct Day!" << endl;
						day_loop = 1;
					} else {  day_loop = 0; 	}
				}
				if (month == 4 || month == 6 || month == 9 || month == 11)
				{
					if(day < 1 || day > 30)
					{
						cout << "Day not accepted. Please enter the correct Day!" << endl;
						day_loop = 1;
					} else {  day_loop = 0; 	}
				}
				if(month == 2)
				{
					if((year % 4) == 0)
					{
						if(day < 1 || day > 29)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop = 1;
						} else {  day_loop = 0; 	}
					}
					else
					{
						if(day < 1 || day > 28)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop = 1;
						} else {  day_loop = 0; 	}
					}
				}
			} while (day_loop == 1);
			
			srand(time(0));
			
			char time_choice;
			int random_time_dep, random_time_arr;
			int add_day = 0;
			cout << endl << endl;
			cout << "Choose Time" << endl;
			cout << "[1] AM" << endl;
			cout << "[2] PM" << endl;
			cout << "Choice: ";
			cin >> time_choice;
			if(time_choice == '1') 
			{ 
				random_time_dep = rand() % 12;	
				random_time_arr = random_time_dep + 2;
			}
			if(time_choice == '2') 
			{ 
				random_time_dep = 12 + rand() % 13;	
				if (random_time_dep == 23)
				{
					random_time_arr = 0;
					add_day = 1;
				}
				if (random_time_dep == 24)
				{
					random_time_arr = 1;
					add_day = 1;
				}
				if(random_time_dep != 23 && random_time_dep != 24)
				{
					random_time_arr = random_time_dep + 2;
					add_day = 0;
				}
			}
			cout << endl;
			cout << endl;
			
			// VARIABLE
			string temp_dep, temp_arr;
			int temp_seat, seats = 0, tfnumber;
			int tday, tmonth, tyear;
			int add_seats, same_fnumber;
			int dtime, atime;
			ifstream check_dep("Local Travel\\Transactions\\departure.txt");
			ifstream check_arr("Local Travel\\Transactions\\arrival.txt");
			ifstream check_seats("Local Travel\\Transactions\\seats.txt");
			ifstream check_fnumber("Local Travel\\Transactions\\fnumber.txt");
			ifstream check_day("Local Travel\\Transactions\\day.txt");
			ifstream check_month("Local Travel\\Transactions\\month.txt");
			ifstream check_year("Local Travel\\Transactions\\year.txt");
			ifstream check_dtime("Local Travel\\Transactions\\arrtime.txt");
			ifstream check_atime("Local Travel\\Transactions\\deptime.txt");
			while(getline(check_dep, temp_dep) && getline(check_arr, temp_arr) && check_seats >> temp_seat
							&& check_day >> tday && check_month >> tmonth && check_year >> tyear && check_fnumber >> tfnumber
							&& check_dtime >> dtime && check_atime >> atime)
			{
				if(latest_city == temp_dep && latest_city2 == temp_arr && month == tmonth && year == tyear && day == tday
					&& random_time_dep == dtime)
				{
					if((hm_passengers - temp_seat) < 60 || (hm_passengers - temp_seat) >= 0 )
					{
						add_seats = temp_seat;
						same_fnumber = tfnumber;
						k = 1;
					}
				}
			}
			check_dep.close(); check_arr.close(); check_seats.close(); check_fnumber.close();
			check_day.close(); check_month.close(); check_year.close(); check_dtime.close(); check_atime.close();
			
			cout << "Departure date & time: " << month_name[month-1] << " " << day << " " << year << " (" << random_time_dep << ":00) " << endl;
			cout << "Arrival date & time: " << month_name[month-1] << " " << day+add_day << " " << year << " (" << random_time_arr << ":00) " << endl;
			cin.ignore();
			do
			{
				do
				{
					char t_hm_passengers[10];
					cout << "How many passengers: ";
					cin.getline(t_hm_passengers, 10);
					temp4 = check_numbers(t_hm_passengers);
					if(temp4 == 1)
					{
						cout << "Invalid input! Please enter the correct number!" << endl;
					}
					else
					{
						istringstream(t_hm_passengers) >> hm_passengers;
					}
				} while(temp4 == 1 );
				if(hm_passengers < 1 || hm_passengers > 10)
				{
					cout << "Only 1 - 10 passengers can be book at a time." << endl;
					temp4 = 1;
				}	
				else
				{
					temp4 = 0;
				}
			} while(temp4 == 1);
			
			// VARIABLE
			char fullname[60], gender;
			char t_month1[20], t_day1[20], t_year1[20];
			float overall_price = 0.0;
			
			for(int i=0; i<hm_passengers; i++)
			{
				cout << endl << "Passenger [" << i+1 << "]" << endl;
				cout << "Fullname: ";
				cin.getline(fullname, 60);
				do
				{	
					cout << "Gender[M/F]: ";
					cin >> gender;
					if(toupper(gender) != 'M' && toupper(gender) != 'F')
					{
						cout << "Invalid Input! Please enter correctly" << endl;
					}
				} while (toupper(gender) != 'M' && toupper(gender) != 'F');
				
				int temp1_2, temp2_2, temp3_2, month2, day2, year2, day_loop2, y=0;
				cin.ignore();
				do
				{
					do
					{
						do
						{
							do
							{	
								char t_month2[20], t_day2[20], t_year2[20];
								cout << "Birthdate: " << endl;
								cout << "(e.g   5  18  2019)" << endl; 
								cout << "Month: ";
								cin.getline(t_month2, 20);
								temp1_2 = check_numbers(t_month2);
								cout << "Day: ";
								cin.getline(t_day2, 20);
								temp2_2 = check_numbers(t_day2);
								cout << "Year: ";
								cin.getline(t_year2, 20);
								temp3_2 = check_numbers(t_year2);
								if (temp1_2 == 1 || temp2_2 == 1 || temp3_2 == 1)
								{
									cout << "Invalid Input! Please enter the correct date!" << endl;
								}
								else
								{	
									istringstream(t_month2) >> month2;	
									istringstream(t_day2) >> day2;
									istringstream(t_year2) >> year2;
								}
							} while (temp1_2 == 1 || temp2_2 == 1 || temp3_2 == 1);
						
							if(year2 < 1900 || year2 >= 2019)
							{
								cout << "Year not accepted. Please enter the correct Year!" << endl;
							}
						} while(year2 < 1900 || year2 >= 2019);
						if(month2 < 1 || month > 12)
						{
							cout << "Month not accepted. Please enter the correct month!" << endl;
						}
					} while (month < 1 || month > 12);
					if (month2 == 1 || month2 == 3 || month2 == 5 || month2 == 7 || month2 == 8 || month2 == 10 || month2 == 12)
					{
						if(day2 < 1 || day2 > 31)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop2 = 1;
						} else {  day_loop2 = 0; 	}
					}
					if (month2 == 4 || month2 == 6 || month2 == 9 || month2 == 11)
					{
						if(day2 < 1 || day2 > 30)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop2 = 1;
						} else {  day_loop2 = 0; 	}
					}
					if(month2 == 2)
					{
						if((year2 % 4) == 0)
						{
							if(day2 < 1 || day2 > 29)
							{
								cout << "Day not accepted. Please enter the correct Day!" << endl;
								day_loop2 = 1;
							} else {  day_loop2 = 0; 	}
						}
						else
						{
							if(day2 < 1 || day2 > 28)
							{
								cout << "Day not accepted. Please enter the correct Day!" << endl;
								day_loop2 = 1;
							} else {  day_loop2 = 0; 	}
						}
					} 
				} while (day_loop2 == 1);
				cout << "Birthday: " << month_name[month2-1] << " " << day2 << " " << year2 << endl;
				float total_price;
				total_price = function_price(latest_city2, latest_city, month2, day2, year2);
				overall_price += total_price;
				
				ofstream input_id("Local Travel\\Transactions\\One way\\id.txt" , ios::out | ios::app);
				ofstream input_arrival("Local Travel\\Transactions\\One way\\arrival.txt" , ios::out | ios::app);
				ofstream input_dep("Local Travel\\Transactions\\One way\\departure.txt" , ios::out | ios::app);
				ofstream input_fullname("Local Travel\\Transactions\\One way\\fullname.txt" , ios::out | ios::app);
				ofstream input_gender("Local Travel\\Transactions\\One way\\gender.txt" , ios::out | ios::app);
				ofstream input_month("Local Travel\\Transactions\\One way\\month.txt" , ios::out | ios::app);
				ofstream input_year("Local Travel\\Transactions\\One way\\year.txt" , ios::out | ios::app);
				ofstream input_day("Local Travel\\Transactions\\One way\\day.txt" , ios::out | ios::app);
				ofstream input_month1("Local Travel\\Transactions\\One way\\month1.txt" , ios::out | ios::app);
				ofstream input_year1("Local Travel\\Transactions\\One way\\year1.txt" , ios::out | ios::app);
				ofstream input_day1("Local Travel\\Transactions\\One way\\day1.txt" , ios::out | ios::app);
				ofstream input_birthday("Local Travel\\Transactions\\One way\\birthday.txt" , ios::out | ios::app);
				ofstream input_ticknum("Local Travel\\Transactions\\One way\\ticketnumber.txt" , ios::out | ios::app);
				ofstream input_flightnum("Local Travel\\Transactions\\One way\\flightnumber.txt" , ios::out | ios::app);
				ofstream input_price("Local Travel\\Transactions\\One way\\price.txt" , ios::out | ios::app);
				ofstream input_deptime("Local Travel\\Transactions\\One way\\deptime.txt" , ios::out | ios::app);
				ofstream input_arrtime("Local Travel\\Transactions\\One way\\arrtime.txt" , ios::out | ios::app);
				
				input_id << latest_id + i + 1 << endl;
				input_arrival << latest_city2 << endl;
				input_dep << latest_city << endl;
				input_fullname << fullname << endl;
				input_gender << gender << endl;
				input_month << month << endl;
				input_day << day << endl;
				input_year << year << endl;
				
				input_month1 << month << endl;
				input_day1 << day+add_day << endl;
				input_year1 << year << endl;
				
				input_birthday << month_name[month2-1] << " " << day2 << " " << year2 << endl;
				input_ticknum << latest_ticket_num + i+1 << endl;
				input_deptime << random_time_dep << endl;
				input_arrtime << random_time_arr << endl;
				if (k == 1)
				{
					input_flightnum << same_fnumber << endl;
				}
				if(k == 0)
				{
					input_flightnum << latest_flight_num + 1 << endl;
				}
				input_price << total_price << endl;	
							
				input_id.close(); input_arrival.close(); input_dep.close(); input_fullname.close();
				input_gender.close(); input_month.close(); input_year.close(); input_day.close(); input_month1.close();
				input_year1.close(); input_day1.close(); input_birthday.close(); input_ticknum.close();
				input_flightnum.close(); input_price.close(); input_deptime.close(); input_arrtime.close(); 
			}
			
				if (k == 1)
				{
					int tdtime, tatime;
					ifstream check_dep("Local Travel\\Transactions\\departure.txt");
					ifstream check_arr("Local Travel\\Transactions\\arrival.txt");
					ifstream check_seats("Local Travel\\Transactions\\seats.txt");
					ifstream check_fnumber("Local Travel\\Transactions\\fnumber.txt");
					ifstream check_day("Local Travel\\Transactions\\day.txt");
					ifstream check_month("Local Travel\\Transactions\\month.txt");
					ifstream check_year("Local Travel\\Transactions\\year.txt");
					
					ifstream check_day1("Local Travel\\Transactions\\day1.txt");
					ifstream check_month1("Local Travel\\Transactions\\month1.txt");
					ifstream check_year1("Local Travel\\Transactions\\year1.txt");
					
					ifstream check_dtime("Local Travel\\Transactions\\deptime.txt");
					ifstream check_atime("Local Travel\\Transactions\\arrtime.txt");
					
					ofstream temp1("Local Travel\\Transactions\\temp1.txt" , ios::out | ios::app);
					ofstream temp2("Local Travel\\Transactions\\temp2.txt" , ios::out | ios::app);
					ofstream temp3("Local Travel\\Transactions\\temp3.txt" , ios::out | ios::app);
					ofstream temp4("Local Travel\\Transactions\\temp4.txt" , ios::out | ios::app);
					ofstream temp5("Local Travel\\Transactions\\temp5.txt" , ios::out | ios::app);
					ofstream temp6("Local Travel\\Transactions\\temp6.txt" , ios::out | ios::app);
					ofstream temp7("Local Travel\\Transactions\\temp7.txt" , ios::out | ios::app);
					ofstream temp8("Local Travel\\Transactions\\temp8.txt" , ios::out | ios::app);
					ofstream temp9("Local Travel\\Transactions\\temp9.txt" , ios::out | ios::app);
					
					ofstream temp10("Local Travel\\Transactions\\temp10.txt" , ios::out | ios::app);
					ofstream temp11("Local Travel\\Transactions\\temp11.txt" , ios::out | ios::app);
					ofstream temp12("Local Travel\\Transactions\\temp12.txt" , ios::out | ios::app);
					int tday1, tmonth1, tyear1;
					while(getline(check_dep, temp_dep) && getline(check_arr, temp_arr) && check_seats >> temp_seat
									&& check_day >> tday && check_month >> tmonth && check_year >> tyear && check_fnumber >> tfnumber
									&& check_dtime >> tdtime && check_atime >> tatime && check_day1 >> tday1 && check_month1 >> tmonth1 && check_year1 >> tyear1)
					{
						if(!(latest_city == temp_dep && latest_city2 == temp_arr && month == tmonth && year == tyear && day == tday
							&& random_time_dep == tdtime && random_time_dep == tatime && day+add_day == tday1 && year == tyear1 && month == tmonth1))
						{	
							temp1 << temp_dep << endl;
							temp2 << temp_arr << endl;
							temp3 << tfnumber << endl;
							temp4 << tmonth << endl;
							temp5 << tyear << endl;
							temp6 << tday << endl;
							temp7 << temp_seat << endl;	
							temp8 << tdtime << endl;
							temp9 << tatime << endl;	
							temp10 << tmonth1 << endl;	
							temp11 << tyear1 << endl;
							temp12 << tday1 << endl;	
						}
					}
							temp1 << latest_city << endl;
							temp2 << latest_city2 << endl;
							temp3 << same_fnumber << endl;
							temp4 << month << endl;
							temp5 << year << endl;
							temp6 << day << endl;
							temp7 << add_seats + hm_passengers << endl;
							temp8 << random_time_dep << endl;
							temp9 << random_time_arr << endl;
							temp10 << month << endl;	
							temp11 << year << endl;
							temp12 << day+add_day << endl;	
							
						check_dep.close(); check_arr.close(); check_seats.close(); check_fnumber.close();
						check_day.close(); check_month.close(); check_year.close(); check_atime.close(); check_dtime.close();
						check_day1.close(); check_month1.close(); check_year1.close();
						
						temp1.close(); temp2.close(); temp3.close(); temp4.close(); 
						temp5.close(); temp6.close(); temp7.close(); temp8.close(); temp9.close(); 
						temp10.close(); temp11.close(); temp12.close(); 
						
						remove("Local Travel\\Transactions\\departure.txt");
						rename("Local Travel\\Transactions\\temp1.txt", "Local Travel\\Transactions\\departure.txt");
						
						remove("Local Travel\\Transactions\\arrival.txt");
						rename("Local Travel\\Transactions\\temp2.txt", "Local Travel\\Transactions\\arrival.txt");
						
						remove("Local Travel\\Transactions\\fnumber.txt");
						rename("Local Travel\\Transactions\\temp3.txt", "Local Travel\\Transactions\\fnumber.txt");
						
						remove("Local Travel\\Transactions\\month.txt");
						rename("Local Travel\\Transactions\\temp4.txt", "Local Travel\\Transactions\\month.txt");
						
						remove("Local Travel\\Transactions\\year.txt");
						rename("Local Travel\\Transactions\\temp5.txt", "Local Travel\\Transactions\\year.txt");
						
						remove("Local Travel\\Transactions\\day.txt");
						rename("Local Travel\\Transactions\\temp6.txt", "Local Travel\\Transactions\\day.txt");
						
						remove("Local Travel\\Transactions\\seats.txt");
						rename("Local Travel\\Transactions\\temp7.txt", "Local Travel\\Transactions\\seats.txt");
						
						remove("Local Travel\\Transactions\\deptime.txt");
						rename("Local Travel\\Transactions\\temp8.txt", "Local Travel\\Transactions\\deptime.txt");
						
						remove("Local Travel\\Transactions\\arrtime.txt");
						rename("Local Travel\\Transactions\\temp9.txt", "Local Travel\\Transactions\\arrtime.txt");
						
						
						remove("Local Travel\\Transactions\\day1.txt");
						rename("Local Travel\\Transactions\\temp12.txt", "Local Travel\\Transactions\\day1.txt");
						
						remove("Local Travel\\Transactions\\month1.txt");
						rename("Local Travel\\Transactions\\temp10.txt", "Local Travel\\Transactions\\month1.txt");
						
						remove("Local Travel\\Transactions\\year1.txt");
						rename("Local Travel\\Transactions\\temp11.txt", "Local Travel\\Transactions\\year1.txt");
				}
				if(k == 0)
				{
					ofstream fdep("Local Travel\\Transactions\\departure.txt" , ios::out | ios::app);
					ofstream farr("Local Travel\\Transactions\\arrival.txt" , ios::out | ios::app);
					ofstream fnumber("Local Travel\\Transactions\\fnumber.txt" , ios::out | ios::app);
					ofstream fmonth("Local Travel\\Transactions\\month.txt" , ios::out | ios::app);
					ofstream fyear("Local Travel\\Transactions\\year.txt" , ios::out | ios::app);
					ofstream fday("Local Travel\\Transactions\\day.txt" , ios::out | ios::app);
					ofstream fseats("Local Travel\\Transactions\\seats.txt" , ios::out | ios::app);
					ofstream fdtime("Local Travel\\Transactions\\deptime.txt" , ios::out | ios::app);
					ofstream fatime("Local Travel\\Transactions\\arrtime.txt" , ios::out | ios::app);
					
					ofstream fday1("Local Travel\\Transactions\\day1.txt" , ios::out | ios::app);
					ofstream fmonth1("Local Travel\\Transactions\\month1.txt" , ios::out | ios::app);
					ofstream fyear1("Local Travel\\Transactions\\year1.txt" , ios::out | ios::app);
					farr << latest_city2 << endl;
					fdep << latest_city << endl;
					fmonth << month << endl;
					fday << day << endl;
					fyear << year << endl;
					fnumber << latest_flight_num + 1 << endl;
					fseats << hm_passengers << endl;
					fdtime << random_time_dep << endl;
					fatime << random_time_arr << endl;
					fmonth1 << month << endl;
					fday1 << day+add_day << endl;
					fyear1 << year << endl;
				}
			char t_payment[20];
			float payment, change, temp_pay;
			cout << "Total Price: " << overall_price << " Yen" << endl << endl;
			do
			{
				do
				{
					cout << "Please enter your payment: ";
					cin.getline(t_payment, 20);
					temp_pay = check_numbers(t_payment);
					if(temp_pay == 1)
					{
						cout << "Please enter numbers only!" << endl;
					}
					else
					{
						istringstream(t_payment) >> payment;
					}
				} while (temp_pay == 1);
				if(payment < overall_price)
				{
					cout << "Insufficient Payment, Please pay the exact amount!" << endl;
				}
			} while (payment < overall_price);
			
			cout << "Change: " << payment - overall_price << endl << endl;
			cout << "Booking Flight Successful!" << endl;
			
				
			cout << endl << endl;
			char choice_temp;
			cout << "[R] Return" << endl;
			cout << "[0] Exit" << endl;
			cout << "Choice: ";
			cin >> choice_temp;
			if(choice_temp == 'R' || choice_temp == 'r') { system("cls"); return 9;	}
			if(choice_temp == '0') { exit (0);		}
}



/////////////////////////////////////////
int local_travel_booking_roundtrip()
{
		ifstream count_users("Local Travel\\Transactions\\Roundtrip\\id.txt");
		int add_id, latest_id = 0;	//VARIABLE
		while(count_users >> add_id)
		{
			latest_id = add_id;
		}
		count_users.close();
		
		ifstream count_t_number("Local Travel\\Transactions\\Roundtrip\\ticketnumber.txt");
		int temp_t, latest_ticket_num;  //VARIABLE
		while(count_t_number >> temp_t)
		{
			latest_ticket_num = temp_t;
		}
		if(latest_ticket_num == 0)
		{
			latest_ticket_num = 532;
		}
		count_t_number.close();
		
		ifstream count_f_number("Local Travel\\Transactions\\Roundtrip\\flightnumber.txt");
		int temp_fl, latest_flight_num;	//VARIABLE
		while(count_f_number >> temp_fl)
		{
			latest_flight_num = temp_fl;
		}
		if(latest_flight_num == 0)
		{
			latest_flight_num = 7023;
		}
		count_f_number.close();
		
		cout << endl << endl;
		list_of_airports();
		cout << endl << "PASSENGER/S TRANSACTION SLIP" << endl;
		
		//VARIABLE
		string dep_choice, arrival_choice;
		string temp_num, temp_city, temp_num2, temp_city2;
		string latest_city, latest_city2;
		int temp11, temp21;
		int k=0, j=0;
		cin.ignore();
	do
	{
		cout << "Enter Departure Location: ";
		getline(cin, dep_choice);
		if(dep_choice[0] == 'R' || dep_choice[0] == 'r') { system("cls"); return 9;	}
		if(dep_choice[0] == '0') { exit(0);	}
		if(dep_choice[0] == ' ') { temp11 = 1;	}
		
		ifstream check_num("Local Travel\\number.txt");
		ifstream check_city("Local Travel\\city.txt");
		while(getline(check_num, temp_num) && getline(check_city, temp_city))
		{
			if(dep_choice == temp_num)
			{
				latest_city = temp_city;
				temp11 = 1;
			}
		}
		check_num.close(); check_city.close();
		if(dep_choice[0] == ' ') { temp11 = 0;	}
		if (temp11 != 1) { cout << "Invalid Input! Try again" << endl;	}
	} while (temp11 != 1);
	
	do
	{
		do
		{
			cout << "Enter Arrival Location: ";
			getline(cin, arrival_choice);
			if(arrival_choice[0] == 'R' || arrival_choice[0] == 'r') { system("cls"); return 9;	}
			if(arrival_choice[0] == '0') { exit(0);	}
			if(arrival_choice[0] == ' ') { temp21 = 1;	}
			
			ifstream check_num("Local Travel\\number.txt");
			ifstream check_city("Local Travel\\city.txt");
			while(getline(check_num, temp_num2) && getline(check_city, temp_city2))
			{
				if(arrival_choice == temp_num2)
				{
					latest_city2 = temp_city2;
					temp21 = 1;
				}
			}
			check_num.close(); check_city.close();
			if(arrival_choice[0] == ' ') { temp21 = 0;	}
			if (temp21 != 1) { cout << "Invalid Input! Try again" << endl;	}
		} while (temp21 != 1);
		if(arrival_choice == dep_choice) { cout << "Please do not enter the same city" << endl; 	}
	} while(arrival_choice == dep_choice);
	
	
	int arr, dep;	//VARIABLE
	istringstream(arrival_choice) >> arr;
	istringstream(dep_choice) >> dep;
	
	cout << endl;
	cout << "======================" << endl;
	cout << "   " << latest_city << " to " << latest_city2 << endl;
	cout << "======================" << endl << endl;
	
	int temp1, temp2, temp3, temp4, month, day, year, day_loop, hm_passengers, x = 0;	//VARIABLE
	
	do
	{
		do
		{
			do
			{
				do
				{	
					char t_month[20], t_day[20], t_year[20];	//VARIABLE
					cout << endl << "Roundtrip" << endl;
					cout << "Departure Date (" << latest_city << "): " << endl;
					cout << "(e.g   5  18  2019)" << endl; 
					cout << "Month: ";
					cin.getline(t_month, 20);
					temp1 = check_numbers(t_month);
					cout << "Day: ";
					cin.getline(t_day, 20);
					temp2 = check_numbers(t_day);
					cout << "Year: ";
					cin.getline(t_year, 20);
					temp3 = check_numbers(t_year);
						if (temp1 == 1 || temp2 == 1 || temp3 == 1)
						{
							cout << "Invalid Input! Please enter the correct date!" << endl;
						}
						else
						{	
							istringstream(t_month) >> month;	
							istringstream(t_day) >> day;
							istringstream(t_year) >> year;
						}
				} while (temp1 == 1 || temp2 == 1 || temp3 == 1);		
				
				if(year < real_year || year > 2050)
				{
					cout << "Year not accepted. Please enter the correct Year!" << endl;
				}
				
			} while(year < real_year || year > 2050);
				
				if(year == real_year && month < real_month)
				{
					cout << "Month not accepted. Please enter the correct Month!" << endl;
					x=0;
				}
				else if(year == real_year && month == real_month && day < real_day)
				{
					cout << "Day not accepted. Please enter the correct Day!" << endl;
					x=0;
				}
				else
				{
					x = 1;
				}
		}  while(x == 0);
				if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				{
					if(day < 1 || day > 31)
					{
						cout << "Day not accepted. Please enter the correct Day!" << endl;
						day_loop = 1;
					} else {  day_loop = 0; 	}
				}
				if (month == 4 || month == 6 || month == 9 || month == 11)
				{
					if(day < 1 || day > 30)
					{
						cout << "Day not accepted. Please enter the correct Day!" << endl;
						day_loop = 1;
					} else {  day_loop = 0; 	}
				}
				if(month == 2)
				{
					if((year % 4) == 0)
					{
						if(day < 1 || day > 29)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop = 1;
						} else {  day_loop = 0; 	}
					}
					else
					{
						if(day < 1 || day > 28)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop = 1;
						} else {  day_loop = 0; 	}
					}
				}
			} while (day_loop == 1);
			
			char time_choice;
			int random_time_dep, random_time_arr;
			int add_day = 0;
			cout << endl << endl;
			cout << "Choose Time" << endl;
			cout << "[1] AM" << endl;
			cout << "[2] PM" << endl;
			cout << "Choice: ";
			cin >> time_choice;
			if(time_choice == '1') 
			{ 
				random_time_dep = rand() % 12;	
				random_time_arr = random_time_dep + 2;
			}
			if(time_choice == '2') 
			{ 
				random_time_dep = 12 + rand() % 13;	
				if (random_time_dep == 23)
				{
					random_time_arr = 0;
					add_day = 1;
				}
				if (random_time_dep == 24)
				{
					random_time_arr = 1;
					add_day = 1;
				}
				else
				{
					random_time_arr = random_time_dep + 2;
					add_day = 0;
				}
			}
			
			cout << "Departure date & time: " << month_name[month-1] << " " << day << " " << year << " (" << random_time_dep << ":00) " << endl;
			cout << "Arrival date & time: " << month_name[month-1] << " " << day + add_day << " " << year << " (" << random_time_arr << ":00) " << endl;
			cout << endl;
			cout << endl;
			
			cin.ignore();
			//check sa local flights
			
			
			int temp1_1, temp2_1, temp3_1, temp4_1, month_1, day_1, year_1, day_loop_1, year_loop = 0;
			do
			{
				do
				{
					do
					{
						do
						{
							do
							{	
								char t_month_1[20], t_day_1[20], t_year_1[20];
								cout << endl << "Round Trip" << endl;
								cout << "Departure Date (" << latest_city2 << "): " << endl;
								cout << "(e.g   5  18  2019)" << endl; 
								cout << "Month: ";
								cin.getline(t_month_1, 20);
								temp1_1 = check_numbers(t_month_1);
								cout << "Day: ";
								cin.getline(t_day_1, 20);
								temp2_1 = check_numbers(t_day_1);
								cout << "Year: ";
								cin.getline(t_year_1, 20);
								temp3_1 = check_numbers(t_year_1);
								if (temp1_1 == 1 || temp2_1 == 1 || temp3_1 == 1)
								{
									cout << "Invalid Input! Please enter the correct date!" << endl;
								}
								else
								{	
									istringstream(t_month_1) >> month_1;	
									istringstream(t_day_1) >> day_1;
									istringstream(t_year_1) >> year_1;
								}
							} while (temp1_1 == 1 || temp2_1 == 1 || temp3_1 == 1);
					
						if(year_1 < year || year_1 > 2024)
						{
							cout << "Year not accepted. Please enter the correct Year!" << endl;
						}
					} while(year_1 < year || year_1 > 2024);
				
					if(year_1 == year)
					{
						if(month_1 < month)
						{
							cout << "Month not accepted. Please enter the correct Month!" << endl;
							year_loop = 1;
						}
						else if(month_1 == month)
						{
							if(day_1 <= day)
							{
								cout << "Day not accepted. Please enter the correct Day!" << endl;
								year_loop = 1;	
							} 
							else
							{
								year_loop = 0;
							}
						}
						else
						{
							year_loop = 0;
						}
					}
				}	while(year_loop == 1);
					if(month_1 < 1 || month_1 > 12)
					{
						cout << "Month not accepted. Please enter the correct Month!" << endl;
					}
				}  while(month_1 < 1 || month_1 > 12);
				if (month_1 == 1 || month_1 == 3 || month_1 == 5 || month_1 == 7 || month_1 == 8 || month_1 == 10 || month_1 == 12)
				{
					if(day_1 < 1 || day_1 > 31)
					{
						cout << "Day not accepted. Please enter the correct Day!" << endl;
						day_loop_1 = 1;
					} else {  day_loop_1 = 0; 	}
				}
				if (month_1 == 4 || month_1 == 6 || month_1 == 9 || month_1 == 11)
				{
					if(day_1 < 1 || day_1 > 30)
					{
						cout << "Day not accepted. Please enter the correct Day!" << endl;
						day_loop_1 = 1;
					} else {  day_loop_1 = 0; 	}
				}
				if(month_1 == 2)
				{
					if((year_1 % 4) == 0)
					{
						if(day_1 < 1 || day_1 > 29)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop_1 = 1;
						} else {  day_loop_1 = 0; 	}
					}
					else
					{
						if(day_1 < 1 || day_1 > 28)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop_1 = 1;
						} else {  day_loop_1 = 0; 	}
					}
				}
			} while (day_loop_1 == 1);
			
			char time_choice2;
			int random_time_dep2, random_time_arr2;
			int add_day2 = 0;
			cout << endl << endl;
			cout << "Choose Time" << endl;
			cout << "[1] AM" << endl;
			cout << "[2] PM" << endl;
			cout << "Choice: ";
			cin >> time_choice2;
			if(time_choice2 == '1') 
			{ 
				random_time_dep2 = rand() % 12;	
				random_time_arr2 = random_time_dep2 + 2;
			}
			if(time_choice2 == '2') 
			{ 
				random_time_dep2 = 12 + rand() % 13;	
				if (random_time_dep2 == 23)
				{
					random_time_arr2 = 0;
					add_day2 = 1;
				}
				if (random_time_dep2 == 24)
				{
					random_time_arr2 = 1;
					add_day2 = 1;
				}
				else
				{
					random_time_arr2 = random_time_dep2 + 2;
					add_day2 = 0;
				}
			}
			cout << "Departure date & time: " << month_name[month_1-1] << " " << day_1 << " " << year_1 << " (" << random_time_dep2 << ":00) " << endl;
			cout << "Arrival date & time: " << month_name[month_1-1] << " " << day_1 + add_day2 << " " << year_1 << " (" << random_time_arr2 << ":00) " << endl;
			cout << endl;
			cout << endl;
			
			
			//check sa local flights
			
			
			
			cin.ignore();
			do
			{
				do
				{
					char t_hm_passengers[10];
					cout << "How many passengers: ";
					cin.getline(t_hm_passengers, 10);
					temp4 = check_numbers(t_hm_passengers);
					if(temp4 == 1)
					{
						cout << "Invalid input! Please enter the correct number!" << endl;
					}
					else
					{
						istringstream(t_hm_passengers) >> hm_passengers;
					}
				} while(temp4 == 1 );
				if(hm_passengers < 1 || hm_passengers > 10)
				{
					cout << "Only 1 - 10 passengers can be book at a time." << endl;
					temp4 = 1;
				}	
				else
				{
					temp4 = 0;
				}
			} while(temp4 == 1);
			char fullname[60], gender;
			char t_month1[20], t_day1[20], t_year1[20];
			int total_price;
			
			// VARIABLE,  unang departure
			string temp_dep, temp_arr;
			int temp_seat, seats = 0, tfnumber;
			int tday, tmonth, tyear;
			int add_seats, same_fnumber;
			int dtime, atime;
			ifstream check_dep("Local Travel\\Transactions\\departure.txt");
			ifstream check_arr("Local Travel\\Transactions\\arrival.txt");
			ifstream check_seats("Local Travel\\Transactions\\seats.txt");
			ifstream check_fnumber("Local Travel\\Transactions\\fnumber.txt");
			ifstream check_day("Local Travel\\Transactions\\day.txt");
			ifstream check_month("Local Travel\\Transactions\\month.txt");
			ifstream check_year("Local Travel\\Transactions\\year.txt");
			ifstream check_dtime("Local Travel\\Transactions\\arrtime.txt");
			ifstream check_atime("Local Travel\\Transactions\\deptime.txt");
			while(getline(check_dep, temp_dep) && getline(check_arr, temp_arr) && check_seats >> temp_seat
							&& check_day >> tday && check_month >> tmonth && check_year >> tyear && check_fnumber >> tfnumber
							&& check_dtime >> dtime && check_atime >> atime)
			{
				if(latest_city == temp_dep && latest_city2 == temp_arr && month == tmonth && year == tyear && day == tday
					&& random_time_dep == dtime && random_time_arr)
				{
					if((hm_passengers - seats) < 60 || (hm_passengers - seats) >= 0 )
					{
						add_seats = temp_seat;
						same_fnumber = tfnumber;
						k = 1;
					}
					else
					{
						k = 0;
					}
				}
			}
			check_dep.close(); check_arr.close(); check_seats.close(); check_fnumber.close();
			check_day.close(); check_month.close(); check_year.close(); check_dtime.close(); check_atime.close();
			
			
			
			// VARIABLE,  pangalawang departure
			string temp_dep1, temp_arr1;
			int temp_seat1, seats1 = 0, tfnumber1;
			int tday1, tmonth1, tyear1;
			int add_seats1, same_fnumber1;
			int dtime1, atime1;
			ifstream check_dep1("Local Travel\\Transactions\\departure.txt");
			ifstream check_arr1("Local Travel\\Transactions\\arrival.txt");
			ifstream check_seats1("Local Travel\\Transactions\\seats.txt");
			ifstream check_fnumber1("Local Travel\\Transactions\\fnumber.txt");
			ifstream check_day1("Local Travel\\Transactions\\day.txt");
			ifstream check_month1("Local Travel\\Transactions\\month.txt");
			ifstream check_year1("Local Travel\\Transactions\\year.txt");
			ifstream check_dtime1("Local Travel\\Transactions\\arrtime.txt");
			ifstream check_atime1("Local Travel\\Transactions\\deptime.txt");	
			while(getline(check_dep1, temp_dep1) && getline(check_arr1, temp_arr1) && check_seats1 >> temp_seat1
							&& check_day1 >> tday1 && check_month1 >> tmonth1 && check_year1 >> tyear1 && check_fnumber1 >> tfnumber1
							&& check_dtime1 >> dtime1 && check_atime1 >> atime1)
			{
				if(latest_city == temp_arr1 && latest_city2 == temp_dep1 && month_1 == tmonth1 && year_1 == tyear1 && day_1 == tday1
					&& random_time_dep2 == dtime1 && random_time_arr2 == atime1)
				{
					if((hm_passengers - seats1) < 60 || (hm_passengers - seats1) >= 0 )
					{
						add_seats1 = temp_seat1;
						same_fnumber1 = tfnumber1;
						j = 1;
					}
					else
					{
						j = 0;
					}
				}
			}
			check_dep1.close(); check_arr1.close(); check_seats1.close(); check_fnumber1.close();
			check_day1.close(); check_month1.close(); check_year1.close(); check_dtime1.close(); check_atime1.close();
			
			float overall_price;
			for(int i=0; i<hm_passengers; i++)
			{
				cout << endl << "Passenger [" << i+1 << "]" << endl;
				cout << "Fullname: ";
				cin.getline(fullname, 60);
				do
				{	
					cout << "Gender[M/F]: ";
					cin >> gender;
					if(toupper(gender) != 'M' && toupper(gender) != 'F')
					{
						cout << "Invalid Input! Please enter correctly" << endl;
					}
				} while (toupper(gender) != 'M' && toupper(gender) != 'F');
				
				int temp1_2, temp2_2, temp3_2, month2, day2, year2, day_loop2;
				cin.ignore();
				do
				{
					do
					{
						do
						{
							do
							{	
								char t_month2[20], t_day2[20], t_year2[20];
								cout << "Birthdate: " << endl;
								cout << "(e.g   5  18  2019)" << endl; 
								cout << "Month: ";
								cin.getline(t_month2, 20);
								temp1_2 = check_numbers(t_month2);
								cout << "Day: ";
								cin.getline(t_day2, 20);
								temp2_2 = check_numbers(t_day2);
								cout << "Year: ";
								cin.getline(t_year2, 20);
								temp3_2 = check_numbers(t_year2);
								if (temp1_2 == 1 || temp2_2 == 1 || temp3_2 == 1)
								{
									cout << "Invalid Input! Please enter the correct date!" << endl;
								}
								else
								{	
									istringstream(t_month2) >> month2;	
									istringstream(t_day2) >> day2;
									istringstream(t_year2) >> year2;
								}
							} while (temp1_2 == 1 || temp2_2 == 1 || temp3_2 == 1);
						
							if(year2 < 1800 || year2 > 2019)
							{
								cout << "Year not accepted. Please enter the correct Year!" << endl;
							}
						} while(year2 < 1800 || year2 > 2019);
					
						if(month2 < 1 || month2 > 12)
						{
							cout << "Month not accepted. Please enter the correct Month!" << endl;
						}
					}  while(month2 < 1 || month2 > 12);
					if (month2 == 1 || month2 == 3 || month2 == 5 || month2 == 7 || month2 == 8 || month2 == 10 || month2 == 12)
					{
						if(day2 < 1 || day2 > 31)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop2 = 1;
						} else {  day_loop2 = 0; 	}
					}
					if (month2 == 4 || month2 == 6 || month2 == 9 || month2 == 11)
					{
						if(day2 < 1 || day2 > 30)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop2 = 1;
						} else {  day_loop2 = 0; 	}
					}
					if(month2 == 2)
					{
						if((year2 % 4) == 0)
						{
							if(day2 < 1 || day2 > 29)
							{
								cout << "Day not accepted. Please enter the correct Day!" << endl;
								day_loop2 = 1;
							} else {  day_loop2 = 0; 	}
						}
						else
						{
							if(day2 < 1 || day2 > 28)
							{
								cout << "Day not accepted. Please enter the correct Day!" << endl;
								day_loop2 = 1;
							} else {  day_loop2 = 0; 	}
						}
					}
				} while (day_loop2 == 1);
				cout << "Birthday: " << month_name[month2-1] << " " << day2 << " " << year2 << endl;
				float total_price;
				total_price = function_price(latest_city, latest_city2, month2, day2, year2) * 2;
				overall_price += total_price;
				ofstream input_id("Local Travel\\Transactions\\Roundtrip\\id.txt" , ios::out | ios::app);
				ofstream input_gender("Local Travel\\Transactions\\Roundtrip\\gender.txt" , ios::out | ios::app);
				ofstream input_birthday("Local Travel\\Transactions\\Roundtrip\\birthday.txt" , ios::out | ios::app);
				ofstream input_fullname("Local Travel\\Transactions\\Roundtrip\\fullname.txt" , ios::out | ios::app);
				ofstream input_price("Local Travel\\Transactions\\Roundtrip\\price.txt" , ios::out | ios::app);
				ofstream input_ticknum("Local Travel\\Transactions\\Roundtrip\\ticketnumber.txt" , ios::out | ios::app);
				ofstream input_arrival("Local Travel\\Transactions\\Roundtrip\\arrival.txt" , ios::out | ios::app);
				ofstream input_dep("Local Travel\\Transactions\\Roundtrip\\departure.txt" , ios::out | ios::app);
				ofstream input_flightnum("Local Travel\\Transactions\\Roundtrip\\flightnumber.txt" , ios::out | ios::app);
				
				ofstream input_arrival1("Local Travel\\Transactions\\Roundtrip\\arrival1.txt" , ios::out | ios::app);
				ofstream input_dep1("Local Travel\\Transactions\\Roundtrip\\departure1.txt" , ios::out | ios::app);
				ofstream input_flightnum1("Local Travel\\Transactions\\Roundtrip\\flightnumber1.txt" , ios::out | ios::app);
				
				
				ofstream input_dday("Local Travel\\Transactions\\Roundtrip\\dday.txt" , ios::out | ios::app);
				ofstream input_dmonth("Local Travel\\Transactions\\Roundtrip\\dmonth.txt" , ios::out | ios::app);
				ofstream input_dyear("Local Travel\\Transactions\\Roundtrip\\dyear.txt" , ios::out | ios::app);
				ofstream input_deptime("Local Travel\\Transactions\\Roundtrip\\deptime.txt" , ios::out | ios::app);
				ofstream input_aday("Local Travel\\Transactions\\Roundtrip\\aday.txt" , ios::out | ios::app);
				ofstream input_amonth("Local Travel\\Transactions\\Roundtrip\\amonth.txt" , ios::out | ios::app);
				ofstream input_ayear("Local Travel\\Transactions\\Roundtrip\\ayear.txt" , ios::out | ios::app);
				ofstream input_arrtime("Local Travel\\Transactions\\Roundtrip\\arrtime.txt" , ios::out | ios::app);
				
				
				ofstream input_dday1("Local Travel\\Transactions\\Roundtrip\\dday1.txt" , ios::out | ios::app);
				ofstream input_dmonth1("Local Travel\\Transactions\\Roundtrip\\dmonth1.txt" , ios::out | ios::app);
				ofstream input_dyear1("Local Travel\\Transactions\\Roundtrip\\dyear1.txt" , ios::out | ios::app);
				ofstream input_deptime1("Local Travel\\Transactions\\Roundtrip\\deptime1.txt" , ios::out | ios::app);
				ofstream input_aday1("Local Travel\\Transactions\\Roundtrip\\aday1.txt" , ios::out | ios::app);
				ofstream input_amonth1("Local Travel\\Transactions\\Roundtrip\\amonth1.txt" , ios::out | ios::app);
				ofstream input_ayear1("Local Travel\\Transactions\\Roundtrip\\ayear1.txt" , ios::out | ios::app);
				ofstream input_arrtime1("Local Travel\\Transactions\\Roundtrip\\arrtime1.txt" , ios::out | ios::app);
				
				
				input_id << latest_id + i + 1 << endl;
				input_arrival << latest_city2 << endl;
				input_dep << latest_city << endl;
				
				input_arrival1 << latest_city << endl;
				input_dep1 << latest_city2 << endl;
				
				input_fullname << fullname << endl;
				input_gender << gender << endl;
				input_birthday << month_name[month2-1] << " " << day2 << " " << year2 << endl;
				input_ticknum << latest_ticket_num + i+1 << endl;
				if (k == 1)
				{
					input_flightnum << same_fnumber << endl;
				}
				if(k == 0)
				{
					input_flightnum << latest_flight_num + 1 << endl;
				}
				
				if (j == 1)
				{
					input_flightnum1 << same_fnumber1 << endl;
				}
				if(j == 0)
				{
					input_flightnum1 << latest_flight_num + 1 << endl;
				}
				
				input_price << total_price << endl;
				
				input_dmonth << month << endl;
				input_dday << day << endl;
				input_dyear << year << endl;		
				input_deptime << random_time_dep << endl;
				input_amonth << month << endl;
				input_aday << day+add_day << endl;
				input_ayear << year << endl;
				input_arrtime << random_time_arr << endl;
				
				input_dmonth1 << month_1 << endl;
				input_dday1 << day_1 << endl;
				input_dyear1 << year_1 << endl;
				input_deptime1 << random_time_dep2 << endl;
				input_amonth1 << month_1 << endl;
				input_aday1 << day_1 + add_day2 << endl;
				input_ayear1 << year_1 << endl;
				input_arrtime1 << random_time_arr2 << endl;
				
				
			}
			
			//dito ilalagay localflights, unang departure
			if (k == 1)
				{
					int tdtime, tatime;
					ifstream check_dep("Local Travel\\Transactions\\departure.txt");
					ifstream check_arr("Local Travel\\Transactions\\arrival.txt");
					ifstream check_seats("Local Travel\\Transactions\\seats.txt");
					ifstream check_fnumber("Local Travel\\Transactions\\fnumber.txt");
					ifstream check_day("Local Travel\\Transactions\\day.txt");
					ifstream check_month("Local Travel\\Transactions\\month.txt");
					ifstream check_year("Local Travel\\Transactions\\year.txt");
					
					ifstream check_day1("Local Travel\\Transactions\\day1.txt");
					ifstream check_month1("Local Travel\\Transactions\\month1.txt");
					ifstream check_year1("Local Travel\\Transactions\\year1.txt");
					
					ifstream check_dtime("Local Travel\\Transactions\\deptime.txt");
					ifstream check_atime("Local Travel\\Transactions\\arrtime.txt");
					
					ofstream temp1("Local Travel\\Transactions\\temp1.txt" , ios::out | ios::app);
					ofstream temp2("Local Travel\\Transactions\\temp2.txt" , ios::out | ios::app);
					ofstream temp3("Local Travel\\Transactions\\temp3.txt" , ios::out | ios::app);
					ofstream temp4("Local Travel\\Transactions\\temp4.txt" , ios::out | ios::app);
					ofstream temp5("Local Travel\\Transactions\\temp5.txt" , ios::out | ios::app);
					ofstream temp6("Local Travel\\Transactions\\temp6.txt" , ios::out | ios::app);
					ofstream temp7("Local Travel\\Transactions\\temp7.txt" , ios::out | ios::app);
					ofstream temp8("Local Travel\\Transactions\\temp8.txt" , ios::out | ios::app);
					ofstream temp9("Local Travel\\Transactions\\temp9.txt" , ios::out | ios::app);
					
					ofstream temp10("Local Travel\\Transactions\\temp10.txt" , ios::out | ios::app);
					ofstream temp11("Local Travel\\Transactions\\temp11.txt" , ios::out | ios::app);
					ofstream temp12("Local Travel\\Transactions\\temp12.txt" , ios::out | ios::app);
					int tday1, tmonth1, tyear1;
					while(getline(check_dep, temp_dep) && getline(check_arr, temp_arr) && check_seats >> temp_seat
									&& check_day >> tday && check_month >> tmonth && check_year >> tyear && check_fnumber >> tfnumber
									&& check_dtime >> tdtime && check_atime >> tatime && check_day1 >> tday1 && check_month1 >> tmonth1 && check_year1 >> tyear1)
					{
						if(!(latest_city == temp_dep && latest_city2 == temp_arr && month == tmonth && year == tyear && day == tday
							&& random_time_dep == tdtime && random_time_dep == tatime && day+add_day == tday1 && year == tyear1 && month == tmonth1))
						{	
							temp1 << temp_dep << endl;
							temp2 << temp_arr << endl;
							temp3 << tfnumber << endl;
							temp4 << tmonth << endl;
							temp5 << tyear << endl;
							temp6 << tday << endl;
							temp7 << temp_seat << endl;	
							temp8 << tdtime << endl;
							temp9 << tatime << endl;	
							temp10 << tmonth1 << endl;	
							temp11 << tyear1 << endl;
							temp12 << tday1 << endl;	
						}
					}
							temp1 << latest_city << endl;
							temp2 << latest_city2 << endl;
							temp3 << same_fnumber << endl;
							temp4 << month << endl;
							temp5 << year << endl;
							temp6 << day << endl;
							temp7 << add_seats + hm_passengers << endl;
							temp8 << random_time_dep << endl;
							temp9 << random_time_arr << endl;
							temp10 << month << endl;	
							temp11 << year << endl;
							temp12 << day+add_day << endl;	
							
						check_dep.close(); check_arr.close(); check_seats.close(); check_fnumber.close();
						check_day.close(); check_month.close(); check_year.close(); check_atime.close(); check_dtime.close();
						check_day1.close(); check_month1.close(); check_year1.close(); 
						
						temp1.close(); temp2.close(); temp3.close(); temp4.close(); temp11.close(); temp12.close(); 
						temp10.close(); temp5.close(); temp6.close(); temp7.close(); temp8.close(); temp9.close(); 
						
						remove("Local Travel\\Transactions\\departure.txt");
						rename("Local Travel\\Transactions\\temp1.txt", "Local Travel\\Transactions\\departure.txt");
						
						remove("Local Travel\\Transactions\\arrival.txt");
						rename("Local Travel\\Transactions\\temp2.txt", "Local Travel\\Transactions\\arrival.txt");
						
						remove("Local Travel\\Transactions\\fnumber.txt");
						rename("Local Travel\\Transactions\\temp3.txt", "Local Travel\\Transactions\\fnumber.txt");
						
						remove("Local Travel\\Transactions\\month.txt");
						rename("Local Travel\\Transactions\\temp4.txt", "Local Travel\\Transactions\\month.txt");
						
						remove("Local Travel\\Transactions\\year.txt");
						rename("Local Travel\\Transactions\\temp5.txt", "Local Travel\\Transactions\\year.txt");
						
						remove("Local Travel\\Transactions\\day.txt");
						rename("Local Travel\\Transactions\\temp6.txt", "Local Travel\\Transactions\\day.txt");
						
						remove("Local Travel\\Transactions\\seats.txt");
						rename("Local Travel\\Transactions\\temp7.txt", "Local Travel\\Transactions\\seats.txt");
						
						remove("Local Travel\\Transactions\\deptime.txt");
						rename("Local Travel\\Transactions\\temp8.txt", "Local Travel\\Transactions\\deptime.txt");
						
						remove("Local Travel\\Transactions\\arrtime.txt");
						rename("Local Travel\\Transactions\\temp9.txt", "Local Travel\\Transactions\\arrtime.txt");
						
						
						remove("Local Travel\\Transactions\\day1.txt");
						rename("Local Travel\\Transactions\\temp12.txt", "Local Travel\\Transactions\\day1.txt");
						
						remove("Local Travel\\Transactions\\month1.txt");
						rename("Local Travel\\Transactions\\temp10.txt", "Local Travel\\Transactions\\month1.txt");
						
						remove("Local Travel\\Transactions\\year1.txt");
						rename("Local Travel\\Transactions\\temp11.txt", "Local Travel\\Transactions\\year1.txt");
				}
				if(k == 0)
				{
					ofstream fdep("Local Travel\\Transactions\\departure.txt" , ios::out | ios::app);
					ofstream farr("Local Travel\\Transactions\\arrival.txt" , ios::out | ios::app);
					ofstream fnumber("Local Travel\\Transactions\\fnumber.txt" , ios::out | ios::app);
					ofstream fmonth("Local Travel\\Transactions\\month.txt" , ios::out | ios::app);
					ofstream fyear("Local Travel\\Transactions\\year.txt" , ios::out | ios::app);
					ofstream fday("Local Travel\\Transactions\\day.txt" , ios::out | ios::app);
					ofstream fseats("Local Travel\\Transactions\\seats.txt" , ios::out | ios::app);
					ofstream fdtime("Local Travel\\Transactions\\deptime.txt" , ios::out | ios::app);
					ofstream fatime("Local Travel\\Transactions\\arrtime.txt" , ios::out | ios::app);
					
					ofstream fday1("Local Travel\\Transactions\\day1.txt" , ios::out | ios::app);
					ofstream fmonth1("Local Travel\\Transactions\\month1.txt" , ios::out | ios::app);
					ofstream fyear1("Local Travel\\Transactions\\year1.txt" , ios::out | ios::app);
					farr << latest_city2 << endl;
					fdep << latest_city << endl;
					fmonth << month << endl;
					fday << day << endl;
					fyear << year << endl;
					fnumber << latest_flight_num + 1 << endl;
					fseats << hm_passengers << endl;
					fdtime << random_time_dep << endl;
					fatime << random_time_arr << endl;
					fmonth1 << month << endl;
					fday1 << day+add_day << endl;
					fyear1 << year << endl;
					
					fdep.close(); farr.close(); fnumber.close(); fmonth.close(); fyear.close(); fday.close();
					fseats.close(); fdtime.close(); fatime.close(); fday1.close(); fmonth1.close(); fyear1.close();
				}
			
			
				//dito yung pangalawa
				if (j == 1)
				{
					int tdtime, tatime;
					ifstream check_dep("Local Travel\\Transactions\\departure.txt");
					ifstream check_arr("Local Travel\\Transactions\\arrival.txt");
					ifstream check_seats("Local Travel\\Transactions\\seats.txt");
					ifstream check_fnumber("Local Travel\\Transactions\\fnumber.txt");
					ifstream check_day("Local Travel\\Transactions\\day.txt");
					ifstream check_month("Local Travel\\Transactions\\month.txt");
					ifstream check_year("Local Travel\\Transactions\\year.txt");
					
					ifstream check_day1("Local Travel\\Transactions\\day1.txt");
					ifstream check_month1("Local Travel\\Transactions\\month1.txt");
					ifstream check_year1("Local Travel\\Transactions\\year1.txt");
					
					ifstream check_dtime("Local Travel\\Transactions\\deptime.txt");
					ifstream check_atime("Local Travel\\Transactions\\arrtime.txt");
					
					ofstream temp1("Local Travel\\Transactions\\temp1.txt" , ios::out | ios::app);
					ofstream temp2("Local Travel\\Transactions\\temp2.txt" , ios::out | ios::app);
					ofstream temp3("Local Travel\\Transactions\\temp3.txt" , ios::out | ios::app);
					ofstream temp4("Local Travel\\Transactions\\temp4.txt" , ios::out | ios::app);
					ofstream temp5("Local Travel\\Transactions\\temp5.txt" , ios::out | ios::app);
					ofstream temp6("Local Travel\\Transactions\\temp6.txt" , ios::out | ios::app);
					ofstream temp7("Local Travel\\Transactions\\temp7.txt" , ios::out | ios::app);
					ofstream temp8("Local Travel\\Transactions\\temp8.txt" , ios::out | ios::app);
					ofstream temp9("Local Travel\\Transactions\\temp9.txt" , ios::out | ios::app);
					
					ofstream temp10("Local Travel\\Transactions\\temp10.txt" , ios::out | ios::app);
					ofstream temp11("Local Travel\\Transactions\\temp11.txt" , ios::out | ios::app);
					ofstream temp12("Local Travel\\Transactions\\temp12.txt" , ios::out | ios::app);
					int tday1, tmonth1, tyear1;
					while(getline(check_dep, temp_dep) && getline(check_arr, temp_arr) && check_seats >> temp_seat
									&& check_day >> tday && check_month >> tmonth && check_year >> tyear && check_fnumber >> tfnumber
									&& check_dtime >> tdtime && check_atime >> tatime && check_day1 >> tday1 && check_month1 >> tmonth1 && check_year1 >> tyear1)
					{
						if(!(latest_city2 == temp_dep && latest_city == temp_arr && month == tmonth && year == tyear && day == tday
							&& random_time_dep == tdtime && random_time_dep == tatime && day+add_day == tday1 && year == tyear1 && month == tmonth1))
						{	
							temp1 << temp_dep << endl;
							temp2 << temp_arr << endl;
							temp3 << tfnumber << endl;
							temp4 << tmonth << endl;
							temp5 << tyear << endl;
							temp6 << tday << endl;
							temp7 << temp_seat << endl;	
							temp8 << tdtime << endl;
							temp9 << tatime << endl;	
							temp10 << tmonth1 << endl;	
							temp11 << tyear1 << endl;
							temp12 << tday1 << endl;	
						}
					}
							temp1 << latest_city2 << endl;
							temp2 << latest_city << endl;
							temp3 << same_fnumber1 << endl;
							temp4 << month_1 << endl;
							temp5 << year_1 << endl;
							temp6 << day_1 << endl;
							temp7 << add_seats1 + hm_passengers << endl;
							temp8 << random_time_dep2 << endl;
							temp9 << random_time_arr2 << endl;
							temp10 << month_1 << endl;	
							temp11 << year_1 << endl;
							temp12 << day_1+add_day2 << endl;	
							
						check_dep.close(); check_arr.close(); check_seats.close(); check_fnumber.close();
						check_day.close(); check_month.close(); check_year.close(); check_atime.close(); check_dtime.close();
						check_day1.close(); check_month1.close(); check_year1.close();
						
						temp1.close(); temp2.close(); temp3.close(); temp4.close();
						temp5.close(); temp6.close(); temp7.close(); temp8.close(); temp9.close(); 
						temp10.close(); temp11.close(); temp12.close();
						
						remove("Local Travel\\Transactions\\departure.txt");
						rename("Local Travel\\Transactions\\temp1.txt", "Local Travel\\Transactions\\departure.txt");
						
						remove("Local Travel\\Transactions\\arrival.txt");
						rename("Local Travel\\Transactions\\temp2.txt", "Local Travel\\Transactions\\arrival.txt");
						
						remove("Local Travel\\Transactions\\fnumber.txt");
						rename("Local Travel\\Transactions\\temp3.txt", "Local Travel\\Transactions\\fnumber.txt");
						
						remove("Local Travel\\Transactions\\month.txt");
						rename("Local Travel\\Transactions\\temp4.txt", "Local Travel\\Transactions\\month.txt");
						
						remove("Local Travel\\Transactions\\year.txt");
						rename("Local Travel\\Transactions\\temp5.txt", "Local Travel\\Transactions\\year.txt");
						
						remove("Local Travel\\Transactions\\day.txt");
						rename("Local Travel\\Transactions\\temp6.txt", "Local Travel\\Transactions\\day.txt");
						
						remove("Local Travel\\Transactions\\seats.txt");
						rename("Local Travel\\Transactions\\temp7.txt", "Local Travel\\Transactions\\seats.txt");
						
						remove("Local Travel\\Transactions\\deptime.txt");
						rename("Local Travel\\Transactions\\temp8.txt", "Local Travel\\Transactions\\deptime.txt");
						
						remove("Local Travel\\Transactions\\arrtime.txt");
						rename("Local Travel\\Transactions\\temp9.txt", "Local Travel\\Transactions\\arrtime.txt");
						
						
						remove("Local Travel\\Transactions\\day1.txt");
						rename("Local Travel\\Transactions\\temp12.txt", "Local Travel\\Transactions\\day1.txt");
						
						remove("Local Travel\\Transactions\\month1.txt");
						rename("Local Travel\\Transactions\\temp10.txt", "Local Travel\\Transactions\\month1.txt");
						
						remove("Local Travel\\Transactions\\year1.txt");
						rename("Local Travel\\Transactions\\temp11.txt", "Local Travel\\Transactions\\year1.txt");
				}
				if(j == 0)
				{
					ofstream fdep("Local Travel\\Transactions\\departure.txt" , ios::out | ios::app);
					ofstream farr("Local Travel\\Transactions\\arrival.txt" , ios::out | ios::app);
					ofstream fnumber("Local Travel\\Transactions\\fnumber.txt" , ios::out | ios::app);
					ofstream fmonth("Local Travel\\Transactions\\month.txt" , ios::out | ios::app);
					ofstream fyear("Local Travel\\Transactions\\year.txt" , ios::out | ios::app);
					ofstream fday("Local Travel\\Transactions\\day.txt" , ios::out | ios::app);
					ofstream fseats("Local Travel\\Transactions\\seats.txt" , ios::out | ios::app);
					ofstream fdtime("Local Travel\\Transactions\\deptime.txt" , ios::out | ios::app);
					ofstream fatime("Local Travel\\Transactions\\arrtime.txt" , ios::out | ios::app);
					
					ofstream fday1("Local Travel\\Transactions\\day1.txt" , ios::out | ios::app);
					ofstream fmonth1("Local Travel\\Transactions\\month1.txt" , ios::out | ios::app);
					ofstream fyear1("Local Travel\\Transactions\\year1.txt" , ios::out | ios::app);
					farr << latest_city << endl;
					fdep << latest_city2 << endl;
					fmonth << month_1 << endl;
					fday << day_1 << endl;
					fyear << year_1 << endl;
					fnumber << latest_flight_num + 1 << endl;
					fseats << hm_passengers << endl;
					fdtime << random_time_dep2 << endl;
					fatime << random_time_arr2 << endl;
					fmonth1 << month_1 << endl;
					fday1 << day_1+add_day2 << endl;
					fyear1 << year_1 << endl;
				}
			
			
		
			
			
			char t_payment[20];
			int payment, change, temp_pay;
			cout << "Total Price: " << overall_price << " Yen" << endl << endl;
			do
			{
				do
				{
					cout << "Please enter your payment: ";
					cin.getline(t_payment, 20);
					temp_pay = check_numbers(t_payment);
					if(temp_pay == 1)
					{
						cout << "Please enter numbers only!" << endl;
					}
					else
					{
						istringstream(t_payment) >> payment;
					}
				} while (temp_pay == 1);
				if(payment < overall_price)
				{
					cout << "Insufficient Payment, Please pay the exact amount!" << endl;
				}
			} while (payment < overall_price);
			
			cout << "Change: " << payment - overall_price << endl << endl;
			
			cout << "Booking Flight Successful!" << endl;	
			
			
			cout << endl << endl;
			char choice_temp;
			cout << "[R] Return" << endl;
			cout << "[0] Exit" << endl;
			cout << "Choice: ";
			cin >> choice_temp;
			if(choice_temp == 'R' || choice_temp == 'r') { system("cls"); return 9;	}
			if(choice_temp == '0') { exit (0);		}
		}
		
		
		
		
		
		
		/////////////////////////////////////
int local_travel_booking()
{
	int temp;
	local_travel_booking_again:
	system("cls");
	char or_choice;
	cout << "Type of Flight" << endl;
	cout << "[1] One way" << endl;
	cout << "[2] Roundtrip (Two way)" << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	cout << "Choice: ";
	cin >> or_choice;	
	
	while(or_choice != '1' && or_choice != '2' && or_choice != 'R' && or_choice != 'r' && or_choice != '0')
	{
		cout << "Invalid Input! Please try again!" << endl;
		cout << "Choice: ";
		cin >> or_choice;
	}
	
	switch (or_choice)
	{
		case '1': temp = local_travel_booking_oneway();	    if(temp == 9) { goto local_travel_booking_again;	} break;
		case '2': temp = local_travel_booking_roundtrip();	if(temp == 9) { goto local_travel_booking_again;	} break;
		case 'R': return 9;	break;
		case 'r': return 9;	break;
		case '0': exit(0);	break;
	}
}

int view_local_oneway()
{
	return_again:
	system("cls");

	string fullname, birthday;
	int ticketnumber, id;
	char gender;
	cout << "=====================" << endl;
	cout << "   TRANSACTIONS" << endl;
	cout << "=====================" << endl;
	ifstream f_fullname("Local Travel\\Transactions\\One way\\fullname.txt");
	ifstream f_gender("Local Travel\\Transactions\\One way\\gender.txt");
	ifstream f_bday("Local Travel\\Transactions\\One way\\birthday.txt");
	ifstream f_t_number("Local Travel\\Transactions\\One way\\ticketnumber.txt");
	ifstream f_id("Local Travel\\Transactions\\One way\\id.txt");
	cout << left << "ID" << setw(10) << " " << setw(35) << "  FULLNAME " <<  setw(18) << "  TICKET NUMBER" << setw(13) << "GENDER"  << "BIRTHDAY" << endl;
		while(f_id >> id && getline(f_fullname, fullname) && f_t_number >> ticketnumber && f_gender >> gender && getline(f_bday, birthday))
		{
			cout << left << "[" << id << setw(10) << "] " << setw(40) << fullname <<  setw(15) << ticketnumber << setw(10) << gender  << birthday << endl;
		}
	char choice;
	cout << endl << endl << endl;
	cout << "MENU" << endl;
	cout << "[1] View Flight Details" << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	do
	{
		cout << "Choice: ";
		cin >> choice;
		if(choice != '1' && choice != 'R' && choice != 'r' && choice != '0')
		{
			cout << "Invalid Input! PLease try again" << endl;
		}
	} while (choice != '1' && choice != 'R' && choice != 'r' && choice != '0');
	if (choice == '1') 
	{ 
		string store_temp_id[50];
		string temp_id, temp_arr, temp_dep, temp_fnumber;
		int temp_day1, temp_day, temp_month1, temp_month, temp_year1, temp_year;
		int x=0;
		int deptime, arrtime;
		string input_id;
		
		tryagain:
		cout << "Enter ID number: ";
		cin >> input_id;
		if(input_id[0] == 'R' || input_id[0] == 'r') {  goto return_again;		}
		if(input_id[0] == '0') {  exit(0);		}
		ifstream count_id("Local Travel\\Transactions\\One way\\id.txt");
		ifstream count_arr("Local Travel\\Transactions\\One way\\arrival.txt");
		ifstream count_dep("Local Travel\\Transactions\\One way\\departure.txt");
		ifstream count_fnumber("Local Travel\\Transactions\\One way\\flightnumber.txt");
		ifstream count_day("Local Travel\\Transactions\\One way\\day.txt");
		ifstream count_day1("Local Travel\\Transactions\\One way\\day1.txt");
		ifstream count_month("Local Travel\\Transactions\\One way\\month.txt");
		ifstream count_month1("Local Travel\\Transactions\\One way\\month1.txt");
		ifstream count_year("Local Travel\\Transactions\\One way\\year.txt");
		ifstream count_year1("Local Travel\\Transactions\\One way\\year1.txt");
		ifstream count_dtime("Local Travel\\Transactions\\One way\\deptime.txt");
		ifstream count_atime("Local Travel\\Transactions\\One way\\arrtime.txt");
		while(getline(count_id, temp_id) && getline(count_arr, temp_arr) && getline(count_dep, temp_dep) && getline(count_fnumber, temp_fnumber) 
				&& count_day >> temp_day && count_day1 >> temp_day1 && count_month >> temp_month && count_month1 >> temp_month1 && count_year >> temp_year && count_year1 >> temp_year1
				&& count_dtime >> deptime && count_atime >> arrtime)
		{
			if(input_id == temp_id)
			{
				cout << endl << endl << "FLIGHT DETAILS" << endl << endl;
				cout << "Route: " << temp_dep << " to " << temp_arr << endl;
				cout << "Flight Number: " << temp_fnumber << endl;   
				cout << "Departure Date & Time: " << month_name[temp_month-1] << " " << temp_day << " " << temp_year << " (" << deptime << ":00)" << endl;
				cout << "Arrival Date & Time: " << month_name[temp_month1-1] << " " << temp_day1 << " " << temp_year1 << " (" << arrtime << ":00)" << endl;
				cout << "Flight Type: Oneway" << endl;
				x = 1;
			}
		}
		if(x == 0)
		{
			cout << "Not existed, Invalid Input, Try again" << endl;
			goto tryagain;
		}
		if(x == 1)
		{
			char choice;
			cout << endl << "[R] Back" << endl;
			cout << "[0] Exit" << endl;
			tryagain2:
			cout << "Choice: ";
			cin >> choice;
			switch(choice)
			{
				case 'R': goto return_again; break;
				case 'r': goto return_again; break;
				case '0': exit(0); break;
				default: cout << "Invalid Input Try again!" << endl; goto tryagain2; break;
			}
			
		}
		cout << endl << endl;
	}
	if (choice == 'R' || choice == 'r')  {	return 9;	}
	if (choice == '0')  { exit(0); }
}

int view_local_roundtrip()
{
	return_again2:
	system("cls");
	string fullname, birthday;
	int ticketnumber, id;
	char gender;
	cout << "=====================" << endl;
	cout << "   TRANSACTIONS" << endl;
	cout << "=====================" << endl;
	ifstream f_fullname("Local Travel\\Transactions\\Roundtrip\\fullname.txt");
	ifstream f_gender("Local Travel\\Transactions\\Roundtrip\\gender.txt");
	ifstream f_bday("Local Travel\\Transactions\\Roundtrip\\birthday.txt");
	ifstream f_t_number("Local Travel\\Transactions\\Roundtrip\\ticketnumber.txt");
	ifstream f_id("Local Travel\\Transactions\\Roundtrip\\id.txt");
	cout << left << "ID" << setw(10) << " " << setw(35) << "  FULLNAME " <<  setw(18) << "  TICKET NUMBER" << setw(13) << "GENDER"  << "BIRTHDAY" << endl;
		while(f_id >> id && getline(f_fullname, fullname) && f_t_number >> ticketnumber && f_gender >> gender && getline(f_bday, birthday))
		{
			cout << left << "[" << id << setw(10) << "] " << setw(40) << fullname <<  setw(15) << ticketnumber << setw(10) << gender  << birthday << endl;
		}
	char choice;
	cout << endl << endl << endl;
	cout << "MENU" << endl;
	cout << "[1] View Flight Details" << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	do
	{
		cout << "Choice: ";
		cin >> choice;
		if(choice != '1' && choice != 'R' && choice != 'r' && choice != '0')
		{
			cout << "Invalid Input! PLease try again" << endl;
		}
	} while (choice != '1' && choice != 'R' && choice != 'r' && choice != '0');
	if (choice == '1')  
	{
		string store_temp_id[50];
	
		int x=0;
		string input_id;
		tryagain:
		cout << "Enter ID number: ";
		cin >> input_id;
		
		if(input_id[0] == 'R' || input_id[0] == 'r') {  goto return_again2;		}
		if(input_id[0] == '0') {  exit(0);		}
		
		ifstream count_id("Local Travel\\Transactions\\Roundtrip\\id.txt");
		ifstream input_arrival("Local Travel\\Transactions\\Roundtrip\\arrival.txt");
		ifstream input_dep("Local Travel\\Transactions\\Roundtrip\\departure.txt");
		ifstream input_flightnum("Local Travel\\Transactions\\Roundtrip\\flightnumber.txt");
		
		ifstream input_arrival1("Local Travel\\Transactions\\Roundtrip\\arrival1.txt");
		ifstream input_dep1("Local Travel\\Transactions\\Roundtrip\\departure1.txt");
		ifstream input_flightnum1("Local Travel\\Transactions\\Roundtrip\\flightnumber1.txt");
			
					
		ifstream input_dday("Local Travel\\Transactions\\Roundtrip\\dday.txt");
		ifstream input_dmonth("Local Travel\\Transactions\\Roundtrip\\dmonth.txt");
		ifstream input_dyear("Local Travel\\Transactions\\Roundtrip\\dyear.txt");
		ifstream input_deptime("Local Travel\\Transactions\\Roundtrip\\deptime.txt");
		
		ifstream input_aday("Local Travel\\Transactions\\Roundtrip\\aday.txt");
		ifstream input_amonth("Local Travel\\Transactions\\Roundtrip\\amonth.txt");
		ifstream input_ayear("Local Travel\\Transactions\\Roundtrip\\ayear.txt");
		ifstream input_arrtime("Local Travel\\Transactions\\Roundtrip\\arrtime.txt");
					
					
		ifstream input_dday1("Local Travel\\Transactions\\Roundtrip\\dday1.txt");
		ifstream input_dmonth1("Local Travel\\Transactions\\Roundtrip\\dmonth1.txt");
		ifstream input_dyear1("Local Travel\\Transactions\\Roundtrip\\dyear1.txt");
		ifstream input_deptime1("Local Travel\\Transactions\\Roundtrip\\deptime1.txt");	
		ifstream input_aday1("Local Travel\\Transactions\\Roundtrip\\aday1.txt");
		
		ifstream input_amonth1("Local Travel\\Transactions\\Roundtrip\\amonth1.txt");
		ifstream input_ayear1("Local Travel\\Transactions\\Roundtrip\\ayear1.txt");
		ifstream input_arrtime1("Local Travel\\Transactions\\Roundtrip\\arrtime1.txt");
		
		
		string temp_id, arrival, dep, flightnum;
		string arrival1, dep1, flightnum1;
		int dday, dmonth, dyear, deptime;
		int aday, amonth, ayear, arrtime;
		int dday1, dmonth1, dyear1, deptime1;
		int aday1, amonth1, ayear1, arrtime1;
		
		while(getline(count_id, temp_id) && getline(input_arrival, arrival) && getline(input_dep, dep) && getline(input_flightnum, flightnum) && 
				getline(input_arrival1, arrival1) && getline(input_dep1, dep1) && getline(input_flightnum1, flightnum1) && 
				input_dday >> dday && input_dmonth >> dmonth && input_dyear >> dyear && input_deptime >> deptime &&
				input_aday >> aday && input_amonth >> amonth && input_ayear >> ayear && input_arrtime >> arrtime &&	
				input_dday1 >> dday1 && input_dmonth1 >> dmonth1 && input_dyear1 >> dyear1 && input_deptime1 >> deptime1 &&
				input_aday1 >> aday1 && input_amonth1 >> amonth1 && input_ayear1 >> ayear1 && input_arrtime1 >> arrtime1  )
		{
			if(input_id == temp_id)
			{
				cout << endl << endl << "FLIGHT DETAILS" << endl << endl;
				cout << "Flight Type: Roundtrip" << endl << endl;
				
				cout << "Route: " << dep << " to " << arrival << endl;
				cout << "Flight Number: " << flightnum << endl;   
				cout << "Departure Date & Time: " << month_name[dmonth-1] << " " << dday << " " << dyear << " (" << deptime << ":00)" << endl;
				cout << "Arrival Date & Time: " << month_name[amonth-1] << " " << aday << " " << ayear << " (" << arrtime << ":00)" << endl;
				cout << endl << endl;
				cout << "Route: " << dep1 << " to " << arrival1 << endl;
				cout << "Flight Number: " << flightnum1 << endl;   
				cout << "Departure Date & Time: " << month_name[dmonth1-1] << " " << dday1 << " " << dyear1 << " (" << deptime1 << ":00)" << endl;
				cout << "Arrival Date & Time: " << month_name[amonth1-1] << " " << aday1 << " " << ayear1 << " (" << arrtime1 << ":00)" << endl;
				x = 1;
			}
		}
		if(x == 0)
		{
			cout << "Not existed, Invalid Input, Try again" << endl;
			goto tryagain;
		}
		if(x == 1)
		{
			char choice;
			cout << endl << "[R] Back" << endl;
			cout << "[0] Exit" << endl;
			tryagain2:
			cout << "Choice: ";
			cin >> choice;
			switch(choice)
			{
				case 'R': goto return_again2; break;
				case 'r': goto return_again2; break;
				case '0': exit(0); break;
				default: cout << "Invalid Input Try again!" << endl; goto tryagain2; break;
			}
			
		}
		cout << endl << endl;
	}
	if (choice == 'R' || choice == 'r')  {	return 9;	}
	if (choice == '0')  { exit(0); }
}

int view_local_transaction()
{
	view_local_transaction:
	system("cls");
	char choice_f_type;
	int temp, temp2;
		cout << "Flight Type" << endl;
		cout << "[1] One way" << endl;
		cout << "[2] Roundtrip" << endl;
		cout << "[R] Return" << endl;
		cout << "[0] Exit" << endl;
	do
	{
		cout << "Choice: ";
		cin >> choice_f_type;
		if(choice_f_type != '1' && choice_f_type != '2' && choice_f_type != 'R' && choice_f_type != 'r' && choice_f_type != '0')
		{
			cout << "Invalid Input! Try again!" << endl;
		}
	} while(choice_f_type != '1' && choice_f_type != '2' && choice_f_type != 'R' && choice_f_type != 'r' && choice_f_type != '0');
	switch (choice_f_type)
	{
		case '1': 
			temp = view_local_oneway(); 
			if(temp == 9) goto view_local_transaction;
		break;
		case '2': 
			temp2 = view_local_roundtrip(); 
			if(temp2 == 9) goto view_local_transaction;
		break;
		case 'R': return 9; break;
		case 'r': return 9; break;
		case '0': exit(0); break;
	}
}

int view_local_flight()
{
	try_again:
	string temp_dep, temp_arr;
	int temp_seat, seats = 0, tfnumber;
	int tday, tmonth, tyear;
	int tday2, tmonth2, tyear2;
	int add_seats, same_fnumber;
	cin.ignore();
	char choice[20];
	int x, temp=0;
	int count = 0;
	int j=0;
	int count_temp = 0;
	int p;
	string check_air_number, air_choice;
	
	list_of_airports();
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	string temp_city, latest_city;
	do
	{
		cout << endl << "Choose airport: ";
		getline(cin, air_choice);
		ifstream check_num("Local Travel\\number.txt");
		ifstream check_city("Local Travel\\city.txt");
		while(getline(check_num, check_air_number) && getline(check_city, temp_city))
		{
			if(check_air_number == air_choice)
			{
				j=1;
				p = count_temp;
				latest_city = temp_city;
			}	
			if(air_choice == "R"|| air_choice == "r")	{	j=1; return 9;	}
			if(air_choice == "0") { j=1; exit(0);	}
			count_temp++;
		}
		if(j == 0)
		{
			cout << "Invalid Input! Please enter the correct number" << endl;
		}
	} while(j == 0);
	
	cout << endl << endl;
	int atime, dtime;
	ifstream check_dep("Local Travel\\Transactions\\departure.txt");
	ifstream check_arr("Local Travel\\Transactions\\arrival.txt");
	ifstream check_seats("Local Travel\\Transactions\\seats.txt");
	ifstream check_fnumber("Local Travel\\Transactions\\fnumber.txt");
	ifstream check_day("Local Travel\\Transactions\\day.txt");
	ifstream check_month("Local Travel\\Transactions\\month.txt");
	ifstream check_year("Local Travel\\Transactions\\year.txt");
	
	ifstream check_day2("Local Travel\\Transactions\\day1.txt");
	ifstream check_month2("Local Travel\\Transactions\\month1.txt");
	ifstream check_year2("Local Travel\\Transactions\\year1.txt");
	
	ifstream check_dtime("Local Travel\\Transactions\\deptime.txt");
	ifstream check_atime("Local Travel\\Transactions\\arrtime.txt");
	
	cout << "List of Local Flights" << endl << endl;
	cout << left << "Flight Number" << setw(10) << " " << setw(25) << "  Departure " <<  setw(24) << "Arrival" << setw(28) << "(Dep) Date & Time" << setw(28) << "    (Arr) Date & Time"  << "\t Available Seats" << endl;
	while(getline(check_dep, temp_dep) && getline(check_arr, temp_arr) && check_seats >> temp_seat
		&& check_day >> tday && check_month >> tmonth && check_year >> tyear && check_fnumber >> tfnumber && check_dtime >> dtime && check_atime >> atime
		&& check_day2 >> tday2 && check_month2 >> tmonth2 && check_year2 >> tyear2) 
	{
		if(temp_dep == latest_city)
		{
			printf("   [%-4i] %-14s %-22s %-23s %-10s%-3i%-4i (%-2i:00) %-6s %-10s%-3i%-4i (%-2i:00) %-14s %-2i\n", tfnumber, " " , temp_dep.c_str(), temp_arr.c_str(), month_name[tmonth-1].c_str(), tday, tyear, dtime, " ",  month_name[tmonth-1].c_str(), tday2, tyear2, atime, " ", 60-temp_seat) ;	
			count = 1;
		}
	}
	check_dep.close(); check_arr.close(); check_seats.close(); check_fnumber.close();
	check_day.close(); check_month.close(); check_year.close();
	check_day2.close(); check_month2.close(); check_year2.close();
	if(count == 0)
	{
		cout << endl;
		cout << "====================================" << endl;
		cout << "      No flights are made! " << endl;
		cout << "====================================" << endl;
	}
	cout << endl << endl;
	char last_choice;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	do
	{
		cout << "Choice: ";
		cin >> last_choice;
		if(last_choice != 'R' && last_choice != 'r' && last_choice != '0')
		{
			cout << "Invalid Input! Please try again!" << endl;
		} 
		if(last_choice == 'R' || last_choice == 'r') { system("cls"); goto try_again; }
		if(last_choice == '0') { exit (0); }
	} while(last_choice != 'R' && last_choice != 'r' && last_choice != '0');
}

int add_airport()
{
	system("cls");
	cin.ignore();
	list_of_airports();
	char city[50], airport[50], choice;
	int number, latest_number;
	cout << endl << endl;
	cout << "ADDING AIRLINES" << endl << endl;
	cout << "Enter the City: ";
	cin.getline(city, 50);
	cout << "Enter the Name of Airport: ";
	cin.getline(airport, 50);
	
	ifstream check_number;
	check_number.open ("Local Travel\\number.txt");
	while(check_number >> number)
	{
		latest_number = number;
	}
	check_number.close();
	
	ofstream f_airport, f_city, f_number;
	f_airport.open ("Local Travel\\airport.txt", ios::out | ios::app);
	f_city.open ("Local Travel\\city.txt", ios::out | ios::app);
	f_number.open ("Local Travel\\number.txt", ios::out | ios::app);
	f_airport << airport << endl;
	f_city << city << endl;
	f_number << latest_number + 1 << endl;
	f_airport.close(); f_city.close(); f_number.close();
	
	cout << endl << "Data has been recorded!" << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	do
	{
		cout << "Choice: ";
		cin >> choice;
		if(choice != 'R' && choice != 'r' && choice != '0')
		{
			cout << "Invalid Input! Please try again!" << endl;
		}
		if(choice == 'R' || choice == 'r') { return 9; }
		if(choice == '0') { exit (0); }
	} while(choice != 'R' && choice != 'r' && choice != '0');
}

int add_flights()
{
	system("cls");
	cin.ignore();
	int temploc1, temploc2;
	string temp_num, temp_num2;
	string dep_choice, arrival_choice;
	string latest_city, latest_city2, temp_city, temp_city2;
	int latest_flight_num;
	int arr, dep;
	list_of_airports();
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	cout << endl << endl;
	do
	{
		cout << "Enter Departure Location: ";
		cin >> dep_choice;
		if(dep_choice == "R" || dep_choice == "r") { temploc1=0; return 9;	}
		if(dep_choice == "0") { temploc1=0; exit(0);	}
		ifstream check_numbers("Local Travel\\number.txt");
		ifstream check_city("Local Travel\\city.txt");
		while(getline(check_numbers, temp_num) && getline(check_city, temp_city))
		{
			if(temp_num == dep_choice)
			{
				latest_city = temp_city;
				temploc1 = 1;
			}
		}
		check_numbers.close(); check_city.close();
		if(temploc1 != 1) { cout << "Invalid Input! Try again!" << endl;		}
	} while (temploc1 != 1);
	
	do
	{
		do
		{
			cout << "Enter Arrival Location: ";
			cin >> arrival_choice;
			if(arrival_choice == "R" || arrival_choice == "r") { temploc2=0; return 9;	}
			if(arrival_choice == "0") { temploc2=0; exit(0);	}
				
			ifstream check_numbers2("Local Travel\\number.txt");
			ifstream check_city2("Local Travel\\city.txt");
			while(getline(check_numbers2, temp_num2) && getline(check_city2, temp_city2))
			{
				if(temp_num2 == arrival_choice)
				{
					latest_city2 = temp_city2;
					temploc2 = 1;
				}
			}
			check_numbers2.close(); check_city2.close();
			if(temploc2 != 1) { cout << "Invalid Input! Try again!" << endl;		}	
		} while (temploc2 != 1);
		(arrival_choice == dep_choice)? cout << "Invalid Input! Please enter the correct choice" << endl : cout << "";
	} while(arrival_choice == dep_choice);
	
	istringstream(arrival_choice) >> arr;
	istringstream(dep_choice) >> dep;
	
	int temp_fl;
	ifstream count_f_number;
	count_f_number.open ("Local Travel\\Transactions\\fnumber.txt");
		while(count_f_number >> temp_fl)
		{
			latest_flight_num = temp_fl;
		}
		if(latest_flight_num == 0)
		{
			latest_flight_num = 7023;
		}
	count_f_number.close();
	
	int temp1, temp2, temp3, temp4, month, day, year, day_loop, hm_passengers, x = 0;
	
			cin.ignore();
			do
			{
				do
				{
					do
					{
						do
						{	
							char t_month[20], t_day[20], t_year[20];
							cout << "Departure Date: " << endl;
							cout << "(e.g   5  18  2019)" << endl; 
							cout << "Month: ";
							cin.getline(t_month, 20);
							temp1 = check_numbers(t_month);
							cout << "Day: ";
							cin.getline(t_day, 20);
							temp2 = check_numbers(t_day);
							cout << "Year: ";
							cin.getline(t_year, 20);
							temp3 = check_numbers(t_year);
							if (temp1 == 1 || temp2 == 1 || temp3 == 1)
							{
								cout << "Invalid Input! Please enter the correct date!" << endl;
							}
							else
							{	
								istringstream(t_month) >> month;	
								istringstream(t_day) >> day;
								istringstream(t_year) >> year;
							}
						} while (temp1 == 1 || temp2 == 1 || temp3 == 1);
					
						if(year < real_year || year > 2050)
						{
							cout << "Year not accepted. Please enter the correct Year!" << endl;
						}
					} while(year < real_year || year > 2050);
					if(year == real_year && month < real_month)
					{
						cout << "Month not accepted. Please enter the correct Month!" << endl;
						x=0;
					}
					else if(year == real_year && month == real_month && day < real_day)
					{
						cout << "Day not accepted. Please enter the correct Day!" << endl;
						x=0;
					}
					else
					{
						x = 1;
					}
				}  while(x == 0);
				if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				{
					if(day < 1 || day > 31)
					{
						cout << "Day not accepted. Please enter the correct Day!" << endl;
						day_loop = 1;
					} else {  day_loop = 0; 	}
				}
				if (month == 4 || month == 6 || month == 9 || month == 11)
				{
					if(day < 1 || day > 30)
					{
						cout << "Day not accepted. Please enter the correct Day!" << endl;
						day_loop = 1;
					} else {  day_loop = 0; 	}
				}
				if(month == 2)
				{
					if((year % 4) == 0)
					{
						if(day < 1 || day > 29)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop = 1;
						} else {  day_loop = 0; 	}
					}
					else
					{
						if(day < 1 || day > 28)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop = 1;
						} else {  day_loop = 0; 	}
					}
				}
			} while (day_loop == 1);
	string z;
	int time_dep_loop;
	int time;
	do
	{
		do
		{		
			cout << endl << "Pick Departure Time (0-24): ";
			getline(cin, z);
			for(int i=0; i<z.size(); i++)
			{
				if(z[i] != '1' && z[i] != '2' && z[i] != '3' && z[i] != '4' && z[i] != '5' && z[i] != '6' && z[i]!= '7' && z[i] != '8' && z[i] != '9' && z[i] != '0')
				{
					time_dep_loop = 1;
				}
				else
				{
					time_dep_loop = 0;
				}
			}
			if(time_dep_loop == 1) { cout << "Invalid Input! Try again!" << endl;	}
		} while(time_dep_loop == 1);
		istringstream(z) >> time;
		if(time < 0 || time > 24)
		{
			cout << "Invalid Input! Try again" << endl;
		}
	} while(time < 0 || time > 24);
	int add_day=0, time2, day2;
	if(time == 23){	time2 = 0; day2 = day + 1; }
 	if(time == 24){	time2 = 1; day2 = day + 1; }
	else { time2 = time+2;	day2 = day; }
	cout << "Time: " << time << ":00" << endl;
	
	ofstream f_dep("Local Travel\\Transactions\\departure.txt", ios::out | ios::app);
	ofstream f_arr("Local Travel\\Transactions\\arrival.txt", ios::out | ios::app);
	ofstream f_seats("Local Travel\\Transactions\\seats.txt", ios::out | ios::app);
	ofstream f_fnumber("Local Travel\\Transactions\\fnumber.txt", ios::out | ios::app);
	ofstream f_day("Local Travel\\Transactions\\day.txt", ios::out | ios::app);
	ofstream f_month("Local Travel\\Transactions\\month.txt", ios::out | ios::app);
	ofstream f_year("Local Travel\\Transactions\\year.txt", ios::out | ios::app);
	
	ofstream f_day2("Local Travel\\Transactions\\day1.txt", ios::out | ios::app);
	ofstream f_month2("Local Travel\\Transactions\\month1.txt", ios::out | ios::app);
	ofstream f_year2("Local Travel\\Transactions\\year1.txt", ios::out | ios::app);
	
	ofstream f_dtime("Local Travel\\Transactions\\deptime.txt", ios::out | ios::app);
	ofstream f_atime("Local Travel\\Transactions\\arrtime.txt", ios::out | ios::app);
	
	f_dep << latest_city << endl;
	f_arr << latest_city2 << endl;
	f_seats << 0 << endl;
	f_fnumber << latest_flight_num+1 << endl;
	f_day << day << endl;
	f_month << month << endl;
	f_year << year << endl;
	
	f_day2 << day2 << endl;
	f_month2 << month << endl;
	f_year2 << year << endl;
	
	f_dtime << time << endl;
	f_atime << time2 << endl;
	
	f_dep.close(); f_arr.close(); f_seats.close(); f_fnumber.close();
	f_day.close(); f_month.close(); f_year.close(); f_dtime.close(); f_atime.close();
	f_day2.close(); f_month2.close(); f_year2.close();
	
	char choice;
	cout << endl << "Data has been recorded!" << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	cout << "Choice: ";
	cin >> choice;
	do
	{
		if(choice != 'R' && choice != 'r' && choice != '0')
		{
			cout << "Invalid Input! Please try again!" << endl;
		}
		if(choice == 'R'|| choice == 'r') { system("cls"); return 9; }
		if(choice == '0') { exit (0); }
	} while(choice != 'R' && choice != 'r' && choice != '0');
	
}

int add_local_flights()
{
	system("cls");
	add_local_flights_menu:
	cin.ignore();
	char choice;
	int temp, temp2;
	list_of_airports();
	cout << endl << endl;
	cout << "[1] Add Airport" << endl;
	cout << "[2] Add Flights" << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	do
	{
		cout << "Choice: ";
		cin >> choice;
		if(choice != '1' && choice != '2' && choice != 'R' && choice != 'r' && choice != '0')
		{
			cout << "Invalid Input! Please try again!" << endl;
		}
	} while(choice != '1' && choice != '2' && choice != 'R' && choice != 'r' && choice != '0');
	
	if (choice == '1')
	{
		temp = add_airport();
		if (temp == 9) { system("cls"); goto add_local_flights_menu;	}
	}
	if (choice == '2')
	{
		temp2 = add_flights();
		if (temp2 == 9) { goto add_local_flights_menu;	}
	}
	if (choice == 'R' || choice == 'r') { return 9; }
	if (choice == '0') { exit (0); }
}

int delete_airport()
{
	cin.ignore();
	system("cls");
	list_of_airports();
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	
	int x = 0;
	string get_number;
	string airport, city, number;
	string temp_number;
	
	cout << endl << endl;
	cout << "Delete Airport" << endl << endl;
	do
	{
		cout << "Please enter the number of the airport: ";
		getline(cin, get_number);
		if(get_number == "R" || get_number == "r") { x=1; system("cls"); return 9;	}
		if(get_number == "0") { x=1; exit(0);	}
		
		ifstream check_number("Local Travel\\number.txt");
		while(getline(check_number, temp_number))
		{
			if(get_number == temp_number)
			{
				x = 1;
			}
		}
		check_number.close();
		if(x == 0)
		{
			cout << "Invalid Input! Please enter the correc number!" << endl;
		}
	} while (x == 0);
	ofstream temp1("Local Travel\\temp1.txt", ios::out | ios::app);
	ofstream temp2("Local Travel\\temp2.txt", ios::out | ios::app);
	ofstream temp3("Local Travel\\temp3.txt", ios::out | ios::app);
	
	ifstream f_airport("Local Travel\\airport.txt");
	ifstream f_city("Local Travel\\city.txt");
	ifstream f_number("Local Travel\\number.txt");
	while(getline(f_airport, airport) && getline(f_city, city) && getline(f_number, number))
	{
		if(get_number != number)
		{
			temp1 << airport << endl;
			temp2 << city << endl;
			temp3 << number << endl;
		}
	}
	f_airport.close(); f_city.close(); f_number.close();
	temp1.close(); temp2.close(); temp3.close();
	
	remove("Local Travel\\airport.txt");
	remove("Local Travel\\city.txt");
	remove("Local Travel\\number.txt");
	
	rename("Local Travel\\temp1.txt", "Local Travel\\airport.txt");
	rename("Local Travel\\temp2.txt", "Local Travel\\city.txt");
	rename("Local Travel\\temp3.txt", "Local Travel\\number.txt");
	
	char choice;
	cout << endl << "Data has been deleted!" << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	cout << "Choice: ";
	cin >> choice;
	do
	{
		if(choice != 'R' && choice != 'r' && choice != '0')
		{
			cout << "Invalid Input! Please try again!" << endl;
		}
		if(choice == 'R' || choice == 'r') { system("cls"); return 9; }
		if(choice == '0') { exit (0); }
	} while(choice != 'R' && choice != 'r' && choice != '0');
}

int delete_local_flights()
{
	cout << "Delete Flights " << endl;
	string temp_dep, temp_arr;
	int tfnumber;
	int temp_seat;
	int tday, tmonth, tyear;
	int tday2, tmonth2, tyear2;
	int atime, dtime;
	cin.ignore();
	char choice[20];
	int x, temp=0;
	int count = 0;
	string store_fnumber[30];
	
	cout << endl << endl;

	ifstream check_dep("Local Travel\\Transactions\\departure.txt");
	ifstream check_arr("Local Travel\\Transactions\\arrival.txt");
	ifstream check_seats("Local Travel\\Transactions\\seats.txt");
	ifstream check_fnumber("Local Travel\\Transactions\\fnumber.txt");
	ifstream check_day("Local Travel\\Transactions\\day.txt");
	ifstream check_month("Local Travel\\Transactions\\month.txt");
	ifstream check_year("Local Travel\\Transactions\\year.txt");
	
	ifstream check_day12("Local Travel\\Transactions\\day1.txt");
	ifstream check_month12("Local Travel\\Transactions\\month1.txt");
	ifstream check_year12("Local Travel\\Transactions\\year1.txt");
	
	ifstream check_dtime("Local Travel\\Transactions\\deptime.txt");
	ifstream check_atime("Local Travel\\Transactions\\arrtime.txt");
	
	cout << "List of Local Flights" << endl << endl;
	cout << left << "Flight Number" << setw(10) << " " << setw(25) << "  Departure " <<  setw(24) << "Arrival" << setw(28) << "(Dep) Date & Time" << setw(28) << "    (Arr) Date & Time"  << "\t Available Seats" << endl;
	while(getline(check_dep, temp_dep) && getline(check_arr, temp_arr) && check_seats >> temp_seat
		&& check_day >> tday && check_month >> tmonth && check_year >> tyear && check_fnumber >> tfnumber && check_dtime >> dtime && check_atime >> atime
		&& check_day12 >> tday2 && check_month12 >> tmonth2 && check_year12 >> tyear2) 
	{
			printf("   [%-4i] %-14s %-22s %-23s %-10s%-3i%-4i (%-2i:00) %-6s %-10s%-3i%-4i (%-2i:00) %-14s %-2i\n", tfnumber, " " , temp_dep.c_str(), temp_arr.c_str(), month_name[tmonth-1].c_str(), tday, tyear, dtime, " ",  month_name[tmonth-1].c_str(), tday2, tyear2, atime, " ", 60-temp_seat) ;	
			count = 1;
	}
	check_dep.close(); check_arr.close(); check_seats.close(); check_fnumber.close();
	check_day.close(); check_month.close(); check_year.close(); check_atime.close();
	check_day12.close(); check_month12.close(); check_year12.close(); check_dtime.close();
	if(count == 0)
	{
		cout << "No flights are made! " << endl;
	}
	int j=0;
	string get_flight_num;
	string temp_the_fnum;
	cout << endl << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl << endl;
	do
	{
		cout << "Enter the flight number you want to delete: ";
		getline(cin, get_flight_num);
		if(get_flight_num == "r" || get_flight_num == "R") { system("cls"); return 9;	}
		if(get_flight_num == "0") { exit (0); 	}
		
		ifstream check_the_fnum("Local Travel\\Transactions\\fnumber.txt");
		while(getline(check_the_fnum, temp_the_fnum))
		{
			if(temp_the_fnum == get_flight_num)
			{
				j = 1;
			}
		}
		if(j == 0)
		{
			cout << "Invalid Input! Please enter the correct number!" << endl;
		}
	} while (j==0);
	
	
	
	ifstream check_dep2("Local Travel\\Transactions\\departure.txt");
	ifstream check_arr2("Local Travel\\Transactions\\arrival.txt");
	ifstream check_seats2("Local Travel\\Transactions\\seats.txt");
	ifstream check_fnumber2("Local Travel\\Transactions\\fnumber.txt");
	ifstream check_day2("Local Travel\\Transactions\\day.txt");
	ifstream check_month2("Local Travel\\Transactions\\month.txt");
	ifstream check_year2("Local Travel\\Transactions\\year.txt");
	ifstream check_day22("Local Travel\\Transactions\\day1.txt");
	ifstream check_month22("Local Travel\\Transactions\\month1.txt");
	ifstream check_year22("Local Travel\\Transactions\\year1.txt");
	ifstream check_dtime2("Local Travel\\Transactions\\deptime.txt");
	ifstream check_atime2("Local Travel\\Transactions\\arrtime.txt");
	
	ofstream temp1("Local Travel\\Transactions\\temp1.txt", ios::out | ios::app);
	ofstream temp2("Local Travel\\Transactions\\temp2.txt", ios::out | ios::app);
	ofstream temp3("Local Travel\\Transactions\\temp3.txt", ios::out | ios::app);
	ofstream temp4("Local Travel\\Transactions\\temp4.txt", ios::out | ios::app);
	ofstream temp5("Local Travel\\Transactions\\temp5.txt", ios::out | ios::app);
	ofstream temp6("Local Travel\\Transactions\\temp6.txt", ios::out | ios::app);
	ofstream temp7("Local Travel\\Transactions\\temp7.txt", ios::out | ios::app);
	ofstream temp8("Local Travel\\Transactions\\temp8.txt", ios::out | ios::app);
	ofstream temp9("Local Travel\\Transactions\\temp9.txt", ios::out | ios::app);
	ofstream temp10("Local Travel\\Transactions\\temp10.txt", ios::out | ios::app);
	ofstream temp11("Local Travel\\Transactions\\temp11.txt", ios::out | ios::app);
	ofstream temp12("Local Travel\\Transactions\\temp12.txt", ios::out | ios::app);
	
	string temp_dep2, temp_arr2, tfnumber2;
	int temp_seat2;
	int tmonth22, tyear22, tday22, dtime2, arrtime2;
	while(getline(check_dep2, temp_dep2) && getline(check_arr2, temp_arr2) && check_seats2 >> temp_seat2
		&& check_day2 >> tday2 && check_month2 >> tmonth2 && check_year2 >> tyear2 && getline(check_fnumber2, tfnumber2)
		&& check_day22 >> tday22 && check_month22 >> tmonth22 && check_year22 >> tyear22 && check_dtime2 >> dtime2
		&& check_atime2 >> arrtime2)
	{
		if(get_flight_num != tfnumber2)
		{
			temp1 << temp_dep2 << endl;
			temp2 << temp_arr2 << endl;
			temp3 << temp_seat2 << endl;
			temp4 << tday2 << endl;
			temp5 << tmonth2 << endl;
			temp6 << tyear2 << endl;
			temp7 << tfnumber2 << endl;
			temp8 << tday22 << endl;
			temp9 << tmonth22 << endl;
			temp10 << tyear22 << endl;
			temp11 << dtime2 << endl;
			temp12 << arrtime2 << endl;
		}
	}
	
	check_dep2.close(); check_arr2.close(); check_seats2.close(); check_fnumber2.close();
	check_day2.close(); check_month2.close(); check_year2.close();
	check_day22.close(); check_month22.close(); check_year22.close();
	check_dtime2.close(); check_atime2.close();
	
	temp1.close(); temp2.close(); temp3.close(); temp4.close();
	temp5.close(); temp6.close(); temp7.close(); temp8.close();
	temp9.close(); temp10.close(); temp11.close(); temp12.close();
	
	remove("Local Travel\\Transactions\\departure.txt");
	remove("Local Travel\\Transactions\\arrival.txt");
	remove("Local Travel\\Transactions\\seats.txt");
	remove("Local Travel\\Transactions\\day.txt");
	remove("Local Travel\\Transactions\\month.txt");
	remove("Local Travel\\Transactions\\year.txt");
	remove("Local Travel\\Transactions\\fnumber.txt");
	
	remove("Local Travel\\Transactions\\day1.txt");
	remove("Local Travel\\Transactions\\month1.txt");
	remove("Local Travel\\Transactions\\year1.txt");
	remove("Local Travel\\Transactions\\deptime.txt");
	remove("Local Travel\\Transactions\\arrtime.txt");
	
	rename("Local Travel\\Transactions\\temp1.txt", "Local Travel\\Transactions\\departure.txt");
	rename("Local Travel\\Transactions\\temp2.txt", "Local Travel\\Transactions\\arrival.txt");
	rename("Local Travel\\Transactions\\temp3.txt", "Local Travel\\Transactions\\seats.txt");
	rename("Local Travel\\Transactions\\temp4.txt", "Local Travel\\Transactions\\day.txt");
	rename("Local Travel\\Transactions\\temp5.txt", "Local Travel\\Transactions\\month.txt");
	rename("Local Travel\\Transactions\\temp6.txt", "Local Travel\\Transactions\\year.txt");
	rename("Local Travel\\Transactions\\temp7.txt", "Local Travel\\Transactions\\fnumber.txt");
	
	rename("Local Travel\\Transactions\\temp8.txt", "Local Travel\\Transactions\\day1.txt");
	rename("Local Travel\\Transactions\\temp9.txt", "Local Travel\\Transactions\\month1.txt");
	rename("Local Travel\\Transactions\\temp10.txt", "Local Travel\\Transactions\\year1.txt");
	rename("Local Travel\\Transactions\\temp11.txt", "Local Travel\\Transactions\\deptime.txt");
	rename("Local Travel\\Transactions\\temp12.txt", "Local Travel\\Transactions\\arrtime.txt");
	
	char choice2;
	cout << endl << "Data has been deleted!" << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	cout << "Choice: ";
	cin >> choice2;
	do
	{
		if(choice2 != 'R' && choice2 != 'r' && choice2 != '0')
		{
			cout << "Invalid Input! Please try again!" << endl;
		}
		if(choice2 == 'R' || choice2 == 'r') { system("cls"); return 9; }
		if(choice2 == '0') { exit (0); }
	} while(choice2 != 'R' && choice2 != 'r' && choice2 != '0');
}

int delete_flights()
{
	char choice;
	int temp1, temp2;
	delete_flights_menu:
	list_of_airports();
	cout << endl << endl;
	cout << "[1] Delete Airport" << endl;
	cout << "[2] Delete Local Flights" << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	do
	{
		cout << "Choice: ";
		cin >> choice;
		if(choice != '1' && choice != '2' && choice != 'R' && choice != 'r' && choice != '0')
		{
			cout << "Invalid Input! Please try again!" << endl;
		}
	} while(choice != '1' && choice != '2' && choice != 'R' && choice != 'r' && choice != '0');
	
	if (choice == '1')
	{
		temp1 = delete_airport();
		if (temp1 == 9) { goto delete_flights_menu;	}
	}
	
	if (choice == '2')
	{
		temp2 = delete_local_flights();
		if (temp2 == 9) { goto delete_flights_menu;	}
	}
	
	if (choice == 'R' || choice == 'r') { return 9; }
	if (choice == '0') { exit (0); }
}



///////////////////////////////////////////TOUR PACAKGES///////////////////////////////////////////////////////

void tour_packages_menu()
{
	header();
	cout <<"\t     TOUR PACKAGES" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "|\t[1] List of Tour Packages\t|" << endl; 
	cout << "|\t[2] Create Tour Packages\t|" << endl; 
	cout << "|\t[3] Delete Tour Packages\t|" << endl; 
	cout << "|\t[4] Transaction\t\t\t|" << endl; 
	cout << "|\t[5] List of Cities in Japan\t|" << endl;
	cout << "|\t[6] Create Cities in Japan\t|" << endl;
	cout << "|\t[7] Delete Cities in Japan\t|" << endl; 
	cout << "|\t[R] Return\t\t\t|" << endl;
	cout << "|\t[0] Exit\t\t\t|" << endl;
	cout << "-----------------------------------------" << endl << endl;
}

void list_of_cities()
{
	string t_number, t_city;
	cout << "======================================================" << endl;
	cout << "             LIST OF CITIES IN JAPAN" << endl;
	cout << "======================================================" << endl;
	ifstream f_number("Tour Packages\\number.txt");
	ifstream f_city("Tour Packages\\city.txt");
	while(getline(f_number, t_number) && getline(f_city, t_city))
	{
		cout << "[" << t_number << "] " << t_city << endl;
	}
	f_number.close(); f_city.close();
}


int check_entered(string a)
{
	int i = 0;
	if(a[i] == ' ')
	{
		return 9;
	}
	if(a == "\0")
	{
		return 9;
	}
}

int check_entered_num(string x)
{
	for(int i=0; i<x.size(); i++)
	{
		if(x[i] != '1' && x[i] != '2' && x[i] != '3' && x[i] != '4' && x[i] != '5' && x[i] != '6' && x[i]!= '7' && x[i] != '8' && x[i] != '9' && x[i] != '0')
		{
			return 9;
		}
		else
		{
			return 0;
		}
	}
}

int check_limit_day(int a)
{
	if(a < 0 || a > 31)
	{
		return 9;
	}
	else
	{
		return 0;
	}
}

int check_limit_price(int a)
{
	if (a < 5000)
	{
		return 9;
	}
	if (a >= 5000)
	{
		return 0;
	}
}

int check_limit_seats(int a)
{
	if (a < 1 || a > 60)
	{
		return 9;
	}
	else
	{
		return 0;
	}
}



int show_cities()
{
	string choice2;
	list_of_cities();
	cout << endl << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	do
	{
		cout << "Choice: ";
		getline(cin, choice2);
		if(choice2 == "R" || choice2 == "r") { system("cls"); return 9;	}
		if(choice2 == "0") { exit(0);		}
		if(choice2 != "R" || choice2 != "r" || choice2 != "0") { cout << "Invalid Input!" << endl;	}
	} while(choice2 != "R" || choice2 != "r" || choice2 != "0");
	
}

int create_city()
{
	string choice2;
	int temp_number, latest_number = 0;
	list_of_cities();
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	cout << endl << endl;
	
	cout << "Adding City" << endl << endl;
	cout << "Enter City: ";
	getline(cin, choice2);
	if(choice2 == "R" || choice2 == "r") { system("cls"); return 9;	}
	if(choice2 == "0") { exit(0);		}
	
	ifstream count_number("Tour Packages\\number.txt");
	while(count_number >> temp_number)
	{
		latest_number = temp_number;
	}
	count_number.close();
	
	
	ofstream f_number("Tour Packages\\number.txt", ios::out | ios::app);
	ofstream f_city("Tour Packages\\city.txt", ios::out | ios::app);
	f_number << latest_number + 1 << endl;
	f_city << choice2 << endl;
	f_number.close(); f_city.close();
	
	string choice;
	cout << endl << endl;
	cout << "City has been added!" << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	do
	{
		cout << "Choice: ";
		getline(cin, choice);
		if(choice == "R" || choice == "r") { system("cls"); return 9;	}
		if(choice == "0") { exit(0);		}
		if(choice != "R" || choice != "r" || choice != "0") { cout << "Invalid Input!" << endl;	}
	} while(choice != "R" || choice != "r" || choice != "0");
}

int delete_city()
{
	string del_city;
	int x = 1;
	list_of_cities();
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	cout << endl << endl;
	
	cout << "Deleting City" << endl << endl;
	do
	{
		cout << "Enter City: ";
		getline(cin, del_city);
		if(del_city == "R" || del_city == "r") { system("cls"); return 9;	}
		if(del_city == "0") { exit(0);		}
		string temp_number;
		ifstream check_number("Tour Packages\\number.txt");
		while(getline(check_number, temp_number))
		{
			if(temp_number == del_city)	{	x = 1;	}
		}
		check_number.close();
	} while (x == 0);
		string num, cit;
		ofstream temp1("Tour Packages\\temp1.txt", ios::out | ios::app);
		ofstream temp2("Tour Packages\\temp2.txt", ios::out | ios::app);
		ifstream check_city1("Tour Packages\\city.txt");
		ifstream check_number1("Tour Packages\\number.txt");
		
		while(getline(check_city1, cit) && getline(check_number1, num))
		{
			if(del_city != num)
			{
				temp1 << cit << endl;
				temp2 << num << endl;
			}
		}
		temp1.close(); temp2.close(); check_number1.close(); check_city1.close();
		
		remove("Tour Packages\\city.txt");
		remove("Tour Packages\\number.txt");
		
		rename("Tour Packages\\temp1.txt", "Tour Packages\\city.txt");
		rename("Tour Packages\\temp2.txt", "Tour Packages\\number.txt");
		
		string choice;
		cout << endl;
		cout << "City has been deleted!" << endl;
		cout << "[R] Return" << endl;
		cout << "[0] Exit" << endl;
		do
		{
			cout << "Choice: ";
			getline(cin, choice);
			if(choice == "R" || choice == "r") { system("cls"); return 9;	}
			if(choice == "0") { exit(0);		}
			if(choice != "R" || choice != "r" || choice != "0") { cout << "Invalid Input!" << endl;	}
		} while(choice != "R" || choice != "r" || choice != "0");
}

int create_tour_packages()
{
	string get_city, get_scenery, get_hotel, get_days, get_price, get_seats;
	string show_city;
	int x = 0, init_day, init_price, init_seats, temp_scen, temp_hotel, temp_days, temp_days2, temp_price, temp_price2, temp_seats, temp_seats2;
	list_of_cities();
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	cout << endl << endl;
	cout << "=========================================" << endl;
	cout << "        Creating Tour Pacakges" << endl;
	cout << "=========================================" << endl << endl;
	cout << "Enter the Information " << endl;
	do
	{
		cout << "Enter City: ";
		getline(cin, get_city);
		if(get_city == "R" || get_city == "r") { system("cls"); return 9;	};
		if(get_city == "0") { exit(0); }
		
		string t_number, t_city;
		ifstream f_number("Tour Packages\\number.txt");
		ifstream f_city("Tour Packages\\city.txt");
		while(getline(f_number, t_number) && getline(f_city, t_city))
		{
			if(get_city == t_number) { show_city = t_city; x = 1;	}
		}
		f_number.close(); f_city.close();
		if(x == 0) { cout << "Invali Input! Please try again" << endl;	}
	} while (x == 0);
	
	cout << "Entered City: " << show_city << endl;
	do
	{
		cout << "Scenery: ";
		getline(cin, get_scenery);
		if(get_scenery == "R" || get_scenery == "r") { system("cls"); return 9;	}
		if(get_scenery == "0") { exit(0); }
		temp_scen = check_entered(get_scenery);
		if(temp_scen == 9) { cout << "Invalid Input!" << endl;	}
	} while (temp_scen == 9);
	
	do
	{		
		cout << "Hotel: ";
		getline(cin, get_hotel);
		if(get_hotel == "R" || get_hotel == "r") { system("cls"); return 9;	}
		if(get_hotel == "0") { exit(0); }
		temp_hotel = check_entered(get_hotel);
		if(temp_hotel == 9) { cout << "Invalid Input!" << endl;	}
	} while (temp_hotel == 9);
	
	do
	{
		cout << "Days: ";
		getline(cin, get_days);
		if(get_days == "R" || get_days == "r") { system("cls"); return 9;	}
		if(get_days == "0") { exit(0); }
		temp_days = check_entered_num(get_days);
		if(temp_days == 9) { cout << "Invalid Input!" << endl;	}
		istringstream(get_days) >> init_day;
		temp_days2 = check_limit_day(init_day);
		if(temp_days2 == 9) { cout << "Invalid Input!" << endl;	}
	} while(temp_days == 9 || temp_days2 == 9);
	
	do
	{
		cout << "Available Seats: ";
		getline(cin, get_seats);
		if(get_seats == "R" || get_seats == "r") { system("cls"); return 9;	}
		if(get_seats == "0") { exit(0); }
		temp_seats = check_entered_num(get_seats);
		if(temp_seats == 9) { cout << "Invalid Input!" << endl;	}
		istringstream(get_seats) >> init_seats;
		temp_seats2 = check_limit_seats(init_seats);
		if(temp_seats2 == 9) { cout << "Invalid Input!" << endl;	}
	} while(temp_seats == 9 || temp_seats2 == 9);
	
	//Date
	
	int temp1, temp2, temp3, temp4, month, day, year, day_loop, hm_passengers, z = 0;	//VARIABLE
	
	do
	{
		do
		{
			do
			{
				do
				{	
					char t_month[20], t_day[20], t_year[20];	//VARIABLE
					cout << "Tour Package Date: " << endl;
					cout << "(e.g   5  18  2019)" << endl; 
					cout << "Month: ";
					cin.getline(t_month, 20);
					temp1 = check_numbers(t_month);
					cout << "Day: ";
					cin.getline(t_day, 20);
					temp2 = check_numbers(t_day);
					cout << "Year: ";
					cin.getline(t_year, 20);
					temp3 = check_numbers(t_year);
						if (temp1 == 1 || temp2 == 1 || temp3 == 1)
						{
							cout << "Invalid Input! Please enter the correct date!" << endl;
						}
						else
						{	
							istringstream(t_month) >> month;	
							istringstream(t_day) >> day;
							istringstream(t_year) >> year;
						}
				} while (temp1 == 1 || temp2 == 1 || temp3 == 1);		
				
				if(year < real_year || year > 2050)
				{
					cout << "Year not accepted. Please enter the correct Year!" << endl;
				}
				
			} while(year < real_year || year > 2050);
				
				if(year == real_year && month < real_month)
				{
					cout << "Month not accepted. Please enter the correct Month!" << endl;
					z=0;
				}
				else if(year == real_year && month == real_month && day < real_day)
				{
					cout << "Day not accepted. Please enter the correct Day!" << endl;
					z=0;
				}
				else
				{
					z = 1;
				}
		}  while(z == 0);
				if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				{
					if(day < 1 || day > 31)
					{
						cout << "Day not accepted. Please enter the correct Day!" << endl;
						day_loop = 1;
					} else {  day_loop = 0; 	}
				}
				if (month == 4 || month == 6 || month == 9 || month == 11)
				{
					if(day < 1 || day > 30)
					{
						cout << "Day not accepted. Please enter the correct Day!" << endl;
						day_loop = 1;
					} else {  day_loop = 0; 	}
				}
				if(month == 2)
				{
					if((year % 4) == 0)
					{
						if(day < 1 || day > 29)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop = 1;
						} else {  day_loop = 0; 	}
					}
					else
					{
						if(day < 1 || day > 28)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop = 1;
						} else {  day_loop = 0; 	}
					}
				}
			} while (day_loop == 1);
			
			cout << "Tour package Date: " << month_name[month-1] << " " << day << " " << year << endl;
	
	do
	{
		cout << "Price(Yen): ";
		getline(cin, get_price);
		if(get_price == "R" || get_price == "r") { system("cls"); return 9;	}
		if(get_price == "0") { exit(0); }
		temp_price = check_entered_num(get_price);
		if(temp_price == 9) { cout << "Invalid Input!" << endl;	}
		istringstream(get_price) >> init_price;
		temp_price2 = check_limit_price(init_price);
		if(temp_price2 == 9) { cout << "Invalid Input!" << endl;	}
	} while(temp_price == 9 || temp_price2 == 9);
	
	int latest_num = 0, show_num;
	ifstream count_number("Tour Packages\\Create\\number.txt");
	while(count_number >> show_num)
	{
		latest_num = show_num;
	}
	
	ofstream input_available("Tour Packages\\Create\\available.txt", ios::out | ios::app);
	ofstream input_city("Tour Packages\\Create\\city.txt", ios::out | ios::app);
	ofstream input_days("Tour Packages\\Create\\days.txt", ios::out | ios::app);
	ofstream input_hotel("Tour Packages\\Create\\hotel.txt", ios::out | ios::app);
	ofstream input_number("Tour Packages\\Create\\number.txt", ios::out | ios::app);
	ofstream input_price("Tour Packages\\Create\\price.txt", ios::out | ios::app);
	ofstream input_scenery("Tour Packages\\Create\\scenery.txt", ios::out | ios::app);
	
	ofstream input_day("Tour Packages\\Create\\day.txt", ios::out | ios::app);
	ofstream input_month("Tour Packages\\Create\\month.txt", ios::out | ios::app);
	ofstream input_year("Tour Packages\\Create\\year.txt", ios::out | ios::app);
	
	input_available << init_seats << endl;
	input_city << show_city << endl;
	input_days << init_day << endl;
	input_hotel << get_hotel << endl;
	input_number << latest_num + 1 << endl;
	input_price << init_price << endl;
	input_scenery << get_scenery << endl;
	input_day << day << endl;
	input_month << month << endl;
	input_year << year << endl;
	
	input_available.close(); input_city.close(); input_days.close(); 
	input_hotel.close(); input_number.close(); input_price.close(); input_scenery.close();
	input_day.close(); input_month.close(); input_year.close(); 
	
	string choice;
	cout << endl << endl;
	cout << "Tour Package has been added!" << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	do
	{
		cout << "Choice: ";
		getline(cin, choice);
		if(choice == "R" || choice == "r") { system("cls"); return 9;	}
		if(choice == "0") { exit(0);		}
		if(choice != "R" || choice != "r" || choice != "0") { cout << "Invalid Input!" << endl;	}
	} while(choice != "R" || choice != "r" || choice != "0");
	
}

void list_of_packages()
{
	cout << "=========================================" << endl;
	cout << "        LIST OF Tour Pacakges" << endl;
	cout << "=========================================" << endl << endl << endl;
	
	string t_city, t_hotel, t_scenery;
	int t_available, t_price, t_number, t_days;
	int t_day, t_month, t_year;
	
	ifstream f_available("Tour Packages\\Create\\available.txt");
	ifstream f_city("Tour Packages\\Create\\city.txt");
	ifstream f_days("Tour Packages\\Create\\days.txt");
	ifstream f_hotel("Tour Packages\\Create\\hotel.txt");
	ifstream f_number("Tour Packages\\Create\\number.txt");
	ifstream f_price("Tour Packages\\Create\\price.txt");
	ifstream f_scenery("Tour Packages\\Create\\scenery.txt");
	ifstream f_day("Tour Packages\\Create\\day.txt");
	ifstream f_month("Tour Packages\\Create\\month.txt");
	ifstream f_year("Tour Packages\\Create\\year.txt");
	
	while(getline(f_city, t_city) && getline(f_hotel, t_hotel) && getline(f_scenery, t_scenery) 
		  && f_available >> t_available && f_price >> t_price && f_days >> t_days && f_number >> t_number
		   && f_day >> t_day && f_month >> t_month && f_year >> t_year )
	{
		cout << "TOUR PACKAGE [" << t_number <<"]" << endl;
		cout << "City: " << t_city << endl;
		cout << "Scenery: " << t_scenery << endl;
		cout << "Hotel: " << t_hotel << endl;
		cout << "Days: " << t_days << endl;
		cout << "Available Seats: " << t_available << endl;
		cout << "Date: " << month_name[t_month-1] << " " << t_day << " " << t_year << endl;
		cout << "Price: " << t_price << endl << endl << endl;
	}
	f_available.close(); f_city.close(); f_days.close(); 
	f_hotel.close(); f_number.close(); f_price.close(); f_scenery.close();
	f_day.close(); f_month.close(); f_year.close(); 
}

int list_of_tour_packages()
{
	list_of_packages();
	string choice2;
	cout << endl << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	do
	{
		cout << "Enter your Choice: ";
		getline(cin, choice2);
		if(choice2[0] == 'R' || choice2 == "r") { system("cls"); return 9;	}
		if(choice2 == "0") { exit(0);		}
		if(choice2 != "R" || choice2 != "r" || choice2 != "0") { cout << "Invalid Input!" << endl;	}
	} while(choice2 != "R" || choice2 != "r" || choice2 != "0");
	
}

int delete_tour_packages()
{
	string del_tp;
	string temp_number;
	int x = 0;
	int count = 0;
	list_of_packages();
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	cout << endl << endl;
	
	cout << "Deleting Tour Packages" << endl << endl;
	do
	{
		cout << "Enter Number of Tour Package: ";
		getline(cin, del_tp);
		if(del_tp == "R" || del_tp == "r") { system("cls"); return 9;	}
		if(del_tp == "0") { exit(0);	}
		
		ifstream check_number("Tour Packages\\Create\\number.txt");
		while(getline(check_number, temp_number))
		{
			if(temp_number == del_tp)	{	x = 1;	}
			count ++;
		}
		check_number.close();
		if(x == 0) { cout << "Invalid Input!" << endl;	}
		if(count == 0) { cout << "No Data Existed" << endl; x = 0;	}
 	} while (x == 0);
 	
		string t_city, t_number, t_hotel, t_scenery;
		int t_available, t_price, t_days;
		int t_day, t_month, t_year;
		
		ofstream temp1("Tour Packages\\Create\\temp1.txt", ios::out | ios::app);
		ofstream temp2("Tour Packages\\Create\\temp2.txt", ios::out | ios::app);
		ofstream temp3("Tour Packages\\Create\\temp3.txt", ios::out | ios::app);
		ofstream temp4("Tour Packages\\Create\\temp4.txt", ios::out | ios::app);
		ofstream temp5("Tour Packages\\Create\\temp5.txt", ios::out | ios::app);
		ofstream temp6("Tour Packages\\Create\\temp6.txt", ios::out | ios::app);
		ofstream temp7("Tour Packages\\Create\\temp7.txt", ios::out | ios::app);
		ofstream temp8("Tour Packages\\Create\\temp8.txt", ios::out | ios::app);
		ofstream temp9("Tour Packages\\Create\\temp9.txt", ios::out | ios::app);
		ofstream temp10("Tour Packages\\Create\\temp10.txt", ios::out | ios::app);
		
		ifstream f_available("Tour Packages\\Create\\available.txt");
		ifstream f_city("Tour Packages\\Create\\city.txt");
		ifstream f_days("Tour Packages\\Create\\days.txt");
		ifstream f_hotel("Tour Packages\\Create\\hotel.txt");
		ifstream f_number("Tour Packages\\Create\\number.txt");
		ifstream f_price("Tour Packages\\Create\\price.txt");
		ifstream f_scenery("Tour Packages\\Create\\scenery.txt");
		ifstream f_day("Tour Packages\\Create\\day.txt");
		ifstream f_month("Tour Packages\\Create\\month.txt");
		ifstream f_year("Tour Packages\\Create\\year.txt");
		
		while(getline(f_city, t_city) && getline(f_hotel, t_hotel) && getline(f_scenery, t_scenery) 
			  && f_available >> t_available && f_price >> t_price && f_days >> t_days && f_number >> t_number
			   && f_day >> t_day && f_month >> t_month && f_year >> t_year )
		{
			if(del_tp != t_number)
			{
				temp1 << t_available << endl;
				temp2 << t_city << endl;
				temp3 << t_days << endl;
				temp4 << t_hotel << endl;
				temp5 << t_number << endl;
				temp6 << t_price << endl;
				temp7 << t_scenery << endl;
				temp8 << t_day << endl;
				temp9 << t_month << endl;
				temp10 << t_year << endl;
			}
		}
		temp1.close(); temp2.close(); temp3.close(); temp4.close();  temp5.close(); temp6.close(); temp7.close(); 
		temp8.close(); temp9.close(); temp10.close(); 
		
		f_available.close(); f_city.close(); f_days.close(); 
		f_hotel.close(); f_number.close(); f_price.close(); f_scenery.close();
		f_day.close(); f_month.close(); f_year.close(); 
		
		remove("Tour Packages\\Create\\available.txt");
		remove("Tour Packages\\Create\\city.txt");
		remove("Tour Packages\\Create\\days.txt");
		remove("Tour Packages\\Create\\hotel.txt");
		remove("Tour Packages\\Create\\number.txt");
		remove("Tour Packages\\Create\\price.txt");
		remove("Tour Packages\\Create\\scenery.txt");
		remove("Tour Packages\\Create\\day.txt");
		remove("Tour Packages\\Create\\month.txt");
		remove("Tour Packages\\Create\\year.txt");
		
		rename("Tour Packages\\Create\\temp1.txt", "Tour Packages\\Create\\available.txt");
		rename("Tour Packages\\Create\\temp2.txt", "Tour Packages\\Create\\city.txt");
		rename("Tour Packages\\Create\\temp3.txt", "Tour Packages\\Create\\days.txt");
		rename("Tour Packages\\Create\\temp4.txt", "Tour Packages\\Create\\hotel.txt");
		rename("Tour Packages\\Create\\temp5.txt", "Tour Packages\\Create\\number.txt");
		rename("Tour Packages\\Create\\temp6.txt", "Tour Packages\\Create\\price.txt");
		rename("Tour Packages\\Create\\temp7.txt", "Tour Packages\\Create\\scenery.txt");
		rename("Tour Packages\\Create\\temp8.txt", "Tour Packages\\Create\\day.txt");
		rename("Tour Packages\\Create\\temp9.txt", "Tour Packages\\Create\\month.txt");
		rename("Tour Packages\\Create\\temp10.txt", "Tour Packages\\Create\\year.txt");
		
		string choice;
		cout << endl;
		cout << "Tour Package has been deleted!" << endl;
		cout << "[R] Return" << endl;
		cout << "[0] Exit" << endl;
		do
		{
			cout << "Choice: ";
			getline(cin, choice);
			if(choice == "R" || choice == "r") { system("cls"); return 9;	}
			if(choice == "0") { exit(0);		}
			if(choice != "R" || choice != "r" || choice != "0") { cout << "Invalid Input!" << endl;	}
		} while(choice != "R" || choice != "r" || choice != "0");
}

void tour_pack_transaction_menu()
{
	cout << "Transaction" << endl;
	cout << "[1] Book a Tour Package" << endl;
	cout << "[2] View Transaction" << endl;
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	cout << "Choice: ";
}


float function_price_tour (string departure_name , string arrival_name, int month, int day, int year, float get_price)
{
	float anumber, dnumber;
	float temp_multiplier;
	string t_depname, t_arrname;
	float fixed_price = get_price;
	float travel_tax = 0.32;
	float env_fee = 536;
	float temp_total, temp_total2;
	float senior_discount;
	float id;
	
	ifstream f_number("Tour Packages\\number.txt");
	ifstream f_city("Tour Packages\\city.txt");
	
	//Travel Tax = 32%
	//Insurance = 5% to 12% upon selection
	//Environmental fee = 5 USD
	//Discounts - Senior Citizen - 12%
	
	//Senior Citizen Discount
	
	//june 2 1959   june 22 2019
	if(year <= real_year)
	{
			if((real_year - year) == 60)
			{
				if(month < real_month)
				{
					senior_discount = .12;
				}
				else if(month == real_month)
				{
					if(day <= real_day)
					{
						senior_discount = .12;
					}
					else
					{
						senior_discount = 0;
					}
				}
				else
				{
					senior_discount = 0;
				}
			}
			else if((real_year - year) > 60)
			{
				senior_discount = .12;
			}
			else
			{
				senior_discount = 0;
			}
	}
	else
	{
		senior_discount = 0;
	}
	
	while(f_number >> id && getline(f_city, t_depname))
	{
		if(departure_name == t_depname)
		{
			dnumber = id;
		}
	}
	
	while(f_number >> id && getline(f_city, t_arrname))
	{
		if(arrival_name == t_arrname)
		{
			anumber = id;
		}
	}
	f_number.close(); f_city.close();
	
	if(dnumber > anumber)
	{
		temp_multiplier = dnumber - anumber;
	}
	if(anumber > dnumber)
	{
		temp_multiplier = anumber - dnumber;	
	}
	float t_insurance;
	if(temp_multiplier == 1) {	t_insurance = .05;	}
	if(temp_multiplier == 2) {	t_insurance = .06;	}
	if(temp_multiplier == 3) {	t_insurance = .07;	}
	if(temp_multiplier == 4) {	t_insurance = .08;	}
	if(temp_multiplier == 5) {	t_insurance = .09;	}
	if(temp_multiplier == 6) {	t_insurance = .10;	}
	if(temp_multiplier == 7) {	t_insurance = .11;	}
	if(temp_multiplier >= 8) {	t_insurance = .12;	}
	
	float temp_env, temp_travel_tax, temp_insurance;
	temp_total = fixed_price * temp_multiplier;
	temp_travel_tax = temp_total * travel_tax; //.32   //8585
	temp_insurance = temp_total * t_insurance;
	
	float tax_env_total;
	tax_env_total = temp_total + env_fee + temp_travel_tax + temp_insurance; //kulang pa insurance dito, 536
	float overall_total;
	overall_total = tax_env_total - (tax_env_total * senior_discount); //.12 or 1
				printf("--------------------------------------------------------------\n");
				printf("| %-18s | %-37f |\n", "Price: ", temp_total);
				printf("| %-18s | %-37f |\n", "Travel Tax: ", temp_travel_tax);
				printf("| %-18s | %-37f |\n", "Insurance: ", temp_insurance);
                printf("--------------------------------------------------------------\n");
				printf("| %-18s | %-37f |\n", "Total Tax: ", tax_env_total);
				printf("| %-18s | %-37f |\n", "Senior Discount: ", senior_discount);
				printf("| %-18s | %-37f |\n", "Total Price: ", overall_total);
                printf("--------------------------------------------------------------\n");
	return overall_total;
}

int tour_package_booking()
{
	try_again:
	string get_number, get_number2, temp_number, temp_number2, temp_city, latest_city, temp_city2, latest_city2;
	int x, x2, count, count2, t_available, latest_available, latest_price, t_price;
	int temp_num, latest_id;
	ifstream get_num("Tour Packages\\Transaction\\id.txt");
	while(get_num >> temp_num)
	{
		latest_id = temp_num;
	}
	get_num.close();
	list_of_packages();	
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	cout << endl << endl;
	do
	{
		cout << "Enter Number of the Tour Package you want: ";
		getline(cin, get_number);
		if(get_number == "R" || get_number == "r") { system("cls"); return 9;	}
		if(get_number == "0") { exit(0);	}
		
		ifstream check_number("Tour Packages\\Create\\number.txt");
		ifstream check_city("Tour Packages\\Create\\city.txt");
		ifstream check_available("Tour Packages\\Create\\available.txt");
		ifstream check_price("Tour Packages\\Create\\price.txt");
		while(getline(check_number, temp_number) && getline(check_city, temp_city) && check_available >> t_available && check_price >> t_price)
		{
			if(temp_number == get_number)	{	latest_city = temp_city;  latest_available = t_available; latest_price = t_price;	x = 1;	}
			count ++;
		}
		check_number.close(); check_city.close(); check_available.close(); check_price.close();
		if(x == 0) { cout << "Invalid Input!" << endl;	}
		if(count == 0) { cout << "No Data Existed" << endl; x = 0;	}
 	} while (x == 0);
 	
 	cout << "Selected: Tour Package No." << get_number << endl;
 	
 	
	list_of_cities();
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	cout << endl << endl;
	do
	{
		cout << "Departure: ";
		getline(cin, get_number2);
		if(get_number2 == "R" || get_number2 == "r") { system("cls"); return 9;	}
		if(get_number2 == "0") { exit(0);	}
		
		ifstream check_number2("Tour Packages\\number.txt");
		ifstream check_city2("Tour Packages\\city.txt");
		while(getline(check_number2, temp_number2) && getline(check_city2, temp_city2))
		{
			if(temp_number2 == get_number2)	{	latest_city2 = temp_city2;  x2 = 1;	}
			count2 ++;
		}
		check_number2.close(); 	check_city2.close();
		if(x2 == 0) { cout << "Invalid Input!" << endl;	}
		if(count2 == 0) { cout << "No Data Existed" << endl; x2 = 0;	}
		if(latest_city2 == latest_city) { cout << "Invalid Input! You are already in that city. Please try again!"	<< endl; x2 = 0;	}
 	} while (x2 == 0);
 	system("cls");
 	cout << endl << endl;
 	cout << "PASSENGER TRANSACTION SLIP" << endl << endl;
 	cout << "Selected: Tour Package No." << get_number << endl;
 	cout << "Route: " << latest_city2 << " to "  << latest_city << " to " << latest_city2 << endl << endl;
 	cout << "Available Seats: " << latest_available << endl << endl;
 	
 	int z = 0;
 	ifstream update_tour_pack_num("Tour Packages\\Create\\number.txt");
 	ifstream update_tour_pack_seat("Tour Packages\\Create\\available.txt");
 	ifstream update_tour_pack_city("Tour Packages\\Create\\city.txt");
 	ifstream update_tour_pack_day("Tour Packages\\Create\\day.txt");
 	ifstream update_tour_pack_days("Tour Packages\\Create\\days.txt");
 	ifstream update_tour_pack_month("Tour Packages\\Create\\month.txt");
 	ifstream update_tour_pack_year("Tour Packages\\Create\\year.txt");
 	ifstream update_tour_pack_price("Tour Packages\\Create\\price.txt");
 	ifstream update_tour_pack_scenery("Tour Packages\\Create\\scenery.txt");
 	ifstream update_tour_pack_hotel("Tour Packages\\Create\\hotel.txt");
 	int re_seats;
 	string re_city, re_day, re_days, re_month, re_year, re_price, re_scenery, re_hotel, add_num, re_num;
 	int  add_seats;
 	string add_city, add_day, add_days, add_month, add_year, add_hotel, add_scenery, add_price;
 	while(getline(update_tour_pack_num, re_num) && update_tour_pack_seat >> re_seats && getline(update_tour_pack_city, re_city)
	     && getline(update_tour_pack_day, re_day) && getline(update_tour_pack_days, re_days) && getline(update_tour_pack_month, re_month)
		 && getline(update_tour_pack_year, re_year) && getline(update_tour_pack_price, re_price) && getline(update_tour_pack_scenery, re_scenery)
		 && getline(update_tour_pack_hotel, re_hotel))
 	{
 		if(get_number == re_num)
 		{
 			add_num = re_num;
 			add_seats = re_seats;
 			add_city = re_city;
 			add_day = re_day;
 			add_days = re_days;
 			add_month = re_month;
 			add_year = re_year;
 			add_price = re_price;
 			add_scenery= re_scenery;
 			add_hotel = re_hotel;
 			z = 1;	
		}
	}
 	update_tour_pack_num.close(); update_tour_pack_seat.close(); update_tour_pack_city.close(); update_tour_pack_day.close();
 	update_tour_pack_days.close(); update_tour_pack_month.close(); update_tour_pack_year.close(); update_tour_pack_price.close();
 	update_tour_pack_scenery.close(); update_tour_pack_hotel.close(); 
 	int temp4, hm_passengers;
 	do
	{
		do
		{
			char t_hm_passengers[10];
			cout << "How many passengers: ";
			cin.getline(t_hm_passengers, 10);
			temp4 = check_numbers(t_hm_passengers);
			if(temp4 == 1)	{	cout << "Invalid input! Please enter the correct number!" << endl; }
			else	{	istringstream(t_hm_passengers) >> hm_passengers;	}
			
		} while(temp4 == 1 );
			if(hm_passengers < 1 || hm_passengers > 10)	{	cout << "Only 1 - 10 passengers can be book at a time." << endl;	temp4 = 1;	}	
			if((latest_available - hm_passengers) < 0)	{	cout << "Seats are not Available! Try again" << endl;	system("pause"); system("cls"); goto try_again;	}	
			else	{	temp4 = 0;	}
			
	} while(temp4 == 1);
			
			// VARIABLE
			char fullname[60], gender;
			char t_month1[20], t_day1[20], t_year1[20];
			float overall_price = 0.0;
			
			for(int i=0; i<hm_passengers; i++)
			{
				cout << endl << "Passenger [" << i+1 << "]" << endl;
				cout << "Fullname: ";
				cin.getline(fullname, 60);
				do
				{	
					cout << "Gender[M/F]: ";
					cin >> gender;
					if(toupper(gender) != 'M' && toupper(gender) != 'F')
					{
						cout << "Invalid Input! Please enter correctly" << endl;
					}
				} while (toupper(gender) != 'M' && toupper(gender) != 'F');
				
				int temp1_2, temp2_2, temp3_2, month2, day2, year2, day_loop2, y=0;
				cin.ignore();
				do
				{
					do
					{
						do
						{
							do
							{	
								char t_month2[20], t_day2[20], t_year2[20];
								cout << "Birthdate: " << endl;
								cout << "(e.g   5  18  2019)" << endl; 
								cout << "Month: ";
								cin.getline(t_month2, 20);
								temp1_2 = check_numbers(t_month2);
								cout << "Day: ";
								cin.getline(t_day2, 20);
								temp2_2 = check_numbers(t_day2);
								cout << "Year: ";
								cin.getline(t_year2, 20);
								temp3_2 = check_numbers(t_year2);
								if (temp1_2 == 1 || temp2_2 == 1 || temp3_2 == 1)
								{
									cout << "Invalid Input! Please enter the correct date!" << endl;
								}
								else
								{	
									istringstream(t_month2) >> month2;	
									istringstream(t_day2) >> day2;
									istringstream(t_year2) >> year2;
								}
							} while (temp1_2 == 1 || temp2_2 == 1 || temp3_2 == 1);
						
							if(year2 < 1900 || year2 >= 2019)
							{
								cout << "Year not accepted. Please enter the correct Year!" << endl;
							}
						} while(year2 < 1900 || year2 >= 2019);
						if(month2 < 1 || month2 > 12)
						{
							cout << "Month not accepted. Please enter the correct month!" << endl;
						}
					} while (month2 < 1 || month2 > 12);
					if (month2 == 1 || month2 == 3 || month2 == 5 || month2 == 7 || month2 == 8 || month2 == 10 || month2 == 12)
					{
						if(day2 < 1 || day2 > 31)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop2 = 1;
						} else {  day_loop2 = 0; 	}
					}
					if (month2 == 4 || month2 == 6 || month2 == 9 || month2 == 11)
					{
						if(day2 < 1 || day2 > 30)
						{
							cout << "Day not accepted. Please enter the correct Day!" << endl;
							day_loop2 = 1;
						} else {  day_loop2 = 0; 	}
					}
					if(month2 == 2)
					{
						if((year2 % 4) == 0)
						{
							if(day2 < 1 || day2 > 29)
							{
								cout << "Day not accepted. Please enter the correct Day!" << endl;
								day_loop2 = 1;
							} else {  day_loop2 = 0; 	}
						}
						else
						{
							if(day2 < 1 || day2 > 28)
							{
								cout << "Day not accepted. Please enter the correct Day!" << endl;
								day_loop2 = 1;
							} else {  day_loop2 = 0; 	}
						}
					} 
				} while (day_loop2 == 1);
				cout << "Birthday: " << month_name[month2-1] << " " << day2 << " " << year2 << endl;
				float total_price;
				total_price = function_price_tour(latest_city, latest_city2, month2, day2, year2, latest_price);
				overall_price += total_price;
				
				ofstream input_id("Tour Packages\\Transaction\\id.txt" , ios::out | ios::app);
				ofstream input_departure("Tour Packages\\Transaction\\departure.txt" , ios::out | ios::app);
				ofstream input_arrival("Tour Packages\\Transaction\\arrival.txt" , ios::out | ios::app);
				ofstream input_tour_id("Tour Packages\\Transaction\\tour_id.txt" , ios::out | ios::app);
				ofstream input_fullname("Tour Packages\\Transaction\\fullname.txt" , ios::out | ios::app);
				ofstream input_gender("Tour Packages\\Transaction\\gender.txt" , ios::out | ios::app);
				ofstream input_birthday("Tour Packages\\Transaction\\birthday.txt" , ios::out | ios::app);
				ofstream input_total_price("Tour Packages\\Transaction\\total_price.txt" , ios::out | ios::app);
				
				input_id << latest_id + 1 << endl;
 				input_fullname << fullname << endl;
 				input_gender << gender <<  endl;
 				input_birthday << month_name[month2-1] << " " << day2 << " " << year2 << endl;
 				input_total_price << total_price << endl;
 				input_tour_id << get_number << endl;
 				input_departure << latest_city2 << endl;
 				input_arrival << latest_city << endl;
 			
 			input_id.close(); input_departure.close();
 			input_arrival.close(); input_tour_id.close();
 			input_fullname.close(); input_gender.close();
 			input_birthday.close(); input_total_price.close();
 				
		}
		
		if (z == 1)
				{
					int tdtime, tatime;
					ifstream check_seats("Tour Packages\\Create\\available.txt");
					ifstream check_city("Tour Packages\\Create\\city.txt");
					ifstream check_day("Tour Packages\\Create\\day.txt");
					ifstream check_days("Tour Packages\\Create\\days.txt");
					ifstream check_hotel("Tour Packages\\Create\\hotel.txt");
					ifstream check_month("Tour Packages\\Create\\month.txt");
					ifstream check_number("Tour Packages\\Create\\number.txt");
					ifstream check_price("Tour Packages\\Create\\price.txt");
					ifstream check_scenery("Tour Packages\\Create\\scenery.txt");
					ifstream check_year("Tour Packages\\Create\\year.txt"); 	
					
					ofstream temp1("Tour Packages\\Create\\temp1.txt" , ios::out | ios::app);
					ofstream temp2("Tour Packages\\Create\\temp2.txt" , ios::out | ios::app);
					ofstream temp3("Tour Packages\\Create\\temp3.txt" , ios::out | ios::app);
					ofstream temp4("Tour Packages\\Create\\temp4.txt" , ios::out | ios::app);
					ofstream temp5("Tour Packages\\Create\\temp5.txt" , ios::out | ios::app);
					ofstream temp6("Tour Packages\\Create\\temp6.txt" , ios::out | ios::app);
					ofstream temp7("Tour Packages\\Create\\temp7.txt" , ios::out | ios::app);
					ofstream temp8("Tour Packages\\Create\\temp8.txt" , ios::out | ios::app);
					ofstream temp9("Tour Packages\\Create\\temp9.txt" , ios::out | ios::app);
					ofstream temp10("Tour Packages\\Create\\temp10.txt" , ios::out | ios::app);
					
					int tday1, tmonth1, tyear1;
					int p_seats, p_day, p_days, p_price, p_year, p_month;
					string p_hotel, p_scenery, p_city, p_number;
					while(check_seats >> p_seats && getline(check_city, p_city) && check_day >> p_day && check_days >> p_days
							&& getline(check_hotel, p_hotel) && check_month >> p_month && getline(check_number, p_number)
							&& check_price >> p_price && getline(check_scenery, p_scenery) && check_year >> p_year)
					{
						if(!(get_number == p_number))
						{	
							
							temp1 << p_seats << endl;
							temp2 << p_city << endl;
							temp3 << p_day << endl;
							temp4 << p_days << endl;
							temp5 << p_hotel << endl;
							temp6 << p_month << endl;
							temp7 << p_number << endl;	
							temp8 << p_price << endl;
							temp9 << p_scenery << endl;	
							temp10 << p_year << endl;	
						}
					}
							temp1 << add_seats - hm_passengers << endl;
							temp2 << add_city << endl;
							temp3 << add_day << endl;
							temp4 << add_days << endl;
							temp5 << add_hotel << endl;
							temp6 << add_month << endl;
							temp7 << add_num << endl;
							temp8 << add_price << endl;
							temp9 << add_scenery << endl;
							temp10 << add_year << endl;	
							
						
						temp1.close(); temp2.close(); temp3.close(); temp4.close(); temp10.close(); 
						temp5.close(); temp6.close(); temp7.close(); temp8.close(); temp9.close(); 
						
						check_seats.close(); check_city.close(); check_day.close(); check_days.close(); check_hotel.close();
						check_month.close(); check_number.close(); check_price.close(); check_scenery.close(); check_year.close();
						
						remove("Tour Packages\\Create\\available.txt");
						rename("Tour Packages\\Create\\temp1.txt", "Tour Packages\\Create\\available.txt");
						
						remove("Tour Packages\\Create\\city.txt");
						rename("Tour Packages\\Create\\temp2.txt", "Tour Packages\\Create\\city.txt");
						
						remove("Tour Packages\\Create\\day.txt");
						rename("Tour Packages\\Create\\temp3.txt", "Tour Packages\\Create\\day.txt");
						
						remove("Tour Packages\\Create\\days.txt");
						rename("Tour Packages\\Create\\temp4.txt", "Tour Packages\\Create\\days.txt");
						
						remove("Tour Packages\\Create\\hotel.txt");
						rename("Tour Packages\\Create\\temp5.txt", "Tour Packages\\Create\\hotel.txt");
						
						remove("Tour Packages\\Create\\month.txt");
						rename("Tour Packages\\Create\\temp6.txt", "Tour Packages\\Create\\month.txt");
						
						remove("Tour Packages\\Create\\number.txt");
						rename("Tour Packages\\Create\\temp7.txt", "Tour Packages\\Create\\number.txt");
						
						remove("Tour Packages\\Create\\price.txt");
						rename("Tour Packages\\Create\\temp8.txt", "Tour Packages\\Create\\price.txt");
						
						remove("Tour Packages\\Create\\scenery.txt");
						rename("Tour Packages\\Create\\temp9.txt", "Tour Packages\\Create\\scenery.txt");
						
						remove("Tour Packages\\Create\\year.txt");
						rename("Tour Packages\\Create\\temp10.txt", "Tour Packages\\Create\\year.txt");
				}
		
			char t_payment[20];
			float payment, change, temp_pay;
			cout << "Total Price: " << overall_price << " Yen" << endl << endl;
			do
			{
				do
				{
					cout << "Please enter your payment: ";
					cin.getline(t_payment, 20);
					temp_pay = check_numbers(t_payment);
					if(temp_pay == 1)
					{
						cout << "Please enter numbers only!" << endl;
					}
					else
					{
						istringstream(t_payment) >> payment;
					}
				} while (temp_pay == 1);
				if(payment < overall_price)
				{
					cout << "Insufficient Payment, Please pay the exact amount!" << endl;
				}
			} while (payment < overall_price);
			
			cout << "Change: " << payment - overall_price << endl << endl;
			
			cout << "Booking Flight Successful!" << endl;
			
			cout << endl << endl;
			char choice_temp;
			cout << "[R] Return" << endl;
			cout << "[0] Exit" << endl;
			cout << "Choice: ";
			cin >> choice_temp;
			if(choice_temp == 'R' || choice_temp == 'r') { system("cls"); return 9;	}
			if(choice_temp == '0') { exit (0);		}
}

int view_transaction_tour()
{
	cout << "TRANSACTIONS " << endl;
	string t_arrival, t_birthday, t_departure, t_fullname, t_gender;
	string t_id, t_total_price, t_tour_id;
	ifstream f_arrival("Tour Packages\\Transaction\\arrival.txt");
	ifstream f_birthday("Tour Packages\\Transaction\\birthday.txt");
	ifstream f_departure("Tour Packages\\Transaction\\departure.txt");
	ifstream f_fullname("Tour Packages\\Transaction\\fullname.txt");
	ifstream f_gender("Tour Packages\\Transaction\\gender.txt");
	ifstream f_id("Tour Packages\\Transaction\\id.txt");
	ifstream f_total_price("Tour Packages\\Transaction\\total_price.txt");
	ifstream f_tour_id("Tour Packages\\Transaction\\tour_id.txt");
	cout << "----------------------------------------------------------------" << endl;
	while(getline(f_arrival, t_arrival) && 	getline(f_birthday, t_birthday) && 	getline(f_departure, t_departure) && getline(f_fullname, t_fullname) 
	      && getline(f_gender, t_gender)  && getline(f_id, t_id) && getline(f_total_price, t_total_price) && getline(f_tour_id, t_tour_id))
	{
		cout << "Name: " << t_fullname << endl; 
		cout << "Gender: " << t_gender << endl;
		cout << "Birthday " << t_birthday << endl;
		cout << "Tour Package: " <<t_tour_id << endl;
		cout << "Route: " << t_departure << " to " << t_arrival << endl;
		cout << "----------------------------------------------------------------" << endl;
	}
	f_arrival.close(); f_birthday.close(); f_departure.close(); f_fullname.close();
	f_gender.close(); f_id.close(); f_total_price.close(); f_tour_id.close();
	
	cout << "[R] Return" << endl;
	cout << "[0] Exit" << endl;
	string menu_choice;
	do
	{	
		cout << "Enter your choice: ";
		getline(cin, menu_choice);
		
		if ((menu_choice[0] != 'R' && menu_choice[0] != 'r' && menu_choice[0] != '0') ||  menu_choice[0] == ' ' || menu_choice[1] ) 
		{ 
			cout << "Invalid Input! Try again!" << endl; 
		}
	} while ((menu_choice[0] != 'R' && menu_choice[0] != 'r' && menu_choice[0] != '0') || menu_choice[0] == ' ' || menu_choice[1]);
	if(menu_choice[0] == 'R' || menu_choice[0] == 'r')
	{
		system("cls");
		return 9;
	}
	if(menu_choice[0] == '0')
	{
		exit(0);
	}
	
 }


int transaction_tour_packages()
{
	transact_loop:
	string transact_choice;
	int temp2;
	tour_pack_transaction_menu();
	getline(cin, transact_choice);
	
	while(transact_choice != "1" && transact_choice != "2" && transact_choice != "R" && transact_choice != "r" && transact_choice != "0")
	{
		cout << "Invalid Input" << endl;
		cout << "Choice: ";
		cin >> transact_choice;
	}
	if(transact_choice == "1") {	system("cls"); temp2 = tour_package_booking();	if(temp2 == 9) goto transact_loop;	} 	
	if(transact_choice == "2") {    system("cls"); temp2 = view_transaction_tour();	if(temp2 == 9) goto transact_loop;	} 	
	if(transact_choice == "R") {	system("cls");  return 9;	} 	
	if(transact_choice == "r") {	system("cls");  return 9;	} 	
	if(transact_choice == "0") {	exit(0);	} 	
		
}



int main()
{
	int x = 0;
	menu:
	string menu_choice;
    system("title Mai Otome Travel Agency");
	menu();
	// ETONG PUTANIGNNA PERPEKTONG VALIDATION 
	do
	{	
		cout << "Enter your choice: ";
		getline(cin, menu_choice);
		
		if ((menu_choice[0] != '1' && menu_choice[0] != '2' && menu_choice[0] != '0') ||  menu_choice[0] == ' ' || menu_choice[1] ) 
		{ 
			cout << "Invalid Input! Try again!" << endl; 
		}
	} while ((menu_choice[0] != '1' && menu_choice[0] != '2' && menu_choice[0] != '0') || menu_choice[0] == ' ' || menu_choice[1]);
	
	switch(menu_choice[0])
	{
		case '1':
			{
			int temp3;
			string tour_packages_menu_choice;
			tour_packages:
			system("cls");
			tour_packages_menu();
			do
			{	
				cout << "Enter your choice: ";
				getline(cin, tour_packages_menu_choice);
				
				if ((tour_packages_menu_choice[0] != '1' && tour_packages_menu_choice[0] != '2' && tour_packages_menu_choice[0] != '3'
					&& tour_packages_menu_choice[0] != '4' && tour_packages_menu_choice[0] != '5' && tour_packages_menu_choice[0] != '6'
					&& tour_packages_menu_choice[0] != '7' && tour_packages_menu_choice[0] != '0' && tour_packages_menu_choice[0] != 'R'
					&& tour_packages_menu_choice[0] != 'r')
					|| tour_packages_menu_choice[0] == ' ' || tour_packages_menu_choice[1] ) 
				{ 
					cout << "Invalid Input! Try again!" << endl; 
				}
			} while ((tour_packages_menu_choice[0] != '1' && tour_packages_menu_choice[0] != '2' && tour_packages_menu_choice[0] != '3'
					&& tour_packages_menu_choice[0] != '4' && tour_packages_menu_choice[0] != '5' && tour_packages_menu_choice[0] != '6'
					&& tour_packages_menu_choice[0] != '7' && tour_packages_menu_choice[0] != '0' && tour_packages_menu_choice[0] != 'R'
					&& tour_packages_menu_choice[0] != 'r')
					|| tour_packages_menu_choice[0] == ' ' || tour_packages_menu_choice[1] );
			
			switch(tour_packages_menu_choice[0])
			{
				case '1':	system("cls");	temp3 = list_of_tour_packages(); if(temp3 == 9) { goto tour_packages; }   break; 
				case '2':	system("cls");	temp3 = create_tour_packages(); if(temp3 == 9) { goto tour_packages; }   break; 
				case '3':	system("cls");	temp3 = delete_tour_packages(); if(temp3 == 9) { goto tour_packages; }   break;
				case '4':	system("cls");	temp3 = transaction_tour_packages(); if(temp3 == 9) { goto tour_packages; } break;
				case '5':	system("cls");  temp3 = show_cities(); if(temp3 == 9) { goto tour_packages; }	break;
				case '6':	system("cls");	temp3 = create_city(); if(temp3 == 9) { goto tour_packages; }	break; 
				case '7':	system("cls");	temp3 = delete_city(); if(temp3 == 9) { goto tour_packages; }	break; 
				case 'R':	system("cls");	goto menu;	break;
				case 'r':	system("cls");	goto menu;	break;
				case '0':	exit(0);	break;
			}
		}
		break;
		
		case '2':
			char local_travel_menu_choice;
			int temp;
			list_of_local_travel_return:
			system("cls");
			local_travel_menu();
			cin >> local_travel_menu_choice;
			while(local_travel_menu_choice != '1' && local_travel_menu_choice != '2' && local_travel_menu_choice != '3' && local_travel_menu_choice != '4' && local_travel_menu_choice != '0' && local_travel_menu_choice != 'R' && local_travel_menu_choice != 'r')
			{
				cout << "Invalid Input" << endl;
				cout << "Choice: ";
				cin >> local_travel_menu_choice;
			}
			switch(local_travel_menu_choice)
			{
				case '1':	system("cls");	temp = view_local_flight();	if(temp == 9) {	 goto list_of_local_travel_return; } break;
				case '2':	system("cls");	temp = add_local_flights();	if(temp == 9) {	goto list_of_local_travel_return; } break;
				case '3':	system("cls");	temp = delete_flights(); if(temp == 9) { goto list_of_local_travel_return; } break;
				case '4':	
					char transact_choice;
					int temp2;
					transact_loop:
					system("cls");	
					transaction_menu();
					cin >> transact_choice;
					while(transact_choice != '1' && transact_choice != '2' && transact_choice != 'R' && transact_choice != 'r' && transact_choice != '0')
					{
						cout << "Invalid Input" << endl;
						cout << "Choice: ";
						cin >> transact_choice;
					}
					switch(transact_choice)
					{
						case '1':	temp2 = local_travel_booking();	if(temp2 == 9) goto transact_loop;	break;
						case '2':	temp2 = view_local_transaction();	if(temp2 == 9) goto transact_loop;	break;
						case 'R':	goto list_of_local_travel_return;	break;
						case 'r':	goto list_of_local_travel_return;	break;
						case '0':	exit(0);	break;
					}
				break;
				case 'R':	system("cls"); cin.ignore();	goto menu;	break;
				case 'r':	system("cls"); cin.ignore();	goto menu;	break;
				case '0':	exit(0);	break;
			}
		break;
		
		case '0': exit(0); break;
	}
}




