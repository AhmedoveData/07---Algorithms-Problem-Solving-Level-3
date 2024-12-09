#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

/*

This project introduces the requirements and implementation of basic 
banking operations. It guides students to design a small banking system, 
focusing on foundational algorithms and file handling techniques, 
including input validation and modular programming.

*/

const string clientsFilename = "newClientsData.txt";

void showMAinMenue();

enum enMenueOptions { eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eExit = 6 };
struct stClient
{
    string accountNumber;
    string pinCode;
    string Name;
    string phoneNumber;
    double accountBalance = 0.0;
    bool markToDelete = false;
};
vector<string> SplitString(string St1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;

    while ((pos = St1.find(Delim)) != std::string::npos)
    {
        sWord = St1.substr(0, pos);
        if (sWord != " ")
        {
            vString.push_back(sWord);
        }
        St1.erase(0, pos + Delim.length());

    }

    if (sWord != "")
    {
        vString.push_back(St1);
    }

    return vString;
}
stClient ConvertClientDataToRecord(string Line, string Seperator = "||")
{
    stClient Client;

    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.accountNumber = vClientData[0];
    Client.pinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.phoneNumber = vClientData[3];
    Client.accountBalance = stod(vClientData[4]);

    return Client;

}
string convertClientDataToLine(stClient Client, string Seperator = "||")
{
    string stClientRecord;

    stClientRecord += Client.accountNumber + Seperator;
    stClientRecord += Client.pinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.phoneNumber + Seperator;
    stClientRecord += to_string(Client.accountBalance);

    return stClientRecord;


}
vector<stClient> loadClientDataFromFile(string fileName)
{
    vector<stClient> vClient;

    fstream MyFile;

    MyFile.open(fileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;

        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertClientDataToRecord(Line);

            vClient.push_back(Client);
        }
        MyFile.close();
    }

    return vClient;
}
bool findClientByAccountNumber(string acoountNumber, vector<stClient> vClient, stClient& client)
{


    for (stClient c : vClient)
    {
        if (c.accountNumber == acoountNumber)
        {
            client = c;
            return true;
        }

    }
    return false;
}
bool markClientToDeleteByAccountNumber(string accoutNumber, vector<stClient>& vClient)
{
    for (stClient& c : vClient)
    {
        if (c.accountNumber == accoutNumber)
        {
            c.markToDelete = true;
            return true;
        }
    }
    return false;
}
vector<stClient> saveClientsDataToFile(string fileName, vector<stClient> vClient)
{
    fstream MyFile;

    MyFile.open(fileName, ios::out);

    string dataLine;

    if (MyFile.is_open())
    {
        for (stClient c : vClient)
        {
            if (c.markToDelete == false)
            {
                dataLine = convertClientDataToLine(c);
                MyFile << dataLine << endl;
            }
        }
        MyFile.close();
    }

    return vClient;

}
void printClientCard(stClient client)
{
    cout << "------------------------------------------------------\n";
    cout << "\n\t\t[Client Card]\n";
    cout << "------------------------------------------------------\n";
    cout << "\n\t\tAccount Number: " << client.accountNumber;
    cout << "\n\t\tPin Code: " << client.pinCode;
    cout << "\n\t\tName: " << client.Name;
    cout << "\n\t\tPhone Number: " << client.phoneNumber;
    cout << "\n\t\tAccount Balance: " << client.accountBalance;
    cout << "\n------------------------------------------------------\n";
}
bool deleteCientByAccountNumber(string accountNumber, vector<stClient>& vClient)
{
    stClient client;

    char answer = 'n';

    if (findClientByAccountNumber(accountNumber, vClient, client))
    {
        printClientCard(client);

        cout << "\n\n\tDo want to delete this record? Y/N";
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            markClientToDeleteByAccountNumber(accountNumber, vClient);
            saveClientsDataToFile(clientsFilename, vClient);
            vClient = loadClientDataFromFile(clientsFilename);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }


    }


    else
    {
        cout << "\nClient with Account Number (" << accountNumber
            << ") is Not Found!";
        return false;
    }


}
stClient changeClientRecord(string accountNumber)
{
    stClient client;

    client.accountNumber = accountNumber;

    cout << "Pin Code:";
    getline(cin >> ws, client.pinCode);
    cout << "Name:";
    getline(cin, client.Name);
    cout << "Phone Number: ";
    getline(cin, client.phoneNumber);
    cout << "Account Balance:";
    cin >> client.accountBalance;

    return client;


}
bool updateCientByAccountNumber(string accountNumber, vector<stClient>& vClient)
{
    stClient client;

    char answer = 'n';

    if (findClientByAccountNumber(accountNumber, vClient, client))
    {
        printClientCard(client);

        cout << "\n\nDo want to update this record? Y/N";
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {

            for (stClient& c : vClient)
            {
                if (c.accountNumber == accountNumber)
                {
                    c = changeClientRecord(accountNumber);
                    break;
                }
            }

            saveClientsDataToFile(clientsFilename, vClient);

            cout << "\n\nClient updated Successfully.";
            return true;
        }


    }


    else
    {
        cout << "\nClient with Account Number (" << accountNumber
            << ") is Not Found!";
        return false;
    }


}
void printClientRecordLine(stClient Client)
{
    cout << "| " << setw(20) << left << Client.accountNumber;
    cout << "| " << setw(10) << left << Client.pinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.phoneNumber;
    cout << "| " << setw(12) << left << Client.accountBalance;
}
string readClientAcountNumber()
{
    string accountNumber = "";
    cout << "\nPlese enter the account number: ";
    cin >> accountNumber;
    return accountNumber;
}
void addDataToFile(string fileName, string dataLine)
{
    fstream MyFile;

    MyFile.open(fileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << dataLine << endl;

        MyFile.close();
    }
}
bool clientExitsByAccountNumber(string accountNumber, string fileName)
{
    vector<stClient> vClient;
    fstream MyFile;

    MyFile.open(fileName, ios::in);

    if (MyFile.is_open())
    {
        string line;
        stClient client;

        while (getline(MyFile, line))
        {
            client = ConvertClientDataToRecord(line);
            if (client.accountNumber == accountNumber)
            {
                MyFile.close();
                return true;
            }
            vClient.push_back(client);
        }

        MyFile.close();
    }

    return false;
}
stClient readNewClient()
{
    stClient client;

    cout << "\tEnter your account number please: ";
    getline(cin >> ws, client.accountNumber);

    while (clientExitsByAccountNumber(client.accountNumber, clientsFilename))
    {
        cout << "\nClient with account number: [" << client.accountNumber << "] is already exit, try anpther one.";
        getline(cin >> ws, client.accountNumber);
    }

    cout << "\tPin Code: ";
    getline(cin, client.pinCode);

    cout << "\tEntr your name plaese: ";
    getline(cin, client.Name);

    cout << "\tPhone number: ";
    getline(cin, client.phoneNumber);

    cout << "\tAccount balance: ";
    cin >> client.accountBalance;

    return client;

}
void addNewClient()
{
    stClient Client;

    Client = readNewClient();

    addDataToFile(clientsFilename, convertClientDataToLine(Client));

}
void addNewClients()
{
    char addMore = 'Y';

    do
    {
        //system("cls");
        //cout << "\t\tAdding new client: \n\n";
        addNewClient();
        cout << "Client added successfully, would you add more? Y/N";
        cin >> addMore;


    } while (toupper(addMore) == 'Y');
}



void showAllClients()
{
    vector<stClient> vClient = loadClientDataFromFile(clientsFilename);
    cout << "\n\t\t\t\t\t Client List [" << vClient.size() << "] client(s)";
    cout << "\n***********************************************************************************************************\n";

    cout << "| " << setw(20) << left << "Account Number";
    cout << "| " << setw(10) << left << "Pin Code";
    cout << "| " << setw(40) << left << "Name";
    cout << "| " << setw(12) << left << "Phone Number";
    cout << "| " << setw(12) << left << "Account Balance";

    cout << "\n***********************************************************************************************************\n";
    cout << "\n***********************************************************************************************************\n";

    if (vClient.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (stClient Client : vClient)
        {
            printClientRecordLine(Client);
            cout << endl;
        }


    cout << "\n************************************************************************************************************\n";
    cout << "\n***********************************************************************************************************\n";
}
void ShowDeleteCientScreen()
{
    cout << "\t===============================\n";
    cout << "\t\t Delete Client\n";
    cout << "\t===============================\n";

    vector<stClient> vClient = loadClientDataFromFile(clientsFilename);
    string accountNumber = readClientAcountNumber();
    deleteCientByAccountNumber(accountNumber, vClient);

}
void showUpdateClientScreen()
{
    cout << "\t===============================\n";
    cout << "\t\t Update Client\n";
    cout << "\t===============================\n";
    vector<stClient> vClient = loadClientDataFromFile(clientsFilename);
    string accountNumber = readClientAcountNumber();
    updateCientByAccountNumber(accountNumber, vClient);

}
void showaddNewClientscreen()
{
    cout << "\t===============================\n";
    cout << "\t\t Add New Client\n";
    cout << "\t===============================\n";
    addNewClients();

}
void showFindClientScreen()
{
    cout << "\t===============================\n";
    cout << "\t\t Find Client\n";
    cout << "\t===============================\n";

    vector<stClient> vClient = loadClientDataFromFile(clientsFilename);
    string accountNumber = readClientAcountNumber();

    stClient client;

    if (findClientByAccountNumber(accountNumber, vClient, client))
        printClientCard(client);
    else
        cout << "Client with account number [" << accountNumber << "] is not found!";


}
void ShowTheEndScreen()
{
    cout << "\t===============================\n";
    cout << "\t\t Thank You!\n";
    cout << "\t===============================\n";
}
void goBackToMainScreen()
{
    cout << "\n\nPress any key to back to the main menue.";
    system("pause>0");
    showMAinMenue();
}
short readMainmenueOption()
{
    short option = 0;
    cout << "which option would you like to chose...[1 to 6]: ";
    cin >> option;
    return option;
}



void performMainMenue(enMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMenueOptions::eShowClientList:
    {
        system("cls");
        showAllClients();
        goBackToMainScreen();
        break;
    }
    case enMenueOptions::eAddNewClient:
        system("cls");
        showaddNewClientscreen();
        goBackToMainScreen();
        break;

    case enMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteCientScreen();
        goBackToMainScreen();
        break;

    case enMenueOptions::eUpdateClient:
        system("cls");
        showUpdateClientScreen();
        goBackToMainScreen();
        break;

    case enMenueOptions::eFindClient:
        system("cls");
        showFindClientScreen();
        goBackToMainScreen();
        break;

    case enMenueOptions::eExit:
        system("cls");
        ShowTheEndScreen();
        break;
    }
}
void showMAinMenue()
{
    system("cls");
    cout << "=======================================================\n";
    cout << "\t\t The main screen\n";
    cout << "=======================================================\n";
    cout << "\t[1] Show the client list.\n";
    cout << "\t[2] Add new client.\n";
    cout << "\t[3] Delete client.\n";
    cout << "\t[4] Update client.\n";
    cout << "\t[5] Find client.\n";
    cout << "\t[6] Exit.\n";
    cout << "=======================================================\n";

    performMainMenue((enMenueOptions)readMainmenueOption());

}







int main()
{
    showMAinMenue();
    system("pause>0");
    return 0;
}


