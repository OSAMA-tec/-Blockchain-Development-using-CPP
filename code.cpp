#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

class DATA {
public:
  int ammount;
  string sender;
  string receiver;
  double id;
  string hash;
  DATA *next;

  DATA() // default constructor
  {
    ammount = 0;
    sender = "";
    receiver = "";

    id = 0; 
    next = NULL;
  }

  DATA(int n, string s, string r) // constructor
  {
    ammount = n;
    sender = s;
    receiver = r;

    id = rand() % 100; // Unique id for each block
    next = NULL;
  }
};

class Blockchain : public DATA {
private:
  DATA *listptr, *temp;//aggregation and composition
  // ptr is used to point at the current data and temp is used for temporary data
  // usages such as iterations , ammount storage for a small time.
public:
  Blockchain() //
  {
    listptr = NULL;
    temp = NULL;
    // initializing the values to NULL , to avoid segmentation error
  }
  void Create(int, string, string);
  int Isempty();
  void Display();
  void HashDisplay();
  int len();
  void Insert();
  void Search();
  void ProofofWork();
  void Mining();
  void Correctblock( Blockchain);
} blockchain1, blockchain2;

void Blockchain::Create(int num, string sender, string receiver) {        //create function 

  DATA *newdata = new DATA(num, sender, receiver);//contructor of data class(values assign by create function arguments)
  if (listptr == NULL)         //    its means if  list is empty
    listptr = temp = newdata;
  else {
    temp->next = newdata;      // temp currently points towards current block
    temp = temp->next;         //
  }
}

int Blockchain::Isempty() {     //empty check function
  if (listptr == NULL)          //if list empty then return 0
    return 0;
  else
    return 1;
}

void Blockchain::Display() {
  DATA *current_position = listptr;   /*    listptr points towards first data*/
  if (Isempty() == 0) {          //its means isempty function returning zero
    cout << "List is empty";
  } else {
    cout << "\n";
    while (current_position != NULL) // iterate till it reaches last block
    {
      cout << "\n |\t" << current_position->ammount << "$ Sent to "
           << current_position->receiver << " by " << current_position->sender
           << " Transaction ID " << current_position->id;
      current_position = current_position->next; /*    move temp to the next data */
    }
    cout << "\n";
  }
}

void Blockchain::HashDisplay() {
  DATA *current_position = listptr; /*    listptr points to first data*/
  if (Isempty() == 0) {                //if list empty then show list is empty
    cout << "List is empty";
  } else {//otherwise display all these data

    cout << "\n";
    while (current_position != NULL) // iterate till it reaches last block
    {
      std::hash<string> shashVal;//struct template string
      string final =current_position->sender +current_position->receiver; // hash value of Sender and receiver
      std::hash<int> ihashVal;//struct template int
      int fin = current_position->id; // hash value of id
      cout << "\n |\t" << current_position->ammount << " Hash value of transaction "<< shashVal(final) + ihashVal(fin);//these all done by STL
      current_position = current_position->next; /*    move temp to the next data */
    }
    cout << "\n";
  }
}

void Blockchain::Insert() {
  DATA *current_position = listptr;
  while (current_position->next != NULL)//dont stop when current position not become null
    current_position = current_position->next;//pointing next data

  int num;
  string sender, receiver;
  cout << "\n Enter the ammount : \n ";
  cin >> num;
  cout << "\n Sender Digital signature : \n ";
  cin >> sender;
  cout << "\n Receiver Digital signature : \n  ";
  cin >> receiver;

  DATA *newdata = new DATA(num, sender, receiver);//passing value to the function
  cout << "\n |\t" << newdata->ammount << " Sent to " << receiver << " by "
       << sender << " ,Transaction ID " << id;

  newdata->next = NULL;//giving next data position to null
  current_position->next = newdata;
}

int Blockchain::len() {
  int count = 0;
  DATA *current_position = listptr; /*    temp points to first data*/
  if (Isempty() == 0) {
    cout << "List is empty";
  } else {
    while (current_position != NULL) {
      count += 1;
      current_position = current_position->next; /*    move temp to the next data */
    }
  }
  return count;
}
void Blockchain::Search() {
  int val;
  cout << "\n Enter  ID  to search  in List \n";
  cin >> val;
  int find = 0;
  int count = 0;
  DATA *current_position = listptr;
  while (current_position->next != NULL) {
    if (current_position->id == val) {
      find = 1;
      break;
    }
    count += 1;
    current_position = current_position->next;//pointing next data block
  }
  if (find == 1)
    cout << "\n Transaction is  present at " << count;
  else
    cout << "\n Transaction not present";
}

void Blockchain::ProofofWork() {

  // Assuming that there are two Blockchains , one starts with 1 while another
  // one starts with zero assuming

  DATA *current_position = listptr; /*    temp points to first data*/
  if (Isempty() == 0) {
    cout << "List is empty";
  } else {
    cout << "\n";
    while (current_position != NULL) {
      std::hash<string> shashVal;//using STL 
      string final = current_position->sender + current_position->receiver;
      if (final[0] == 1) {
        cout << "Block A";
      } else if (final[1] == 0) {
        cout << "Block B";
      } else
        cout << "Block no pattern";
      break;
    }
  }
}
void Blockchain::Mining() {
 
  DATA *current_position = listptr;
  string senderMin;
  cout << "\n Enter  Sender name  to check  \n";
  cin >> senderMin;
  int find = 0;
  int count = 0;
  while (current_position->next != NULL) {
    if (current_position->sender == senderMin) {
      if (current_position->ammount < 100) {
        count += 1;
        cout << "Not enough credit , required credit: \t"
             << current_position->ammount - 100;
      }
      break;
    }
    current_position = current_position->next;
  }
  if (count == 0) // If transactions is valid the
  {
    DATA *newdata = new DATA(current_position->ammount, current_position->sender,current_position->receiver);
  }

  Correctblock( blockchain2);
}

void Blockchain::Correctblock( Blockchain l2) {
  int x, y;
  x = this->len();
  y = l2.len();
  if (x > y) {//to check this is correct or not
    cout << "Blockchain A is longer hence , block will be added into ";
    this->Display();
  } else {
    cout << "Blockchain B is longer hence , block will be added into ";
    l2.Display();
  }
}
int main() {
  Blockchain blockchain;
  int k = 0;
  // string fsender = "OSAMA", freceiver = "ALISHBA";
  int num;
  string sender, receiver;
  cout << "\t\x1b[1mWelcome to Blockchain implementation by OSAMA HASHMI\x1b[0m \n";
  // blockchain.Create(num = 100, fsender, freceiver);
  do {
    int ch;
    cout << "Press 1.Add Blocks in block chain  \n\nPress 2.Display the blocks "
            "without hash function  \n\nPress 3.Display the HASH Blocks   \n\nPress 4.Length "
            "of Block chain   \n\nPress 5.Search Transaction  \n\nPress 6.Proof of Work \n\nPress "
            "7.Mining \n\nPress 8.Insert in the HASH Blocks   \n\nPress 9.Block is correct or not   \n\n";

    cin >> ch;

    switch (ch) {
    case 1:
      cout << "\n Enter the ammount  \n";
              
      cin >> num;
      cout << "\n Sender Digital signature \n";
              
      cin >> sender;
      cout << "\n Receiver Digital signature \n  ";
      cin >> receiver;
      blockchain.Create(num, sender, receiver);
      break;
    case 2:
      blockchain.Display();
      break;
    case 8:
      blockchain.Insert();
      break;
    case 9:
      blockchain.Correctblock(blockchain);
      break;
    case 3:
      blockchain.HashDisplay();
      break;
    case 4:
      cout << "Length of Link List is" << blockchain.len();
      break;
    case 5:
      blockchain.Search();
      break;
    case 6:
      blockchain.ProofofWork();
      break;
    case 7:
      blockchain.Mining();
      break;
    default:
      break;
    }
    cout << "\n To continue press 0 \n";
    cin >> k;

  } while (k == 0);
  return 0;
}